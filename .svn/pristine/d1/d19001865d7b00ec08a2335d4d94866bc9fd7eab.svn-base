struct ItemEditorGUI : public gui_module {
    void initialize();
    void create_item_editor_gui();
    bool OnItemLocalSearch(const CEGUI::EventArgs &event);
    bool OnItemGlobalSearch(const CEGUI::EventArgs &event);
    bool OnItemModifyPress(const CEGUI::EventArgs &event);
    bool OnItemDeletePress(const CEGUI::EventArgs &event);
    bool OnItemLockPress(const CEGUI::EventArgs &event);
    bool OnItemDetailsRequest(const CEGUI::EventArgs &event);
    bool OnItemAddPress(const CEGUI::EventArgs &event);
};
ItemEditorGUI ChuckECheeze; // Yes, this line is actually needed.
void ItemEditorGUI::initialize() {
	create_item_editor_gui();
	event_subscribe("ItemEditor/LocalButton",CEGUI::PushButton::EventClicked, ItemEditorGUI::OnItemLocalSearch);
	event_subscribe("ItemEditor/GlobalButton",CEGUI::PushButton::EventClicked, ItemEditorGUI::OnItemGlobalSearch);
	event_subscribe("ItemEditor/ItemModify",CEGUI::PushButton::EventClicked, ItemEditorGUI::OnItemModifyPress);
	event_subscribe("ItemEditor/ItemAdd",CEGUI::PushButton::EventClicked, ItemEditorGUI::OnItemAddPress);
	event_subscribe("ItemEditor/ItemDelete",CEGUI::PushButton::EventClicked, ItemEditorGUI::OnItemDeletePress);
	event_subscribe("ItemEditor/SearchResultsListbox",CEGUI::Listbox::EventSelectionChanged,ItemEditorGUI::OnItemDetailsRequest);
	//event_subscribe("ItemEditorGUI/Searchbox",CEGUI::Combobox::EventTextAccepted,ItemEditorGUI::OnPlayerOLCSearch);
}

