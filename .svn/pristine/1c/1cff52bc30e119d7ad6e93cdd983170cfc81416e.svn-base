/********************************************************************************
NAMC - MMorpg Game System
Copyright (C) 2007 Matthew Adams

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
********************************************************************************/

#ifdef TOOLS_H
#else
#define TOOLS_H 1
#include <vector>
#include <string>
#include <fstream>
#include <Ogre.h>
#include <algorithm>
#include <cctype>       // std::toupper

#ifndef DWORD
#define DWORD unsigned long
#endif
enum { xplus, xminus, yplus, yminus, zplus, zminus, yjump, frun, fruno, none };

namespace Tools 
{
	struct UserData {
		enum { player, portal, unknown };
		int type;
		void *data;
	};
	struct shortSort
	{
		template<class t>
	bool operator()(t &s, t &e)
     {
          return s.num < e.num;
     }
	};
	enum 
	{
		ID_MOVEMENT  = 101,
		ID_NEW_PLAYER = 102,
		ID_MAP = 103,
		ID_PLAYERS = 104,
		ID_SETUPPLAYER = 105,
		ID_REMOTEPLAYER = 106,
		ID_BYEBYE,
		ID_HARDMOVE,
		ID_SYNCUP,
		ID_TIMESYNC
	}; 
	class PlayerEntity 
	{
	public:
		int index;
		bool local;
		int startspot; // location in startspots vector, that's sent along with map ^^
		Ogre::Vector3 position;
		Ogre::Quaternion orientation;
	};

	class MapEntHeader
	{
	public:
		unsigned char name1;
		unsigned char name2;
		unsigned char name3;
		unsigned char name4;

		unsigned char file1;
		unsigned char file2;
		unsigned char file3;
		unsigned char file4;

		unsigned long materialnamesize;
	};
	class MapEnt
	{
	public:
		unsigned char *name;
		unsigned char *modelfile;
		unsigned char *materialname;
		unsigned char type;
		unsigned char lighttype;
		Ogre::Vector3 position;
		Ogre::Vector4 diffuse, specular;
		Ogre::Quaternion orientation;
		int collide; // type of collision..
		Ogre::Vector3 scale;
		unsigned char mass[4];
		Ogre::Vector3 campos;
	} ;
	class Map
	{
	public:
		MapEntHeader head;
		MapEnt body;
	};
	// sfind, str2vec
	enum RType 
	{
        INT,
        FLOAT,
        DOUBLE,
        STRING,
        CHAR,
        CHARP,
        VOIDP,
        INTP
	};
	extern float movescale;
	class Attributes 
	{
        public:
        Attributes() { hidden = false; webbcmd = false; immcmd = false;};
        bool hidden; //hidden
        bool webbcmd; //web command
        bool immcmd; //immortal command
        int type;

        class returnType 
		{
                public:
                returnType(){;};
                returnType(const returnType &in) 
				{
                        if(in.s.size() > 0)
                        s.append(in.s);
                        d = in.d;
                        f = in.f;
                        i = in.i;
                        c = in.c;
                        cp = in.cp;
                        vp = in.vp;
                        ip = in.ip;
                }
                RType myType;
                std::string s;
                double d;
                float f;
                int i;
                char c;
                char *cp;
                void *vp;
                int *ip;
        };
        returnType _return;
	};

	inline size_t sfind(std::string &in, const char *seq, size_t startpos)
	{
		//return in.find(seq, startpos);
		if(startpos >= in.size()) return std::string::npos;
		static std::string seqbuf;
		seqbuf = seq;
		size_t end = in.size()-startpos;
		end++;
		size_t cur = startpos;
		size_t cursize = seqbuf.size();
		size_t curseq = 0;
		while(end-- != 0) 
		{
			if(cursize != 0) 
			{
				if(in[cur] == seqbuf[curseq]) curseq++,cursize--;
	            else if(curseq != 0) curseq=0,cursize=seqbuf.size();
			} else 
				return (cur-seqbuf.size());
			cur++;
	    }
	    return std::string::npos;
	}
	/*
	    This is a very generic strToVec and does format the original string.
	    it compensates for the difference between ms and linux files by completely ignoring \r (bad 4 binary)
	    and ignores \t.. 
	    
	    it's used in the basic command processor, beware of these issues!
	    Because of these issues, the command processor for the network layer uses 
	    a second call() that just makes the original input as the first element in the array
	    without any forwarding (skipping this function).
	*/
	inline std::vector<std::string> strToVec(std::string &in, bool newl = false, char delim = ' ') 
	{
			std::vector<std::string> strvec;
			{
					std::string::const_iterator scroller = in.begin(), end = in.end();
					//size_t last = 0, next = 0;
					bool quote = false;
					bool escape = false;
					std::string temp;
					for(scroller = in.begin(); scroller < end; scroller++)
					{
							if(escape) 
							{
									temp += *scroller;
									escape = false;
									continue;
							}
							if(*scroller=='\t')continue;
							if(*scroller == '\\') {escape = true; continue;} 
							if(*scroller=='\"') 
							{
									quote = !quote;
									continue;
							}
							if(*scroller==delim && !quote) 
							{
									if(temp.size() > 0)
									strvec.push_back(temp);
									temp.erase();
									continue;
							} 
							if( !newl) 
							{
									if(*scroller != '\r' && *scroller != '\n')
									temp += *scroller;
							}
							else 
								{ 
									if(*scroller == '\r') continue;
									if(*scroller == '\n') 
									{ 
										temp.append("\r\n");
										continue;
									} else temp += *scroller;
								}
	
					}
					if(temp.size() > 0) strvec.push_back(temp);
			}
//			if(strvec.size() == 0) 
//			{
//					std::string mpty = "\r\n";
//					strvec.push_back(mpty);
//			}
			return strvec;
	}
	inline void replaceAll(std::string &in, std::string with,std::string tok)
	{
		size_t x = in.find(tok);
		while(x != std::string::npos) {
			in.replace(x, tok.size(), with);
			x=in.find(tok, x+with.size());
		}
	}
	inline std::string str_replace(std::string in, std::string with,std::string tok)
	{
		size_t x = in.find(tok);
		while(x != std::string::npos) {
			in.replace(x, tok.size(), with);
			x=in.find(tok, x+with.size());
		}
		return in;
	}
	inline std::string readFile(std::string fname) {
#ifdef _WINDOWS
		replaceAll(fname, "\\", "/");
#endif
		std::ifstream in(fname.c_str(), std::ios::in);
		char c;
		std::string ret;
		while( in.get(c) ) ret += c;
		return ret;
	}

