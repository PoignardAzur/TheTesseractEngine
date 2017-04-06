
#include <OgreManualObject.h>
#include "CubeGameScene.h"

CubeGameScene::CubeGameScene()
{
}

CubeGameScene::~CubeGameScene()
{
    delete m_cameraMan;
}

void CubeGameScene::open(Ogre::Root* root, Ogre::RenderWindow* window)
{
    m_sceneManager = root->createSceneManager(Ogre::ST_GENERIC);

    m_camera = m_sceneManager->createCamera("MainCam");
    m_camera->setPosition(10, 10, 10);
    m_camera->lookAt(0, 0, 0);
    m_camera->setNearClipDistance(5);

    m_overlaySystem = new Ogre::OverlaySystem();
    m_sceneManager->addRenderQueueListener(m_overlaySystem);

    Ogre::Viewport* viewport = window->addViewport(m_camera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5));

    m_camera->setAspectRatio(
        Ogre::Real(viewport->getActualWidth()) /
        Ogre::Real(viewport->getActualHeight())
    );

    m_cameraMan = new OgreBites::SdkCameraMan(m_camera);

    m_sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    createScene();
}

void CubeGameScene::createScene(void)
{
    Ogre::ManualObject* cube = new Ogre::ManualObject("Cube_obj");

    cube->begin("Cube/Dirt");

    cube->position(0.5,-0.5,1.0);
    cube->normal(0.408248,-0.816497,0.408248);
    cube->textureCoord(1,0);

    cube->position(-0.5,-0.5,0.0);
    cube->normal(-0.408248,-0.816497,-0.408248);
    cube->textureCoord(0,1);

    cube->position(0.5,-0.5,0.0);
    cube->normal(0.666667,-0.333333,-0.666667);
    cube->textureCoord(1,1);

    cube->position(-0.5,-0.5,1.0);
    cube->normal(-0.666667,-0.333333,0.666667);
    cube->textureCoord(0,0);

    cube->position(0.5,0.5,1.0);
    cube->normal(0.666667,0.333333,0.666667);
    cube->textureCoord(1,0);

    cube->position(-0.5,-0.5,1.0);
    cube->normal(-0.666667,-0.333333,0.666667);
    cube->textureCoord(0,1);

    cube->position(0.5,-0.5,1.0);
    cube->normal(0.408248,-0.816497,0.408248);
    cube->textureCoord(1,1);

    cube->position(-0.5,0.5,1.0);
    cube->normal(-0.408248,0.816497,0.408248);
    cube->textureCoord(0,0);

    cube->position(-0.5,0.5,0.0);
    cube->normal(-0.666667,0.333333,-0.666667);
    cube->textureCoord(0,1);

    cube->position(-0.5,-0.5,0.0);
    cube->normal(-0.408248,-0.816497,-0.408248);
    cube->textureCoord(1,1);

    cube->position(-0.5,-0.5,1.0);
    cube->normal(-0.666667,-0.333333,0.666667);
    cube->textureCoord(1,0);

    cube->position(0.5,-0.5,0.0);
    cube->normal(0.666667,-0.333333,-0.666667);
    cube->textureCoord(0,1);

    cube->position(0.5,0.5,0.0);
    cube->normal(0.408248,0.816497,-0.408248);
    cube->textureCoord(1,1);

    cube->position(0.5,-0.5,1.0);
    cube->normal(0.408248,-0.816497,0.408248);
    cube->textureCoord(0,0);

    cube->position(0.5,-0.5,0.0);
    cube->normal(0.666667,-0.333333,-0.666667);
    cube->textureCoord(1,0);

    cube->position(-0.5,-0.5,0.0);
    cube->normal(-0.408248,-0.816497,-0.408248);
    cube->textureCoord(0,0);

    cube->position(-0.5,0.5,1.0);
    cube->normal(-0.408248,0.816497,0.408248);
    cube->textureCoord(1,0);

    cube->position(0.5,0.5,0.0);
    cube->normal(0.408248,0.816497,-0.408248);
    cube->textureCoord(0,1);

    cube->position(-0.5,0.5,0.0);
    cube->normal(-0.666667,0.333333,-0.666667);
    cube->textureCoord(1,1);

    cube->position(0.5,0.5,1.0);
    cube->normal(0.666667,0.333333,0.666667);
    cube->textureCoord(0,0);

    cube->triangle(0,1,2);      cube->triangle(3,1,0);
    cube->triangle(4,5,6);      cube->triangle(4,7,5);
    cube->triangle(8,9,10);     cube->triangle(10,7,8);
    cube->triangle(4,11,12);    cube->triangle(4,13,11);
    cube->triangle(14,8,12);    cube->triangle(14,15,8);
    cube->triangle(16,17,18);   cube->triangle(16,19,17);
    cube->end();

    Ogre::Entity* myCube = m_sceneManager->createEntity(cube->convertToMesh("Cube_mesh"));
    Ogre::SceneNode* node = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    node->attachObject(myCube);

    std::cerr << node->getPosition() << std::endl;
}

void CubeGameScene::close()
{
    delete m_camera;
    delete m_sceneManager;
    delete m_cameraMan;
}

// OgreEvents
bool CubeGameScene::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    if (m_shutDown)
        return false;

    m_cameraMan->frameRenderingQueued(evt);

    return true;
}

// OIS Events
bool CubeGameScene::keyPressed(const OIS::KeyEvent &arg)
{
    if (arg.key == OIS::KC_ESCAPE) {
        m_shutDown = true;
    }

    m_cameraMan->injectKeyDown(arg);

    return true;
}

bool CubeGameScene::keyReleased(const OIS::KeyEvent &arg) {
    m_cameraMan->injectKeyUp(arg);
    return true;
}

bool CubeGameScene::mouseMoved(const OIS::MouseEvent &arg) {
    m_cameraMan->injectMouseMove(arg);
    return true;
}

bool CubeGameScene::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    m_cameraMan->injectMouseDown(arg, id);
    return true;
}

bool CubeGameScene::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    m_cameraMan->injectMouseUp(arg, id);
    return true;
}
