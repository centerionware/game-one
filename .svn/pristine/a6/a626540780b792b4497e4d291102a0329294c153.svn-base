void check_close_player_chunks(inet_player *p) {
  static chunk_quick_cache ccc;
	  vec3 pp = p->position;
	  std::vector<chunk_quick_cache::clientChunkRemember> nearby = ccc.nearby(p);
	  std::vector<chunk_quick_cache::clientChunkRemember>::iterator i = nearby.begin(), ie = nearby.end();
	  for(;i!=ie;++i) {
//		  size_t ts = ccc.find((*i).c.position).timestamp;
//		std::cout <<"Chunk is nearby";
		  if(ccc.has_sent(p, (*i).c.position))continue;// && (ts == (*i).c.timestamp)) continue;
		  else {
			  std::string output;
			  output+=to_value(NetCommand);
			  output+=to_value(GetChunk);
			    
			  char tarr[sizeof(size_t)];
			  memcpy(tarr, &((*i).c.id), sizeof(size_t));
			  output.append(tarr, sizeof(size_t));
			  memcpy(tarr, &((*i).c.timestamp), sizeof(size_t));
			  output.append(tarr, sizeof(size_t)); 
			 
			  p->send_text(output, p->socket);
			//  std::cout << "Sending hm("<< ((*i).c.id) << ") (" << ((*i).c.timestamp )<< ")\n";
			  ccc.sent_chunk_player(p,(*i).c.position);
		  }
	  }
	  
}