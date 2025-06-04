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
#include "command.h"
#include "tools.h"
#include "functors.h"
#include "server-map.h"
using namespace Commands;
   unsigned int sthreadcount = 1;
   

    boost::asio::io_service io_service;
    boost::thread_group threads;
    boost::asio::io_service::work m_pWork(io_service);
struct thread_initializer {
  boost::asio::io_service::work m_pWork;
  thread_initializer():m_pWork(io_service) {
    
//    for (size_t i = 0; i < sthreadcount; ++i)
	  threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service)); 
  }
  ~thread_initializer() {
	io_service.stop();
	threads.join_all();
  }
};
static volatile thread_initializer blahblahblahblahblah;
	
Proc::Proc()  {
  // m_pWork.reset( new boost::asio::io_service::work(io_service) );// boost::asio::io_service::work work(io_service);

}
    

Proc* Proc::tis = NULL;
//std::vector<TFunctor*> Proc::all_commands;
/*

TFunctor *find_all_command(TFunctor *o) {
	std::vector<TFunctor*>::iterator ac = all_commands.begin(), acend = all_commands.end();
	for(;ac != acend;ac++) {
		if( (*o) == (*(*ac))) {
			delete o;
			return (*ac);
		}
	}
	// not found.
	all_commands.push_back(o);
	return o;
}*/

aCom* Proc::get(char a, char b) {
	std::vector<aCom>::iterator iter = commands.begin(), end = commands.end();
	while(iter != end) 	if((*(iter)).ida == a && (*(iter)).idb == b) return &(*(iter)); else ++iter;
	return NULL;
}
sCom* Proc::get(std::string &a) {
	std::vector<sCom>::iterator iter = str_commands.begin(), end = str_commands.end();
	while(iter != end) 	if((*(iter)).ida == a) return &(*(iter)); else iter++;
	return NULL;
}
extern bool is_server;
void Proc::Call(char com, char comB, std::string arguments, bool isDown, boost::shared_ptr<inet_player> shptr){
  // this one is nice. works great.
	aCom* c = get(com, comB);
	
	//std::cout << "Found command: " << c << std::endl;
	if ( c == NULL) return; // no comm found
	std::vector<std::string> args;// = Tools::strToVec(arguments); 
	args.push_back(arguments);
	int s  = 0;
//	c->com->Call(args, s,&isDown);
//		return;
		
	//to_value(LocalEvent), to_value(Connected)
	//to_value(LocalEvent), to_value(Disconnected)
	/*
	if(!is_server) {
		unsigned char vals[] = { 
			to_value(NetCommand), to_value(PushChunk),
			to_value(NetCommand), to_value(GetChunk)
		};
	
		for(unsigned int x = 0; x < sizeof(vals); x+=2)
			if(com == vals[x] && comB == vals[x+1]) {
				io_service.post(boost::bind(&TFunctor::Call, c->com , args, s, &isDown,shptr));
				return;
			} 
	}
	*/
	c->com->Call(args, s,&isDown,shptr);
	
}
void Proc::Call(char com, char comB, bool isDown,boost::shared_ptr<inet_player> shptr){
	aCom* c = get(com, comB);
	if(c == NULL) return; // no comm found
	std::vector<std::string> args;
	int s = 0;
	c->com->Call(args, s, &isDown,shptr);
}
void Proc::Call(std::string &input, bool isDown,boost::shared_ptr<inet_player> shptr){
// Don't use this one unless you want to trash your input.
	if(input.size() == 0) return;
	std::vector<std::string> args = Tools::strToVec(input);
	sCom* c = get(args[0]);
	if(c == NULL) return; // no comm found
	//args.erase(args.begin()); the functor call method is able to pass the right argument(s) to the function. functions can even get their callback word
	//if they take std::vector<std::string>& as their first argument. isDown can be used to inicate whether the mouse is down, for mouse callback functions.
	//isDown is passed if the function takes a single bool* as an argument.
	// or if the function takes exactly: void (TClass::*fpt12)(std::vector<std::string *> *, int &, bool);.....
	int s = 0;
	c->com->Call(args, s,&isDown,shptr);
	//io_service.post(boost::bind(&TFunctor::Call, c->com , args, s, &isDown));
}
void Proc::Add(TFunctor*c, char Id, char Idb) {
	//c=find_all_command(c);
	aCom n;
	n.com= c;
	n.ida = Id;
	n.idb = Idb;
	for(auto i=commands.begin(), e = commands.end();i!=commands.end();) {
		if((*i).ida == n.ida && (*i).idb == n.idb){ delete (*i).com; i = commands.erase(i);break;}
		else i++;
	}
	commands.push_back(n);
}
void Proc::Add(std::string input, TFunctor*c) {
	//c=find_all_command(c);
	sCom n;
	n.ida = input;
	n.com =c;
	str_commands.push_back(n);
}

void Proc::pop_last(std::string &input) {
      std::vector<sCom>::iterator iter = str_commands.begin(), end = str_commands.end();
	for(;iter != end;++iter) 
	  if((*(iter)).ida == input){
	    delete (*iter).com;
	    str_commands.erase(iter);
	    return;	    
	  }
	
}
Proc::~Proc() {

  
  {
   std::vector<sCom>::iterator iter = str_commands.begin(), end = str_commands.end();
   for(;iter != end;++iter) delete (*iter).com;
  }
  
  {
    std::vector<aCom>::iterator iter = commands.begin(), end = commands.end();
    for(;iter != end;++iter) delete (*iter).com;
  }
  
}



	//struct tProc : public Proc
	//{
		
		
		// unmap the old ida and TFunctor* that match this, and then call Add(TFunctor*,T)
	  //private:
	//	std::vector<T> template_commands;
	//}