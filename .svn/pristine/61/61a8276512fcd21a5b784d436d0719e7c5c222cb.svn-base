void inet_player::followPlayer(std::vector<std::string>&i) {
	unsigned int player1;
	unsigned int player2;
	
	memcpy(&player1, i[0].substr(0,sizeof(unsigned int)).c_str(), sizeof(unsigned int));
	memcpy(&player2, i[0].substr(sizeof(unsigned int),sizeof(unsigned int)).c_str(), sizeof(unsigned int));
	inet_player *p1, *p2;
	if(player1 == 0) p1 = (inet_player *)this;
	else p1 = find_player(player1);
	if(player1!=0 && player2 == 0) p2 = (inet_player*)this;
	else if(player1 == 0 && player2 == 0) p2 = NULL;
	else p2 = find_player(player2);
	
	if(p1!=NULL &&p2!=NULL) p1->following_player = p2;
	
	
}
void inet_player::unFollowPlayer(std::vector<std::string>&i) {
	unsigned int player1;
	unsigned int player2;
	
	memcpy(&player1, i[0].substr(0,sizeof(unsigned int)).c_str(), sizeof(unsigned int));
	memcpy(&player2, i[0].substr(sizeof(unsigned int),sizeof(unsigned int)).c_str(), sizeof(unsigned int));
	inet_player *p1;
	if(player1 == 0) p1 = (inet_player *)this;
	else p1 = find_player(player1);
	
	
	if(p1!=NULL) p1->following_player = NULL;
	
	
}