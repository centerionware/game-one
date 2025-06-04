namespace heightmap_globals {
	extern bool volatile alive;
}
void inet_player::initChunkNet(std::vector<std::string>&in) {
 	heightmap_globals::synchingchunk.lock();
	if(heightmap_globals::alive == false) {heightmap_globals::synchingchunk.unlock();return; } 
 unsigned int timestamp,id;
 
 // heightmap_globals::mut_c.lock();
  memcpy(&id, in[0].substr(0, NET_MESSAGE_SIZE).c_str() ,NET_MESSAGE_SIZE);
  memcpy(&timestamp, in[0].substr(NET_MESSAGE_SIZE, NET_MESSAGE_SIZE).c_str() ,NET_MESSAGE_SIZE);
  
  if(NewHeightmapLoader::hm_instance->needs_chunk_update(id, timestamp)) {

	    try_cached_copy(id,NewHeightmapLoader::hm_instance->updatets );

	if(NewHeightmapLoader::hm_instance->updatets < timestamp) {
		std::cout << "Requesting chunk update from server updatets: "<< NewHeightmapLoader::hm_instance->updatets << std::endl;
		std::string output;
		output+=(to_value(NetCommand));
		output+=(to_value(GetChunk));
		
		char arr[NET_MESSAGE_SIZE];
		memcpy(arr, &id, NET_MESSAGE_SIZE);
		output.append(arr,NET_MESSAGE_SIZE);
		memcpy(arr, &(NewHeightmapLoader::hm_instance->updatets), NET_MESSAGE_SIZE);
		output.append(arr,NET_MESSAGE_SIZE);
		
		send_text(output,socket);
	}
  }
	heightmap_globals::synchingchunk.unlock();
}