/**
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CState_Splash.h
 * Description: Introductory Game State
 * Legal stuff ~
 */


#ifndef CSTATE_SPLASH_H
#define CSTATE_SPLASH_H

#include <Ogre.h>
#include <OgreViewport.h>

#include <OIS.h>

#include <CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <SdkCameraMan.h>

#include "dotscene/dotscene.h"

#include "CState.h"
#include "CState_MainMenu.h"
#include "server-map.h"


class CState_Splash : public CState
{
public:
    void Enter();
    
    void Exit();
    
    
    void Pause();
    
    void Resume();
    
    
    bool frameStarted( const Ogre::FrameEvent & event );
    
    bool frameRenderingQueued( const Ogre::FrameEvent &event);
    
    bool frameEnded( const Ogre::FrameEvent & event );
    
    
    void keyPressed( const OIS::KeyEvent & event );
    
    void keyReleased( const OIS::KeyEvent & event );
    
    
    void mouseMoved( const OIS::MouseEvent & event );
    
    void mousePressed( const OIS::MouseEvent & event, OIS::MouseButtonID identifier );
    
    void mouseReleased( const OIS::MouseEvent & event, OIS::MouseButtonID identifier );
    
    static CState_Splash * ReturnInstance() { return & STATE_SPLASH; }
    
    float Alpha;
    
    void FadeIn();
    
    void FadeOut();
    
    bool ActivateFadeOut;
    
protected:
    CState_Splash() {};
    
    void CreateGUI( void );
    
    bool IsRunning;

    CEGUI::MouseCursor		*MouseCursor;
    CEGUI::AnimationInstance* spinner_instance;
private:
    static CState_Splash STATE_SPLASH;
};

#endif // CSTATE_SPLASH_H
