#ifndef __SpaceshipAndCamera_H
#define __SpaceshipAndCamera_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include "Spaceship.h"

class SpaceshipAndCamera : public Ogre::FrameListener
{
public:
	SpaceshipAndCamera(Ogre::SceneManager*);
	virtual ~SpaceshipAndCamera(void);
	Spaceship* getSpaceship();
	Ogre::Camera* getCamera();
	void moveRelative(Ogre::Vector3);
	void setKeyboard(OIS::Keyboard*);


protected:
	bool frameStarted(const Ogre::FrameEvent &evt);

private:
	Spaceship* spaceship;
	Ogre::Camera* camera;
	OIS::Keyboard* keyboard;
	Ogre::Vector3 translation;
	Ogre::Vector3 acceleration;
	float velocity;

};
#endif
