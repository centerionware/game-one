void inet_player::changePosition(std::vector<std::string>&in) {
	float x,y,z;
	unsigned int player_socket;
	static unsigned int float_size = sizeof(float);
	if(in[0].size() < float_size*3) return; // error;
	int offset = sizeof(unsigned int);
	memcpy(&player_socket,in[0].substr(0, offset).c_str(), offset);
	memcpy(&x, in[0].substr(offset,float_size).c_str(), float_size);
	memcpy(&y, in[0].substr(offset+float_size,float_size).c_str(), float_size);
	memcpy(&z, in[0].substr(offset+(float_size*2),float_size).c_str(), float_size);
	auto iter = Players.begin(), end = Players.end();
	for(;iter!=end;iter++) {
		if( (*iter)->socket == player_socket) {
			(*iter)->actual_target_position = vec3(x,y,z);
		}
	}
}