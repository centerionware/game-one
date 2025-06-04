

struct a_door {
	int x,z;
};

#include <algorithm>
/***
@name editor_circle_scraper_gen1
@bugs not suitable for autogeneration. Must have provided 2 pnt selections 

@value pnt1 the first selected point
@value pnt2 the second selected point


*/
std::vector<std::string> NewHeightmapLoader::editor_circle_scraper_gen1(vec3 pnt, int radius) {
	/**
	   Build a circular or semi-circular skyscraper, with multiple floors, and stairs between the floors. 
	   Walls optional for now.




	**/
	int diam = (radius*2);
	std::vector<std::string> r;
	if(selectedChunk == NULL) {
	std::cout << "Selected chunk was null? Wtf?!\n";	
		return r;
	}
	{
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
		static unsigned short tube_height = rand()%(120-70)+70;
		bool flattop = rand()%1==0?false:true;
		static unsigned short roof_curverate = rand()%(4-1)+1; // only used if flattop=false
		// First, get worldspace of identity 'voxel'
		multipoint pntcontainer;
		multi_chunk_updates output;
		int radiusp1 = radius + 1;
		for(int x=-radiusp1,y=0,z=-radiusp1;x<radiusp1;++x)for(y=0;y<63*2;++y)for(z=-radiusp1;z<radiusp1;++z) {
			multipoint mp;
			int distance_to_centre = sqrt(float((x)*(x) + (z)*(z)));
			if (distance_to_centre == radius && y < tube_height) {
				//std::cout << "NEw point found!\n";
				vec3 np = pnt+vec3(x,y,z);
				Chunk *mc = NULL;
				unsigned short idx;
				if( !NewHeightmapLoader::get_instance()->is_voxel(np, idx, mc) ) {
					//std::cout << "Adding voxel\n";
					chunkvox l = add_voxel(np);
					mc = l.c;
					idx = l.idx;
				}
				//std::cout << "New point: " << idx << std::endl;
				multipoint::pnt newpnt(mc, idx);
				mp.pnts.push_back(newpnt);
				mp.tex = walltex;
				output.add(mp,newpnt);
			}
		}
		auto v = output.serialize_all();
		//std::cout << "Returning " << output.updates[0].chunk.voxels.size() << " voxels in first chunk to update\n";
		return output.serialize_all();
	}

}
