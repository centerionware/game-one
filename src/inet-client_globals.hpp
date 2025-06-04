void player_follow_test(inet_player *p, vec3 &i) {
	bool f = false;
	auto it = inet_player::Players.begin(), ie = inet_player::Players.end();
	for(;it!=ie;++it) if(p!=(*it).get()) if(i+vec3(0,0.5,0) == (*it)->position) {
	      std::string update;
	      update += (to_value(NetCommand));
	      update += (to_value(FollowPlayer));
	      char sArr[sizeof(unsigned int)];
	      memcpy( sArr, & (*it)->socket, sizeof(unsigned int));
	      update.append(sArr, sizeof(unsigned int));
	      p->send_text(update, p->socket);
	      std::cout << "Sending follow player to server\n";
	      f = true;
	      break;
	}
	if(!f) {
	      if(p->following_player != NULL) {
		      p->following_player = NULL;
		      std::string update;
		      update += (to_value(NetCommand));
		      update += (to_value(FollowPlayer));
		      char sArr[sizeof(unsigned int)];
		      unsigned int zero = 0;
		      memcpy( sArr, &zero, sizeof(unsigned int));
		      update.append(sArr, sizeof(unsigned int));
		      p->send_text(update, p->socket);
		      std::cout << "Sending unfollow player to server\n";
		      f = true;
	      }
	}
}

//namespace heightmap_globals {
//extern boost::mutex mut_c;
//}


namespace effectivestl {
	std::string get_file_contents(const char *filename)
	{
		std::ifstream in(filename, std::ios::in | std::ios::binary);
		if (in)
		{
		return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
		}
		throw(errno); 
	}
}
void add_chatwindow_text(const std::string &pText, const std::string &WindowName ) {
 using namespace CEGUI;
 
		WindowManager& winMgr = WindowManager::getSingleton();
		Listbox* chatHistory = static_cast<Listbox*> (winMgr.getWindow(WindowName));
 
		// If there's text then add it
		if(pText.size())
		{
			// Add the Editbox text to the history Listbox
			ListboxTextItem* chatItem;
			if(chatHistory->getItemCount() == 50)
			{
				/* We have reached the capacity of the Listbox so re-use the first Listbox item.
				   This code is a little crafty.  By default the ListboxTextItem is created with
				   the auto-delete flag set to true, which results in its automatic deletion when
				   removed from the Listbox.  So we change that flag to false, extract the item
				   from the Listbox, change its text, put the auto-delete flag back to true, and
				   finally put the item back into the Listbox. */
				chatItem = static_cast<ListboxTextItem*>(chatHistory->getListboxItemFromIndex(0));
				chatItem->setAutoDeleted(false);
				chatHistory->removeItem(chatItem);
				chatItem->setAutoDeleted(true);
				chatItem->setText(pText);
			}
			else
			{
				// Create a new listbox item
				chatItem = new ListboxTextItem(pText);
			}
			chatHistory->addItem(chatItem);
			chatHistory->ensureItemIsVisible(chatHistory->getItemCount());
		} 
}
inet_player::~inet_player() {
	if(is_client) {
		m_chatClient->close();
		m_chatThread->join();
	}
  //    for(auto i = Players.begin(); i!=Players.end(); i++) { // Should replace with std::map? It'd probably be faster.
//	  if( (*i).get() == this){ Players.erase(i); break; }
//      }
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
void remove_player(unsigned int socket) {
	
	auto iter = inet_player::Players.begin(), end = inet_player::Players.end();
	for(;iter!=end;iter++) if( (*iter)->following_player != NULL && (*iter)->following_player->socket == socket) (*iter)->following_player = NULL;
	iter = inet_player::Players.begin(), end = inet_player::Players.end();
	for(;iter!=end;iter++) 
		  if( (*iter)->socket == socket) { /*delete (*iter);*/ inet_player::Players.erase(iter); return;}
	return;
}
void erase_all_players() {
//	auto iter = inet_player::Players.begin(), end = inet_player::Players.end();
//	for(;iter!=end;iter++) delete (*iter);
	while(inet_player::Players.size() > 0) inet_player::Players.pop_back();
}