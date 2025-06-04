/**
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CHUD.h
 * Description: Control the playing state's Heads Up Display
 * Legal stuff
 */

#ifndef _CHUD_H_
#define _CHUD_H_

#include <OIS.h>

#include <CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

class CHUD
{
private:
//     int mHistorySize;
//     CEGUI::Window	*Instruments;

public:
    CHUD();
    ~CHUD();

    /** General HUD functions */
    void CreateHUD( );
    void DestroyHUD();

    /** Player Status HUD Instruments*/
    void UpdateHealth( const float& Percent );
    void UpdateFatigue( const float& Percent );

    /** ChatBox instrument functions */
    void CreateChatBox();
    void RegisterHandlers();
    bool Handle_TextSubmitted( const CEGUI::EventArgs &e );
    bool Handle_SendButtonPressed( const CEGUI::EventArgs &e );
    void ParseText( CEGUI::String message );
    void OutputText( CEGUI::String message, CEGUI::colour colour = CEGUI::colour( 0xFFFFFFFF ) );
};

#endif //_CHUD_H_