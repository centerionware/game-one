/**
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CEventManager.cpp
 * Description: Manages Events in a separate file, to facilitate implementation of State Machine
 * Legal stuff ~
 */

#include "CEventManager.h"

CEventManager *CEventManager::EventManager=NULL;

CEventManager::CEventManager( void ) :
    mInputManager( 0 ),
    mMouse( 0 ),
    mKeyboard( 0 )
{
}

CEventManager::~CEventManager( void )
{
    if( mInputManager )
    {
	if( mMouse )
	{
	    mInputManager->destroyInputObject( mMouse );
	    mMouse = 0;
	}
	
	if( mKeyboard )
	{
	    mInputManager->destroyInputObject( mKeyboard );
	    mKeyboard = 0;
	}
	mInputManager->destroyInputSystem(mInputManager);
	OIS::InputManager::destroyInputSystem( mInputManager );
	mInputManager = 0;
	
	mKeyListeners.clear();
	mMouseListeners.clear();
    }
}

void CEventManager::OnInit( Ogre::RenderWindow * window )
{
    if( !mInputManager )
    {
	OIS::ParamList paramList;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	
	window->getCustomAttribute( "WINDOW", &windowHnd );
	windowHndStr << windowHnd;
	
	paramList.insert( std::make_pair( std::string( "WINDOW" ), windowHndStr.str() ) );
	
	mInputManager = OIS::InputManager::createInputSystem( paramList );
	
	mKeyboard = static_cast<OIS::Keyboard*>( mInputManager->createInputObject( OIS::OISKeyboard, true ) );
	mKeyboard->setEventCallback( this );
	
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ) );
	mMouse->setEventCallback( this );
	
// 	Ogre::WindowEventUtilities::addWindowEventListener( window );
	
	unsigned int width, height, depth;
	int left, top;
	
 	window->getMetrics( width, height, depth, left, top );
  	this->SetWindowDimensions( width, height );
    }
}

void CEventManager::OnCapture( void )
{
//     if( mMouse )
//     {
	mMouse->capture();
//     }
    
//     if( mKeyboard )
//     {
	mKeyboard->capture();
//     }
}

// void CEventManager::AddKeyListener( OIS::KeyListener * keyListener, const std::string & name )
// {
//     if( mKeyboard )
//     {
// 	iteratorKeyListeners = mKeyListeners.find( name );
// 	
// 	if( iteratorKeyListeners = mKeyListeners.end() )
// 	{
// 	    mKeyListeners[ name ] = keyListener;
// 	}
// 	else
// 	{
// 	}
//     }
// }

void CEventManager::AddKeyListener( OIS::KeyListener * keyListener, const std::string & name )
{
    if( mKeyboard )
    {
	iteratorKeyListeners = mKeyListeners.find( name );
	
	if( iteratorKeyListeners == mKeyListeners.end() )
	{
	    mKeyListeners[ name ] = keyListener;
	}
	else
	{
	}
    }
}

void CEventManager::AddMouseListener( OIS::MouseListener* mouseListener, const std::string& name )
{
    if( mMouse )
    {
	iteratorMouseListeners = mMouseListeners.find( name );
	
	if( iteratorMouseListeners == mMouseListeners.end() )
	{
	    mMouseListeners[ name ] = mouseListener;
	}
    }
}

void CEventManager::RemoveKeyListener( const std::string & name )
{
    iteratorKeyListeners = mKeyListeners.find( name );
    
    if( iteratorKeyListeners != mKeyListeners.end() )
    {
	mKeyListeners.erase( iteratorKeyListeners );
    }
    else
    {
	
    }
}

void CEventManager::RemoveMouseListener( const std::string & name )
{
    iteratorMouseListeners = mMouseListeners.find( name );
    
    if( iteratorMouseListeners != mMouseListeners.end() )
    {
	mMouseListeners.erase( iteratorMouseListeners );
    }
    else
    {
	
    }
}

