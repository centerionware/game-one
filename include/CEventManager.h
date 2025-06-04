/** 
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CEventManager.cpp
 * Description: Manages Events in a separate file, to facilitate implementation of State Machine
 * Legal stuff ~
 */

#ifndef _CGAMEEVENTMANAGER_H_
#define _CGAMEEVENTMANAGER_H_

#include <Ogre.h>
#include <OIS/OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

//#include <OIS.h>
#include <OgreStdHeaders.h>

class CEventManager : public OIS::KeyListener, OIS::MouseListener
{
public:    
    virtual ~CEventManager( void );
    
    
    void OnInit( Ogre::RenderWindow * window );
    
    void OnCapture( void );
    
    
    void AddKeyListener( OIS::KeyListener* keyListener, const std::string& name );
    
    void AddMouseListener( OIS::MouseListener* mouseListener, const std::string& name );
    
    
    void RemoveKeyListener( const std::string& name );
    
    void RemoveMouseListener( const std::string& name );
    
    
    void RemoveKeyListener( OIS::KeyListener * keyListener );
    
    void RemoveMouseListener( OIS::MouseListener * mouseListener );
    
    
    void RemoveAllListeners( void );
    
    void RemoveAllKeyListeners( void );
    
    void RemoveAllMouseListeners( void );
    
    
    void SetWindowDimensions( int W, int H );
    
    
    OIS::Mouse* ReturnMouse( void );
    
    OIS::Keyboard* ReturnKeyboard( void );
    
    
    static CEventManager* ReturnSingletonPointer( void );
    
private:
    CEventManager( void );
    
    CEventManager( const CEventManager& ) { }
    
    CEventManager & operator = ( const CEventManager& );
    
    //These are overrides - golden note to self:
    //dont reinvent the wheel and change things
    //you do not understand
    bool keyPressed( const OIS::KeyEvent & event );
    
    bool keyReleased( const OIS::KeyEvent & event );
    
    
    bool mouseMoved( const OIS::MouseEvent & event );
    
    bool mousePressed( const OIS::MouseEvent & event, OIS::MouseButtonID identifier );
    
    bool mouseReleased( const OIS::MouseEvent & event, OIS::MouseButtonID identifier );
    
    
    OIS::InputManager*	mInputManager;
    
    OIS::Mouse*		mMouse;
    
    OIS::Keyboard*	mKeyboard;
    
    
    std::map< std::string, OIS::KeyListener* > mKeyListeners;
    
    std::map< std::string, OIS::MouseListener* > mMouseListeners;
    
    
    std::map< std::string, OIS::KeyListener* >::iterator iteratorKeyListeners;
    
    std::map< std::string, OIS::MouseListener* >::iterator iteratorMouseListeners;
    
    
    std::map< std::string, OIS::KeyListener* >::iterator iteratorKeyListenersEnd;
    
    std::map< std::string, OIS::MouseListener* >::iterator iteratorMouseListenersEnd;
    
    static CEventManager*	EventManager;
};

#endif // _CGAMEEVENTMANAGER_H_

