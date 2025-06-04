
struct multipoint {
      struct pnt {
	Chunk *c;
	unsigned short idx;
	pnt(Chunk *_c, unsigned short &_idx) :c(_c),idx(_idx){}
	pnt(){}
	pnt(const pnt& o) : c(o.c),idx(o.idx) {}
      };
      std::vector<multipoint::pnt> pnts;
      unsigned char tex;
      bool contains(Chunk *c, unsigned short idx) {
	std::vector<multipoint::pnt>::iterator i = pnts.begin(), end = pnts.end();
	for(;i!=end;i++) if( (*i).c == c && (*i).idx == idx) return true;
	return false;
      }
};
static multipoint transparented;