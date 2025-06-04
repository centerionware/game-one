void inet_player::getName(std::vector<std::string> &i) {
	unsigned int size;
	unsigned int playerid;

	memcpy(&playerid, i[0].substr(0,sizeof(unsigned int)).c_str(), sizeof(unsigned int));
	memcpy(&size, i[0].substr(sizeof(unsigned int),sizeof(unsigned int)).c_str(), sizeof(unsigned int));
	std::string n;
	for(unsigned int xx = 0; xx < size; ++xx) {
	n.append( i[0].substr(( sizeof(unsigned int)*2)+xx,1));
	}
	std::cout << "Trying to set players name to " << n << " for id " << playerid << std::endl;
	auto iter = Players.begin(), iend = Players.end();
	for(;iter!=iend;++iter) 
	  if( (*iter)->socket == playerid) {
	      (*iter)->name = n;
	      break;
	  }
}