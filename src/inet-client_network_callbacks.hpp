INET_CALLBACK(InventoryCommand, WearItem) { 
      if(player.admin) {
	  // Just put the item on
      } else {
	  // Do level checks
      }
}
INET_CALLBACK(InventoryCommand, RemoveItem) { 
      if(player.admin) {
	// cursed items? Muahaha.
      } else {
	
      }
}
INET_CALLBACK(InventoryCommand, DropItem) { 
	if(player.admin) {
		// just drop the item.
	} else {
		// search the players inventory, if the item is in the inventory remove from and put on floor.
	}
}
#include "OLC/base_network_client.hpp"
/*
void inet_player::getZoneList(std::vector<std::string>&in){
//uid, # of results, {chunkid, locked}
#undef discern
#define discern(X,Y) std::string X = non_safe_string_deserialize(b); \
  WinMan->getWindow("ZoneEditor/"#Y)->setText(X);
  
  auto WinMan = CState_Testing::ReturnInstance()->WinMan;

  std::string &b=in[0];
  discern(id, PlayerID)
  discern(owned, OwnedZones)
  CEGUI::MultiColumnList *mListBox = ((CEGUI::MultiColumnList*)(WinMan->getWindow("ZoneEditor/ZoneList")));
  unsigned int zn = fromstring<unsigned int>(owned);
  for(unsigned int i = 0; i < zn; ++i) {
    unsigned int mRow = mListBox->addRow();
    CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(non_safe_string_deserialize(b).c_str(), 0);
    mListBox->setItem(item, 0, mRow);
    item = new CEGUI::ListboxTextItem(non_safe_string_deserialize(b).c_str(), 0);
    mListBox->setItem(item, 1, mRow);
  }
  
}*/
