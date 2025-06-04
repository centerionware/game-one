bool NewHeightmapLoader::moveCurVoxel(const Ogre::Camera *mCam) { // Unused, depricated, remove.
	return false;
}

void NewHeightmapLoader::RunVoxelSelection() { //find the voxel straight underneath the camera
/*	return;
	Ogre::Ray SelRay = mCam->getCameraToViewportRay(0.5,0.5);
	if(selectedChunk != NULL) {
		selectedChunk->voxel_materials[selectedVoxel] -=17;
		selectedChunk->cleanup();
		selectedChunk = NULL;
	} 
	for(unsigned short c = 0; c < 30; c++) {
		Ogre::Vector3 pnt = SelRay.getPoint(c);
		pnt.x = sym_round(pnt.x);
		pnt.y = sym_round(pnt.y); 
		pnt.z = sym_round(pnt.z);
		Chunk *fChunk = qgetChunk(pnt);
		if(fChunk != NULL) {
			vec3 _position(pnt);
			vec3 temp_v = _position-fChunk->position;
			vec3 offset(15,30,15);
			temp_v += offset;
			unsigned short idx = ((temp_v.y*31*31)+(temp_v.x*31)+temp_v.z );
			
			std::vector<unsigned short>::iterator i = fChunk->all_voxels.begin(),ie=fChunk->all_voxels.end();
			for(;i!=ie;i++) {
				if((*i) == idx) {
					selectedChunk = fChunk;
					selectedVoxel = idx; 
					// Need to find the selected face next.. but for now, just do the selected voxel.. don't have per face texturing atm anyway.
					selectedFace = top;
					
					fChunk->voxel_materials[idx] = fChunk->get_material_id(idx)+17;
					if(fChunk->myVertexList != NULL) fChunk->cleanup();
					
					return; // Found! No need to keep running...
				}
			}

		}
	}*/
}
