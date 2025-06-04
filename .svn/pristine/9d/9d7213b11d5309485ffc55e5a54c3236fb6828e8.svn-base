
std::map<inet_player*,int> user_ids;
Item *find_item(unsigned int iid) {
	auto it = all_items.begin(), end = all_items.end();
	for(unsigned int idx = 0;it!=end;++it,++idx) {
		if(idx == iid) return &(*it);
	}
	return NULL;
}

inet_player *find_player(unsigned int socket) {
	auto iter = inet_player::Players.begin(), end = inet_player::Players.end();
	for(;iter!=end;iter++) 
		  if( (*iter)->socket == socket)  return (*iter).get();
	return NULL;
}
int player_count() { 
    return inet_player::Players.size();
}
void remove_following(unsigned int socket);
void remove_player(unsigned int socket);


struct movement_teleporter_helperthingy {
	Ogre::Timer timer;
	bool has_teleported;
};
std::map<inet_player*, movement_teleporter_helperthingy> standing_still_timer;
Ogre::Timer queue_timer;

struct queue_obj{ 
	queue_obj(int fd):socket(fd),login_time(queue_timer.getMicroseconds()) {}
	int socket;
	unsigned long login_time;
};

std::vector<queue_obj> login_queue;
fd_set *mset;

#define sOfT sizeof(size_t)