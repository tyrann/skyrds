#include "Spaceship.h"

Spaceship::Spaceship(Ogre::SceneManager* mSceneMgr)
{
	entity = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	entity->setCastShadows(true);
	node = mSceneMgr->createSceneNode("Node1");
	node->attachObject(entity);
}

Spaceship::~Spaceship(void)
{
	delete entity;
	delete node;
}

Ogre::SceneNode* Spaceship::getNode()
{
	return node;
}

void Spaceship::moveRelative(Ogre::Vector3 direction) {
	node->translate(direction);
}
