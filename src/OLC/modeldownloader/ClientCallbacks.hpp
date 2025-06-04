struct ModelDownloaderClientNetmodule : public net_module {
    void initialize() {
	mPlayer->netbind(mPlayer.get(), &inet_player::getModelGlobalList, OLC, GetModelGlobalList);
    }
};

void inet_player::getModelGlobalList(std::vector<std::string>&i){
  std::string &b = i[0];
  ((CEGUI::Listbox*)(CState_Testing::ReturnInstance()->WinMan->getWindow("ModelDownloaderSearch")))->resetList();
  std::string lm = non_safe_string_deserialize(b);
  while(lm != "") {
    CEGUI::String un = lm;
    ((CEGUI::Listbox*)(CState_Testing::ReturnInstance()->WinMan->getWindow("ModelDownloaderSearch")))->addItem(new CEGUI::ListboxTextItem(un));
    lm = non_safe_string_deserialize(b);
  }

}
