
#include "TutorialApplication.h"
#include <OgreConfigFile.h>
#include <OgreWindowEventUtilities.h>

TutorialApplication::TutorialApplication(void)
{

}

TutorialApplication::~TutorialApplication(void)
{
    Ogre::WindowEventUtilities::removeWindowEventListener(m_window, this);
    windowClosed(m_window);

    delete m_root;
}

bool TutorialApplication::go()
{
    m_root = new Ogre::Root("plugins.cfg");

    Ogre::ConfigFile cf;
    cf.load("resources.cfg");

    auto configIt = cf.getSectionIterator();
    while (configIt.hasMoreElements())
    {
        Ogre::ConfigFile::SettingsMultiMap* settings = configIt.getNext();

        for (const auto& pair : *settings)
        {
            Ogre::String resourceArchiveType = pair.first;
            Ogre::String resourcePath = pair.second;

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                resourcePath, resourceArchiveType
            );
        }
    }

    //if (!mRoot->restoreConfig() && !mRoot->showConfigDialog()))
    if (!m_root->showConfigDialog())
    {
        return false;
    }

    m_window = m_root->initialise(true, "TutorialApplication Render Window");

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    m_scene = new EnvGameScene();
    m_scene->open(m_root, m_window);

    // Create window inputs
    {
        OIS::ParamList pl;
        size_t windowHnd = 0;
        std::ostringstream windowHndStr;

        m_window->getCustomAttribute("WINDOW", &windowHnd);
        windowHndStr << windowHnd;
        pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

        m_inputManager = OIS::InputManager::createInputSystem(pl);
    }

    m_keyboard = static_cast<OIS::Keyboard*>(
        m_inputManager->createInputObject(OIS::OISKeyboard, true)
    );
    m_mouse = static_cast<OIS::Mouse *>(
        m_inputManager->createInputObject(OIS::OISMouse, true)
    );

    m_mouse->setEventCallback(this);
    m_keyboard->setEventCallback(this);
    m_root->addFrameListener(this);
    Ogre::WindowEventUtilities::addWindowEventListener(m_window, this);

    m_root->startRendering();

    return true;
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &event)
{
    (void)event; // not sure what this parameter even does

    if (m_window->isClosed())
        return false;

    m_keyboard->capture();
    m_mouse->capture();

    return m_scene->frameRenderingQueued(event);
}

void TutorialApplication::windowResized(Ogre::RenderWindow *rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);
    (void)depth;
    (void)left;
    (void)top;

    const OIS::MouseState &ms = m_mouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void TutorialApplication::windowClosed(Ogre::RenderWindow *rw)
{
    if (rw == m_window)
    {
        if (m_inputManager)
        {
            m_inputManager->destroyInputObject(m_mouse);
            m_inputManager->destroyInputObject(m_keyboard);

            OIS::InputManager::destroyInputSystem(m_inputManager);
            m_inputManager = nullptr;
        }
    }
}

// OIS Events
bool TutorialApplication::keyPressed(const OIS::KeyEvent &arg)
{
    return m_scene->keyPressed(arg);
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent &arg)
{
    return m_scene->keyReleased(arg);
}

bool TutorialApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    return m_scene->mouseMoved(arg);
}

bool TutorialApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    return m_scene->mousePressed(arg, id);
}

bool TutorialApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    return m_scene->mouseReleased(arg, id);
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

extern "C"
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
        return 0;
    }
}
