struct PlayerZoneEditor : public gui_module {
    bool OnPlayerOLCSearch(const CEGUI::EventArgs &event);
    void initialize();
    void create_player_zone_editor();
    bool OnPlayerZoneEditorOpen(const CEGUI::EventArgs &event);
};
PlayerZoneEditor FarmVille; // Yes, this line is actually needed.
void PlayerZoneEditor::initialize() {
	create_player_zone_editor();	//event_subscribe("PlayerZoneEditor/Searchbox",CEGUI::Combobox::EventTextAccepted,PlayerZoneEditor::OnPlayerOLCSearch);
}
void PlayerZoneEditor::create_player_zone_editor() {
	auto zone_editor_window = basic_window_create("TaharezLook/FrameWindow", "ZoneEditorWindow",0.25,0.25,0.5,0.5,WinMan);
	auto player_id_editbox = basic_window_create("TaharezLook/StaticText", "ZoneEditor/PlayerID",0,0,.49,0.06,WinMan);
	auto player_ownedzones = basic_window_create("TaharezLook/StaticText", "ZoneEditor/OwnedZones",.51,0,.49,0.06,WinMan);
	auto zonelist = basic_window_create("TaharezLook/MultiColumnList","ZoneEditor/ZoneList",0,.08,.49,.91,WinMan);
	
	
// Set the users selection ability
//zonelist->setSelectionMode(CEGUI::MultiColumnList::SelectionMode::RowMultiple);

// Add some column headers
	CEGUI::String zid = "Zone ID";
	CEGUI::String llabl = "Locked";
	CEGUI::UDim p1(0.8f,0), p2(0.2f,0);
((CEGUI::MultiColumnList*)zonelist)->addColumn(zid, 0, p1);
((CEGUI::MultiColumnList*)zonelist)->addColumn(llabl, 1, p2);
	
	auto lock_button = basic_window_create("TaharezLook/Button","ZoneEditor/LockZone", .51,0.65,.49,0.06,WinMan);
	auto unlock_button = basic_window_create("TaharezLook/Button","ZoneEditor/UnlockZone",.51,0.13,.49,0.06,WinMan);
	auto copy_button = basic_window_create("TaharezLook/Button","ZoneEditor/CopyZone", .51,0.195,.49,0.06, WinMan);
	auto paste_button = basic_window_create("TaharezLook/Button","ZoneEditor/PasteZone", .51,0.23,.49,0.06, WinMan);
	auto reset_button = basic_window_create("TaharezLook/Button","ZoneEditor/ResetZone", .51,0.295,.49,0.06, WinMan);
	zone_editor_window->addChildWindow(player_id_editbox);
	zone_editor_window->addChildWindow(zonelist);
	zone_editor_window->addChildWindow(lock_button);
	zone_editor_window->addChildWindow(unlock_button);
	zone_editor_window->addChildWindow(copy_button);
	zone_editor_window->addChildWindow(paste_button);
	zone_editor_window->addChildWindow(reset_button);
	zone_editor_window->addChildWindow(player_ownedzones);
	zone_editor_window->hide();
	Window->addChildWindow(zone_editor_window);
}

bool PlayerZoneEditor::OnPlayerZoneEditorOpen(const CEGUI::EventArgs &event){
	#undef inscern
	#define inscern(X,Y) std::string X = WinMan->getWindow("PlayerEditor/"#Y)->getText().c_str(); output.append(X);
	std::string output;
	output += to_value(OLC);
	output += to_value(GetZoneList);
	inscern(id,IDNumber)
	mPlayer->send_text(output,mPlayer->socket);
	return true;
}