#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H 

#include <string>
#include <Ogre.h>
#include <OgreViewport.h>
#include <OIS.h>
#include "generic_utilities.h"
class inet_player;
class ObjectTextDisplay;
class Player {
public:
	Ogre::SceneManager *mSceneMgr;
	Ogre::Entity *ent;
	Ogre::Camera *mCamera; 
	std::string name;
	std::string currentmesh;
	
	bool admin;
	int admin_level;
	vec3 actual_target_position;
	inet_player *following_player;
	bool walking;
	vec3 targetposition;
	vec3 orig_position;
	float previous_time;
	Ogre::Timer GMT_Clock;
	ObjectTextDisplay *textBox;
	Ogre::Vector3 position;
    // Need to track orientation too...
	Ogre::SceneNode *mSceneNd; // mSceneNode
	Ogre::AnimationState *mCharWalkAnimationState;
	Player(Ogre::SceneManager*,std::string meshFileName, std::string playername,Ogre::Camera*,int);
	Player();
	virtual ~Player();
	
	void frameRenderingQueued(const Ogre::FrameEvent &);
	vec3 getPositionAtFrame(unsigned int offset);
	
	void noAnimFrameRenderingQueued();
	
	virtual void inet_update_other_players(const Ogre::FrameEvent &) = 0;
	virtual void pump_net_messages() = 0;
	virtual void Pathfind();
	virtual void ServerPathfind();
	virtual void pathfind_internal();
	
};

// from http://www.ogre3d.org/tikiwiki/ObjectTextDisplay.
#include <OgreFont.h>
#include <OgreFontManager.h>
#include <sstream>
class ObjectTextDisplay {
 
public:
    ObjectTextDisplay(const Ogre::MovableObject* p, const Ogre::Camera* c, int idnum);
    virtual ~ObjectTextDisplay();
    void enable(bool enable);
    void setText(const Ogre::String& text);
    bool frameRenderingQueued( const Ogre::FrameEvent &event);
    void update();
 
protected:
  
    const Ogre::MovableObject* m_p;
    const Ogre::Camera* m_c;
    bool m_enabled;
    Ogre::Overlay* m_pOverlay;
    Ogre::OverlayElement* m_pText;
    Ogre::OverlayContainer* m_pContainer;
    Ogre::String m_text;
    
    std::string nsname;
};
#endif