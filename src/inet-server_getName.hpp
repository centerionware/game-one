void inet_player::getName(std::vector<std::string> &i) {
	std::cout << "getName\n";
	std::string output;
	output +=to_value(NetCommand);
	output +=to_value(GetName);
	if(i[0].size() < sizeof(size_t)) return;
	unsigned int psocket;
	memcpy(&psocket, i[0].c_str(), sizeof(size_t));
	std::string name;
	
	{
		bool found = false;
		auto iter = Players.begin(), end = Players.end();
		for(;iter!=end&&!found;iter++) 
			if((*iter)->socket == psocket) {
				found = true;
				name = (*iter)->name;
			}
		
	}
	output.append(i[0].c_str(), sizeof(size_t));
	char tarr[sizeof(size_t)];
	size_t nsze = name.size();
	memcpy(tarr, &nsze, sizeof(size_t));
	output.append(tarr, sizeof(size_t));
	output.append(name);
	std::cout << "Sending name " << name << std::endl;
	send_text(output, socket);
}