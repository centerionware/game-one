struct PlayerEditor : public gui_module {
    bool OnPlayerOLCSearch(const CEGUI::EventArgs &event);
    bool OnPlayerModifyPress(const CEGUI::EventArgs &event);
    bool OnPlayerDeletePress(const CEGUI::EventArgs &event);
    bool OnPlayerLockPress(const CEGUI::EventArgs &event);
    bool OnPlayerDetailsRequest(const CEGUI::EventArgs &event);
    bool OnPlayerZoneEditorOpen(const CEGUI::EventArgs &event);
    void initialize();
    void create_player_editor();

};
PlayerEditor ChuckNorris; // Yes, this line is actually needed.

void PlayerEditor::initialize() {

	create_player_editor();
	event_subscribe("PlayerEditor/PlayerSearch",CEGUI::Combobox::EventTextAccepted,PlayerEditor::OnPlayerOLCSearch);
	event_subscribe("PlayerEditor/SearchResultsListbox",CEGUI::Listbox::EventSelectionChanged,PlayerEditor::OnPlayerDetailsRequest);
	event_subscribe("PlayerEditor/PlayerSaveButton",CEGUI::PushButton::EventClicked,PlayerEditor::OnPlayerModifyPress);
	event_subscribe("PlayerEditor/DeleteButton",CEGUI::PushButton::EventClicked,PlayerEditor::OnPlayerDeletePress);
	event_subscribe("PlayerEditor/LockCheckbox",CEGUI::Checkbox::EventMouseClick,PlayerEditor::OnPlayerLockPress);
}
void PlayerEditor::create_player_editor() {
	auto player_editor_window = basic_window_create("TaharezLook/FrameWindow", "PlayerEditorWindow", 0.25,0.25,0.5,0.5,WinMan);
	player_editor_window->hide();
	Window->addChildWindow(player_editor_window);
	auto player_search = basic_window_create("TaharezLook/Combobox", "PlayerEditor/PlayerSearch", 0,0,0.49, 0.06,WinMan);
	auto player_list_button = basic_window_create("TaharezLook/Button", "PlayerEditor/PlayerSaveButton", .51,0,.49,0.06,WinMan);
	auto search_results_list = basic_window_create("TaharezLook/Listbox", "PlayerEditor/SearchResultsListbox",0,0.065,.49,.49,WinMan);
	auto player_view = basic_window_create("TaharezLook/StaticImage", "PlayerEditor/PlayerViewRTT",0,0.065,.49,0.49,WinMan);
	auto name_editbox = basic_window_create("TaharezLook/Editbox", "PlayerEditor/NameEditor"                 ,.51,0.065,.23,0.06,WinMan);
	auto id_box = basic_window_create("TaharezLook/StaticText", "PlayerEditor/IDNumber"                 ,.75,0.065,.23,0.06,WinMan);
	
	auto admin_checkbox = basic_window_create("TaharezLook/Editbox", "PlayerEditor/AdminLevel"             ,.51,0.130,.1,0.06,WinMan);
	auto email_box = basic_window_create("TaharezLook/Editbox","PlayerEditor/EmailAddress",0.63,0.130,.37,0.06,WinMan);
	auto zone_editor_button = basic_window_create("TaharezLook/Button", "PlayerEditor/ZoneEditorWindowButton",0.51,0.195,.49,0.06,WinMan);
		
	auto delete_button = basic_window_create("TaharezLook/Button", "PlayerEditor/DeleteButton",  0.51, 0.26,.49,0.06,WinMan);
	//auto modify_button = basic_window_create("TaharezLook/Button", "PlayerEditor/ModifyButton",   .51, .325,.49,0.06,WinMan);
	auto lock_checkbox = basic_window_create("TaharezLook/Checkbox","PlayerEditor/LockCheckbox", 0.51,  .39,.49,0.06,WinMan);
	auto last_x = basic_window_create("TaharezLook/Editbox","PlayerEditor/LastX",0.51,.45,.15,0.06,WinMan);
	auto last_z = basic_window_create("TaharezLook/Editbox","PlayerEditor/LastY",0.67,.45,.15,0.06,WinMan);
	auto last_y = basic_window_create("TaharezLook/Editbox","PlayerEditor/LastZ",0.84,.45,.15,0.06,WinMan);
	auto inventory_list = basic_window_create("TaharezLook/Listbox","PlayerEditor/InventoryList",	0,  .55,  1, .45,WinMan);
	player_editor_window->addChildWindow(last_x);
	player_editor_window->addChildWindow(last_y);
	player_editor_window->addChildWindow(last_z);
	player_editor_window->addChildWindow(player_search);
	player_editor_window->addChildWindow(player_list_button);
	player_editor_window->addChildWindow(search_results_list);
	player_editor_window->addChildWindow(player_view);
	player_editor_window->addChildWindow(name_editbox);
	player_editor_window->addChildWindow(admin_checkbox);
	player_editor_window->addChildWindow(zone_editor_button);
	player_editor_window->addChildWindow(inventory_list);
//	player_editor_window->addChildWindow(modify_button);
	player_editor_window->addChildWindow(delete_button);
	player_editor_window->addChildWindow(lock_checkbox);
	player_editor_window->addChildWindow(id_box);
	player_editor_window->addChildWindow(email_box);
}


