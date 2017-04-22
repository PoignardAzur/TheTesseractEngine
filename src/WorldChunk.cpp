
#include "WorldChunk.hpp"

#include <OgreEntity.h>

WorldChunk::WorldChunk(Ogre::SceneNode *chunkNode, Ogre::SceneManager *sceneManager) {
    for (auto &block : m_blockIds) {
        block = BlockType::AIR;
    }
    for (auto &node : m_blockNodes) {
        node = nullptr;
    }
    m_chunkNode = chunkNode;
    m_sceneManager = sceneManager;
}

BlockType WorldChunk::getBlock(size_t x, size_t y, size_t z) const {
    // Out of Range Check
    long int target = x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE;
    if (target < 0 || target > static_cast<long int>((CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE) - 1))
        return BlockType::AIR;
    // Out of Range Check

    return m_blockIds[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE];
}

void WorldChunk::setBlock(size_t x, size_t y, size_t z, BlockType newBlock) {
    // Out of Range Check
    long int target = x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE;
    if (target < 0 || target > static_cast<long int>((CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE) - 1))
        return;
    // Out of Range Check

    m_blockIds[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE] = newBlock;
    Ogre::SceneNode *&blockNode = m_blockNodes[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE];

    if (blockNode && newBlock == BlockType::AIR) {
        m_chunkNode->removeChild(blockNode);
    }
    if (newBlock != BlockType::AIR) {
        Ogre::Entity *blockEntity;

        if (!blockNode) {
            blockEntity = m_sceneManager->createEntity("Cube_mesh");
            blockNode = m_chunkNode->createChildSceneNode(
                    Ogre::Vector3(x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE)
            );
            blockNode->setScale(10, 10, 10);
            blockNode->attachObject(blockEntity);
        } else {
            blockEntity = dynamic_cast<Ogre::Entity *>(
                    blockNode->getAttachedObject(0)
            );
            assert(blockEntity);
        }
        if (newBlock == BlockType::STONE) {
            blockEntity->setMaterialName("Cube/Stone");
        } else {
            blockEntity->setMaterialName("Cube/Dirt");
        }
    }
}

Ogre::SceneNode *WorldChunk::getChunkNode() {
    return m_chunkNode;
}

const Ogre::SceneNode *WorldChunk::getChunkNode() const {
    return m_chunkNode;
}

void WorldChunk::removeBlock(Ogre::Vector3 fromPos, Ogre::Vector3 dir) {
    Ogre::Vector3 toCheck = fromPos;
    BlockType hit = BlockType::AIR;

    // Raycasting Configuration
    float max_range = 1000.0f; // define the range between the camera and the farest block that can be destroyed
    float current_range = 0.0f;
    float precision = 0.05f; // The more accurate the raycasting is the more resources it will consume, be careful with this one

    size_t X = 0;
    size_t Y = 0;
    size_t Z = 0;

    while (hit == BlockType::AIR) {

        toCheck += (dir * precision);

        // Scaling to block grid
        X = static_cast<int>(toCheck.x) / BLOCK_SIZE;
        Y = static_cast<int>(toCheck.y) / BLOCK_SIZE;
        Z = static_cast<int>(toCheck.z) / BLOCK_SIZE;

        hit = getBlock(X, Y, Z);

        current_range += precision;
        if (current_range >= max_range)
            return;
    }
    setBlock(X, Y, Z, BlockType::AIR);
}
