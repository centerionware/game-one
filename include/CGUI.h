/**
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CGUI.cpp
 * Description: Graphical User Interface control
 * Legal stuff
 */
//     CEGUI::Font::setDefaultResourceGroup("Fonts"); 
//     CEGUI::Scheme::setDefaultResourceGroup("Schemes");
//     CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
//     CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
//     CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
//     CEGUI::SchemeManager::getSingleton().create("GameOneLook.scheme");
//     CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
//     CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());

#ifndef CGUI_H
#define CGUI_H

#include "CEGUI.h"
#include "CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h"

class CGUI
{    
public:
    CEGUI::OgreRenderer * GUIRenderer;
    
    CGUI();
    ~CGUI();
    
    void Construct();
};

#endif // CGUI_H
