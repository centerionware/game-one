
//http://www.tenouk.com/Module41.html

/*******select.c*********/
/*******Using select() for I/O multiplexing */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "inet.h"
#include "command.h"
#define DISABLE_DEBUG
#include "database_utilities.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

#include <fstream>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

/* port we're listening on */
MySQL_Helper database_connection;
using namespace boost::iostreams;

struct storage_device {
    vec3 position;
    
    struct voxel {
      unsigned short idx;
      unsigned char color;
      unsigned short fixed;
    };
    std::vector<voxel> voxels;
    void verify_position() {
	vec3 &v = position;
      	vec3 chunk_containing_v = vec3(0,0,0); // First chunk is at 14,0,0.. why not 0,0,0? I don't fucking know..
	vec3 offset(((unsigned int)std::fabs(v.x))/31,((unsigned int)std::fabs(v.y))/61,((unsigned int)std::fabs(v.z))/31);
	std::cout << offset.print("After modulus") << std::endl;
	
	if(v.x < 0) offset.x = offset.x*-1;
	if(v.y < 0) offset.y = offset.y*-1;
	if(v.z < 0) offset.z = offset.z*-1;
	std::cout << offset.print("After negativize") << std::endl;
	chunk_containing_v = offset*31;//.set(xoff*31,yoff*61,zoff*31);
	std::cout << chunk_containing_v.print("After multiply") << std::endl;
	//if(v.x < 0) 
	//  chunk_containing_v.x -= 14;
	//else 
	//  chunk_containing_v.x += 14; 
	if(v!= chunk_containing_v) {
	  std::cout <<v.print("Position was") <<chunk_containing_v.print("Position to")<<std::endl;
	    std::cout << "Repairing broken chunk position.\n";
	    v = chunk_containing_v;
	}
	
    }
    void push_back(unsigned short idx, unsigned char color) {
	
	std::for_each(voxels.begin(),voxels.end(),[&](voxel&v){
	  if(v.idx == idx) { v.color=color; return; } 
	});
	voxel add;
	add.idx = idx;
	add.color = color;
	voxels.push_back(add);
    }
    
    unsigned short to_voxid(vec3 C) { return (floor(C.y)*31*31)+(floor(C.x)*31)+floor(C.z); }
    vec3 from_voxid(unsigned short idx) {
	    int j = 31;
	    int k =j*j;
	    signed short y = idx/(k);
	    signed short x = (idx - y*k)/j;
	    signed short z = idx - y*k - x*j;
	    return vec3(x,y,z);
    }

    void fix_voxels() {
	std::for_each(voxels.begin(),voxels.end(),[&](voxel&v){
	  v.fixed = to_voxid( vec3(0,-30,0)+from_voxid(v.idx));
	});
    }
};
std::vector<storage_device> allChunks;
size_t orig_count;
void fill_allChunks() {
  std::string dataFilename = "../data/heightmap.3.voxmap.gz";
	//size_t import_count = 0;	
	std::ifstream myrfile(dataFilename.c_str());
	std::stringstream myfile;
	filtering_streambuf<input> in;
	in.push(gzip_decompressor());
	in.push(myrfile);
	boost::iostreams::copy(in,myfile);
	myrfile.close();
	myfile.seekg(0,std::ios::end);
	size_t count = myfile.tellg();
	size_t ccount;
	count = count-(sizeof(size_t)*2);
	
	myfile.seekg(count,std::ios::beg);

	int xk1 = sizeof(size_t), xk2 = sizeof(float)*3, ushort=sizeof(unsigned short);
//	int ind_length = xk2+xk3+xk4;
	char wk1[xk1],wk2[xk2];
	for(int y = 0;y<xk1;y++)
		myfile >> wk1[y];
	memcpy(&ccount, wk1, xk1);
	for(int y=0; y<xk1; y++) 
		myfile >> wk1[y];
	memcpy(&count, wk1, xk1); 
	orig_count = count;
	// count now contains the number of voxels
	// ccount contains the number of chunks
	
	myfile.seekg(0,std::ios::beg);
	
	std::cout << "Chunk count: " << ccount << " voxel count: " << count << std::endl;
	
	for(size_t x = 0; x < ccount; ++x) {
		float p[3];
		size_t i;
		//size_t chunk_id;//= row[0];
		myfile.read(wk2,xk2);
		memcpy(p, wk2,xk2);
		// extract the # of voxel entries in this chunk
		myfile.read(wk1,xk1);
		memcpy(&i, wk1,xk1);
		storage_device nc;
		nc.position.set(p[0],p[1],p[2]);
		nc.verify_position();
		std::cout << nc.position.print("Adding chunk")<<std::endl;
		allChunks.push_back(nc);
		for(size_t incount = 0; incount < i; ++incount) {
		
			unsigned short j;
			unsigned char matid;
			
			char igloo[ushort];
			myfile.read(igloo,ushort);
			memcpy(&j, igloo, ushort);
			
			myfile.read(igloo,sizeof(unsigned char));
			memcpy(&matid, igloo, sizeof(unsigned char));
			
			allChunks.back().push_back(j,matid);
			
		}
		
	}
}

