float getColourAt(GOREAL h, GOREAL w, internal_image &loader) {
  // This was used when reading a heightmap image.. Currently is not used.
	Ogre::ColourValue cv = loader.img.getColourAt(w,h,0);
	GOREAL tl = cv.r+cv.g+cv.b; // normalized between 0-3
	// 0-0, 3=1024, convert now.
	// 
	if(tl == 0) return 0;
	//std::cout << "((int)(((tl/3)*ROOF)+15)&~15)= " << ((int)(((tl/3)*ROOF)+15)&~15) << std::endl; 
	return std::ceil(((float)(((tl/3.0)*ROOF)))*0.5);//+0.5)&~0.5); // get a ratio find closest multiple of 16
	// multiple of 8 makes this a fast operation, looks like some sort of
	// binary shift. I found it on google, says it was borrowed from sdl
}

// iw is the width of the image
// for the 'case (number)' numbers I used the middle image from the 3
// numbered squares at the top of this file.
/*
voxel *NewHeightmapLoader::comp_neighbor_from_heightmap(size_t count, int iw, int neighbor_id) {
	  switch (neighbor_id) {
	    case 0:
	      return voxels.size() > count+1 ? voxels[count+1] : NULL;
	    case 5:
	      return count > 0 ? voxels[count-1] : NULL;
	    case 3:
	      return voxels.size() > count+iw ? voxels[count+iw] : NULL;
	    case 2:
	      return count >= (size_t)iw ? voxels[count-iw] : NULL;
	    default:
	      // invalid case, die?
	      string x = "Invalid neighbor ";
	      x.append(to_string(neighbor_id));
	      x.append(" at count ");
	      x.append(to_string(count));
	      throw x.c_str(); 
	      break;
	  }
	  return NULL;
}
void NewHeightmapLoader::set_neighbor(voxel *i, int number, voxel *v) {
	i->connect_voxel(v, number);
}*/
void NewHeightmapLoader::load(std::string filename) {
	internal_image v(filename);
	this->loader = v;
	load_img(v);
}
//static size_t gap_count = 0;


void NewHeightmapLoader::load_img(internal_image &img) { // redo this to load an image into a chunk
	// if file dataFilename != exists, continue this, else run other constructor to load old data.
	/*
	unsigned int iw = img.width;
	unsigned int ih = img.height;
	weight = CUBE_SIZE;
	std::cout << "Creating Voxels" << std::endl;
	
	for(unsigned int h = 0; h < ih; h++) {
		for(unsigned int w = 0; w < iw; w++) {
			// Defines the center point for the cube
			vec3 p;
			p.x = (w * (CUBE_SIZE *2.0)) + CUBE_SIZE;
			p.z = (- ( h * ( CUBE_SIZE *2.0 )) )-CUBE_SIZE;
			p.y = getColourAt(w, h, img);
			voxel *v = new voxel(p, true);
			if(curVoxel == NULL) curVoxel = v; // use the first point defined as the current voxel
			voxels.push_back(v);
		}
	}
	std::cout << "Creating default neighbors from heightmap image" << std::endl;
	{ // This just sets pointers based on the voxels array..
	    std::vector<voxel*>::iterator iter = voxels.begin(), end = voxels.end();
	    long long unsigned int count = 0, tw=0;
	    // Certain assumptions can be made
	    // since it's a heightmap, and not a true 3d image yet
	    // there should be 3-8 neighbors per cube, depending on 
	    // if it's at an edge, multiple edges, or not.
	    unsigned int h = 0;
	    voxel *_p = NULL;
	    
	    for(;iter!=end;iter++,count++,tw=count) {
		  while(tw > iw) { tw -= iw ; h++; }
		  _p = (*iter);
		    heightmap_neighbor(0);
		    heightmap_neighbor(2);
		    heightmap_neighbor(5);
		    heightmap_neighbor(3);
	    }
	}
	// Add in voxels where the neighbors arn't touching along the z;
	std::cout << "Filling in gaps\n";
	{ /// The newly created voxels are in the memory chain only
	 /// so from here out the chain should be accessed from curVoxel and use it's neighbors array, do not
	 /// rely on the voxels vector anymore after this.
		std::vector<voxel*>::iterator iter = voxels.begin(), end = voxels.end();
		for(;iter!=end;iter++,gap_count++)
			fill_in_gaps(*iter);
	}
	std::cout << "Done";*/
}

