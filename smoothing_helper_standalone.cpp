#include <iostream>
#include "include/generic_utilities.h"
/*
struct vec3 {
	template<class AA, class BB, class CC>
	vec3(const AA &_x, const BB &_y, const CC &_z) : x(_x),y(_y),z(_z) {}
	vec3(): x(0),y(0),z(0){}
	float x,y,z;
	void print() {
		std::cout <<"CVEC3("<< x << "," << y << "," << z << ")";
	}
};
*/
static vec3 cubeVerts[8] = {
	vec3(-0.5, -0.5, 0.5), vec3(-0.5,0.5,0.5), vec3(-0.5,-0.5,-0.5), vec3(-0.5,0.5,-0.5),
	vec3(0.5, -0.5, 0.5), vec3(0.5,0.5,0.5), vec3(0.5,-0.5,-0.5), vec3(0.5,0.5,-0.5)
};
static vec3 cubeVerts2[8] = {
        vec3(-1.0, -1.0, 1.0), vec3(-1.0,1.0,1.0), vec3(-1.0,-1.0,-1.0), vec3(-1.0,1.0,-1.0),
        vec3(1.0, -1.0, 1.0), vec3(1.0,1.0,1.0), vec3(1.0,-1.0,-1.0), vec3(1.0,1.0,-1.0)
};


vec3* gen_array() {
	static vec3 array_base[27];
	static bool init=false;
	if(!init) {
		int count = 0;
		for(float x = -1;x<2;x++) 
			for(float y = -1;y<2;y++) 
				for(float z =-1;z<2;z++) {
					array_base[count] = vec3(x,y,z);
					++count;
				}
		init = true;
		return array_base;	
	} else {
		return array_base;
	}
}
#define GOREAL float
#include <cmath>
float _get3d_vecdistref(const vec3 &p, const vec3 &y) {
		GOREAL c_x = p.x-y.x;
		GOREAL c_y = p.y-y.y;
		GOREAL c_z = p.z-y.z;
		return sqrt((c_x*c_x)+(c_y*c_y)+(c_z*c_z));
}
#include <sstream>
void verts_neighboring_cubes(vec3* neighbors) {
	std::stringstream output;
	for(int x = 0; x < 8; x++) {
//		output << "if(";
		bool first = true;
		int ex[4];
		int yi[4];
		int ze[4];
		int excount=0;
		int yicount=0;
		int zecount=0;
		for(int y = 0; y < 27; y++) {
			if(y==13)continue;
			float dist; 
			if( (dist = _get3d_vecdistref(neighbors[y],cubeVerts[x])) < 1) {
				if(cubeVerts2[x].x == neighbors[y].x) { ex[excount]=y; excount++; }
				if(cubeVerts2[x].y == neighbors[y].y) { yi[yicount]=y; yicount++; }
				if(cubeVerts2[x].z == neighbors[y].z) { ze[zecount]=y; zecount++; }
			}
			std::cout << dist << " ";
			
			
		}
		std::cout << "\n";

		output << "if(!neighbors["<<ex[0]<<"] && !neighbors["<<ex[1]<<"] && !neighbors["<<ex[2]<<"] && !neighbors["<<ex[3]<<"]) { cubeVerts["<<x<<"].x = cubeVerts["<<x<<"].x*0.15; }\n";
		output << "if(!neighbors["<<yi[0]<<"] && !neighbors["<<yi[1]<<"] && !neighbors["<<yi[2]<<"] && !neighbors["<<yi[3]<<"]) { cubeVerts["<<x<<"].y = cubeVerts["<<x<<"].y*0.15; }\n";
		output << "if(!neighbors["<<ze[0]<<"] && !neighbors["<<ze[1]<<"] && !neighbors["<<ze[2]<<"] && !neighbors["<<ze[3]<<"]) { cubeVerts["<<x<<"].z = cubeVerts["<<x<<"].z*0.15; }\n";
	}
std::cout << output.str();
}

void vertex_normal_gen() {
	vec3* neighbors = gen_array();
	const int cubeFaceIndices[24] = {
		1,0,5,4, //front  
		6,2,7,3, // back
	//	3,1,7,5, // top 
		7,3,5,1,
		4,0,6,2,  //bottom
		5,4,7,6,  //right
		0,1,2,3  // left
	}; 
	std::vector<vec3> normals;
	for(int i = 0; i<8; i++) {
	    vec3 normal = vec3(0,0,0);
	    for(int j = 0; j < 24; j+=4) {
		if(cubeFaceIndices[j]  == i ||cubeFaceIndices[j+1]  == i ||cubeFaceIndices[j+2]  == i) {
		  //vec3 tria = vec3(j,j+1,j+2);
		  
		  vec3 p0 = cubeVerts[cubeFaceIndices[j]];
		  vec3 p1 = cubeVerts[cubeFaceIndices[j+1]];
		  vec3 p2 = cubeVerts[cubeFaceIndices[j+2]];
		  
		  vec3 tb = p1-p0;
		  vec3 tc = p2-p0;
		  vec3 td = p2-p1;
		  
		  
		  normal += tb.cross_product(tc);
		  
		}
		if(cubeFaceIndices[j+1]  == i ||cubeFaceIndices[j+2]  == i || cubeFaceIndices[j+3]  == i) {
		  
		  //vec3 trib = vec3(j+2,j+3,j+4);
		   vec3 p1 = cubeVerts[cubeFaceIndices[j+1]];
		  vec3 p2 = cubeVerts[cubeFaceIndices[j+2]];
		  vec3 p3 = cubeVerts[cubeFaceIndices[j+3]];
		  vec3 td = p2-p1;
		  vec3 te = p3-p1;
		  
		  
		  normal += td.cross_product(te);
		}
	    }
	    normal=normal/8;
	    std::cout << "Normal " << i << normal.print("Normal") << "\n";
	}
}
int main() {
	vec3* array = gen_array();
	 std::cout.precision(1);
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	for(int x = 0; x < 27; x++) {
		array[x].print();
		if(x!=26) {std::cout << ", "; if(x%4==0) std::cout << "\n"; }
	}
	std::cout << "\n\n";
	verts_neighboring_cubes(array);
	cubeVerts[0].x = cubeVerts[0].x * .125;
	vertex_normal_gen();
	
	return 0;
}