void runDatabaseInserts() {
  
  std::string clear = "truncate Chunk_Voxels";
  database_connection.runQuery(clear);
  clear = "delete from Chunks";
  database_connection.runQuery(clear);
  
  size_t import_count = 0;
  size_t incount = 0;
  
 // clear = "start transaction";
 // database_connection.runQuery(clear);
 // clear = "commit";
  // Create a chunk in the database with position p. p = {x,y,z}
  // sql_insert(new chunk p[0],p[1],p[2]);..
  // get chunk_id response.
  char progress[] = { '/','|','\\','-' };
  unsigned char prog_pos = 0;
  unsigned char slowdowner = 0;
  std::string cs;
std::for_each(allChunks.begin(), allChunks.end(), [&](storage_device&item) {
      if(item.voxels.size() > 0) {
		std::stringstream chunk_insert_query;
		chunk_insert_query << "insert into Chunks (X,Y,Z) values("<< item.position.x << "," << item.position.y << "," << item.position.z << ")";
		//std::cout << chunk_insert_query.str() << std::endl;
		database_connection.query(chunk_insert_query.str());
		size_t chunk_id = mysql_insert_id(database_connection.connection);
		//std::cout << "Chunk id is " << chunk_id<<std::endl;;
		item.fix_voxels();
		if(chunk_id >=0) {

			std::stringstream voxel_insert_base;
			voxel_insert_base << "insert into Chunk_Voxels (chunk_id,voxid,matid) values";
			bool isFirst = true;
			clear = "start transaction";
			database_connection.runQuery(clear);
			clear = "commit";
			std::for_each(item.voxels.begin(), item.voxels.end(), [&](storage_device::voxel &vox) {
				
				if(!isFirst) {
					voxel_insert_base << ",("<<chunk_id<<","<<vox.fixed<<","<<(int)vox.color<<")";
				} else {
					isFirst = false;
					voxel_insert_base << "("<<chunk_id<<","<<vox.fixed<<","<<(int)vox.color<<")";
				}
				if(1){//incount%1==0) {
					cs = voxel_insert_base.str();
					//if(!ignore_chunk)
					while(database_connection.runQuery(cs) ==-1);
		//			std::cout << "Ran query " << cs << std::endl;
					voxel_insert_base.str("");// = std::stringstream();
					voxel_insert_base << "insert into Chunk_Voxels (chunk_id,voxid,matid) values";
					isFirst = true;
					std::cout <<progress[prog_pos]<<"\r";
					++slowdowner;
					if(slowdowner >30) {
						++prog_pos;
						if(prog_pos >3) prog_pos = 0;
						slowdowner = 0;
					}
				}
				++import_count;
				++incount;
			});

			cs = voxel_insert_base.str();
			if(cs.size() > 55) database_connection.runQuery(cs);
			database_connection.runQuery(clear);

		}
	}
	
});

  std::cout << "Tried to insert (" << import_count << ") individual voxels into the database.\n" << " Original voxel count: " << orig_count << std::endl;  
}


