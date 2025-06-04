struct Example : public gui_module {
    bool OnPlayerOLCSearch(const CEGUI::EventArgs &event);
    void initialize();
    void create_example();
};
Example ChuckNorris; // Yes, this line is actually needed.
void Example::initialize() {
	create_example();	event_subscribe("Example/Searchbox",CEGUI::Combobox::EventTextAccepted,Example::OnPlayerOLCSearch);
}
void Example::create_example() {
	auto example_window = basic_window_create("TaharezLook/FrameWindow", "ExampleWindow", 0.25,0.25,0.5,0.5,WinMan);
	example_window->hide();
	Window->addChildWindow(example_window);
	auto search = basic_window_create("TaharezLook/Combobox", "Example/SearchBox", 0,0,0.49, 0.06,WinMan);
	auto search_results_list = basic_window_create("TaharezLook/Listbox", "Example/SearchResultsListbox",0,0.065,.49,.49,WinMan);
	example_window->addChildWindow(search);
	example_window->addChildWindow(search_results_list);
}
bool Example::ExampleSearch(const CEGUI::EventArgs &event){
  std::string output;
  output += to_value(OLC);
  output += to_value(GetExampleSearch);
  output.append(WinMan->getWindow("Example/SearchBox")->getText().c_str());
  mPlayer->send_text(output,mPlayer->socket);
  return true;
}