bool PlayerEditor::OnPlayerOLCSearch(const CEGUI::EventArgs &event){
  std::string output;
  output += to_value(OLC);
  output += to_value(GetPlayerList);
  std::string update;
  update.append("S/:");
  update.append(WinMan->getWindow("PlayerEditor/PlayerSearch")->getText().c_str());
  WinMan->getWindow("lblCurrentEditMode")->setText(update);
  output.append(WinMan->getWindow("PlayerEditor/PlayerSearch")->getText().c_str());
  mPlayer->send_text(output,mPlayer->socket);
  return true;
}
bool PlayerEditor::OnPlayerDetailsRequest(const CEGUI::EventArgs &event) {
  std::string output;
  output += to_value(OLC);
  output += to_value(GetPlayerDetails);
  auto lbitem = ((CEGUI::Listbox*)(WinMan->getWindow("PlayerEditor/SearchResultsListbox")))->getFirstSelectedItem();
  output.append(lbitem->getText().c_str());
  mPlayer->send_text(output,mPlayer->socket);
  return true;
}
bool PlayerEditor::OnPlayerModifyPress(const CEGUI::EventArgs &event){
  #define inscern(X,Y) std::string X = WinMan->getWindow("PlayerEditor/"#Y)->getText().c_str(); output.append(string_serialize(X));
  std::string output;
  output += to_value(OLC);
  output += to_value(ModifyPlayer);
  
  inscern(id,IDNumber)
  inscern(name,NameEditor)
  inscern(email,EmailAddress)
  inscern(LastPosX,LastX)
  inscern(LastPosY,LastY)
  inscern(LastPosZ,LastZ)
  inscern(AdminLevel,AdminLevel)
  mPlayer->send_text(output,mPlayer->socket);
  
  return true;
}
bool PlayerEditor::OnPlayerDeletePress(const CEGUI::EventArgs &event){
#undef inscern
#define inscern(X,Y) std::string X = WinMan->getWindow("PlayerEditor/"#Y)->getText().c_str(); output.append(string_serialize(X));
  std::string output;
  output += to_value(OLC);
  output += to_value(DeletePlayer);
  inscern(id,IDNumber)
  mPlayer->send_text(output,mPlayer->socket);
  return true;
}
bool PlayerEditor::OnPlayerLockPress(const CEGUI::EventArgs &event){
#undef inscern
   #define inscern(X,Y) std::string X = WinMan->getWindow("PlayerEditor/"#Y)->getText().c_str(); output.append(string_serialize(X));
  std::string output;
  output += to_value(OLC);
  output += to_value(LockPlayer);
  inscern(id,IDNumber)
  mPlayer->send_text(output,mPlayer->socket);
  return true;
}
