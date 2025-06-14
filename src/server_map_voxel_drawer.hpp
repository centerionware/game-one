
void sync_render_array(std::vector<Chunk*>&read_only_cpy) {
	
	static Chunk *last_beg = NULL;
	if(chunks._chunks.size() > 0) {
		if(read_only_cpy.size() == chunks._chunks.size() && last_beg == chunks._chunks[0]) return;
		chunk_iterator_locker itlocker;
		read_only_cpy.clear();
		std::copy(chunks._chunks.begin(), chunks._chunks.end(), std::back_inserter(read_only_cpy));
		last_beg = chunks._chunks[0];
	}
}


std::ostringstream timer_log;
struct time_logger {
	static time_logger *time_logger_inst;
	static time_logger* instance() {if(time_logger_inst == NULL) time_logger_inst = new time_logger(); return time_logger_inst; }
	
	Ogre::Timer dtimer;
	void start() { dtimer.reset(); }
	void stop() { log(dtimer.getMicroseconds()); }
	template<class T> void stop(T _in) { log(_in,dtimer.getMicroseconds()); }
	template<class T> void log(T _in) {
		timer_log << _in <<"�s\n";
	}
	template<class T,class Y> void log(T _in,Y _el) {
		timer_log << _in << " " << _el <<"�s\n";
	}
	time_logger() {start();} 
	~time_logger() {}
};
time_logger *time_logger::time_logger_inst = NULL;
struct blahdidyblah {
	blahdidyblah() {}
	~blahdidyblah() { 
		std::ofstream outfile;
		outfile.open("timer_log.output",std::ios_base::out);
		outfile << timer_log.str().c_str();
		outfile.close();
	}
};
volatile blahdidyblah foofoo; // Memory cleanup 
struct CameraPosOriRememberer {
	struct posori {
		Ogre::Vector3 pos;
		Ogre::Quaternion ori;
	};
	std::vector<posori> remembering;
	bool has_changed(std::vector<Ogre::Camera *> &c) {
		if(c.size() != remembering.size()) {
			remembering.clear();
			for(auto a=c.begin(), b=c.end(); a<b;a++) { posori y; y.pos = (*a)->getPosition(); y.ori = (*a)->getOrientation(); remembering.push_back(y); }
			return true;
		}
		int ct = 0;
		bool ret = false;
		for(auto a=c.begin(), b=c.end(); a<b;++a,++ct) {
			if(remembering[ct].pos != (*a)->getRealPosition()) {remembering[ct].pos = (*a)->getRealPosition(); ret = true; }
			if(remembering[ct].ori != (*a)->getRealOrientation()) {remembering[ct].ori = (*a)->getRealOrientation(); ret = true; }
		}
		return ret;
	}
	
