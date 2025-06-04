void inet_player::getChunk(std::vector<std::string>&i) {
   std::cout << "Client requested chunk\n"; 
      unsigned int chunkid,timestamp;
      std::string oarg = i[0];
      i.pop_back();
      memcpy(&chunkid, i[0].substr(0,sizeof(unsigned int)).c_str(),sizeof(unsigned int));
      memcpy(&timestamp, i[0].substr(sizeof(unsigned int),sizeof(unsigned int)).c_str(),sizeof(unsigned int));
	if(!chunk_quick_cache::ptr->exists(chunkid)) {
		std::cout << "quick ignore..\n";
		 return; // quick ignore.
	}
	basic_chunk_update& up_chuk = db_retrieve_chunk(chunkid,timestamp);
    		//if(socket == other_player_socket) return;
	std::string update;
	update += to_value(NetCommand);
	update += to_value(PushChunk);
	{std::string tmp = up_chuk.serialize();
	update.append(gzip_compress_string(tmp));
	}
	send_text(update, socket);

     std::cout << "Sending chunk update\n"; 
}