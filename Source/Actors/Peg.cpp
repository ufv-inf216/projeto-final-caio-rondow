#include "Peg.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"

Peg::Peg(InterfaceGame *game, float x, float y, char PegType):
    Block(game, x, y)
{
    std::string PieceTexture = "../Assets/Sprite/Pegs/" + std::string(1,PegType) + ".png";
    new DrawSpriteComponent(this, PieceTexture, BLOCK_SIZE, BLOCK_SIZE, PEG_DRAW_ORDER);

    new AABBColliderComponent(
        this, Vector2(0,0), BLOCK_SIZE, BLOCK_SIZE, ColliderLayer::PEG,
        PEG_UPDATE_ORDER
    );

    /* SHOW PEG COLLIDER - DEBUG ONLY */
    std::vector<Vector2> vertices;
    vertices.push_back(Vector2(0,0));
    vertices.push_back(Vector2(BLOCK_SIZE,0));
    vertices.push_back(Vector2(BLOCK_SIZE,BLOCK_SIZE));
    vertices.push_back(Vector2(0,BLOCK_SIZE));
    new DrawPolygonComponent(this, vertices);
    /* SHOW PEG COLLIDER - DEBUG ONLY */
}