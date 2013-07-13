#include "SpaceshipAndCamera.h"

SpaceshipAndCamera::SpaceshipAndCamera(Ogre::SceneManager* mSceneMgr) :
	translation(Ogre::Vector3(0, 0, 0)),
	keyboard(0),
	velocity(200)
{
    // create the camera
    camera = mSceneMgr->createCamera("SpaceshipCamera");
    // set its position, direction
    camera->setPosition(Ogre::Vector3(0,200,500));
    camera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    camera->setNearClipDistance(5);

	spaceship = new Spaceship(mSceneMgr);
}

SpaceshipAndCamera::~SpaceshipAndCamera(void)
{
	delete camera;
	delete spaceship;
}

Spaceship* SpaceshipAndCamera::getSpaceship()
{
	return spaceship;
}

Ogre::Camera* SpaceshipAndCamera::getCamera()
{
	return camera;
}

void SpaceshipAndCamera::setKeyboard(OIS::Keyboard* keyb) {
	keyboard = keyb;
}

void SpaceshipAndCamera::moveRelative(Ogre::Vector3 direction) {
	camera->move(direction);
	spaceship->moveRelative(direction);
}

bool SpaceshipAndCamera::frameStarted(const Ogre::FrameEvent &evt)
{
	translation = Ogre::Vector3(0, 0, 0);
	keyboard->capture();
    if (keyboard->isKeyDown(OIS::KC_LEFT)) {
    	translation += Ogre::Vector3(-1, 0, 0) * velocity;
    }
    else if (keyboard->isKeyDown(OIS::KC_RIGHT)) {
    	translation += Ogre::Vector3(1, 0, 0) * velocity;
    }
    else if (keyboard->isKeyDown(OIS::KC_UP)) {
    	translation += Ogre::Vector3(0, 0, -1) * velocity;
    }
	moveRelative(translation * evt.timeSinceLastFrame);
	return true;
}