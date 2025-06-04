void remove_following(unsigned int socket) {
auto i = inet_player::Players.begin(), e = inet_player::Players.end();
for(;i!=e;++i) if( (*i)->following_player!= NULL &&(*i)->following_player->socket == socket) (*i)->following_player = NULL;

}

void inet_player::followPlayer(std::vector<std::string>&i) {
	std::string output;
	output +=to_value(NetCommand);


	if(i[0].size() < sizeof(size_t)) return;
	unsigned int psocket;
	memcpy(&psocket, i[0].c_str(), sizeof(size_t));
	std::string name;
	if(psocket == 0) {
		following_player = NULL;
		output += to_value(UnFollowPlayer);
	} else {
		output +=to_value(FollowPlayer);

		bool found = false;
		auto iter = inet_player::Players.begin(), end = inet_player::Players.end();
		for(;iter!=end&&!found;iter++) 
			if((*iter)->socket == psocket) {
				found = true;
				name = (*iter)->name;
				following_player = (*iter).get();
				broadcastNearby(FollowPlayer);
			}
	}
	char S[sizeof(size_t)];
	size_t l = 0;
	memcpy(S, &l, sizeof(size_t));
	output.append(S, sizeof(size_t));
	output.append(i[0].c_str(), sizeof(size_t));

	send_text(output, socket);
	std::cout << "Sending followplayer back to client";
}
void player_follow_test(inet_player *p, vec3 &i){}