
basic_chunk_update& get_cached_copy(unsigned int);
void store_cached_copy(std::string cpy, unsigned int id) {
	std::ofstream o_fp;
	unsigned int csize = cpy.size();
	
	std::string indfilename = cache_filedir;
		std::ostringstream idnum;
		idnum << id;
		indfilename.append(idnum.str());
		
		//fp.open(indfilename);
		
	
	o_fp.open(indfilename, std::ios::out | std::ios::trunc | std::ios_base::binary		);// std::ios_base::trunc);
	//o_fp.seekp(std::ios::end);
	char *buff_1 = new char[sizeof(unsigned int)];
	char *buff_2 = new char[sizeof(unsigned int)];
	memcpy(buff_1, &id,sizeof(unsigned int));
	
	memcpy(buff_2, &csize, sizeof(unsigned int));
	
	std::string output_str;
	output_str.append(buff_1, sizeof(unsigned int));
	output_str.append(buff_2, sizeof(unsigned int));
	output_str.append(cpy);
	o_fp << output_str;
	//std::cout << "writing " << output_str.size() <<" to " << indfilename <<std::endl;
	o_fp.close();
	delete[] buff_1;
	delete[] buff_2;
}
basic_chunk_update& get_cached_copy(unsigned int id) {
	
	/*
	* File Layout:
	* {unsigned int = chunk_id, size_t = sizeof(serialized_chunk_string), serialized_chunk_string}
	* 
	* This file layout makes incompatible files for 32-bit vs 64-bit and is probably not endian-safe.
	* Files created on one computer may not be compatible with another (Though, same architecture should be safe)
	* 
	*/
	unsigned int chunk_id_t = 0;
	unsigned int chunk_size_t = 0;
	static basic_chunk_update chunk_update_t;
	chunk_update_t = basic_chunk_update();
	char *buff_1 = new char[sizeof(unsigned int)];
	char *buff_2 = new char[sizeof(unsigned int)];
	char *cdata = NULL;
	
	std::ifstream fp;
	
	std::string indfilename = cache_filedir;
	std::ostringstream idnum;
	idnum << id;
	indfilename.append(idnum.str());
	fp.open(indfilename);
	if(!fp.fail()) {
		fp.close();
		std::string input = effectivestl::get_file_contents(indfilename.c_str());
		fp.seekg(0);
		fp.read(buff_1, sizeof(unsigned int));
		//fp.seekg(sizeof(unsigned int));
		fp.read(buff_2, sizeof(unsigned int));
		memcpy(&chunk_id_t, input.substr(0,sizeof(unsigned int)).c_str(), sizeof(unsigned int));
		memcpy(&chunk_size_t, input.substr(sizeof(unsigned int),sizeof(unsigned int)).c_str(), sizeof(unsigned int));
		std::string ans = input.substr(sizeof(unsigned int)+sizeof(unsigned int), chunk_size_t);
			
		chunk_update_t = basic_chunk_update::deserialize(ans);
		//std::cout << "Read timestamp of " << chunk_update_t.timestamp << std::endl;
			
		//fp.close();
	}
	
	if(fp.is_open()) fp.close();
	if(cdata != NULL) delete[] cdata;
	delete[] buff_1;
	delete[] buff_2;
	return chunk_update_t;
}
void try_cached_copy(unsigned int id, unsigned int timestamp) {
  basic_chunk_update &chunk_update_t = get_cached_copy(id);
  if(chunk_update_t.timestamp > timestamp) {
	 // std::cout << "Using cached copy with TS " << chunk_update_t.timestamp << std::endl;
	  NewHeightmapLoader::hm_instance->chunk_update(chunk_update_t);
  }
}