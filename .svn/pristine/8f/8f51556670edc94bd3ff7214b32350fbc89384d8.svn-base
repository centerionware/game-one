void inet_player::changeHeadText(std::vector<std::string>&in) {

	std::string nt;
	std::vector<std::string>::iterator i = in.begin(), end = in.end();
	for(;i!=end;i++) nt.append((*i));
	headtext = nt;
	broadcastNearby(HeadText);//pass it this user id, the id for the changeHeadText command, and the new text..
}