void CEventManager::RemoveKeyListener( OIS::KeyListener * keyListener )
{
    iteratorKeyListeners	=	mKeyListeners.begin();
    iteratorKeyListenersEnd	=	mKeyListeners.end();
    
    for( ; iteratorKeyListeners != iteratorKeyListenersEnd; ++iteratorKeyListeners )
    {
	if( iteratorKeyListeners->second == keyListener )
	{
	    mKeyListeners.erase( iteratorKeyListeners );
	}
    }
}

void CEventManager::RemoveMouseListener( OIS::MouseListener * mouseListener )
{
    iteratorMouseListeners	=	mMouseListeners.begin();
    iteratorMouseListenersEnd	=	mMouseListeners.end();
    
    for( ; iteratorMouseListeners != iteratorMouseListenersEnd; ++iteratorMouseListeners )
    {
	if( iteratorMouseListeners->second == mouseListener )
	{
	    mMouseListeners.erase( iteratorMouseListeners );
	}
    }
}

void CEventManager::RemoveAllListeners( void )
{
    mKeyListeners.clear();
    mMouseListeners.clear();
}

void CEventManager::RemoveAllKeyListeners( void )
{
    mKeyListeners.clear();
}

void CEventManager::RemoveAllMouseListeners( void )
{
    mMouseListeners.clear();
}

void CEventManager::SetWindowDimensions( int W, int H ) 
{
    const OIS::MouseState &mouseState = mMouse->getMouseState();
    
    mouseState.width = W;
    mouseState.height = H;
}

OIS::Mouse * CEventManager::ReturnMouse( void )
{
    return mMouse;
}

OIS::Keyboard * CEventManager::ReturnKeyboard( void )
{
    return mKeyboard;
}

bool CEventManager::keyPressed( const OIS::KeyEvent & event )
{
    iteratorKeyListeners	= mKeyListeners.begin();
    iteratorKeyListenersEnd	= mKeyListeners.end();
    
    for( ; iteratorKeyListeners != iteratorKeyListenersEnd; ++iteratorKeyListeners )
    {
	iteratorKeyListeners->second->keyPressed( event );
    }
    
    return true;
}

bool CEventManager::keyReleased( const OIS::KeyEvent & event )
{
    iteratorKeyListeners	= mKeyListeners.begin();
    iteratorKeyListenersEnd	= mKeyListeners.end();
    
    for( ; iteratorKeyListeners != iteratorKeyListenersEnd; ++iteratorKeyListeners )
    {
	iteratorKeyListeners->second->keyReleased( event );
    }
    
    return true;
}

bool CEventManager::mouseMoved( const OIS::MouseEvent & event )
{
    iteratorMouseListeners	= mMouseListeners.begin();
    iteratorMouseListenersEnd	= mMouseListeners.end();
    
    for( ; iteratorMouseListeners != iteratorMouseListenersEnd; ++iteratorMouseListeners )
    {
	iteratorMouseListeners->second->mouseMoved( event );
    }
    
    return true;
}

bool CEventManager::mousePressed( const OIS::MouseEvent & event, OIS::MouseButtonID identifier )
{
    iteratorMouseListeners	= mMouseListeners.begin();
    iteratorMouseListenersEnd	= mMouseListeners.end();
    
    for( ; iteratorMouseListeners != iteratorMouseListenersEnd; ++iteratorMouseListeners )
    {
	iteratorMouseListeners->second->mousePressed( event, identifier );
    }
    
    return true;
}

bool CEventManager::mouseReleased( const OIS::MouseEvent & event, OIS::MouseButtonID identifier )
{
    iteratorMouseListeners	= mMouseListeners.begin();
    iteratorMouseListenersEnd	= mMouseListeners.end();
    
    for( ; iteratorMouseListeners != iteratorMouseListenersEnd; ++iteratorMouseListeners )
    {
	iteratorMouseListeners->second->mouseReleased( event, identifier );
    }
    
    return true;
}

CEventManager *CEventManager::ReturnSingletonPointer( void )
{
    if( !EventManager )
    {
	EventManager = new CEventManager();
    }
    
    return EventManager;
}
