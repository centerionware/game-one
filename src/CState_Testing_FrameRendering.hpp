
bool CState_Testing::frameStarted( const Ogre::FrameEvent & event )
{
    if(FreelookEditMode) {
		
	mCamNode->translate(mTranslateVector * event.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		
    } 
    {
        std::vector<Ogre::FrameListener*>::iterator iter = pending_delete_frame_listeners.begin(), end = pending_delete_frame_listeners.end();
        for (;iter!=end;iter++) {
            delete (*iter);
        }
        while (pending_delete_frame_listeners.size() > 0) pending_delete_frame_listeners.pop_back();
    }
    {
        std::vector<Ogre::FrameListener*>::iterator iter = Removed_Frame_Listeners.begin(), end = Removed_Frame_Listeners.end();
        for (;iter!=end;iter++) {
            Ogre::Root::getSingletonPtr()->removeFrameListener((*iter));
            pending_delete_frame_listeners.push_back(*iter);
        }
        while (Removed_Frame_Listeners.size() > 0) Removed_Frame_Listeners.pop_back();
    }
    
    if( IsConnected == false )
    {
	CGameManager::ReturnSingletonPointer()->InsertInterCom( "MainMenu", LostConnectionStates::MAINMENU_DISCONNECTED_FROM_SERVER );
	DoStateChange( CState_MainMenu::ReturnInstance() );
    }
    
    return true;
}


bool CState_Testing::frameRenderingQueued( const Ogre::FrameEvent &event)
{
    mPlayer->pump_net_messages();
    mPlayer->inet_update_other_players(event);
    NewHeightmapLoader::get_instance()->transparent_roofs(mPlayer.get());
   // mPlayer->frameRenderingQueued(event); // do it before the raycast, before moving the camera. if after the raycast it never progresses.
    CEGUI::Window* sheet = CEGUI::System::getSingleton().getGUISheet();
    CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    CEGUI::Window* active_window = sheet->getChildAtPosition(mousePos);
    if((FreelookEditMode || FreelookEditModeFPS) && Window && !m_texture_atlas->isVisible()) {
		float x,y;
		CEGUI::Rect orect = Window->getInnerRectClipper();
		x = (float)((float)mousePos.d_x-(float)orect.d_left)/((float)orect.d_right-orect.d_left);
		y = (float)((float)mousePos.d_y-(float)orect.d_top) / ((float)orect.d_bottom-orect.d_top);
		NewHeightmapLoader::get_instance()->viewportSelectionArea(x,y,mCamera);
    }
 
    float current_time = CState_Clock.getMicroseconds();
    if (current_time >= 200000 || instant_rightmouse_movement_initiate) {
	if(instant_rightmouse_movement_initiate)instant_rightmouse_movement_initiate = false;
	CState_Clock.reset();
	static vec3 opos = vec3(0.0,0.5,0.0);
       

	
	if (isrightmouse == true ) {
	    Ogre::Viewport* vp = mSceneManager->getCurrentViewport();
		    float x,y;
		    const Ogre::Camera *outcam = NULL;
	//	    if(showing_minimap && (active_window && (active_window->getName() == "MinimapImage" || active_window->getName() == "TerrainMinimap"))) {
	//		    CEGUI::Rect orect = active_window->getInnerRectClipper();
	//		    x = (float)((float)mousePos.d_x-(float)orect.d_left)/((float)orect.d_right-orect.d_left);
	//		    y = (float)((float)mousePos.d_y-(float)orect.d_top) / ((float)orect.d_bottom-orect.d_top);
	//		    outcam = m_minimap_camera;
	//	    } else {
			    x = mousePos.d_x / float(vp->getActualWidth());
			    y = mousePos.d_y / float(vp->getActualHeight());
	//		    outcam = mCamera;
	//	    }
    //        float x = CEGUI::MouseCursor::getSingleton().getPosition().d_x/float(vp->getActualWidth());
      //      float y = CEGUI::MouseCursor::getSingleton().getPosition().d_y/float(vp->getActualHeight());
	    
	    ViewportClickReturnVoxel nm = NewHeightmapLoader::get_instance()->viewportRightClicked(x,y,outcam);
	    if(nm.found)
	    mPlayer->actual_target_position = vec3(nm.position);//+vec3(0,.5,0);
	
	}
	if (mPlayer->actual_target_position != opos) {
		mPlayer->send_to_server(Position);
		opos = mPlayer->targetposition;
		opos = mPlayer->actual_target_position;
	}
   }
   if(mPlayer->walking && mPlayer->actual_target_position == vec3(mPlayer->mSceneNd->getPosition())) {
    mPlayer->walking = false;
    mPlayer->mCharWalkAnimationState->setEnabled(false);
   }
// if(isrightmouse == true) ++frame_since_lastraycast;
   if(!FreelookEditMode && !FreelookEditModeFPS)
	   {
		   mCamNode->setPosition(mPlayer->position.x+camera_circle_position_offset.xOff(),mPlayer->position.y+15.5,mPlayer->position.z+camera_circle_position_offset.yOff());
		   
		  
		   mCamNode->lookAt(mPlayer->position, Ogre::Node::TS_WORLD);
	   }
	else if(FreelookEditModeFPS) mCamNode->setPosition(mPlayer->position.x,mPlayer->position.y+3.0,mPlayer->position.z);
//    mCamNode->setPosition(mPlayer->position.x,mPlayer->position.y+25.5,mPlayer->position.z);
    if(0&&showing_minimap) {
		float x = minimap_slider; 
		float top = 325;
		top = std::ceil(top*x);
		// unsigned int max_render = 1;
		/*
			layer1 = 1*1; 1
			layer2 = 3*3; 9
			layer3 = 5*5; 25
			layer4 = 7*7; 49
			layer5 = 9*9; 81
			layer6 = 11*11; 121
			layer7 = 13*13; 169
			*/
		if(top <= 50) {
			Global_Configuration.Values["MAX_RENDER_CHUNKS"].e = 9;
		} else if(top > 250) {
			Global_Configuration.Values["MAX_RENDER_CHUNKS"].e = 121;
		} else if(top > 200) {
			Global_Configuration.Values["MAX_RENDER_CHUNKS"].e = 81;
		} else if(top > 150) {
			Global_Configuration.Values["MAX_RENDER_CHUNKS"].e = 49;
		} else if(top > 50) {
			Global_Configuration.Values["MAX_RENDER_CHUNKS"].e = 25;
		}
		  //  Global_Configuration.Values["MAX_RENDER_CHUNKS"].e = max_render;
//		mMinimapCamNode->setPosition(mPlayer->position.x,mPlayer->position.y+3.5+top,mPlayer->position.z);
	}
	

//	m_minimap_rt->update();
//	minimap->hide();
//	minimap->show();
 //   } else {
////	  mMinimapCamNode->setPosition(mPlayer->position.x,mPlayer->position.y+3.5,mPlayer->position.z); // This will reduce the size to render when minimap is  closed..
 //   } 

    create_heightmap_each_frame(mCamera);
    //create_heightmap_each_frame(m_minimap_camera);
  
    mTrayMan->frameRenderingQueued(event);

    if (!mTrayMan->isDialogVisible())
    {
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }
    return true;
}

bool CState_Testing::frameEnded( const Ogre::FrameEvent & event )
{
	if ( switch_1 == false ) i = i + 0.01;
	if ( switch_1 == true) i = i - 0.01;
	if ( i <= 0.00 ) switch_1 = false;
	if ( i >= 1 ) switch_1 = true;
	if ( switch_2 == false && switch_1 == true ) j = j + 0.01;
	if ( switch_2 == true && switch_1 == false ) j = j - 0.01;
	if ( j <= 0.00 ) switch_2 = false;
	if ( j >= 1 ) switch_2 = true;

//	HUD.UpdateHealth(i);
//	HUD.UpdateFatigue(j);

	if ( IsRunning == false )
	{
	    return false;
	}
	return true;
}