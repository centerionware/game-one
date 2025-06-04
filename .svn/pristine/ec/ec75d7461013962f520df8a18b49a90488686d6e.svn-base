void inet_player::getModelList(std::vector<std::string>&i){
  std::string &b = i[0];
  auto *LB = ((CEGUI::Listbox*)(CState_Testing::ReturnInstance()->WinMan->getWindow("ModelUploaderWindow/SearchResultsListbox")));
  LB->resetList();
  std::string id = non_safe_string_deserialize(b);
  if(b.size() == 0) return;
  std::string lm = non_safe_string_deserialize(b);
  while(lm != "") {
    CEGUI::String un = lm;
    auto tst = new CEGUI::ListboxTextItem(un);
    tst->setID(fromstring<unsigned int>(id));
    LB->addItem(tst);
    id = non_safe_string_deserialize(b);
    lm = non_safe_string_deserialize(b);
  }

}
void inet_player::getModel(std::vector<std::string>&i) {
	std::string &b = i[0];
	std::string modelname = non_safe_string_deserialize(b);
	std::string model = non_safe_string_deserialize(b);
	// Now it's ready to be passed off to ogre. sweet eh'.
//obviously that part isn't implimented yet. it goes right here.

}
