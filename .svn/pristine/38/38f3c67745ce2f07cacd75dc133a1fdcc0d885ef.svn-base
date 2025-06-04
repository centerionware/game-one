CEGUI::Window *basic_window_create(std::string type, std::string name, float x, float y, float sx, float sy, CEGUI::WindowManager *WinMan) {
	auto nw = WinMan->createWindow(type.c_str(), name.c_str());
	nw->setPosition(CEGUI::UVector2(cegui_reldim(x), cegui_reldim(y)));
	nw->setSize(CEGUI::UVector2(cegui_reldim(sx), cegui_reldim(sy)));
	return nw;
}

#define event_subscribe(winname, eventType,eventCallback) { CState_Testing::ReturnInstance()->WinMan->getWindow(winname)->subscribeEvent(eventType,CEGUI::Event::Subscriber(&eventCallback,this)); } 
/*
template<class X, class Y, typename Z>
void event_subscribe(const X winname, const Y eventType, const Z *eventCallback)  {
   CState_Testing *i = CState_Testing::ReturnInstance();
   CState_Testing::ReturnInstance()->WinMan->getWindow(winname)->subscribeEvent(eventType,CEGUI::Event::Subscriber(eventCallback,CState_Testing::ReturnInstance()));
}*/
namespace gui_modules {
#include "OLC/base_gui.hpp"
};

