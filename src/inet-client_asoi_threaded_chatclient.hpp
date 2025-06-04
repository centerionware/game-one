
chat_client::chat_client(boost::asio::io_service& io_service,tcp::resolver::iterator endpoint_iterator) 
	: io_service_(io_service), socket_(io_service), read_msg_(NULL)
{
	isConnected = false;
	tcp::endpoint endpoint = *endpoint_iterator;
	socket_.async_connect(
		endpoint, boost::bind( &chat_client::handle_connect, this, boost::asio::placeholders::error,++endpoint_iterator )
	);
}
chat_client::~chat_client(){
	if(isConnected){ 
		io_service_.stop();
		socket_.close();
	}
	if(read_msg_ != NULL) delete[] read_msg_; 

}
void chat_client::write(const std::string msg)
{
	io_service_.post(boost::bind(&chat_client::do_write, this, msg));
}
void chat_client::close()
{
	io_service_.post(boost::bind(&chat_client::do_close, this));
}
void chat_client::handle_connect(const boost::system::error_code& error,
    tcp::resolver::iterator endpoint_iterator)
{
	if (!error) {
		if(read_msg_ != NULL) delete[] read_msg_;
		read_msg_ = new char[NET_MESSAGE_SIZE];
		//std::cout << "Connection to server a success. " << std::endl;
		char auth_array[3];
		auth_array[0] = 0xff;
		auth_array[1] = 0xda;
		auth_array[2] = 0xbb;
		std::string auth_out;
		auth_out.append(auth_array,3);
		write(auth_out);
		isConnected = true;
		std::string connect_message;

		connect_message += to_value(LocalEvent);
		connect_message += to_value(Connected);
		
		msg_queue.push_back(connect_message);
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_,NET_MESSAGE_SIZE),
			boost::bind(&chat_client::handle_read_header, this, boost::asio::placeholders::error)
		);
	} else if (endpoint_iterator != tcp::resolver::iterator()) {
		//std::cout <<"Failed to connect to server. Retrying." << std::endl;
		      socket_.close();
		      tcp::endpoint endpoint = *endpoint_iterator;
		      socket_.async_connect(endpoint,
			  boost::bind(&chat_client::handle_connect, this,
			    boost::asio::placeholders::error, ++endpoint_iterator));
	}
}
void chat_client::handle_read_header(const boost::system::error_code& error)
{
	if (!error) {
		memcpy(&msg_len, read_msg_, NET_MESSAGE_SIZE);
		//std::cout << "Read header with size of " << msg_len << std::endl;
		delete[] read_msg_;
		read_msg_ = new char[msg_len];
		//read_msg_ = "";
		boost::asio::async_read(socket_,
		    boost::asio::buffer(read_msg_, msg_len),
		    boost::bind(&chat_client::handle_read_body, this,
		      boost::asio::placeholders::error));
	} else { do_close(); }
}
void chat_client::handle_read_body(const boost::system::error_code& error)
{ 
  
	if (!error) {
		std::string m;
		m.append(read_msg_, msg_len);

		msg_queue.push_back(m);
		//std::cout << "Adding command with length of " << msg_len << " m length is " << m.size() << std::endl;
		//std::cout << " Read body containing message:";
		//print_string_as_ints(m);
		delete[] read_msg_;
		read_msg_ = new char[NET_MESSAGE_SIZE];
		//read_msg_ = "";
		boost::asio::async_read(socket_,
		    boost::asio::buffer(read_msg_, NET_MESSAGE_SIZE),
		    boost::bind(&chat_client::handle_read_header, this,
		      boost::asio::placeholders::error));
	} else { do_close(); }
}
void chat_client::do_write(std::string msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if (!write_in_progress) {
		boost::asio::async_write(socket_,
		    boost::asio::buffer(write_msgs_.front().c_str(),
		      write_msgs_.front().size()),
		    boost::bind(&chat_client::handle_write, this,
		      boost::asio::placeholders::error));
	}
}
void chat_client::handle_write(const boost::system::error_code& error)
{
	if (!error) {
		write_msgs_.pop_front();
		if (!write_msgs_.empty()) {
			boost::asio::async_write(socket_,
			    boost::asio::buffer(write_msgs_.front().c_str(),
			      write_msgs_.front().size()),
			    boost::bind(&chat_client::handle_write, this,
			      boost::asio::placeholders::error));
		}
	} else { do_close(); }
}
void chat_client::do_close() { 
	std::string close_message;
	close_message += to_value(LocalEvent);
	close_message += to_value(Disconnected);
	msg_queue.push_back(close_message);
	socket_.close(); 

}