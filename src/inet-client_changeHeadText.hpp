void inet_player::changeHeadText(std::vector<std::string>&in) {
	unsigned int player_socket;
	memcpy(&player_socket,in[0].substr(0,sizeof(unsigned int)).c_str(),sizeof(unsigned int));
	std::string nt;
	nt = in[0].substr(sizeof(unsigned int),in[0].size()-sizeof(unsigned int));
	auto iter = Players.begin(), iend = Players.end();
	bool found = false;
	for(;iter!=iend&&!found;++iter) {
		if( (*iter)->socket == player_socket) {
			(*iter)->headtext = nt;
			Ogre::String fi = nt.c_str();
			(*iter)->textBox->setText(fi);
			found = true;
			if((*iter)->name != "unnamed") {
				std::string chat_text;
				chat_text.append((*iter)->name);
				chat_text.append(": ");
				chat_text.append(fi);
				add_chatwindow_text(chat_text,"MainChatBox");
			}
			break;
		}
	}

}