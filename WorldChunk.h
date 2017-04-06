
#ifndef WORLD_CHUNK_H
#define WORLD_CHUNK_H

#include <OgreSceneNode.h>

constexpr size_t CHUNK_SIZE = 16;

enum class BlockType
{
    AIR = 0,
    DIRT,
    STONE
};

class WorldChunk
{
public:
    WorldChunk(Ogre::SceneNode* chunkNode);

    BlockType getBlock(size_t x, size_t y, size_t z) const;
    void setBlock(size_t x, size_t y, size_t z, BlockType newBlock);

    Ogre::SceneNode* getChunkNode();
    const Ogre::SceneNode* getChunkNode() const;

    void removeBlock(Ogre::Vector3 fromPos, Ogre::Quaternion dir);

private:
    BlockType m_blockIds[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

    Ogre::SceneNode* m_chunkNode;
};

#endif // !WORLD_CHUNK_H
