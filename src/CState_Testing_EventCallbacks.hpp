bool CState_Testing::OnMinimapSliderChanged(const CEGUI::EventArgs &event) {
  const CEGUI::WindowEventArgs &args = (CEGUI::WindowEventArgs&)event;
 minimap_slider = 1-((CEGUI::Scrollbar*)args.window)->getScrollPosition();
 return false;
}
bool CState_Testing::Event_LeaveGame(const CEGUI::EventArgs& e) {
	EscPressed = true;
        DoStateChange( CState_MainMenu::ReturnInstance() );
		return true;
}
extern vec3 from_voxid(unsigned short idx);
bool CState_Testing::Event_RadiusEntered(const CEGUI::EventArgs& e) {
	std::string rad = m_EnterRadius->getChild("EnterRadiusFrameWindow")->getChild("Radius")->getText().c_str();
	std::stringstream conv;
	conv << rad;
	int radius;
	conv >> radius;
	Chunk * selectedChunk = NewHeightmapLoader::get_instance()->getSelChunk();
	vec3 pnt = selectedChunk->position+(from_voxid(NewHeightmapLoader::get_instance()->getSelVoxel())-vec3(15,30,15)); 
	std::vector<string> neout = NewHeightmapLoader::get_instance()->editor_circle_scraper_gen1(pnt, radius);
	if(neout.size() != 0) {
		std::cout << "Sending " << neout.size() << " updates\n";
		std::vector<std::string>::iterator oiter = neout.begin(), nend = neout.end();
		for(;oiter!=nend;++oiter) {
			std::string outputtwo;
			outputtwo+=(to_value(NetCommand));
			outputtwo+=(to_value(PushChunk));
			outputtwo.append( (*oiter));
			mPlayer->send_text(outputtwo,mPlayer->socket);
		}
	} else {
		std::cout << "No chunks returned to update?..\n";
	}
	m_EnterRadius->hide();
	return true;

}
void CState_Testing::Toggle3DView(const CEGUI::EventArgs &event) {
	if(FreelookEditMode) {
		mCamNode->setPosition(mPlayer->position + Ogre::Vector3(0, 25, 0));
		mCamNode->resetOrientation();
		//mMinimapCamPitchNode->resetOrientation();
		mCamNode->pitch(Ogre::Degree(-90),Ogre::Node::TS_LOCAL);
		FreelookEditMode = false;
	} else {
		FreelookEditMode = true;
	}
}
