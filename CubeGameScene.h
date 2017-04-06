
#ifndef CUBE_GAME_SCENE_H_
#define CUBE_GAME_SCENE_H_

#include <OgreSceneManager.h>
#include <OgreCamera.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

class CubeGameScene
{
public:
    CubeGameScene();
    ~CubeGameScene();

    void open(Ogre::Root* root, Ogre::RenderWindow* window);
    void close();

    void createScene();

    // OgreEvent
    bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    // OIS Events
    bool keyPressed(const OIS::KeyEvent &arg);
    bool keyReleased(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
    bool m_shutDown = false;
    Ogre::Camera* m_camera = nullptr;
    Ogre::SceneManager* m_sceneManager = nullptr;
    Ogre::OverlaySystem* m_overlaySystem = nullptr;

    OgreBites::SdkCameraMan* m_cameraMan = nullptr;
};

#endif // !CUBE_GAME_SCENE_H_
