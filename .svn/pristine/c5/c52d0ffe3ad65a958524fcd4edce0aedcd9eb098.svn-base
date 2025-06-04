/**
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CGameManager.cpp
 * Description: This source will manage the components required to start various game states.
 * Legal stuff ~
 */

#include "CGameManager.h"
#include "CState.h"
#include "CGUI.h"

template<> CGameManager* Ogre::Singleton<CGameManager>::msSingleton = 0;


CGameManager::CGameManager() :
    mRoot( 0 )
{
      
}

CGameManager::~CGameManager()
{
    StateInterCom.clear();
    
    while( !States.empty() )
    {
	States.back()->Exit();
	States.pop_back();
    }
    
    if( mRenderWindow )
    {
	Ogre::WindowEventUtilities::removeWindowEventListener( mRenderWindow, this );
	windowClosed( mRenderWindow );
    }
    
    
    if( mRoot )
    {
	delete mRoot;
    }
}

void CGameManager::start( CState * state )
{
#ifdef WIN32
	#ifdef _DEBUG
		mOgreCfg 	= "../data/winconfig/ogre.cfg";
		mPluginsCfg =  "../data/winconfig/plugins_d.cfg";
	#else
		mOgreCfg 	= "../data/winconfig/ogre.cfg";
		mPluginsCfg =  "../data/winconfig/plugins.cfg";
	#endif
#else
	#ifdef _DEBUG
		mOgreCfg 	= "../data/config/ogre.cfg";
		mPluginsCfg =  "../data/config/plugins_d.cfg";
	#else
		mOgreCfg 	= "../data/config/ogre.cfg";
		mPluginsCfg =  "../data/config/plugins.cfg";
	#endif
#endif
    mRoot = new Ogre::Root( mPluginsCfg, mOgreCfg );
    
    if ( !Configure() ) return;
    
    SetupResources();
    
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps( 5 );
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    
static bool events_setup = false;
if(!events_setup) {
 EventManager = CEventManager::ReturnSingletonPointer();
    EventManager->OnInit( mRenderWindow );
    EventManager->AddKeyListener( this, "CGameManager" );
    EventManager->AddMouseListener( this, "CGameManager" ); 
events_setup = true;
}

    mRoot->addFrameListener( this );
    Ogre::WindowEventUtilities::addWindowEventListener( mRenderWindow, this );
    
   // CGUI *GUI;
    GUI = new CGUI();
    GUI->Construct();
    
    DoStateChange( state );
  //  mRoot->addFrameListener(this);
    mRoot->startRendering();
    current_state = state;
}

void CGameManager::DoStateChange( CState * state )
{
    if( !States.empty() )
    {
	States.back()->Exit();
	States.pop_back();
    }
    current_state = state;
    States.push_back( state );
    States.back()->Enter();
	
}

void CGameManager::SetupResources( void )
{
    Ogre::ConfigFile configFile;
#ifdef WIN32
	configFile.load("../data/winconfig/resources.cfg");
#else
    configFile.load( "../data/config/resources.cfg" );
#endif
    Ogre::ConfigFile::SectionIterator sect = configFile.getSectionIterator();
    
    std::string sectName, typeName, archName;
    while( sect.hasMoreElements() )
    {
	sectName = sect.peekNextKey();
	
	Ogre::ConfigFile::SettingsMultiMap *settings = sect.getNext();
	Ogre::ConfigFile::SettingsMultiMap::iterator configFileIt;
	for( configFileIt = settings->begin(); configFileIt != settings->end(); ++configFileIt )
	{
	    typeName = configFileIt->first;
	    archName = configFileIt->second;
	    
	    Ogre::ResourceGroupManager::getSingleton().addResourceLocation( archName, typeName, sectName );
	}
    }
}

bool CGameManager::Configure( void )
{
    if( !mRoot->restoreConfig() )
    {
	if( !mRoot->showConfigDialog() )
	{
	    return false;
	}
    }
    
    mRenderWindow = mRoot->initialise( true );
    
//     Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); Initialising here is a mistake
   
    return true;
}

Ogre::RenderWindow * CGameManager::GetRenderWindow()
{
    return mRenderWindow;
}

bool CGameManager::frameRenderingQueued( const Ogre::FrameEvent & event )
{
//     std::cout << "test" << std::endl;
//     EventManager->OnCapture();
//     
     return States.back()->frameRenderingQueued( event );
	return true;
}

bool CGameManager::frameStarted( const Ogre::FrameEvent & event )
{
    EventManager->OnCapture();
    
    return States.back()->frameStarted( event );
}

bool CGameManager::frameEnded( const Ogre::FrameEvent & event )
{
    return States.back()->frameEnded( event );
}

bool CGameManager::keyPressed( const OIS::KeyEvent & event )
{
    States.back()->keyPressed( event );
    
    return true;
}

bool CGameManager::keyReleased( const OIS::KeyEvent & event )
{
    States.back()->keyReleased( event );
    
    return true;
}

bool CGameManager::mouseMoved( const OIS::MouseEvent & event )
{
    States.back()->mouseMoved( event );
    
    return true;
}

bool CGameManager::mousePressed( const OIS::MouseEvent & event, OIS::MouseButtonID identifier )
{
    States.back()->mousePressed( event, identifier );
    
    return true;
}

bool CGameManager::mouseReleased( const OIS::MouseEvent & event, OIS::MouseButtonID identifier )
{
    States.back()->mouseReleased( event, identifier );
    
    return true;
}

CGameManager * CGameManager::ReturnSingletonPointer( void )
{
    return msSingleton;
}

CGameManager & CGameManager::ReturnSingleton( void )
{
    assert( msSingleton );
    
    return *msSingleton;
}

void CGameManager::InsertInterCom( std::string Title, int Arg )
{
    InterCom::iterator Iterator_ = StateInterCom.begin();
    Iterator_ = StateInterCom.find( Title );
    
    if( Iterator_ != StateInterCom.end() )
    {
	//Replace key if it exists
	StateInterCom.erase( Title );
	StateInterCom.insert( std::pair< std::string, int > ( Title, Arg ) );
    }
    else
    {
	//Place key if it doesn't yet exist
	StateInterCom.insert( std::pair< std::string, int > ( Title, Arg ) );
    }
}

int CGameManager::GetInterCom( std::string Query )
{
    InterCom::iterator Iterator_ = StateInterCom.begin();
    Iterator_ = StateInterCom.find( Query );
    
    if( Iterator_ != StateInterCom.end() )
    {
	return Iterator_->second;
    }
    return -1;
}

void CGameManager::windowResized(Ogre::RenderWindow* rw){
  std::cout << "Resizing screen!"<<std::endl;
    rw->windowMovedOrResized();
    EventManager->SetWindowDimensions(rw->getWidth(),rw->getHeight());
    CEGUI::Size size;
   size.d_width = static_cast<float>(rw->getWidth());
   size.d_height = static_cast<float>(rw->getHeight());
   CEGUI::System::getSingleton().notifyDisplaySizeChanged(size);
}


