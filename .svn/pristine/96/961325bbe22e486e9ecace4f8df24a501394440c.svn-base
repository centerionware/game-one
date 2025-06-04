/**
 * GAME-ONE APPLICATION FRAMEWORK
 * Filename: CHUD.cpp
 * Description: Functions to control the playing state's Heads Up Display
 * Legal stuff
 */
#include <stddef.h>
#include "CHUD.h"
#include "iostream"

CHUD::CHUD()
{
}

CHUD::~CHUD()
{
}

void CHUD::DestroyHUD()
{
//     CEGUI::OgreRenderer::destroySystem(); 
}

void CHUD::CreateHUD()
{
//     Instruments	= NULL;
//     
// //     Renderer = &CEGUI::OgreRenderer::bootstrapSystem();
//     //CEGUI::WindowManager *WinMan = CEGUI::WindowManager::getSingletonPtr();
// 
//     
//     
//      Instruments = CEGUI::WindowManager::getSingleton().loadWindowLayout("../data/gui/layouts/HUD.layout"); 
// // //     mInstrumentsWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("../data/gui/layouts/Instruments_Instruments.layout"); 
// //     
// 
//  	CEGUI::System::getSingleton().getGUISheet()->addChildWindow( Instruments );
//   	(this)->RegisterHandlers();

//      if( mInstrumentsWindow )
}

void CHUD::RegisterHandlers()
{
//     std::cout << "TEST 1" << std::endl;
//     CEGUI::WindowManager *WinMan = CEGUI::WindowManager::getSingletonPtr();
//     WinMan->getWindow( "Root/btnSubmit" )->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( &CHUD::Handle_SendButtonPressed, this ) );
}

bool CHUD::Handle_SendButtonPressed( const CEGUI::EventArgs &e )
{
//     std::cout << "TEST 2" << std::endl;
//     CEGUI::String message = Instruments->getChild( "Root/txtChatBox" )->getText();
//     (this)->ParseText( message );
//     
//     Instruments->getChild( "Root/txtChatBox" )->setText( "" );
//     
//     return true;
return true;
}

bool CHUD::Handle_TextSubmitted( const CEGUI::EventArgs &e )
{
//     std::cout << "TEST 2" << std::endl;
//     const CEGUI::WindowEventArgs* args = static_cast< const CEGUI::WindowEventArgs* > ( &e );
//     CEGUI::String message = Instruments->getChild( "Root/txtChatBox" )->getText();
//     
//     (this)->ParseText( message );
//     
//     Instruments->getChild( "Root/txtChatBox" )->setText( "" );
//     
//     return true;
return true;
}

void CHUD::ParseText( CEGUI::String message )
{
//     std::cout << "TEST 3" << std::endl;
//     std::string Input = message.c_str();
//     if( Input.length() >= 1 )
//     {
// 	if( Input.at( 0 ) == '/' )
// 	{
// 	    std::string::size_type	cmdFinaliser = Input.find( "", 1 );
// 	    std::string 		cmd = Input.substr( 1, cmdFinaliser - 1 );
// 	    std::string			cmdArgs = Input.substr( cmdFinaliser + 1, Input.length() - ( cmdFinaliser + 1 ) );
// 	    
// 	    for( std::string::size_type i = 0; i < cmd.length(); ++i )
// 	    {
// 		cmd[ i ] = tolower( cmd[ i ] );
// 	    }
// 	    
// 	    //command processing
// 	    if( cmd == "test" )
// 	    {
// 		//Do Something
// 	    }
// 	    else
// 	    {
// 		std::string Output = "<" + Input + "> is not a recognised command.";
// 		(this)->OutputText( Output, CEGUI::colour( 1.0f, 0.0f, 0.0f ) );
// 	    }
// 	}
// 	else
// 	{
// 	    (this)->OutputText( Input );
// 	}
//     }
}

void CHUD::OutputText( CEGUI::String message, CEGUI::colour colour )
{
//     CEGUI::Listbox *lstChatBox = static_cast< CEGUI::Listbox* > ( Instruments->getChild( "Root/lstChatBox" ) );
//     
//     CEGUI::ListboxTextItem *Entry = 0;
//     Entry =  new CEGUI::ListboxTextItem( message, CEGUI::HTF_WORDWRAP_JUSTIFIED );
//     Entry->setTextColours( colour );
//     lstChatBox->addItem( Entry );
}

void CHUD::UpdateHealth( const float& Percent )
{
//     CEGUI::ProgressBar *healthBar = ( CEGUI::ProgressBar* )CEGUI::WindowManager::getSingletonPtr()->getWindow( "Root/barHealth" );
//     healthBar->setProgress( Percent );
}

void CHUD::UpdateFatigue( const float& Percent )
{
//     CEGUI::ProgressBar *fatigueBar = ( CEGUI::ProgressBar* )CEGUI::WindowManager::getSingletonPtr()->getWindow( "Root/barFatigue" );
//     fatigueBar->setProgress( Percent );
}
