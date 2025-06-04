inline bool is_xz_contained(unsigned char cnt, unsigned short in_walls,unsigned char cmp,unsigned short inset, unsigned short wall_spacing,unsigned short*arr) {
      if(arr[cnt]>=in_walls) {
	return cmp > inset+(arr[cnt]*wall_spacing) && cmp < 30-(inset);
      } else {
	return cmp > inset+(arr[cnt]*wall_spacing) && cmp < (inset+(arr[cnt]*wall_spacing)+wall_spacing);
      }
}
inline bool xz_isadoor(unsigned short y, unsigned char &cmp, unsigned short &doorpose) {
	return y<=3&&cmp==doorpose;
}
inline bool xz_isawall(unsigned char &cmp, unsigned short &inset, unsigned short &my_spacing, unsigned char &cnt) {
	return cmp== inset+(my_spacing*cnt);
}
unsigned short gen_xz_walls(unsigned short first_doorpos,short (&matrix)[31][63][31], unsigned short inset, unsigned short roofheight, \
			  unsigned short inside_x_walls, unsigned short xwall_spacing, unsigned short inside_z_walls, \
			  unsigned short zwall_spacing, unsigned short floors, bool am_x) {
/**
    There is something off in here where it makes thin walls against the outside without doors, in the loop in the else {}
**/

	unsigned short wall_tex_array[] = {26,27,28,29,34,10,13};
	
	unsigned short walltex = wall_tex_array[(rand() % msize(wall_tex_array))];
	unsigned char cnt = 0;
	unsigned short r = 0;
	//std::cout <<"Inside xz walls: " << inside_x_walls << std::endl;
	unsigned char x,y,z;
	unsigned char &cmp = am_x ? x : z;
	unsigned char &ocmp = am_x ? z : x;
	unsigned short &my_walls = am_x ? inside_x_walls : inside_z_walls;
	unsigned short &other_walls = am_x ? inside_z_walls : inside_x_walls;
	unsigned short &my_spacing = am_x ? xwall_spacing : zwall_spacing;
	unsigned short &other_spacing = am_x ? zwall_spacing : xwall_spacing;
	
	if(first_doorpos == 0 || other_walls == 0) {
		unsigned short doorpos = rand()%30;
		if(doorpos<=inset+1)doorpos+=(inset+3);
		if(doorpos+inset+1 >= 30) doorpos -=(inset+3);
		r = doorpos;
		for(x=0,y=1,z=0;x<31;++x,y=1,z=0)for(y=1;y<63;++y,z=0)for(z=0;z<31;++z) {
			if(!(y>=roofheight))
			if((ocmp >=inset+1 && ocmp <=30-(inset+1))) 
			if(!( (y==0 || (y<=3 && ocmp == doorpos)) ))
			for(cnt=1;cnt<=my_walls;++cnt) if(cmp == inset+(my_spacing*cnt) ) matrix[x][y][z] = walltex;
		}
	} else {
		/** Now things get a tad harder. Need to generate walls between the existing walls, without crossing into them, ensuring
		    that the generated doorway is still on that new wall. **/
		unsigned short *arr = new unsigned short[my_walls+1];
		unsigned short *doorposes = new unsigned short[my_walls+1];
		for(cnt=0;cnt<=my_walls;cnt++) {
			arr[cnt] = (rand()%(other_walls+1));
			// rand from max 30-(inset+(arr[cnt]*zwall_spacing) to min inset+(arr[cnt]*zwall_spacing)
			doorposes[cnt] = ((rand() % (other_spacing-2))+inset+(arr[cnt]*other_spacing))+1;
		}
		for(x=0,y=1,z=0;x<31;++x,y=1,z=0)for(y=1;y<63;++y,z=0)for(z=0;z<31;++z) {
		      if(!(y>=roofheight)) 
			for(cnt=1;cnt<=my_walls;++cnt) 
			  if( !xz_isadoor(y,ocmp,doorposes[cnt]) \
			  && is_xz_contained(cnt,other_walls,ocmp,inset,other_spacing,arr) \
			  && cmp!=first_doorpos \
			  && xz_isawall(cmp, inset, my_spacing, cnt) ) matrix[x][y][z]=walltex; 
		}
		delete[] doorposes;
		delete[] arr;
	} 
	return r;
}

