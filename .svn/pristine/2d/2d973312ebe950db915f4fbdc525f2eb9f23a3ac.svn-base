
struct ModelUploader : public gui_module {
	FileBrowserDataStorage<ModelUploader> Model;
	FileBrowserDataStorage<ModelUploader> Skele;
	FileBrowserDataStorage<ModelUploader> Materials;
	ModelUploader():Model(this, &ModelUploader::UpdateModelBox), Skele(this,&ModelUploader::UpdateSkeleBox), Materials(this,&ModelUploader::UpdateMaterialsBox,true){}
	bool SearchModels(const CEGUI::EventArgs &event);
	bool SelectModel(const CEGUI::EventArgs &event);
	
	
	bool UploadModel(const CEGUI::EventArgs &event);
	bool FBModel(const CEGUI::EventArgs &event);
	bool FBSkele(const CEGUI::EventArgs &event);
	bool FBMaterial(const CEGUI::EventArgs &event);
	void UpdateModelBox();
	void UpdateSkeleBox();
	void UpdateMaterialsBox();
	void initialize();
	void create_example();    
};
ModelUploader Grapevine; // Yes, this line is actually needed.
void ModelUploader::initialize() {
	create_example();
	event_subscribe("ModelUploaderWindow/ListAllModels", CEGUI::PushButton::EventClicked,ModelUploader::SearchModels);
	event_subscribe("ModelUploaderWindow/UploadButton", CEGUI::PushButton::EventClicked, ModelUploader::UploadModel);
	event_subscribe("ModelUploaderWindow/SearchResultsListbox", CEGUI::Listbox::EventSelectionChanged,ModelUploader::SelectModel);
	event_subscribe("ModelUploaderWindow/Filenamebox",CEGUI::Editbox::EventActivated,
	ModelUploader::FBModel);
	event_subscribe("ModelUploaderWindow/Skelenamebox",CEGUI::Editbox::EventActivated,
	ModelUploader::FBSkele);
	event_subscribe("ModelUploaderWindow/MaterialsBox",CEGUI::Listbox::EventActivated, ModelUploader::FBMaterial);
}
void ModelUploader::UpdateModelBox() {
	WinMan->getWindow("ModelUploaderWindow/Filenamebox")->setText(Model.data.c_str());
	FileBrowserSingleton.hide();
}
void ModelUploader::UpdateMaterialsBox() {
  /// split up @ ;'s, then add each as seperate list item. (double click to remove?)
  
  CEGUI::Listbox *lbwin = ((CEGUI::Listbox*)(WinMan->getWindow("ModelUploaderWindow/MaterialsBox")));
  
  std::vector<std::string> cvec = Tools::strToVec(Materials.data, false, ';');
  for(auto i = cvec.begin(), e = cvec.end(); i!=e;++i) {
      lbwin->addItem(new CEGUI::ListboxTextItem((*i).c_str()));
  }
  FileBrowserSingleton.hide();
}
void ModelUploader::UpdateSkeleBox() {
	WinMan->getWindow("ModelUploaderWindow/Skelenamebox")->setText(Skele.data.c_str());
	FileBrowserSingleton.hide();
}
bool ModelUploader::FBModel(const CEGUI::EventArgs &event) {
	FileBrowserSingleton.setDataStorage(Model);
	FileBrowserSingleton.show();
	return true;
}
bool ModelUploader::FBSkele(const CEGUI::EventArgs &event) {
	FileBrowserSingleton.setDataStorage(Skele);
	FileBrowserSingleton.show();
	return true;
}
bool ModelUploader::FBMaterial(const CEGUI::EventArgs &event) {
	FileBrowserSingleton.setDataStorage(Materials);
	FileBrowserSingleton.show();
	return true;
}
void ModelUploader::create_example() {
//	0,0                                                   1,0         (x,y)
	/*******************************************************
	 *                        \ |_Model File_________(a)_| *
	 *   (AM)                 \                            *   
	 *   All Models           \ |_Skeleton File______(b)_| *  Var: XPOS, YPOS, XSCALE, YSCALE  
	 *                        \  ________________________  *   
	 *   Position 0,0         \ |                    (c) | *  (AM): 0,   0,    .5,     .85
	 *   Scale 50%w 85%h      \ | Material Files         | *  (a) : .51, .05,  .49,    .05
	 *                        \ |                        | *  (b) : .51, .115, .49,    .05
	 *                        \ |________________________| *  (c) : .51, .17,  .49,    .25
	 *                        \                            *  (U) : .895,.945, .1,     .05
	 *                        \                            *  (LA): 0,   .945, .45,    .05
	 *                        \                            *
	 * ------------------------                            *
	 *                                                     *
	 * ____________________                        ________*
	 * List All Models(LA)|                       |(U)pload*
	 * ----------------------------------------------------*
	0,1                                                   1,1
	
	*/
	auto example_window = basic_window_create("TaharezLook/FrameWindow", "ModelUploaderWindow", 0.25,0.25,0.5,0.5,WinMan);
	auto AM = basic_window_create("TaharezLook/Listbox", "ModelUploaderWindow/SearchResultsListbox",0,0,.5,.85,WinMan);
	auto a = basic_window_create("TaharezLook/Editbox", "ModelUploaderWindow/Filenamebox", .51,.05,.49, 0.05,WinMan);
	auto b = basic_window_create("TaharezLook/Editbox", "ModelUploaderWindow/Skelenamebox", .51,.115,.49,.05,WinMan);
	auto c = basic_window_create("TaharezLook/Listbox", "ModelUploaderWindow/MaterialsBox", .51,.17,.49,.25,WinMan);
	auto U = basic_window_create("TaharezLook/Button", "ModelUploaderWindow/UploadButton", .895,.945,.1,.05,WinMan);
	auto LA = basic_window_create("TaharezLook/Button", "ModelUploaderWindow/ListAllModels",0,.945,.45,.05,WinMan);
 // List all existing  models?
	example_window->hide();
	Window->addChildWindow(example_window);
	example_window->addChildWindow(AM);
	example_window->addChildWindow(a);
	example_window->addChildWindow(b);
	example_window->addChildWindow(U);
	example_window->addChildWindow(LA);
	example_window->addChildWindow(c);
}
bool ModelUploader::SearchModels(const CEGUI::EventArgs &event) {
	std::string output;
	output += to_value(OLC);
	output += to_value(GetModelList);
	mPlayer->send_text(output,mPlayer->socket);
	return true;
}
bool ModelUploader::SelectModel(const CEGUI::EventArgs &event) {
	std::string output;
	output += to_value(OLC);
	output += to_value(GetModelDetails);
	auto lbitem = ((CEGUI::Listbox*)(WinMan->getWindow("ModelUploaderWindow/SearchResultsListbox")))->getFirstSelectedItem();
	output += tostring(lbitem->getID());
	mPlayer->send_text(output, mPlayer->socket);
	return true;
}
bool ModelUploader::UploadModel(const CEGUI::EventArgs &event){
	std::string output;
	output += to_value(OLC);
	output += to_value(AddModel);
	std::string filename = WinMan->getWindow("ModelUploaderWindow/Filenamebox")->getText().c_str();
	if(filename.size() != 0) {
		output.append(string_serialize(boost::filesystem::path(filename).filename().string()));
		output.append(string_serialize(Tools::readFile(filename)));
		filename = WinMan->getWindow("ModelUploaderWindow/Skelenamebox")->getText().c_str();
		if(filename.size() != 0) {
		    output.append(string_serialize(boost::filesystem::path(filename).filename().string()));
		    output.append(string_serialize(Tools::readFile(filename)));
		}
		CEGUI::Listbox *materials = (CEGUI::Listbox*)WinMan->getWindow("ModelUploaderWindow/MaterialsBox");
		for(auto i = materials->getFirstSelectedItem(); i!=NULL; i = materials->getNextSelected(i)) {
		    filename = i->getText().c_str();
		    output.append(string_serialize(boost::filesystem::path(filename).filename().string()));
		    output.append(string_serialize(Tools::readFile(filename)));
		}
		mPlayer->send_text(output,mPlayer->socket);
	} else {
		// No model selected. don't try to upload.
	}
	return true;
}