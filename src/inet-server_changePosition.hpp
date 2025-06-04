void inet_player::changePosition(std::vector<std::string>&in) {
	std::cout << "movement detected on socket " << socket << "\n";
	//print_string_as_ints(in[0]);
	float x,y,z;
	static unsigned int float_size = sizeof(float);
	if(in[0].size() < float_size*3) {
		std::cout << "Movement error, in[0] size != sizeof(float)*3!" << std::endl;
		return; // error;
	}
	memcpy(&x, in[0].substr(0,float_size).c_str(), float_size);
	memcpy(&y, in[0].substr(float_size,float_size).c_str(), float_size);
	memcpy(&z, in[0].substr((float_size*2),float_size).c_str(), float_size);
	//orig_position = position;
	actual_target_position = vec3(x,y,z);
std::cout << "Actual target position: " << vec3(actual_target_position).print() << std::endl;
	//previous_time = 0;
	//GMT_Clock.reset();
	broadcastNearby(Position); // pass the user id, the position.
}