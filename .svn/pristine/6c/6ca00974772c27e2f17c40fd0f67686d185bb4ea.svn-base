ViewportClickReturnVoxel NewHeightmapLoader::viewportRightClicked(float x, float y,const Ogre::Camera*inCam) { // find the voxel at x,y closest to the camera in the direction it's looking
	ViewportClickReturnVoxel r;
	r.found = false;
	if(inCam == NULL) inCam = mCam;
	Ogre::Ray SelRay = inCam->getCameraToViewportRay(x,y);
	Ogre::Vector3 last_point(0,0,0);
	for(float c = 0; c < 450; c+=0.1) {
		Ogre::Vector3 pnt = SelRay.getPoint(c);
		pnt.x = sym_round(pnt.x);
		pnt.y = sym_round(pnt.y); 
		pnt.z = sym_round(pnt.z);
		if(c!=0) if(last_point == pnt) continue;
		
		last_point = pnt;
		Chunk *fChunk = qgetChunk(pnt);
		if(fChunk != NULL) {
			chunk_lock locker(fChunk);
			vec3 _position(pnt);
			vec3 temp_v = _position-fChunk->position;
			vec3 ortmp_v = temp_v;
			vec3 offset(15,30,15);
			int j = 31;
			int k =j*j;

			temp_v += offset;
			unsigned short idx = ((temp_v.y*k)+(temp_v.x*j)+temp_v.z );
			if(0){
				
				signed short y = idx/(k);
				signed short x = (idx - y*k)/j;
				signed short z = idx - y*k - x*j;
				
				std::cout << " X(" << x << ") Y(" << y << ") Z(" << z << ")" << " ortmp_v("<<ortmp_v.print()<<") _position("<<_position.print()<<") fChunk->position("<<fChunk->position.print()<<")"<< std::endl;
			}
			auto i = fChunk->NewNewVoxels.begin(),ie=fChunk->NewNewVoxels.end();
			{
			    if(transparented.contains(fChunk, idx)) 
					continue;
			    
			}
			for(;i!=ie;++i) {
				if((*i).first == idx) {
					vec3 temp_iv = fChunk->position;
					// 30x60x30.. // follow vertice definition, first is at 0 (-x -z -y),  then goes through z, then y.
					// the position of the chunk indicates it's center. The voxel at the exact center of 15x15x30 is equal to {x,y,z} = 0
					signed short y = idx/(k);
					signed short x = (idx - y*k)/j;
					signed short z = idx - y*k - x*j;
					// now normalize to between {-15,-15,-30} - {15,15,30}
					x-=15; z-=15;y-=30;
					temp_iv.x += x;
					temp_iv.y += y;
					temp_iv.z += z;
					r.position = temp_iv.toOgre();
					item_pickup_test(localPlayer, temp_iv);
					player_follow_test(localPlayer, temp_iv);
					r.found = true;
				//	std::cout << "Found" << std::endl;
					
					return r; // Found! No need to keep running...
				}
			}
			//std::cout << "Not yet found." << std::endl;
			
		}
	}
	
	return r;
}	