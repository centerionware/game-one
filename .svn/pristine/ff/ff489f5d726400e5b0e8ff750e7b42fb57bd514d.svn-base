#include <stddef.h>
#include "CGUI.h"
#include <iostream>
CGUI::CGUI() 
{
    GUIRenderer = NULL;
}

CGUI::~CGUI()
{
    try
    {
	    CEGUI::OgreRenderer::destroySystem(); // deletes everything
    }
    catch(std::exception& e)
    {
// 	    this happens, if the program dies before the renderer was initialized
	    printf("Caught exception: [%s]", e.what ());
    }
}

void CGUI::Construct()
{   
    CEGUI::OgreRenderer::bootstrapSystem();
    CEGUI::Font::setDefaultResourceGroup("Fonts"); 
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::AnimationManager::setDefaultResourceGroup("Animations");
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
    CEGUI::SchemeManager::getSingleton().create("GameOneLook.scheme");
    CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
    CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());
	CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("WaitSpinner.animation");
}
