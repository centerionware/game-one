struct AdminWindow : public gui_module {
	void initialize();
	void create_window();

	bool show_pe(const CEGUI::EventArgs &event);
	bool show_ie(const CEGUI::EventArgs &event);
	bool show_mu(const CEGUI::EventArgs &event);
	void toggle_hidden(const char *windowName);
};
AdminWindow theSuperAdminWindowWoot;
void AdminWindow::initialize() {
	create_window();

	event_subscribe("AdminWindow/Player Editor", CEGUI::PushButton::EventClicked, AdminWindow::show_pe);
	event_subscribe("AdminWindow/Item Editor", CEGUI::PushButton::EventClicked, AdminWindow::show_ie);
	event_subscribe("AdminWindow/Model Uploader", CEGUI::PushButton::EventClicked, AdminWindow::show_mu);
}
void AdminWindow::create_window() {
	auto example_window = basic_window_create("TaharezLook/FrameWindow", "AdminWindow", 0.25,0.25,0.5,0.5,WinMan);
	example_window->hide();
	Window->addChildWindow(example_window);

	auto pe = basic_window_create("TaharezLook/Button", "AdminWindow/Player Editor",		 0,0,1, 0.06,WinMan);
	auto ie = basic_window_create("TaharezLook/Button", "AdminWindow/Item Editor", 		 0,.1,1, 0.06,WinMan);
	auto mu = basic_window_create("TaharezLook/Button", "AdminWindow/Model Uploader", 	 0,.2,1, 0.06,WinMan);
//	auto iu = basic_window_create("TaharezLook/Button", "AdminWindow/ImageUploader(NotIMPLD)", 0,0,0.3, 0.06,WinMan);
//	auto o1 = basic_window_create("TaharezLook/Button", "AdminWindow/Something else",		 0,0,0.4, 0.06,WinMan);
//	auto o2 = basic_window_create("TaharezLook/Button", "AdminWindow/Something else else", 	 0,0,0.5, 0.06,WinMan);
	

	example_window->addChildWindow(pe);
	example_window->addChildWindow(ie);
	example_window->addChildWindow(mu);
//	example_window->addChildWindow(iu)
	
}
bool AdminWindow::show_pe(const CEGUI::EventArgs &event){
	toggle_hidden("PlayerEditorWindow");
	return true;
}
bool AdminWindow::show_ie(const CEGUI::EventArgs &event){
	toggle_hidden("ItemEditorWindow");
	return true;
}
bool AdminWindow::show_mu(const CEGUI::EventArgs &event){
	toggle_hidden("ModelUploaderWindow");
	return true;
}
void AdminWindow::toggle_hidden(const char *windowName) {
	if(WinMan->getWindow(windowName)->isVisible()) {
		WinMan->getWindow(windowName)->hide();
		WinMan->getWindow(windowName)->deactivate();
	} else {
		WinMan->getWindow(windowName)->show();
		WinMan->getWindow(windowName)->activate();
		
	}
}