void runDatabaseUpdates() {
  std::string clear = "truncate Chunk_Voxels_backup";
  database_connection.runQuery(clear);
  clear = "delete from Chunk_Voxels_backup";
  database_connection.runQuery(clear);
  clear = "select into Chunks_backup select * from chunks";
  database_connection.runQuery(clear);
  clear = "select into Chunk_Voxels_backup select * from Chunk_Voxels";
  database_connection.runQuery(clear);
  
  size_t import_count = 0;
  size_t incount = 0;
  
 // clear = "start transaction";
 // database_connection.runQuery(clear);
 // clear = "commit";
  // Create a chunk in the database with position p. p = {x,y,z}
  // sql_insert(new chunk p[0],p[1],p[2]);..
  // get chunk_id response.
  //char progress[] = { '/','|','\\','-' };
  //unsigned char prog_pos = 0;
  unsigned char slowdowner = 0;
  
std::for_each(allChunks.begin(), allChunks.end(), [&](storage_device&item) {
      if(item.voxels.size() > 0) {
		std::stringstream chunk_insert_query;
		chunk_insert_query << "select id from Chunks (X,Y,Z) values("<< item.position.x << "," << item.position.y << "," << item.position.z << ")";
		//std::cout << chunk_insert_query.str() << std::endl;
		database_connection.query(chunk_insert_query.str());
		size_t chunk_id = 0;
		if(database_connection.numrows > 0) {
			#define streq(X,Y) std::string X; X.append(lmrow[Y],lengths[Y]);
			MYSQL_ROW& lmrow = database_connection.row();
			unsigned long *lengths = mysql_fetch_lengths(database_connection.result());
			streq(id,0)
			chunk_id = fromstring<size_t>(id);
		} 
		
		//std::cout << "Chunk id is " << chunk_id<<std::endl;;
		item.fix_voxels();
		if(chunk_id >=0) {

			std::stringstream voxel_update_base;
			
			
			clear = "start transaction";
			database_connection.runQuery(clear);
			clear = "commit";
			bool first = true;
			std::for_each(item.voxels.begin(), item.voxels.end(), [&](storage_device::voxel &vox) {
				//voxel_update_base << "update Chunk_Voxels set voxid='"<<vox.fixed->idx<<"' where voxid='"<<vox.idx<<"';";
				if(first) {
				      voxel_update_base << "delete from Chunk_Voxels where voxid='"<<vox.fixed<<"' or  voxid='"<<vox.idx<<"' ";
				      first = false;
				} else {
				  voxel_update_base << " or voxid='"<<vox.fixed<<"' or voxid='"<<vox.idx<<"'";
				}
				if(incount%1000==0) {
					database_connection.query(voxel_update_base.str());
					first = true;
					voxel_update_base.str("");
					std::cout << ".";
					std::cout.flush();
					++slowdowner;
					if(slowdowner >200) {
						slowdowner = 0;
						std::cout << "\r";
					}
				}
				++import_count;
				++incount;
			});
			
			//cs = voxel_insert_base.str();
			//if(cs.size() > 55) database_connection.runQuery(cs);
			if(voxel_update_base.str().size()!=0) database_connection.query(voxel_update_base.str());
			database_connection.runQuery(clear);

		}
	}
	
});

  std::cout << "Tried to insert (" << import_count << ") individual voxels into the database.\n" << " Original voxel count: " << orig_count << std::endl;  
}



int main(int argc, char *argv[])
{
	database_connection.setup("localhost","gameone","gameonedbpassword","GameOne");


//	std::streambuf* cout_sbuf = std::cout.rdbuf(); // save original sbuf
//	std::ofstream   fout("/dev/null");
//	std::cout.rdbuf(fout.rdbuf()); // redirect 'cout' to a 'fout'
	// ...
//	std::cout.rdbuf(cout_sbuf); // restore the original stream buffer
	
	fill_allChunks();
	runDatabaseInserts();
	
//	database_connection.close();

}


