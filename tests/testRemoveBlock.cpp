//
// Created by waether on 22/04/17.
//

/*

Test Remove Block

This test remove a block in position [1, 1, 1] when pressing 'P'
To use it just replace the EnvGameScene::keyReleased function in EnvGameScene.cpp with the one below
Compile run and press 'P'
A Stone block should disappear

// */

bool EnvGameScene::keyReleased(const OIS::KeyEvent &arg) {
    m_cameraMan->injectKeyUp(arg);

    if (arg.key == OIS::KeyCode::KC_P) {
        if (m_world->getBlock(1, 1, 1) != BlockType::AIR) // Check if there is a Cube
            m_world->setBlock(1, 1, 1, BlockType::AIR); // Delete Cube
    }

    return true;
}