	inline std::string ValueFromString(std::string &cfg, std::string key) 
	{
		size_t x = cfg.find(key);
		if(x == std::string::npos) return "";
	
		std::ostringstream ffs; ffs<< std::endl;
		size_t y = cfg.find(ffs.str(),x);
		if(y == std::string::npos)  y = cfg.find("\n", x);
		if(y == std::string::npos) y = cfg.find((char)10,x);
		if(y == std::string::npos) y = cfg.size();
		x += key.size();
		return cfg.substr(x, y-x);
	}
	inline bool writeFile(std::string fname, std::string &output) {
	    std::ofstream outfile(fname.c_str(), std::ios::trunc);
		if(!outfile.is_open()) {
			
			return false;
		} else {
			outfile << output;
			outfile.close();
			return true;
		}
    }
	inline bool appendFile(std::string fname, std::string &output) {

	    std::ofstream outfile(fname.c_str(), std::ios::app);
		if(!outfile.is_open()) {
		
			return false;
		} else {
			outfile << output;
			outfile.close();
			return true;
		}
	}
	inline void Log(std::string output, std::string fname = "ogretest3.log") {
	
		appendFile(fname, output);
	};
	class BitConverter {
	public:
		/*
		// 11 | 00 | 00 | 00 = 192 = 0xC0
		// 00 | 11 | 00 | 00 = 48 = 0x30 
		// 00 | 00 | 11 | 00 = 12 = 0xC
		// 00 | 00 | 00 | 11 = 3 = 0x3

		// 01 | 00 00 00 = 64 = 0x40 + x
		// 10 | 00 00 00 = 128 = 0x80 -

		// 00 01 | 00 00 = 16 = 0x10 + y
		// 00 10 | 00 00 = 32 = 0x20 -
		
		// 00 00 01 | 00 = 4 = 0x04 + z
		// 00 00 10 | 00 = 8 = 0x08 -
		
		// 00 00 00 01 | = 1 = 0x01 run = true
		// 00 00 00 10 | = 2 = 0x02 jump = true
		// 00 00 00 11 | = 3 = 0x03; run & jump = true
		*/
		bool opt1; // run 
		bool opt2; // jump
		Ogre::Vector3 ByteToVector3(unsigned char byte)
		{
			Ogre::Vector3 ret(0,0,0);
			unsigned char firstpos = 192;
			unsigned char secondpos = 48;
			unsigned char thirdpos = 12;
			unsigned char fourthpos = 3;
	
			unsigned char one = byte & firstpos; // Logical ands to extract the values
			unsigned char two = byte & secondpos;
			unsigned char three = byte & thirdpos;
			unsigned char four = byte & fourthpos;
		
			if(one == 64) ret.x = movescale;
			else if(one == 128) ret.x = -movescale;
	
			if(two == 16) ret.y = movescale;
			else if(two == 32) ret.y = -movescale;
			
			if(three == 8) ret.z = -movescale;
			else if(three == 4) ret.z = movescale;

			if(four == 3) opt1 = true, opt2 = true;
			else if(four == 2) opt1 = false, opt2 = true;
			else if(four == 1) opt1 = true, opt2 = false;
			else opt1 = false, opt2 = false;
			return ret;
		};
		unsigned char Vector3ToByte(Ogre::Vector3 &in, bool run, bool jump)
		{
			unsigned char ret = 0;
			if(in.x > 0) {
				ret = ret | 64;
			} else if(in.x < 0) {
				ret = ret | 128;
			}
			if(in.y > 0) {
				ret = ret | 16;
			} else if(in.y < 0) {
				ret = ret | 32;
			} 
			if(in.z > 0) {
				ret = ret | 4;
			} else if(in.z < 0) {
				ret = ret | 8;
			} 
			if(run && jump) {
				ret = ret | 3;
			} else if(run) {
				ret = ret | 1;
			} else if(jump) {
				ret = ret | 2;
			} 
			//ret = parts[0] | parts[1] | parts[2] | parts[3]; // Logical ors to combine the values
			return ret;
		};
	};
}
#endif
