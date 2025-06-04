

void CState_Testing::createInitialKeyboardMapping() {
	KeyboardMap.Add(new TemplateFunctor<CState_Testing, OIS::KeyCode>(this, &CState_Testing::ToggleMinimap), OIS::KC_M);
	KeyboardMap.Add(new TemplateFunctor<CState_Testing, OIS::KeyCode>(this, &CState_Testing::CyclePolygonFilterMode), OIS::KC_T);
	KeyboardMap.Add(new TemplateFunctor<CState_Testing, OIS::KeyCode>(this, &CState_Testing::CyclePolygonRenderingMode), OIS::KC_R);
	KeyboardMap.Add(new TemplateFunctor<CState_Testing, OIS::KeyCode>(this, &CState_Testing::RefreshAllTextures), OIS::KC_F5);
	KeyboardMap.Add(new TemplateFunctor<CState_Testing, OIS::KeyCode>(this, &CState_Testing::ToggleRareDebugStats), OIS::KC_G);
	KeyboardMap.Add(new TemplateFunctor<CState_Testing, OIS::KeyCode>(this, &CState_Testing::ToggleFrameStats), OIS::KC_F);
	KeyboardMap.Add(new TemplateFunctor<CState_Testing, OIS::KeyCode>(this, &CState_Testing::ScreenShot), OIS::KC_SYSRQ);
}
void CState_Testing::createInitialMouseMapping(){
  
}

void CState_Testing::ToggleMinimap(OIS::KeyCode) {
	if(showing_minimap) {
		m_minimap_window->hide();
		Global_Configuration.Values["MAX_RENDER_CHUNKS"].e = 45;
//		FreelookEditMode = false;
//		FreelookEditModeFPS = false;
//		NewHeightmapLoader::get_instance()->selcur->turnOff();		
	}else {
		m_minimap_window->show();
		//Global_Configuration.Values["MAX_RENDER_CHUNKS"].e = minimap_slider;
	}
	showing_minimap = !showing_minimap;
}
void CState_Testing::CyclePolygonFilterMode(OIS::KeyCode) {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;
        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
}
void CState_Testing::CyclePolygonRenderingMode(OIS::KeyCode) {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
//	m_minimap_camera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
	
}
void CState_Testing::RefreshAllTextures(OIS::KeyCode) {
  Ogre::TextureManager::getSingleton().reloadAll();
}
void CState_Testing::ToggleRareDebugStats(OIS::KeyCode) {
          if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            mTrayMan->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
            mDetailsPanel->show();
        }
        else
        {
            mTrayMan->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
}
void CState_Testing::ToggleFrameStats(OIS::KeyCode) {
	mTrayMan->toggleAdvancedFrameStats();
}
void CState_Testing::ScreenShot(OIS::KeyCode) {
	mRoot->getAutoCreatedWindow()->writeContentsToTimestampedFile("screenshot", ".jpg");
}

bool CState_Testing::Event_ChatTextAdded(const CEGUI::EventArgs& args) {
using namespace CEGUI;
		WindowManager& winMgr = WindowManager::getSingleton();
		Editbox* chatText = static_cast<Editbox*> (winMgr.getWindow("/ChatBox/Text"));
		
		
		std::string text;
		CEGUI::String cetxt = chatText->getText();
		text.append(cetxt.c_str(), cetxt.size());
		{
			std::string text_to_selfchat;
			text_to_selfchat.append("You: ");
			text_to_selfchat.append(text);
			add_chatwindow_text(text_to_selfchat, "MainChatBox");
		}
		mPlayer->headtext = text;
		mPlayer->send_to_server(HeadText);
		// Clear the text in the Editbox
		chatText->setText("");
		return true;
}