/**
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CState_Splash.h
 * Description: Introductory Game State
 * Legal stuff ~
 */

#include "CState_Splash.h"
#include "CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h"

CState_Splash CState_Splash::STATE_SPLASH;

void CState_Splash::FadeIn()
{
    if ( Alpha > 0 )
    {
        Alpha = Alpha - 0.01;
        WinMan->getWindow( "Splash/imgSplashAlpha" )->setAlpha( Alpha );
    }
}

void CState_Splash::FadeOut()
{
    Alpha = Alpha + 0.01;
    WinMan->getWindow( "Splash/imgSplashAlpha" )->setAlpha( Alpha );
    if ( Alpha > 1 )
    {
        DoStateChange( CState_MainMenu::ReturnInstance() );
    }
}

void CState_Splash::CreateGUI( void )
{
    WinMan	= CEGUI::WindowManager::getSingletonPtr();
    SysMan	= CEGUI::System::getSingletonPtr();
    MouseCursor	= CEGUI::MouseCursor::getSingletonPtr();
    
    Window = WinMan->loadWindowLayout( "Splash.layout" );
    
    SysMan->setGUISheet( Window );
    MouseCursor->hide();
	
}

void CState_Splash::Enter()
{
    Alpha = 1;
    ActivateFadeOut = false;
    mRoot = Ogre::Root::getSingletonPtr();
    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC);
    CreateGUI();
    IsRunning = true;
	spinner_instance =  CEGUI::AnimationManager::getSingleton().instantiateAnimation("WaitSpinner");
	spinner_instance->setTargetWindow(CEGUI::WindowManager::getSingleton().getWindow("Splash/WaitSpinner"));
	spinner_instance->start();
}

void CState_Splash::Exit()
{
	CEGUI::AnimationManager::getSingleton().destroyAnimationInstance(spinner_instance);
    CEGUI::WindowManager::getSingleton().destroyWindow( Window );

    if ( mSceneManager != NULL )
    {
        mSceneManager->clearScene();
    }

    mRoot->getAutoCreatedWindow()->removeAllViewports();
    MouseCursor->show();
}

bool CState_Splash::frameStarted( const Ogre::FrameEvent & event )
{
	if(event.timeSinceLastFrame > 0.0)
	SysMan->injectTimePulse(event.timeSinceLastFrame);
    if ( ActivateFadeOut == false )
    {
        FadeIn();
    }

    if ( ActivateFadeOut == true )
    {
        FadeOut();
    }
    return true;
}

bool CState_Splash::frameRenderingQueued( const Ogre::FrameEvent &event)
{
    return true;
}

bool CState_Splash::frameEnded( const Ogre::FrameEvent & event )
{
    if ( IsRunning == false )
    {
        return false;
    }

    return true;
}

void CState_Splash::keyPressed( const OIS::KeyEvent  & event)
{
    SysMan->injectKeyDown( event.key );
    SysMan->injectChar( event.text );
}

void CState_Splash::keyReleased( const OIS::KeyEvent  & event)
{
    SysMan->injectKeyUp( event.key );
    SysMan->injectChar( event.text );

    if ( event.key == OIS::KC_ESCAPE )
    {
        ActivateFadeOut = true;
    } else if ( event.key == OIS::KC_SPACE )
    {
        ActivateFadeOut = true;
    }
}

void CState_Splash::mouseMoved( const OIS::MouseEvent  & event)
{
    SysMan->injectMouseMove( event.state.X.rel, event.state.Y.rel );
}

void CState_Splash::mousePressed( const OIS::MouseEvent  & event, OIS::MouseButtonID identifier )
{
    switch ( identifier )
    {
    case OIS::MB_Left:
    {
        SysMan->injectMouseButtonDown( CEGUI::LeftButton );
        break;
    }

    case OIS::MB_Right:
    {
        SysMan->injectMouseButtonDown( CEGUI::RightButton );
        break;
    }

    case OIS::MB_Middle:
    {
        SysMan->injectMouseButtonDown( CEGUI::MiddleButton );
        break;
    }

    default:
    {
        SysMan->injectMouseButtonDown( CEGUI::LeftButton);
    }

    }
}

void CState_Splash::mouseReleased( const OIS::MouseEvent  & event, OIS::MouseButtonID identifier )
{
    switch ( identifier )
    {
    case OIS::MB_Left:
    {
        SysMan->injectMouseButtonUp( CEGUI::LeftButton );
        break;
    }

    case OIS::MB_Right:
    {
        SysMan->injectMouseButtonUp( CEGUI::RightButton );
        break;
    }

    case OIS::MB_Middle:
    {
        SysMan->injectMouseButtonUp( CEGUI::MiddleButton );

        break;
    }

    default:
    {
        SysMan->injectMouseButtonUp( CEGUI::LeftButton);
    }
    }
}