void NewHeightmapLoader::loadDatafile(std::string dataFilename) {
#ifndef WIN32
/*
	using namespace boost::iostreams;
	//This function is compatible with all three versions of the format. 
	//version 1 always has filenames that end with .voxmap.gz
	//version 2 is always .2.voxmap.gz
	//version 3 is always .3.voxmap.gz
	//I think this name scheme for versioning will continue.
	// Version 4 does not read from a file at all in the server - it will read from the DB,
	// in the client it will read from the local cache file or the server.
	//
	try{
		std::ifstream myrfile(dataFilename.c_str());// replace with dataFilename after testing.
		std::stringstream myfile;
		filtering_streambuf<input> in;
		in.push(gzip_decompressor());
		in.push(myrfile);
		boost::iostreams::copy(in,myfile);
		myrfile.close();
		myfile.seekg(0,std::ios::end);
		size_t count = myfile.tellg();
		size_t ccount;
		count = count-(sizeof(size_t)*2) ;
		myfile.seekg(count,std::ios::beg);
		  
		static int xk1 = sizeof(size_t), xk2=sizeof(GOREAL)*3,xk3=sizeof(unsigned long long),xk4=xk3*6,ushort=sizeof(unsigned short);
		
		static size_t ind_length = xk2+xk3+xk4;
		char wk1[xk1],wk2[xk2];
		
		for(int y = 0; y < xk1; y++) {
			myfile >> wk1[y];
		}
		memcpy(&ccount, wk1, xk1); // chunk count.. works with older versions by being ignored during processing.
		for(int y = 0; y < xk1; y++) {
			myfile >> wk1[y];
		}
		memcpy(&count, wk1, xk1);
		std::cout << "Loading " << count << " Voxels from " << dataFilename  << " with ccount " << ccount << std::endl;

		if(dataFilename.rfind(".3.voxmap.gz",dataFilename.size()) != std::string::npos) {
			myfile.seekg(0,std::ios::beg);
			for(size_t x = 0; x< ccount; ++x) {
				GOREAL p[3];
				size_t i;
				myfile.read(wk2,xk2);
				memcpy(p, wk2, xk2);
				vec3 m(p[0],p[1],p[2]);
				Chunk *n = new Chunk(m);
				chunks.insert(n,zerovec);
				myfile.read(wk1, xk1);
				memcpy(&i, wk1, xk1);
				for(size_t incount = 0; incount < i; ++incount) {
			//	  std::cout <<" i: " << i << " incount " << incount << std::endl;
					unsigned short j;
					unsigned char mat;
					char igloo[ushort];
					myfile.read(igloo,ushort);
					memcpy(&j, igloo, ushort);
					myfile.read(igloo,sizeof(unsigned char));
					memcpy(&mat, igloo, sizeof(unsigned char));
					n->all_voxels.push_back(j);
					n->voxel_materials[j] = mat;
				}
			}
		} else if(dataFilename.rfind(".2.voxmap.gz",dataFilename.size()) != std::string::npos) {
			myfile.seekg(0,std::ios::beg);
			for(size_t x = 0; x< ccount; ++x) {
				GOREAL p[3];
				size_t i;
				myfile.read(wk2,xk2);
				memcpy(p, wk2, xk2);
				vec3 m(p[0],p[1],p[2]);
				Chunk *n = new Chunk(m);
				chunks.insert(n,zerovec);
				myfile.read(wk1, xk1);
				memcpy(&i, wk1, xk1);
				for(size_t incount = 0; incount < i; incount++) {
					unsigned short j;
					char igloo[ushort];
					myfile.read(igloo,ushort);
					memcpy(&j, igloo, ushort);
					n->all_voxels.push_back(j);
				}
			}
		} else { // first format.
						
			for(size_t x = 0; x< count; ++x) {
				GOREAL p[3];
				myfile.seekg(x*ind_length,std::ios::beg);
				myfile.read(wk2,xk2);
				memcpy(p, wk2, xk2);
				vec3 m(p[0],p[1],p[2]);
				chunk_control(m);
			}
		}
	}catch(const boost::iostreams::gzip_error& exception) {  
	  int error = exception.error();  
	  std::cout  << "Boost iostreams error code #"<< error <<std::endl;
	  throw exception;
	}*/
#else
throw "Don't use this function...";
#endif
} 
void NewHeightmapLoader::saveDatafile(std::string dataFilename) {
#ifndef WIN32
	using namespace boost::iostreams;
  /*
	  VERSION 3
	  each_chunk {
		  float3 position // The center position of each_chunk.
		  size_t chunk_voxel_count // amount of voxels that are not 'air' in this chunk.
		  unsigned short voxel_id[chunk_voxel_count] // extracted by for loop using chunk_voxel_count . each 'encoded' voxel.
	  }
	  size_t chunk_count (varies on 32bit and 64-bit builds.) // Uses this for the for loop that extracts each_voxel this many times.
	  size_t voxel_count (not entirely needed. left only to display voxel count when loading without recounting them all)
	*/
	/*
	std::ofstream myrfile(dataFilename.c_str(),std::ios::trunc); 
	std::stringstream myfile;
	size_t count=0;
	insert_sorted_chunks::iterator *iter = chunks.begin();
	std::vector<unsigned short>::iterator bi, be;
	static int threefloats=sizeof(GOREAL)*3, ushort=sizeof(unsigned short);
	static int tsize = sizeof(size_t), ccsize=sizeof(char);
	size_t ccount = 0;
	for(;iter!=NULL;iter=iter->next){
		bi = (iter)->ele->all_voxels.begin(), be = (iter)->ele->all_voxels.end();
		char arr[threefloats]; 
		memcpy(arr, &(iter->ele->position._int), threefloats);
		myfile.write(arr,threefloats);
		char dsize[tsize];
		size_t c = iter->ele->all_voxels.size();
		memcpy(dsize, &c, tsize);
		myfile.write(dsize, tsize);
		for(;bi!=be;bi++) {
			char in_size[ushort];
			memcpy( in_size,&(*bi),ushort);
			myfile.write(in_size,ushort);
			unsigned char matid = iter->ele->get_material_id((*bi));
			memcpy(in_size, &matid, ccsize);
			myfile.write(in_size,ccsize);
			count++;
		}
		ccount++;
	}
	char t[tsize];
	memcpy(t,&ccount, tsize);
	myfile.write(t, tsize);
	memcpy(t,&count, tsize);
	myfile.write(t, tsize);
	std::cout << "Saving " << count << " voxels as " << dataFilename << std::endl;  
	filtering_streambuf<input> out;
	out.push(gzip_compressor());
	out.push(myfile);
	boost::iostreams::copy(out,myrfile);
	myrfile.close();
	std::cout << "Saved " << count << " voxels" << std::endl;
	#else
throw "Don't use this function...";*/
#endif
}