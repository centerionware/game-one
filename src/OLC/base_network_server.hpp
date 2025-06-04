class net_module;
std::vector<net_module *> net_init_list;

struct net_module {
	inet_player *mPlayer;
	net_module() : mPlayer(NULL) { add_to_net_init_list(); }
	
	~net_module() { remove_from_net_init_list(); }
	void internal_init(const inet_player *p) {
	  mPlayer = (inet_player*)p;
	  if(mPlayer != NULL) initialize();
	}
	virtual void initialize()=0;
	virtual void deinitialize() { }

	virtual void internal_deinit() {
		deinitialize();
	}
	void add_to_net_init_list() {
		net_init_list.push_back(this);
	}
	void remove_from_net_init_list() {
		for(auto i = net_init_list.begin(), e = net_init_list.end(); i!=e;++i) 
			if((*i)==this) { net_init_list.erase(i); break; }
	}
	
};

void initialize_net_modules(inet_player const* p) { 	
		for(auto i = net_init_list.begin(), e = net_init_list.end(); i!=e;++i) 
			(*i)->internal_init(p);
}
void clean_net_modules() {
		for(auto i = net_init_list.begin(), e = net_init_list.end(); i!=e;++i) 
			(*i)->internal_deinit();
}
#include "PlayerEditor/ServerCallbacks.hpp"
#include "ItemEditor/ServerCallbacks.hpp"
#include "modeluploader/ServerCallbacks.hpp"