void CState_Testing::CreateGUI( void )
{
    WinMan = CEGUI::WindowManager::getSingletonPtr();
    SysMan = CEGUI::System::getSingletonPtr();
    Window = CEGUI::WindowManager::getSingleton().loadWindowLayout("../data/gui/layouts/HUD_Base.layout");

    SysMan->setGUISheet( Window );
    /*
    m_minimap_camera=mSceneManager->createCamera("minimap_camera");
    m_minimap_camera->setNearClipDistance(0.1);
    m_minimap_camera->setFarClipDistance(2000);
    m_minimap_camera->setPosition( Ogre::Vector3( 0, 0, 0 ) );
    m_minimap_camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    
    mMinimapCamNode = mSceneManager->getRootSceneNode()->createChildSceneNode("MinimapCamNode", Ogre::Vector3(0, 25, 0));
	mMinimapCamNode->attachObject(m_minimap_camera);
	mMinimapCamNode->pitch(Ogre::Degree(-90),Ogre::Node::TS_LOCAL);

   
   Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual( "minimap_tex", 
         "General", Ogre::TEX_TYPE_2D,    512,512, 0, Ogre::PF_R8G8B8A8, Ogre::TU_RENDERTARGET );
   
   m_minimap_rt = texture->getBuffer()->getRenderTarget();
   m_minimap_rt ->setAutoUpdated(false);
   
   Ogre::Viewport *v = m_minimap_rt->addViewport( m_minimap_camera );
  // v->setClearEveryFrame(true);
   v->setOverlaysEnabled (true);
   v->setBackgroundColour(Ogre::ColourValue(0,0,0,0) );
   m_minimap_camera->setAspectRatio(Ogre::Real(v->getActualWidth()) / Ogre::Real(v->getActualHeight()));
   
   CEGUI::OgreTexture* ceguiTex = (CEGUI::OgreTexture*)
	  &((CEGUI::OgreRenderer*)CEGUI::System::getSingleton().getRenderer())->createTexture( texture,true);
   
   textureImageSet = &CEGUI::ImagesetManager::getSingleton().create("minimap", *ceguiTex);
   textureImageSet->setAutoScalingEnabled(true);
   textureImageSet->defineImage( "minimap_img", 
                  CEGUI::Point( 0.0f, 0.0f ), 
                  CEGUI::Size( 512,512),//((CEGUI::Texture*)ceguiTex)->getWidth(), ((CEGUI::Texture*)ceguiTex->getHeight()) ), 
                  CEGUI::Point( 0.0f, 0.0f ) ); 
   
	// DEBUG("size %i %i",ceguiTex->getWidth(), ceguiTex->getHeight() );
	// I tried moving the minimap window part to the MiniMap.layout, but it failed to render no matter what i changed.
	// I have no idea why.
	minimap =(CEGUI::FrameWindow*) WinMan->createWindow("TaharezLook/FrameWindow", "MinimapWindow");
	*/
	m_texture_atlas = (CEGUI::FrameWindow*) WinMan->createWindow("TaharezLook/FrameWindow", "TextureAtlasWindow");
	auto mtex_labl = WinMan->loadWindowLayout("../data/gui/layouts/TextureAtlas.layout");
	m_texture_atlas->addChildWindow(mtex_labl);



	mtex_labl->setInheritsAlpha(false);
	mtex_labl->setAlpha(1.0);
	m_texture_atlas->setPosition(CEGUI::UVector2(cegui_reldim(0.05f), cegui_reldim( 0.05f))); //0.0/0.8
	m_texture_atlas->setSize(CEGUI::UVector2(cegui_reldim(0.9f), cegui_reldim( 0.8f)));
	m_texture_atlas->hide();
	m_texture_atlas->setProperty("FrameEnabled","false");
	m_texture_atlas->setProperty("TitlebarEnabled","false");
	m_texture_atlas->setProperty("CloseButtonEnabled","false");
	m_texture_atlas->setAlpha (0.0);
	m_EnterRadius = (CEGUI::FrameWindow*) WinMan->createWindow("TaharezLook/FrameWindow", "EnterRadiusWindow");


	auto enterRadius_label = WinMan->loadWindowLayout("../data/gui/layouts/EnterRadius.layout");
	m_EnterRadius->addChildWindow(enterRadius_label);
	enterRadius_label->setInheritsAlpha(false);
	enterRadius_label->setAlpha(1.0);
	m_EnterRadius->setPosition(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim( 0.25f))); //0.0/0.8
	m_EnterRadius->setSize(CEGUI::UVector2(cegui_reldim(0.55f), cegui_reldim( 0.55f)));
	m_EnterRadius->hide();
	m_EnterRadius->setProperty("FrameEnabled","false");
	m_EnterRadius->setProperty("TitlebarEnabled","false");
	m_EnterRadius->setProperty("CloseButtonEnabled","false");
	m_EnterRadius->setAlpha (0.0);
	//m_minimap_window = minimap;
	/*
	minimap->setPosition(CEGUI::UVector2(cegui_reldim(0.05f), cegui_reldim( 0.05f))); //0.0/0.8
	minimap->setSize(CEGUI::UVector2(cegui_reldim(0.9f), cegui_reldim( 0.8f))); //1.0/0.2
	minimap->setProperty("FrameEnabled","false");
	minimap->setProperty("TitlebarEnabled","false");
	minimap->setProperty("CloseButtonEnabled","true");
	minimap->setAlpha (0.0);*/
	Window->addChildWindow(m_texture_atlas);
	Window->addChildWindow(m_EnterRadius);
	//Window->addChildWindow(minimap);
	
	//minimap->addChildWindow( WinMan->loadWindowLayout( "../data/gui/layouts/MiniMap.layout" ));
	//minimap->hide();
	
	gui_modules::initialize_modules();
	//event_subscribe("MinimapZoom", CEGUI::Scrollbar::EventScrollPositionChanged,CState_Testing::OnMinimapSliderChanged);
	event_subscribe("LeaveButton", CEGUI::PushButton::EventClicked, CState_Testing::Event_LeaveGame);
	event_subscribe("RadiusEnterButton", CEGUI::PushButton::EventClicked, CState_Testing::Event_RadiusEntered);
/*
 *  All of the following need to be event subscribed and created for both client side and server side..
 *  There seems to be an awful lot of boiler code necessary to do it all..   
    bool OnItemOLCSearch(const CEGUI::EventArgs &event);
    bool OnItemModifyPress(const CEGUI::EventArgs &event);
    bool OnItemDeletePress(const CEGUI::EventArgs &event);
    bool OnItemLockPress(const CEGUI::EventArgs &event);
    bool OnItemDetailsRequest(const CEGUI::EventArgs &event);
    bool OnItemAddPress(const CEGUI::EventArgs &event);

    bool OnModelOLCSearch(const CEGUI::EventArgs &event);
    bool OnModelModifyPress(const CEGUI::EventArgs &event);
    bool OnModelDeletePress(const CEGUI::EventArgs &event);
    bool OnModelLockPress(const CEGUI::EventArgs &event);
    bool OnModelDetailsRequest(const CEGUI::EventArgs &event);
    bool OnModelAddPress(const CEGUI::EventArgs &event);
    
 */
//	WinMan->getWindow("chat_box")->setEnabled(true);
   
}