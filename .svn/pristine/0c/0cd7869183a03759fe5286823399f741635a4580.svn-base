struct HUD_GUI : public gui_module {
    bool OnPlayerOLCSearch(const CEGUI::EventArgs &event);
    void initialize();
    void create_hud();
};

HUD_GUI NiftyHudMart;
void HUD_GUI::initialize() {
	create_hud();

}
void HUD_GUI::create_hud() {
	/**************** )(@)( .Hud. )(@)( ****************/
	auto hud_leave_button = basic_window_create("TaharezLook/Button", "LeaveButton",0.5,0.5,0.1,0.035,WinMan);
	//WinMan->getWindow("LeaveButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CState_Testing::Event_LeaveGame    ,this)); 
	// ^^^^ This is done below in createGui.. copied here for reference
	hud_leave_button->setText("Leave");
	Window->addChildWindow(hud_leave_button);
	hud_leave_button->hide();
	hud_leave_button->setAlwaysOnTop(true);

	auto hud_editmode_text = basic_window_create("TaharezLook/StaticText", "lblCurrentEditMode",0.78,0.855,0.2,0.04,WinMan);
			
	hud_editmode_text->setText("Press TAB while in F5");
	auto hud_active_cegui_window = basic_window_create("TaharezLook/StaticText","lblCurrentCEGUISheet", 0,0,0.4,0.04,WinMan);
	Window->addChildWindow(hud_active_cegui_window);
	auto hud_chatbox = basic_window_create("TaharezLook/Listbox", "MainChatBox",0.25,0.795,0.5,0.15,WinMan);
	auto hud_chatbox_input = basic_window_create("TaharezLook/Editbox", "MainChatInputBar",0.25,0.93,0.5,0.04,WinMan);
	auto hud_health_bar = basic_window_create("TaharezLook/ProgressBar", "MainHealthBar",0.78,0.795,0.15,0.02,WinMan);
	auto hud_fatigue_bar = basic_window_create("TaharezLook/ProgressBar", "MainFatigueBar",0.78,0.825,0.15,0.02,WinMan);

	Window->addChildWindow(hud_fatigue_bar);
	Window->addChildWindow(hud_health_bar);
	Window->addChildWindow(hud_chatbox_input);
	Window->addChildWindow(hud_chatbox);
	Window->addChildWindow(hud_editmode_text);
}
