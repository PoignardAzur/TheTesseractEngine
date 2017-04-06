
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreFrameListener.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "EnvGameScene.h"

class TutorialApplication :
    public Ogre::FrameListener,
    public Ogre::WindowEventListener,
    public OIS::KeyListener,
    public OIS::MouseListener
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

    bool go();

protected:
    // OgreEvents
    bool frameRenderingQueued(const Ogre::FrameEvent &evt);
    void windowResized(Ogre::RenderWindow *rw);
    void windowClosed(Ogre::RenderWindow *rw);

    // OIS Events
    bool keyPressed(const OIS::KeyEvent &arg);
    bool keyReleased(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
    Ogre::Root* m_root = nullptr;
    Ogre::RenderWindow* m_window = nullptr;

    EnvGameScene* m_scene = nullptr;

    OIS::InputManager *m_inputManager = nullptr;
    OIS::Mouse *m_mouse = nullptr;
    OIS::Keyboard *m_keyboard = nullptr;
};

#endif // #ifndef __TutorialApplication_h_
