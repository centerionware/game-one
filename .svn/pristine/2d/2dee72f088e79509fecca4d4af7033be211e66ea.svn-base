void inet_player::add_in_range(inet_player*_p) {
	std::vector<inet_player *>::iterator i = players_in_range.begin(), end = players_in_range.end();
	for(;i!=end;i++) if((*i) == _p) return;
	net_commands x = AddPlayer;
	send_updates(x, (_p->socket));
	players_in_range.push_back(_p);
	
	_p->send_updates(x, socket);
	_p->players_in_range.push_back(this);
	broadcastNearby(Teleport, &(_p->socket));
	broadcastNearby(Position);
	_p->broadcastNearby(Teleport, &socket); // send the teleports before the positions.
	// because teleport will reset the targetposition.
	_p->broadcastNearby(Position);
	std::cout << "Players  in range, teleporting.\n";
}