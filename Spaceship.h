#ifndef __Spaceship_H
#define __Spaceship_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

class Spaceship
{
public:
	Spaceship(Ogre::SceneManager*);
	virtual ~Spaceship(void);

private:
	Ogre::SceneNode* node;
	Ogre::Entity* entity;

public:
	Ogre::SceneNode* getNode();
	void moveRelative(Ogre::Vector3);
};

#endif