	void crit_reset() { remembering.clear(); }
};
extern bool is_server;
struct voxel_drawer {
	vec3 allfaces[12];
	vec3 curfaces[12];
	std::map<unsigned int, vec3> new_normals;
	insert_sorted_vec3s faces; // the faces are ready to be inserted in to ogre order after calling create_faces.
	//insert_sorted_vec3s vertex_number_map_list;
	insert_sorted_vec3s vertex_number_map;
	bool set;
	static voxel_drawer _int_draw;
	static voxel_drawer*get_drawer() {
	      return &_int_draw;
	}
	static void clear() {
	      _int_draw.faces.clear();
	      _int_draw.vertex_number_map.clear();
	     _int_draw.set = false;
	}
	voxel_drawer() : set(false){};
	void create_faces(vec3 &cp, std::vector<Ogre::Camera *>&mCam) {
		/// The very first order of business is to create faces using the normal numbers
		/// for each vertice in this voxel.
		if(mCam.size() == 0) return;
		static CameraPosOriRememberer cposrem;
		static bool FRUN = true;
		static Ogre::Vector3 MainCamPosition = mCam[0]->getRealPosition();
		if(!heightmap_globals::network_changed)
			if(!heightmap_globals::changed)
				if(!cposrem.has_changed(mCam)) return;
		heightmap_globals::network_changed = false; // immediatly set to false after checking. It works great in the non-linearity of how the parts are fitting together. 
		// however, setting network_changed to false immediatly has the small drawback of over-running the below code for better accuracy.
		// if set to false after running the following code, it'd work sometimes instead of always and under-run the below code. 
		// accuracy > speed for now since it's pretty zippy already.
		sync_render_array(heightmap_globals::rendered_chunks);

		auto iter = heightmap_globals::rendered_chunks.begin(), end = heightmap_globals::rendered_chunks.end();

		for(;iter!=end;++iter) {
			if(faces.begin() != faces.end()) faces.clear();
			if(vertex_number_map.begin() != vertex_number_map.end()) { vertex_number_map.clear(); }
			chunk_lock locker( (*iter));
			if((*iter)->in_view(cp,mCam)){ 
				if( (*iter)->myVertexList == NULL ) {
					(*iter)->changed_from_last_render = true;
					setup_from_vector( (*iter) ,mCam );
					heightmap_globals::changed = true;
				}
			}
		}

	}
	inline void setup_from_vector(Chunk*c, std::vector<Ogre::Camera *>&mCam) 
	{
		if(c->myVertexList != NULL) {delete[] c->myVertexList; c->myVertexList = NULL; }
		if(c->pColor != NULL) { delete[] c->pColor; c->pColor = NULL; }
		if(c->mcWeights != NULL) { delete[] c->mcWeights; c->mcWeights = NULL; }
		c->re_render_needed = true;
		c->vertex_count = c->NewNewVoxels.size();
		c->myVertexList = new GOREAL[c->vertex_count*3+1];
		c->pColor = new Ogre::RGBA[c->NewNewVoxels.size()+1];
		c->mcWeights = new float[c->vertex_count*3+1];
		auto iter = c->NewNewVoxels.begin();
		auto end =  c->NewNewVoxels.end();
		Ogre::RGBA *color_inserter = c->pColor;
		size_t final_size = 0;

		vec3 list[14] = { 
				vec3(-1,0,0), vec3(1,0,0),vec3(0,-1,0), vec3(0,1,0), vec3(0,0,-1),vec3(0,0,1),
				vec3(-1,1,-1), vec3(1,1,-1), vec3(-1,1,1), vec3(1,1,1),
				vec3(-1,-1,-1), vec3(1,-1,-1), vec3(-1,-1,1), vec3(1,-1,1)
		};

		const unsigned int valuel[27] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864 };
		const vec3 neighbor_list[27]= {
			vec3(-1,-1,-1), 
			vec3(-1,-1,0), vec3(-1,-1,1), vec3(-1,0,-1), vec3(-1,0,0), 
			vec3(-1,0,1), vec3(-1,1,-1), vec3(-1,1,0), vec3(-1,1,1), 
			vec3(0,-1,-1), vec3(0,-1,0), vec3(0,-1,1), vec3(0,0,-1), 
			vec3(0,0,0), vec3(0,0,1), vec3(0,1,-1), vec3(0,1,0), 
			vec3(0,1,1), vec3(1,-1,-1), vec3(1,-1,0), vec3(1,-1,1), 
			vec3(1,0,-1), vec3(1,0,0), vec3(1,0,1), vec3(1,1,-1), 
			vec3(1,1,0), vec3(1,1,1)
		};

		for(size_t count = 0;iter!=end;++iter,count+=3){
			vec3 temp_v = c->position+(from_voxid((*iter).first)-vec3(15,30,15)); 
			c->myVertexList[count] = temp_v.x;
			c->myVertexList[count+1] = temp_v.y;
			c->myVertexList[count+2] = temp_v.z;
			unsigned char mmid = c->get_material_id((*iter).first);
			unsigned int zed = 0;
			// the ZED color is used to determine which faces to draw (So no lines in glass)
			for(unsigned char counter = 0; counter < 6; ++counter) {
				auto vWorldPos = temp_v+list[counter];
				auto varp = (vWorldPos+vec3(15,30,15))-c->position;
				Chunk * bld = c;
				if(varp.x < 0 || varp.y < 0 || varp.z < 0 || varp.x > 30 || varp.y > 60 || varp.z > 30) {
					//testcreate_chunks(vWorldPos);
					chunk_iterator_locker itlocker;
					vec3 cppos = chunk_position_from_contained_voxel(vWorldPos);
					for(auto i = chunks._chunks.begin(), e= chunks._chunks.end();i!=e&&bld==c;++i){
						if((*i)->position == cppos) bld=(*i);
					}
								
					if(bld==c) { zed += valuel[counter]; continue; }
					varp = (vWorldPos+vec3(15,30,15)) - bld->position;
				}
				auto lp = bld->NewNewVoxels.find(to_voxid(varp));
				if(lp != bld->NewNewVoxels.end() && bld->get_material_id((*lp).first)  == mmid);
				else
				    zed += valuel[counter];
			}
			unsigned int cubeindex = 0;
			unsigned int cubeindextwo = 0;
			// The cubeindex is used to help smooth the terrain using neighboring terrain as input
			{
					for(int ctr = 0; ctr <= 14; ctr++) {
						if(ctr != 13) {
							vec3 vpos = temp_v+neighbor_list[ctr];
							Chunk *bc = qgetChunk(vpos.toOgre());
						
							if(bc != NULL) {
								auto varp = (vpos+vec3(15,30,15))-bc->position;
								if(bc->voxel_exists(to_voxid(varp))) {
									cubeindex += valuel[ctr];
								}
							}
						}
					}
					for(int ctr = 0; ctr < 12; ctr++) {
						
							vec3 vpos = temp_v+neighbor_list[ctr+15];
							Chunk *bc = qgetChunk(vpos.toOgre());
						
							if(bc != NULL) {
								auto varp = (vpos+vec3(15,30,15))-bc->position;
								if(bc->voxel_exists(to_voxid(varp))) {
									cubeindextwo += valuel[ctr];
								}
							}
					}	
			}
			c->mcWeights[(final_size)*3] = zed;
			c->mcWeights[((final_size)*3)+1] =cubeindex; // for now. later pass in edge list, EXTREMELY SIMILIAR to the above neighborlist, for awesomesauce marching cube geom shader which will smooth outh all the terrain and make it bad-ass.
			c->mcWeights[((final_size)*3)+2] =cubeindextwo; // for now. later pass in edge list, EXTREMELY SIMILIAR to the above neighborlist, for awesomesauce marching cube geom shader which will smooth outh all the terrain and make it bad-ass.
			float mid = float(mmid);
			float yid = 0.0f;
			if(mid == 19) yid = 1;
			if(mid == 25) yid = 1;
			if(mid >= 128) {
				mid -=128;
				yid = 1;
			}
			final_size++;
			if(mmid == 31 || mmid == 21) {
#ifndef SERVER
				/*std::stringstream ls;
				ls << "light_autogen_"<<(*iter).first<< c->id;
				try{
					//CState_Testing::ReturnInstance()->mSceneManager->getLight(ls.str().c_str());
				/// OH, I forgot, OGRE can't be manipulated cross threads. This needs to be moved out from here.
					// This is the cause of all the crashing. stupid me!.
					auto *Light = CState_Testing::ReturnInstance()->mSceneManager->createLight(ls.str().c_str());
					Light->setPosition(temp_v.toOgre());
					Light->setType(Ogre::Light::LT_POINT);
					Light->setVisible(true);
					Light->setDiffuseColour(1.0, 1.0, 1.0);
					Light->setSpecularColour(1.0, 1.0, 1.0);
					Light->setAttenuation(.5,1,1,.6);*/
					c->lights.push_back((*iter).first);
				/*} catch(...) {
				}*/
#endif
			}
			Ogre::Root::getSingleton().getRenderSystem()->convertColourValue(Ogre::ColourValue(mid/255, yid,0,1.0f), color_inserter++);
		}
		c->vertex_count = final_size;
		return;
	}
	volatile bool dbbreak() {
	      return true;
	}


};
voxel_drawer voxel_drawer::_int_draw = voxel_drawer();


