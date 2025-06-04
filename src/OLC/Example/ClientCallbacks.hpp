void inet_player::getExampleSearch(std::vector<std::string>&i){
  std::string &b = i[0];
  ((CEGUI::Listbox*)(CState_Testing::ReturnInstance()->WinMan->getWindow("Example/SearchResultsListbox")))->resetList();
  std::string lm = non_safe_string_deserialize(b);
  while(lm != "") {
    CEGUI::String un = lm;
    ((CEGUI::Listbox*)(CState_Testing::ReturnInstance()->WinMan->getWindow("example/SearchResultsListbox")))->addItem(new CEGUI::ListboxTextItem(un));
    lm = non_safe_string_deserialize(b);
  }

}
