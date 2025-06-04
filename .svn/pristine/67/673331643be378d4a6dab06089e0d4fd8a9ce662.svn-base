void tick_server(unsigned long int last_frame, unsigned long int current_frame) {
  return;
	auto aiter= inet_player::Players.begin(), aend = inet_player::Players.end(), biter= inet_player::Players.begin(), bend = inet_player::Players.end();
	for(;aiter!=aend;aiter++) 
	    for(;biter!=bend;biter++) {
		    if( ((*aiter)) != (*biter)) {
			  bool this_frame_in_range = false;
			  bool last_frame_in_range = false;
			  vec3 a_pos_lf = (*aiter)->getPositionAtFrame(current_frame-last_frame);
			  vec3 b_pos_lf = (*biter)->getPositionAtFrame(current_frame-last_frame);
			  vec3 a_pos_now = (*aiter)->getPositionAtFrame(0);
			  vec3 b_pos_now = (*biter)->getPositionAtFrame(0);
			   
			  vec3 srt = a_pos_lf;
			  if(b_pos_lf > a_pos_lf) {
				a_pos_lf = b_pos_lf;
				b_pos_lf = srt;
			  } 
			  srt = a_pos_now;
			  if(b_pos_now > a_pos_now) {
				a_pos_now = b_pos_now;
				b_pos_now = srt;
			  } 
			  
			   vec3 diff = a_pos_lf-b_pos_lf;
			    if(  diff.x < 60.0 && diff.x > -60.0 && diff.z < 60.0 && diff.z > -60.0 ) last_frame_in_range = true;
			    else continue;
			   diff= a_pos_now-b_pos_now;
			   if(  diff.x < 60.0 && diff.x > -60.0 && diff.z < 60.0 && diff.z > -60.0 ) this_frame_in_range = true;
			   
			   if(this_frame_in_range && !last_frame_in_range) {
				  std::cout << " Players came into range. teleporting.\n";
				  (*aiter)->broadcastNearby(Teleport, &((*biter)->socket));
				  (*aiter)->broadcastNearby(Position);
				  
				  (*biter)->broadcastNearby(Teleport, &((*aiter)->socket)); // send the teleports before the positions.
				  // because teleport will reset the targetposition.
				  (*biter)->broadcastNearby(Position);
			   }
			   
		    }
	    }
}