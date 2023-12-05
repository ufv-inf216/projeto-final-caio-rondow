#include "Block.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"

/* create a block */
Block::Block(InterfaceGame *game, float x, float y, bool enable):
    Piece(game, x, y)
{
    /* could be a cursor, instead of a static block */
    mIsEnabled = enable;
    std::string TextureFile = "../Assets/Sprite/Table/block.png";
    new DrawSpriteComponent(this,TextureFile,BLOCK_SIZE,BLOCK_SIZE,BLOCK_DRAW_ORDER);
}