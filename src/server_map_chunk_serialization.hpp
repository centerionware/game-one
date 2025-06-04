volatile bool is_big_endian(void)
{
short var = 0x1;  
return  (((char *)&var)[0] > 0) ? false : true;


}

unsigned char
bytereverse(register unsigned char v)
{
  // http://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64BitsDiv
return (v * 0x0202020202ULL & 0x010884422010ULL) % 1023;

}


void* reverse(void *optr, size_t s) {
        unsigned char *d = (unsigned char*)optr;
        size_t ds = s;
        for(;s!=0;--s) {
                unsigned char input = (unsigned char)(*d);
                unsigned char &output = (unsigned char&)(*d);
                output = bytereverse(input);
                ++d;
        }
        --d;
        unsigned char *l = (unsigned char *)optr;
        for(;ds!=0&&d!=l;--(--ds)) {
                unsigned char vv = *l;
                *l = *d;
                *d = vv;
                ++l;
                --d;
        }
        return optr;
}
/* Warning! endiansafe_memcpy will alter the original in the case of a big endian machine. Do not re-use the o pointer after calling for safety.
Use whatever you copied it into.
*/
void endiansafe_memcpy(void *t, const void*o, size_t s) {
        if(is_big_endian()) {
                memcpy(t,reverse(const_cast<void*>(o), s), s);
        } else {
                memcpy(t,o,s);
        }
}


