
#include <OgreManualObject.h>
#include "EnvGameScene.hpp"

EnvGameScene::EnvGameScene() {
}

EnvGameScene::~EnvGameScene() {
    delete m_cameraMan;
}

void EnvGameScene::open(Ogre::Root *root, Ogre::RenderWindow *window) {
    m_sceneManager = root->createSceneManager(Ogre::ST_GENERIC);

    m_camera = m_sceneManager->createCamera("MainCam");
    m_camera->setPosition(10, 10, 10);
    m_camera->lookAt(0, 0, 0);
    m_camera->setNearClipDistance(5);

    m_overlaySystem = new Ogre::OverlaySystem();
    m_sceneManager->addRenderQueueListener(m_overlaySystem);

    Ogre::Viewport *viewport = window->addViewport(m_camera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5));

    m_camera->setAspectRatio(
            Ogre::Real(viewport->getActualWidth()) /
            Ogre::Real(viewport->getActualHeight())
    );

    m_cameraMan = new OgreBites::SdkCameraMan(m_camera);

    m_sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    createScene();
}

void EnvGameScene::createScene(void) {
    Ogre::ManualObject cube("Cube_obj");

    cube.begin("Cube/Dirt");

    cube.position(0.5, -0.5, 1.0);
    cube.normal(0.408248, -0.816497, 0.408248);
    cube.textureCoord(1, 0);

    cube.position(-0.5, -0.5, 0.0);
    cube.normal(-0.408248, -0.816497, -0.408248);
    cube.textureCoord(0, 1);

    cube.position(0.5, -0.5, 0.0);
    cube.normal(0.666667, -0.333333, -0.666667);
    cube.textureCoord(1, 1);

    cube.position(-0.5, -0.5, 1.0);
    cube.normal(-0.666667, -0.333333, 0.666667);
    cube.textureCoord(0, 0);

    cube.position(0.5, 0.5, 1.0);
    cube.normal(0.666667, 0.333333, 0.666667);
    cube.textureCoord(1, 0);

    cube.position(-0.5, -0.5, 1.0);
    cube.normal(-0.666667, -0.333333, 0.666667);
    cube.textureCoord(0, 1);

    cube.position(0.5, -0.5, 1.0);
    cube.normal(0.408248, -0.816497, 0.408248);
    cube.textureCoord(1, 1);

    cube.position(-0.5, 0.5, 1.0);
    cube.normal(-0.408248, 0.816497, 0.408248);
    cube.textureCoord(0, 0);

    cube.position(-0.5, 0.5, 0.0);
    cube.normal(-0.666667, 0.333333, -0.666667);
    cube.textureCoord(0, 1);

    cube.position(-0.5, -0.5, 0.0);
    cube.normal(-0.408248, -0.816497, -0.408248);
    cube.textureCoord(1, 1);

    cube.position(-0.5, -0.5, 1.0);
    cube.normal(-0.666667, -0.333333, 0.666667);
    cube.textureCoord(1, 0);

    cube.position(0.5, -0.5, 0.0);
    cube.normal(0.666667, -0.333333, -0.666667);
    cube.textureCoord(0, 1);

    cube.position(0.5, 0.5, 0.0);
    cube.normal(0.408248, 0.816497, -0.408248);
    cube.textureCoord(1, 1);

    cube.position(0.5, -0.5, 1.0);
    cube.normal(0.408248, -0.816497, 0.408248);
    cube.textureCoord(0, 0);

    cube.position(0.5, -0.5, 0.0);
    cube.normal(0.666667, -0.333333, -0.666667);
    cube.textureCoord(1, 0);

    cube.position(-0.5, -0.5, 0.0);
    cube.normal(-0.408248, -0.816497, -0.408248);
    cube.textureCoord(0, 0);

    cube.position(-0.5, 0.5, 1.0);
    cube.normal(-0.408248, 0.816497, 0.408248);
    cube.textureCoord(1, 0);

    cube.position(0.5, 0.5, 0.0);
    cube.normal(0.408248, 0.816497, -0.408248);
    cube.textureCoord(0, 1);

    cube.position(-0.5, 0.5, 0.0);
    cube.normal(-0.666667, 0.333333, -0.666667);
    cube.textureCoord(1, 1);

    cube.position(0.5, 0.5, 1.0);
    cube.normal(0.666667, 0.333333, 0.666667);
    cube.textureCoord(0, 0);

    cube.triangle(0, 1, 2);
    cube.triangle(3, 1, 0);
    cube.triangle(4, 5, 6);
    cube.triangle(4, 7, 5);
    cube.triangle(8, 9, 10);
    cube.triangle(10, 7, 8);
    cube.triangle(4, 11, 12);
    cube.triangle(4, 13, 11);
    cube.triangle(14, 8, 12);
    cube.triangle(14, 15, 8);
    cube.triangle(16, 17, 18);
    cube.triangle(16, 19, 17);
    cube.end();

    cube.convertToMesh("Cube_mesh");

    Ogre::SceneNode *rootNode = m_sceneManager->getRootSceneNode();
    m_world = new WorldChunk(rootNode, m_sceneManager);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == j) {
                m_world->setBlock(i, 1, j, BlockType::STONE);
            }
            m_world->setBlock(i, 0, j, BlockType::DIRT);
        }
    }
    m_world->setBlock(2, 0, 6, BlockType::AIR);
    m_world->setBlock(2, 0, 7, BlockType::AIR);
    m_world->setBlock(3, 0, 6, BlockType::AIR);
    m_world->setBlock(3, 0, 7, BlockType::AIR);
}

void EnvGameScene::close() {
    delete m_camera;
    delete m_sceneManager;
    delete m_cameraMan;
}

// OgreEvents
bool EnvGameScene::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    if (m_shutDown)
        return false;

    m_cameraMan->frameRenderingQueued(evt);

    return true;
}

// OIS Events
bool EnvGameScene::keyPressed(const OIS::KeyEvent &arg) {
    if (arg.key == OIS::KC_ESCAPE) {
        m_shutDown = true;
    }

    m_cameraMan->injectKeyDown(arg);

    return true;
}

bool EnvGameScene::keyReleased(const OIS::KeyEvent &arg) {
    m_cameraMan->injectKeyUp(arg);
    return true;
}

bool EnvGameScene::mouseMoved(const OIS::MouseEvent &arg) {
    m_cameraMan->injectMouseMove(arg);
    return true;
}

bool EnvGameScene::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    m_cameraMan->injectMouseDown(arg, id);
    return true;
}

bool EnvGameScene::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    m_cameraMan->injectMouseUp(arg, id);
    return true;
}
