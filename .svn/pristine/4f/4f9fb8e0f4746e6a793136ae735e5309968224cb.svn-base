void login_queue_receive(int fd, std::string &data, fd_set&master) {
	mset = &master;
	
	std::cout << "Recieved " << fd << " " << data << std::endl;
	
	if(data.size() < 3) {
		std::vector<queue_obj>::iterator iter = login_queue.begin(), end = login_queue.end();
		for(;iter!=end;iter++) {
			if((*iter).socket == fd) {
				close((*iter).socket);
				FD_CLR((*iter).socket, &master);
				login_queue.erase(iter);
				std::cout << "Missing||Invalid app code!\n";
				return;
			}
		}
	}
	char auth_array[3];
	auth_array[0] = 0xff;
	auth_array[1] = 0xda;
	auth_array[2] = 0xbb;
	
	if(memcmp(data.c_str(),auth_array, 3) == 0) {
		std::vector<queue_obj>::iterator iter = login_queue.begin(), end = login_queue.end();
		for(;iter!=end;iter++) {
			if((*iter).socket == fd) {
				
				//pre_logged_players.push_back((*iter));
				inet_player::Players.push_back(boost::shared_ptr<inet_player>(new inet_player()));
				inet_player::Players.back()->socket = fd;
				inet_player::Players.back()->name = "Not logged in";
				inet_player::Players.back()->create_commands();
				inet_player::Players.back()->headtext = "Good Ninja.";
				inet_player::Players.back()->logged_in = false;
				inet_player::Players.back()->lobby_logged_in = false;
				if(data.size() > 2){
				std::string txt = data.substr(3, data.size()-3);
				  inet_player::Players.back()->recv_text(txt);
				}
				/*inet_player::Players.back()->broadcastNearby(AddPlayer); // sends a global broadcast.*/
				login_queue.erase(iter);
				std::cout << "Logged in!\n";
				return;
			}
		}
	}
	std::vector<queue_obj>::iterator iter = login_queue.begin(), end = login_queue.end();
	for(;iter!=end;iter++) {
		std::vector<queue_obj>::iterator iter = login_queue.begin(), end = login_queue.end();
		for(;iter!=end;iter++) {
			if((*iter).socket == fd) {
				close((*iter).socket);
				FD_CLR((*iter).socket, &master);
				login_queue.erase(iter);
				std::cout << "Unknown error\n";
				return;
			}
		}
		
	}
}