// This ensures the memory isn't leaked when the program exits, in cases where the operating system isn't smart enough to clean up new'd memory. (Older fedora systems had this problem)
// Please note, I'm not blaming fedora. It was most likely the kernels being used.
std::string basic_chunk_update::serialize() {
    std::string r;
    unsigned int tmp;
	char idarr[sizeof(unsigned int)];
	char farr[sizeof(float)];
	
	memcpy(idarr, &chunk.id, sizeof(unsigned int));
	r.append( idarr, sizeof(unsigned int) );
	memcpy(idarr, &timestamp, sizeof(unsigned int));
	r.append ( idarr, sizeof(unsigned int) );
	
	
	memcpy(farr, &chunk.x, sizeof(float));
	r.append( farr,sizeof(float) );
	memcpy(farr, &chunk.y, sizeof(float));
	r.append( farr,sizeof(float) );
	memcpy(farr, &chunk.z, sizeof(float));
	r.append( farr,sizeof(float) );
	
	tmp = chunk.voxels.size();
	memcpy(idarr,&tmp, sizeof(unsigned int));
	r.append ( idarr,sizeof(unsigned int) ); 
	for(size_t i = 0; i < chunk.voxels.size(); i++) {
		char varr[sizeof(unsigned short)];
		memcpy(varr,&(chunk.voxels[i]) , sizeof(unsigned short));
		r.append(varr,sizeof(unsigned short));
	}
	tmp= chunk.matids.size();
	memcpy(idarr,&tmp , sizeof(unsigned int));
	r.append ( idarr, sizeof(unsigned int) ); 
	for(size_t i = 0; i < chunk.matids.size(); i++) {
	  	char varr[sizeof(unsigned char)];
		memcpy(varr,&(chunk.matids[i]) , sizeof(unsigned char));
		r.append(varr,sizeof(unsigned char));
	      
	}
	tmp=  removed_voxels.size();
	memcpy(idarr,&tmp , sizeof(unsigned int));
	r.append ( idarr, sizeof(unsigned int) ); 
	for(size_t i = 0; i < removed_voxels.size(); i++) {
	  	char varr[sizeof(unsigned short)];
		memcpy(varr,&(removed_voxels[i]) , sizeof(unsigned short));
		r.append(varr,sizeof(unsigned short));
	}
	    
    return r;
  }
  #define NET_MESSAGE_SIZE 4 /*sizeof(unsigned int) on the server(32-bit) */
  basic_chunk_update basic_chunk_update::deserialize(std::string in) {
      basic_chunk_update r;
      
      unsigned int strptr = 0;
      endiansafe_memcpy(&r.chunk.id, (in.substr(0,  NET_MESSAGE_SIZE).c_str()) ,NET_MESSAGE_SIZE);
      strptr += NET_MESSAGE_SIZE;
      endiansafe_memcpy(&r.timestamp, in.substr(strptr,  NET_MESSAGE_SIZE).c_str(),NET_MESSAGE_SIZE);
      strptr += NET_MESSAGE_SIZE;
      
      endiansafe_memcpy(&r.chunk.x, in.substr(strptr,  sizeof(float)).c_str(),sizeof(float));
      strptr += sizeof(float);
      endiansafe_memcpy(&r.chunk.y, in.substr(strptr,  sizeof(float)).c_str(),sizeof(float));
      strptr += sizeof(float);
      endiansafe_memcpy(&r.chunk.z, in.substr(strptr,  sizeof(float)).c_str(),sizeof(float));
      strptr += sizeof(float);
      
      unsigned int vsize;
      endiansafe_memcpy(&vsize, in.substr(strptr,  NET_MESSAGE_SIZE).c_str(),NET_MESSAGE_SIZE);
      strptr+= NET_MESSAGE_SIZE;
      for(unsigned int i = 0; i < vsize; ++i) {
	      unsigned short voxid;
	      endiansafe_memcpy(&voxid, in.substr(strptr,  sizeof(unsigned short)).c_str(),sizeof(unsigned short));
	      r.chunk.voxels.push_back(voxid);
	      strptr += sizeof(unsigned short);
      }
     // endiansafe_memcpy(&vsize, in.substr(strptr,  NET_MESSAGE_SIZE).c_str(),NET_MESSAGE_SIZE);
      strptr+= NET_MESSAGE_SIZE;
      for(unsigned int i = 0; i < vsize; ++i) {
	      unsigned char voxid;
	      endiansafe_memcpy(&voxid, in.substr(strptr,  sizeof(unsigned char)).c_str(),sizeof(unsigned char));
	      r.chunk.matids.push_back(voxid);
	      strptr += sizeof(unsigned char);
      }
      endiansafe_memcpy(&vsize, in.substr(strptr,  NET_MESSAGE_SIZE).c_str(),NET_MESSAGE_SIZE);
      strptr+= NET_MESSAGE_SIZE;
      for(unsigned int i = 0; i < vsize; ++i) {
	      unsigned short voxid;
	      endiansafe_memcpy(&voxid, in.substr(strptr,  sizeof(unsigned short)).c_str(),sizeof(unsigned short));
	      r.removed_voxels.push_back(voxid);
	      strptr += sizeof(unsigned short);
      }
      return r;
  }
  basic_chunk_update& basic_chunk_update::merge(basic_chunk_update&other) {
   basic_chunk_update &newest = this->timestamp > other.timestamp ? *this : other;
   basic_chunk_update &oldest = &newest == this ? other : *this;
   
   std::map<unsigned short, unsigned char> matids;
   std::map<unsigned short, bool> voxids;
   
   static basic_chunk_update output;
   output = basic_chunk_update();
   output.chunk.id = other.chunk.id;
   
   output.chunk.x = other.chunk.x;
   output.chunk.y = other.chunk.y;
   output.chunk.z = other.chunk.z;
   
   auto it = oldest.chunk.voxels.begin(), ie = oldest.chunk.voxels.end();
   auto lt = oldest.chunk.matids.begin(), le = oldest.chunk.matids.end();
   for(;it!=ie;++it,++lt) {
      voxids[(*it)] = true;
      matids[(*it)] = (*lt);
   }
   it = newest.chunk.voxels.begin(), ie = newest.chunk.voxels.end();
   lt = newest.chunk.matids.begin(), le = newest.chunk.matids.end();
   for(;it!=ie;++it,++lt) {
      voxids[(*it)] = true;
      matids[(*it)] = (*lt);
   }
   it = newest.removed_voxels.begin(), ie = newest.removed_voxels.end();
   for(;it!=ie;++it) {
	voxids[(*it)] = false;
   }
   auto outit1 = voxids.begin(), outendit = voxids.end();
   for(;outit1!=outendit;++outit1) {
	  if( (*outit1).second == true) {
		output.chunk.voxels.push_back( (*outit1).first);
		output.chunk.matids.push_back( matids[(*outit1).first]);
	  }
   }
   output.timestamp = newest.timestamp;
   return output;
  }