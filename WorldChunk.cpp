
#include "WorldChunk.h"

#include <cassert>

WorldChunk::WorldChunk(Ogre::SceneNode* chunkNode)
{
    for (auto& block : m_blockIds)
    {
        block = BlockType::AIR;
    }
    for (auto& node : m_blockNodes)
    {
        node = nullptr;
    }
    m_chunkNode = chunkNode;
}

BlockType WorldChunk::getBlock(size_t x, size_t y, size_t z) const
{
    return m_blockIds[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE];
}

void WorldChunk::setBlock(size_t x, size_t y, size_t z, BlockType newBlock)
{
    m_blockIds[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE] = newBlock;
    (Ogre::SceneNode*)& blockNode = m_blockNodes[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE];

    if (blockNode && newBlock == BlockType::AIR)
    {
        m_chunkNode->removeChild(blockNode);
    }
    if (newBlock != BlockType::AIR)
    {
        Ogre::Entity* blockEntity;

        if (!blockNode)
        {
            blockEntity = m_sceneManager->createEntity("Cube_mesh");
            blockNode = m_chunkNode->createChildSceneNode(
                Ogre::Vector3(x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE)
            );
            blockNode->setScale(10, 10, 10);
            blockNode->attachObject(blockEntity);
        }
        else
        {
            blockEntity = dynamic_cast<Ogre::Entity*>(
                blockNode->getAttachedObject(0)
            );
            assert(blockEntity);
        }
    }
}

Ogre::SceneNode* WorldChunk::getChunkNode()
{
    return m_chunkNode;
}

const Ogre::SceneNode* WorldChunk::getChunkNode() const
{
    return m_chunkNode;
}

void WorldChunk::removeBlock(Ogre::Vector3 fromPos, Ogre::Quaternion dir)
{

}
