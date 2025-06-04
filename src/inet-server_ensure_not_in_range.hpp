void inet_player::ensure_not_in_range(inet_player*_p) {
  std::vector<inet_player *>::iterator i = players_in_range.begin(), end = players_in_range.end();
	for(;i!=end;i++) if((*i) == _p) { 
		net_commands x = RemPlayer;
		send_updates(x,(_p->socket));
		_p->send_updates(x,socket);
		players_in_range.erase(i);
		auto ie = _p->players_in_range.begin(), iend = _p->players_in_range.end();
		for(;ie!=iend;ie++) {
			if( (*ie)->socket == socket) {
				_p->players_in_range.erase(ie);
				return;
			}
		}
		return; 
	}
}