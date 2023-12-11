#include "Wall.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"

Wall::Wall(InterfaceGame *game, float x, float y, uint WallWidth, uint WallHeight):
    Block(game)
{
    SetPosition(Vector2(x,y));

    new AABBColliderComponent(
        this, Vector2(0,0), WallWidth, WallHeight, ColliderLayer::WALL
    );
        
    // /* SHOW WALL COLLIDER - DEBUG ONLY */
    // std::vector<Vector2> vertices;
    // vertices.push_back(Vector2(0,0));
    // vertices.push_back(Vector2(WallWidth,0));
    // vertices.push_back(Vector2(WallWidth,WallHeight));
    // vertices.push_back(Vector2(0,WallHeight));
    // new DrawPolygonComponent(this, vertices);
    // /* SHOW WALL COLLIDER - DEBUG ONLY */
}

void Wall::OnUpdate(float DeltaTime){

}

void Wall::OnCollision(Actor *response){

}
