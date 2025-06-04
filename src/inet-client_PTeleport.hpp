void inet_player::PTeleport(std::vector<std::string>&in) {
  if(mSceneNd == NULL) {
      std::cout << "Trying to teleport without a scene node? Check the server maybe?"<<std::endl;
      return;
  }
	float x,y,z;
	unsigned int player_socket;
	static unsigned int float_size = sizeof(float);
	if(in[0].size() < float_size*3) return; // error;
	int offset = sizeof(unsigned int);
	memcpy(&player_socket,in[0].substr(0, offset).c_str(), offset);
	memcpy(&x, in[0].substr(offset,float_size).c_str(), float_size);
	memcpy(&y, in[0].substr(offset+float_size,float_size).c_str(), float_size);
	memcpy(&z, in[0].substr(offset+(float_size*2),float_size).c_str(), float_size);
	offset = offset+(float_size*3);
	std::string rest = in[0].substr(offset, in[0].size()-offset);
	auto iter = Players.begin(), end = Players.end();
//	std::cout << "client side teleport good for player " << player_socket << " to position " << vec3(x,y,z).print() << std::endl;
	if(player_socket == 0) {
		position.x = x;//
		position.y = y;
		position.z = z;// = vec3(x,y,z).toOgre(); 
		mSceneNd->setPosition(position);
		actual_target_position = vec3(x,y,z);
		targetposition = vec3(position);
		std::cout << "Teleporting self to " << vec3(position).print("xyz")<<std::endl;
	} else {
	for(;iter!=end;iter++) 
		if( (*iter)->socket == player_socket) { 
			(*iter)->position = vec3(x,y,z).toOgre(); 
			(*iter)->mSceneNd->setPosition((*iter)->position);
			(*iter)->actual_target_position = vec3(x,y,z);
			(*iter)->targetposition = vec3(x,y,z);
			(*iter)->headtext = rest;
			(*iter)->textBox->setText(rest);
			std::cout << "Teleporting other dude to " << vec3((*iter)->position).print("xyz")<<std::endl;
			return; 
		}
	}
}