void gen_inside_walls(short (&matrix)[31][63][31], unsigned short inset, unsigned short roofheight, unsigned short inside_x_walls, \
		      unsigned short xwall_spacing, unsigned short inside_z_walls, unsigned short zwall_spacing, unsigned short do_xwalls_first,unsigned short floors) {
	if(do_xwalls_first) {
	  gen_xz_walls(gen_xz_walls(0, matrix,inset,roofheight,inside_x_walls,xwall_spacing,inside_z_walls,zwall_spacing,floors,true) \
	  ,matrix,inset,roofheight,inside_x_walls,xwall_spacing,inside_z_walls,zwall_spacing,floors,false);
	} else {
	  gen_xz_walls(gen_xz_walls(0, matrix,inset,roofheight,inside_x_walls,xwall_spacing,inside_z_walls,zwall_spacing,floors,false) \
	  ,matrix,inset,roofheight,inside_x_walls,xwall_spacing,inside_z_walls,zwall_spacing,floors,true);
	
	}
}
#include <algorithm>
std::string NewHeightmapLoader::editor_stair_gen1() {
 std::string r;
 
 std::cout << "Editor stair gen\n";
 if(selectedChunk == NULL) return r;
 std::cout << "MAde it past selectedChunk\n";
 /**
	    The basic idea here, each chunk is 31x63x31 individual voxels (It just is okay)
	    So, create a 31x63x31 matrix, set each element to -1
	    Then if we want to create something (Say a street), we set the x,y,z in the matrix to the texture number of blacktop.
	    
	**/
	
	short matrix[31][63][31]; /// Our 31x63x31 matrix
	{ ///Initialize that matrix to -1
	  signed short n = -1;
	  for(unsigned char x=0,y=0,z=0;x<31;++x,y=0,z=0)for(y=0;y<63;++y,z=0)for(z=0;z<31;++z) matrix[x][y][z] = n;
	  
	}
	unsigned char x,y,z; /// used for scrolling though the for loop
	signed short selected_x,selected_y,selected_z;
	{
	  int j = 31;
	  int k = j*j;
	selected_y = selectedVoxel/(31*31);
	selected_x = (selectedVoxel - selected_y*k)/j;
	selected_z = selectedVoxel - selected_y*k - selected_x*j;
	/*selected_x+= 15;
	selected_z+= 15;
	selected_y+= 31;
	*/
	std::cout << "Selected_Y(" << selected_y << ") Selected_z("<<selected_z<<") Selected_x("<<selected_x<<")"<<std::endl;
	}
	unsigned char mgic = selected_y<31?0:31;
	/** The magic loop. **/
	for(x=0,y=0,z=0;x<31;++x,y=0,z=0)for(y=0;y<63;++y,z=0)for(z=0;z<31;++z) {
		if(x+mgic == y && z == selected_z) matrix[x][y][z] = 1;
	}
		/// Convert the short matrix[31][63][31] to a basic_chunk_update.
	basic_chunk_update up;
	up.chunk.x = selectedChunk->position.x;
	up.chunk.y = selectedChunk->position.y;
	up.chunk.z = selectedChunk->position.z;
	up.chunk.id = selectedChunk->id;
	
	for(x=0,y=0,z=0;x<31;++x,y=0,z=0)for(y=0;y<63;++y,z=0)for(z=0;z<31;++z)
		if(matrix[x][y][z] != -1) {
			vec3 pos(x,y,z);
			up.chunk.voxels.push_back(to_voxid(pos));
			up.chunk.matids.push_back(matrix[x][y][z]);
			
		}
	return up.serialize();
}
std::string NewHeightmapLoader::editor_building_gen1() {
	/**
	    The basic idea here, each chunk is 31x63x31 individual voxels (It just is okay)
	    So, create a 31x63x31 matrix, set each element to -1
	    Then if we want to create something (Say a street), we set the x,y,z in the matrix to the texture number of blacktop.
	    
	**/
	static bool do_undo = true; // Allow the very last generated chunk to be un-generated. Very useful.
	std::string r;
	if(selectedChunk == NULL) return r;
	{
		static Chunk *lc = NULL;
		if(lc != NULL && selectedChunk != lc) do_undo = true; /// Don't undo if the last chunk gen'd on wasn't this chunk.
		lc = selectedChunk;
	}
	short matrix[31][63][31]; /// Our 31x63x31 matrix
	{ ///Initialize that matrix to -1
	  signed short n = -1;
	  for(unsigned char x=0,y=0,z=0;x<31;++x,y=0,z=0)for(y=0;y<63;++y,z=0)for(z=0;z<31;++z) matrix[x][y][z] = n;
	  
	}
	unsigned char x,y,z; /// used for scrolling though the for loop
	/// Variables that effect the outcome of the generated building. Use static and set inside if to allow undo of the last one.
	/// These must stay the same or the generated voxel id's will vary over the do/undo cycle.
	/// 
	/// Later I plan on adding an undo/redo system inside the server itself, so nothing on the client will be needed except
	/// hotkeys or undo/redo mode..
	static unsigned short inset = rand() %6+3; // outside wall
	static unsigned short roofheight = rand() %6+5;
	static unsigned short doorside = rand()%4;
	static unsigned short doorpos = rand()%30;
	static unsigned short maxroofheight=rand()%10;
	static unsigned short inside_x_walls = rand()%3;
	static unsigned short inside_z_walls = rand()%3;
	static unsigned short xwall_spacing = (rand()%5)+3;
	static unsigned short zwall_spacing = (rand()%5)+3;
	static unsigned short floors = rand()%5;
	static bool do_xwalls_first = rand()%2==0?true:false;
	if(do_undo) {
	      inset = rand() %6+3;
	      roofheight = rand() %6+5;
	      doorside = rand()%4;
	      doorpos = rand()%30;
	      maxroofheight=rand()%(30-((inset+1)*2));
	      inside_x_walls = rand()%3;
	      inside_z_walls = rand()%3;
	      do_xwalls_first = rand()%2==0?true:false;
	      xwall_spacing = (rand()%5)+3;
	      zwall_spacing = (rand()%5)+3;
	      floors = rand()%5;
	      
	}
//	inside_x_walls = 3;
//	inside_z_walls = 3;
	if(doorside>=4)doorside=3;
	  
	if(doorpos>=30-(inset+1))doorpos-=(inset+3); /// Prevent outside door from not being on the building wall
	if(doorpos<=inset+1)doorpos+=(inset+3); /// Prevent outside door from not being on the building wall
	if(roofheight<4)roofheight=4;
	/// Variables that effect the texture outcome of the building
	unsigned short grass_tex_array[] = {0,1,2,3,4,5,21};
	unsigned short wall_tex_array[] = {26,27,28,29,34,10,13};
	unsigned short floor_tex_array[] = {29,30,32,33,35,40,8,12};
	unsigned short roof_tex_array[] = {24,26,27,28,29,30,32,34,4};
	unsigned short glass_tex_array[] = {19,25};
	
	
	unsigned short walltex = wall_tex_array[(rand() % msize(wall_tex_array))];
	unsigned short grasstex = grass_tex_array[(rand() % msize(grass_tex_array))];
	unsigned short floortex = floor_tex_array[(rand() % msize(floor_tex_array))];
	unsigned short glasstex = glass_tex_array[(rand() % msize(glass_tex_array))];
	unsigned short rooftex = roof_tex_array[(rand() % msize(roof_tex_array))];
	
	/** The magic loop. **/
	for(x=0,y=0,z=0;x<31;++x,y=0,z=0)for(y=0;y<63;++y,z=0)for(z=0;z<31;++z) {
		/** Draw the streets **/
		if(y==0&&( (x==0||x==2||x==30||x==28) || (z==0||z==2||z==30||z==28)) ) matrix[x][y][z] = 18; // street black
		else if(y==0&&((x==1||x==29) && !(z==1||z==29))) matrix[x][y][z] = 16;  // street striped vert
		else if(y==0&&((z==1||z==29) && !(x==1||x==29))) matrix[x][y][z] = 17;  // street striped horiz
		else if(y==0&&((x==1||x==29) && (z==1||z==29))) matrix[x][y][z] = 18; // more blacktop.

		  /** Draw the grass **/
		else if(y==0&&(x<inset||z<inset)) matrix[x][y][z] = grasstex; // grass outside
		else if(y==0&&x==inset&&z<inset) matrix[x][y][z] = grasstex;
		else if(y==0&&z==inset&&x<inset) matrix[x][y][z] = grasstex;
		
		else if(y==0&&x==inset&&z>30-inset) matrix[x][y][z] = grasstex;
		else if(y==0&&z==inset&&x>30-inset) matrix[x][y][z] = grasstex;
		/** Draw the inside floors and some more grass **/ 
		else if(y==0&&(x>inset&&z>inset)) {
		      if(x+inset < 30 && z+inset < 30)
			    matrix[x][y][z] = floortex; // floor inside
		      else 
			    matrix[x][y][z] = grasstex; // More grass outside
		}
		/** Next 4 are the entrance way to the building.. **/
		else if(y==0&&doorside ==0 && (x==inset&&z==doorpos)) matrix[x][y][z] = floortex;
		else if(y==0&&doorside ==1 && (x==doorpos&&z==inset)) matrix[x][y][z] = floortex;
		else if(y==0&&doorside ==2 && (x==30-inset&&z==doorpos)) matrix[x][y][z] = floortex;
		else if(y==0&&doorside ==3 && (z==30-inset&&x==doorpos)) matrix[x][y][z] = floortex;
		/** Next 4 are the squares where the door should go **/
		else if(y<roofheight&&y<=3&&doorside ==0 && (x==inset&&z==doorpos)) continue;
		else if(y<roofheight&&y<=3&&doorside ==1 && (x==doorpos&&z==inset)) continue;
		else if(y<roofheight&&y<=3&&doorside ==2 && (x==30-inset&&z==doorpos)) continue;
		else if(y<roofheight&&y<=3&&doorside ==3 && (z==30-inset&&x==doorpos)) continue;

		/** All the windows in the walls **/
		else if(y>2 && y<roofheight-2&&(x==inset||z==inset||x==30-inset||z==30-inset)&&((x>=inset+3&&x<=30-(inset+3))&&(z>=inset&&z<=30-inset))) matrix[x][y][z] = glasstex; // windows
		else if(y>2 && y<roofheight-2&&(x==inset||z==inset||x==30-inset||z==30-inset)&&((x>=inset&&x<=30-(inset))&&(z>=inset+3&&z<=30-(inset+3)))) matrix[x][y][z] =glasstex; // windows
		/** All the walls **/
		else if(y<roofheight&&(x==inset||z==inset||x==30-inset||z==30-inset)&&((x>=inset&&x<=30-inset)&&(z>=inset&&z<=30-inset))) matrix[x][y][z] = walltex; // Walls...
		#define roof_diff (y-roofheight)
		#define is_inside_building(X) X<30-inset-roof_diff &&X>inset+roof_diff
		#define is_partof_roof y>=roofheight&&y<maxroofheight+roofheight
		#define is_stepping_partof_roof(X) ((X==inset+(roof_diff)+1||X==30-(inset+roof_diff)-1))
		  // The ceilings.
		else if(is_partof_roof && (is_stepping_partof_roof(x)||is_stepping_partof_roof(z)) && is_inside_building(z)&& is_inside_building(x)  ) matrix[x][y][z] = rooftex;

		else if(y>roofheight&&y==maxroofheight+roofheight&&((x>inset+maxroofheight&&z>inset+maxroofheight)&&(x+inset < 30-maxroofheight && z+inset < 30-maxroofheight))) matrix[x][y][z] = rooftex;
	}
	gen_inside_walls(matrix,inset,roofheight,inside_x_walls,xwall_spacing,inside_z_walls,zwall_spacing,do_xwalls_first,floors);
	
	/// Convert the short matrix[31][63][31] to a basic_chunk_update.
	basic_chunk_update up;
	up.chunk.x = selectedChunk->position.x;
	up.chunk.y = selectedChunk->position.y;
	up.chunk.z = selectedChunk->position.z;
	up.chunk.id = selectedChunk->id;
	
	for(x=0,y=0,z=0;x<31;++x,y=0,z=0)for(y=0;y<63;++y,z=0)for(z=0;z<31;++z)
		if(matrix[x][y][z] != -1) {
			vec3 pos(x,y,z);
			if(do_undo) { /// Apply the do/undo stuff here...
				up.chunk.voxels.push_back(to_voxid(pos));
				up.chunk.matids.push_back(matrix[x][y][z]);
			} else {
				up.removed_voxels.push_back(to_voxid(pos));
				
			}
		}
	/// Set undo mode by turning do_undo to false, which may be reset back to true if the last chunk is not the next chunk clicked on.
	if(do_undo)do_undo = false;
	else do_undo = true;
	return up.serialize();
}