void NewHeightmapLoader::transparent_roofs(inet_player *oldpdontuse) {
	// Better done via the camera position and player position in the shader.
	// The camera position is already set, the player position would need to be set per-frame
	// and would be passed as a uniform to the shaders.
	// Not only quicker, but easier to impliment, and more accurate.
	return;
	vec3 pnt2(vec3(player_position)+vec3(-2,3.5,-2));
	vec3 pnt1(vec3(player_position)+vec3(2,25.5,2));
	vec3 nodecimals((long long)player_position.x,(long long)player_position.y,(long long)player_position.z);
	nodecimals.floor();

	static vec3 last_pnt(0,.001,0);//, last_pnt2(0,0,0);
	if(last_pnt  == vec3(nodecimals)) return;//pnt1 && last_pnt2 
	last_pnt = vec3(nodecimals);
	if(transparented.pnts.size() != 0) {
		auto it = transparented.pnts.begin(), end = transparented.pnts.end();
		for(;it!=end;++it) {
			(*it).c->NewNewVoxels[(*it).idx].matid -= 128;
			(*it).c->cleanup();
		}
		transparented.pnts.clear();
	}
	editor_2pnt roofpnts;
	Chunk *c1, *c2;
	c1 = contains(pnt1);
	c2 = contains(pnt2);
	if(c2 != NULL) while(c1 == NULL && pnt1.y > pnt2.y) {
		pnt1 = pnt1-vec3(0,1,0);
		c1 = contains(pnt1);
		
	}
	if(c1 == NULL || c2 == NULL) return; // avoid segfault by introducing potential roof bug near high areas without a chunk over them.

	{
		vec3 temp_v = (pnt1-c1->position)+vec3(15,30,15);
		unsigned short idx = to_voxid(temp_v);
		roofpnts.setup(true, c1, idx);
		temp_v = (pnt2-c2->position)+vec3(15,30,15);
		idx = to_voxid(temp_v);
		roofpnts.setup(false, c2, idx);
	}
	if(roofpnts.c[0] != NULL && roofpnts.c[1] != NULL) roofpnts.set = true;
	static multipoint last;
	multipoint existing = roofpnts.all_existing_between(this);
	std::vector<multipoint::pnt>::iterator iter = existing.pnts.begin(), end = existing.pnts.end();
	for(;iter!=end;++iter) { 
		(*iter).c->cleanup(); 
		(*iter).c->NewNewVoxels[(*iter).idx].matid += 128; 
		transparented.pnts.push_back((*iter));
	}
}