CEGUI::Window* add_and_create_window(std::string type, std::string name, float x, float y, float sx, float sy, CEGUI::WindowManager *WinMan, CEGUI::Window *AddToWindow) {
      auto t = basic_window_create(type,name,x,y,sx,sy,WinMan);
      AddToWindow->addChildWindow(t);
      return t;
      
}
void ItemEditorGUI::create_item_editor_gui() {
	/*
	 It will also need new && delete mechanisms. Buttons?
#define BLAHBLAHBLAHBLAHBLAHBLAHBLAH item_window->addChildWindow(add_and_create_window .. didn't work.
To make something similar work, will need func
	 */

	auto item_window = basic_window_create("TaharezLook/FrameWindow", "ItemEditorWindow",0.25,0.25,0.5,0.5,WinMan);
	item_window->setProperty("InheritsAlpha","False");
	item_window->setProperty("Alpha", "1");
	auto locals_button = add_and_create_window("TaharezLook/Button", "ItemEditor/LocalButton", 0,0,.45, 0.06,WinMan,item_window);
	auto globals_button = add_and_create_window("TaharezLook/Button", "ItemEditor/GlobalButton",0.55,0,.45,0.06,WinMan,item_window);
	add_and_create_window("TaharezLook/Listbox", "ItemEditor/SearchResultsListbox", 0, 0.065, .5, 0.5,WinMan,item_window);
	add_and_create_window("TaharezLook/Editbox", "ItemEditor/ItemName", 0.55, 0.065, .3, 0.06,WinMan,item_window);
	add_and_create_window("TaharezLook/Editbox", "ItemEditor/ItemID", 0.855, 0.065, .14, 0.06,WinMan,item_window);
	add_and_create_window("TaharezLook/Editbox", "ItemEditor/LevelList", 0.55, 0.13, .45, 0.06,WinMan,item_window);
	add_and_create_window("TaharezLook/Editbox", "ItemEditor/ItemTypeList", 0.55, 0.195, .45, 0.06,WinMan,item_window);
	// Change item_level and item_type to combobox's later..
	add_and_create_window("TaharezLook/Button", "ItemEditor/ItemModify", 0.55, 0.26,.45,0.06,WinMan,item_window);
	add_and_create_window("TaharezLook/Button", "ItemEditor/ItemAdd", 0.55, 0.325,.45,0.06,WinMan,item_window);
	add_and_create_window("TaharezLook/Button", "ItemEditor/ItemDelete", 0.55, 0.39,.45,0.06,WinMan,item_window);
	add_and_create_window("TaharezLook/StaticImage", "ItemEditor/ItemImage",  0, .570, 0.1, 0.1,WinMan,item_window);
	auto image_button = add_and_create_window("TaharezLook/Button", "ItemEditor/ImageButton", 0,   0.675, 0.45,0.06,WinMan,item_window);
	auto model_button = add_and_create_window("TaharezLook/Button", "ItemEditor/ModelButton",0.55, 0.675, 0.45, 0.06,WinMan,item_window);
	add_and_create_window("TaharezLook/Editbox", "ItemEditor/ExtraText", 0, 0.74,1, 0.12,WinMan,item_window);
	
	locals_button->setText("Locals");
	globals_button->setText("Globals");
	model_button->setText("Model");
	image_button->setText("Image");

	Window->addChildWindow(item_window);
	item_window->hide();
}


    bool ItemEditorGUI::OnItemLocalSearch(const CEGUI::EventArgs &event){
        std::string output;
	output += to_value(OLC);
	output += to_value(GetItemLocalList);
	std::string update;
	update.append("S/:");
	update.append(WinMan->getWindow("ItemEditor/ItemName")->getText().c_str());
	WinMan->getWindow("lblCurrentEditMode")->setText(update);
	output.append(WinMan->getWindow("ItemEditor/ItemName")->getText().c_str());
	mPlayer->send_text(output,mPlayer->socket);
	return true;
    }
    bool ItemEditorGUI::OnItemGlobalSearch(const CEGUI::EventArgs &event){
        std::string output;
	output += to_value(OLC);
	output += to_value(GetItemGlobalList);
	std::string update;
	update.append("S/:");
	update.append(WinMan->getWindow("ItemEditor/ItemName")->getText().c_str());
	WinMan->getWindow("lblCurrentEditMode")->setText(update);
	output.append(WinMan->getWindow("ItemEditor/ItemName")->getText().c_str());
	mPlayer->send_text(output,mPlayer->socket);
	return true;
    }
    bool ItemEditorGUI::OnItemModifyPress(const CEGUI::EventArgs &event){
      	#undef inscern
	#define inscern(X,Y) std::string X = WinMan->getWindow("ItemEditor/"#Y)->getText().c_str(); output.append(string_serialize(X));
	std::string output;
	output += to_value(OLC);
	output += to_value(ModifyItem);
	
	//auto WinMan = ItemEditorGUI::ReturnInstance()->WinMan;

	inscern(id,ItemID)
	inscern(name,ItemName)
	inscern(ilvl,LevelList)
	inscern(itype,ItemTypeList)
	inscern(etxt,ExtraText)
	
	mPlayer->send_text(output,mPlayer->socket);
	
	return true;
    }
    bool ItemEditorGUI::OnItemDeletePress(const CEGUI::EventArgs &event){
        #undef inscern
	#define inscern(X,Y) std::string X = WinMan->getWindow("ItemEditor/"#Y)->getText().c_str(); output.append(string_serialize(X));
	std::string output;
	output += to_value(OLC);
	output += to_value(DeleteItem);
	
	//auto WinMan = ItemEditorGUI::ReturnInstance()->WinMan;

	inscern(id,ItemID)
		
	mPlayer->send_text(output,mPlayer->socket);
	
	return true;
    }
    bool ItemEditorGUI::OnItemLockPress(const CEGUI::EventArgs &event){
              #undef inscern
	#define inscern(X,Y) std::string X = WinMan->getWindow("ItemEditor/"#Y)->getText().c_str(); output.append(string_serialize(X));
	std::string output;
	output += to_value(OLC);
	output += to_value(LockItem);
	
	//auto WinMan = ItemEditorGUI::ReturnInstance()->WinMan;

	inscern(id,ItemID)
		
	mPlayer->send_text(output,mPlayer->socket);
	
	return true;
    }
    bool ItemEditorGUI::OnItemDetailsRequest(const CEGUI::EventArgs &event){
         std::string output;
	  output += to_value(OLC);
	  output += to_value(GetItemDetails);
	  auto lbitem = ((CEGUI::Listbox*)(WinMan->getWindow("ItemEditor/SearchResultsListbox")))->getFirstSelectedItem();
	  output.append(lbitem->getText().c_str());
	  mPlayer->send_text(output,mPlayer->socket);
	  return true;
      
    }
    bool ItemEditorGUI::OnItemAddPress(const CEGUI::EventArgs &event){
	#undef inscern
	#define inscern(X,Y) std::string X = WinMan->getWindow("ItemEditor/"#Y)->getText().c_str(); output.append(string_serialize(X));
	std::string output;
	output += to_value(OLC);
	output += to_value(AddItem);
	
	//auto WinMan = ItemEditorGUI::ReturnInstance()->WinMan;

	//inscern(id,IDNumber)
	inscern(name,ItemName)
	inscern(ilvl,LevelList)
	inscern(itype,ItemTypeList)
	inscern(etxt,ExtraText)
	
	mPlayer->send_text(output,mPlayer->socket);
	
	return true;
    }

