/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __BasicTutorial2_H
#define __BasicTutorial2_H

#include "BaseApplication.h"

class BasicTutorial2 : public BaseApplication
{
public:
	BasicTutorial2(void);
	virtual ~BasicTutorial2(void);

protected:
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
};
#endif
