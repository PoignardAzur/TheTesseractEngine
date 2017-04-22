//
// Created by waether on 22/04/17.
//

/*

Test Remove Block

This test remove a block in front of the camera when pressing 'P'
To use it just replace the EnvGameScene::keyReleased function in EnvGameScene.cpp with the one below
Compile run and press 'P'

 /!\ Crash in current version when going out of range /!\ 

// */

bool EnvGameScene::keyReleased(const OIS::KeyEvent &arg) {
  m_cameraMan->injectKeyUp(arg);

  if (arg.key == OIS::KeyCode::KC_P)
    m_world->removeBlock(m_camera->getPosition(), m_camera->getDirection());

  return true;
}
