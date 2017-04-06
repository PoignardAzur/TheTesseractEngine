
#include "WorldChunk.h"

WorldChunk::WorldChunk(Ogre::SceneNode* chunkNode)
{
    for (auto& block : m_blockIds)
    {
        block = BlockType::AIR;
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
