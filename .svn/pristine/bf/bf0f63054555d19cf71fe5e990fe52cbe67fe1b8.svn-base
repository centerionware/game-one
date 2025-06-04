#include "inet-protocol.h"
#include "configuration_system.h"
/*Yeah this file is not used */
using std::string;
using boost::asio::ip::udp;

enum { max_length = 1024 };

void inet::inet() : 
s(this->io_service, udp::endpoint::v4(), 0), 
resolver(this->io_service),
query(udp::v4(), Configuration::get_singleton()->config("server").c_str(), Configuration::get_singleton()->config("port").c_str() )
 {
	this->server = Configuration::get_singleton()->config("server");
	this->port = Configuration::get_singleton()->config("port");
	this->username = Configuration::get_singleton()->config("username");
	this->password = Configuration::get_singleton()->config("password");
	this->iterator = this->resolver.resolve(query);
	// now use boost::asio to connect to the server.
}
/**
 * This function blocks. Use threads and thread safe methods of communication with the server
 *
 * Once it gets to this function, it's actually already connected.
 * the connection is done, I think, on creating of the query.
 * 
 * Calls handle_network_message, a virtual function to be overloaded 
 * to handle the different message types. 
 * 
 * 
 */
bool inet::listen_to_server() {
	char reply[max_length];
	size_t reply_length = this->s.recieve_from(boost::asio::buffer(reply, max_length), *iterator);
	std::string lr;
	lr.append(reply, reply_length);
	handle_network_message(lr);
	
}
