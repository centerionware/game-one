void player_login_queue(int fd) {
	login_queue.push_back(fd);
						/*
						Players.push_back(new inet_player());
						Players.back()->socket = newfd;
						Players.back()->name = "Not logged in";
						Players.back()->create_commands();
						Players.back()->broadcastNearby(AddPlayer); // sends a global broadcast.*/
}
void tick_login_queue(fd_set& master) {
	std::vector<queue_obj>::iterator iter = login_queue.begin(), end = login_queue.end();
	for(;iter!=end;iter++) {
		if(queue_timer.getMicroseconds()-(*iter).login_time >=3000000) {
			close((*iter).socket);
			FD_CLR((*iter).socket, &master);
			login_queue.erase(iter);
			
		}
	}
}