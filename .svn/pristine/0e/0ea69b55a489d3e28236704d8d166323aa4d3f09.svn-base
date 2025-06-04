/**
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CState_Testing.h
 * Description: Introductory Game State
 * Legal stuff ~
 */

#include "CState_Testing.h"
#include "CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h"
#include "CEGUI/RendererModules/Ogre/CEGUIOgreTexture.h"
#include <time.h>

/*
yyyyyyy  layer1 = 1*1; 1
y12345y  layer2 = 3*3; 9
y6xxxay  layer3 = 5*5; 25
y7xixby  layer4 = 7*7; 49
y8xxxcy  layer5 = 9*9; 81
y9defgy  layer6 = 11*11; 121
yyyyyyy  layer7 = 13*13; 169

*/
#include "CState_Testing_Borrowed_Editstring.hpp"
#include "CState_Testing_Globals.hpp"


CState_Testing::CState_Testing()  {
	createInitialKeyboardMapping();
	createInitialMouseMapping();
	minimap_slider = 1;
	FreelookEditMode = false;
	FreelookEditModeFPS = false;
	
}

CState_Testing::~CState_Testing() {
 //   if (mPlayer != boost::shared_ptr<inet_player>()){
//	auto i = Players.begin(), ie = Players.end();
//		for(;i!=ie;++i) if((*i) == mPlayer) { Players.erase(i); break; }
  //    mPlayer.reset();//delete mPlayer;
 //   }
 //   NewHeightmapLoader::clean_instance();
}
CState_Testing CState_Testing::STATE_TESTING;

#include "CState_Testing_createViewportSceneCamera.hpp"
#include "CState_Testing_createGui.hpp"
#include "CState_Testing_EventCallbacks.hpp"
#include "CState_Testing_Enter.hpp"

#include "CState_Testing_Exit.hpp"
#include "CState_Testing_FrameRendering.hpp"
#include "CState_Testing_KeyboardMappings.hpp"
#include "CState_Testing_keyPressed.hpp"

#include "CState_Testing_EverythingMouse.hpp"
// inline include cstate_testing_networkstuffs
void CState_Testing::ConnectionSuccess() {
	std::string uname = CState_MainMenu_Login::ReturnInstance()->mUname;
	std::string pword = CState_MainMenu_Login::ReturnInstance()->mPword;
	char op[4];
	size_t t_si = uname.size();
	memcpy(op, &(t_si), 4);
	std::string update;
	update += to_value(LoginCommand);
	update += to_value(DoLogin);
	//update+= (char)1;
	//update+= (char)3;
	update.append(op,4);
	t_si = pword.size();
	memcpy(op, &(t_si), 4);
	update.append(op,4);
	update.append(uname.c_str(), uname.size());
	update.append(pword.c_str(), pword.size());
	mPlayer->send_text(update, mPlayer->socket);
	IsConnected = true;
}

void CState_Testing::ConnectionClosed() {
    if ( EscPressed == false )
    {
	IsConnected = false;
    }
}
