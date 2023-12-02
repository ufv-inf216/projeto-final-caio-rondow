#include "DrawPolygonComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game/InterfaceGame.h"

DrawPolygonComponent::DrawPolygonComponent(Actor* owner, std::vector<Vector2> &vertices, int drawOrder):
    DrawComponent(owner),
    mVertices(vertices),
    mDrawOrder(drawOrder)
{
    mColor[0] = 0x00;
    mColor[1] = 0xFF;
    mColor[2] = 0x00;
    mColor[3] = 0xFF;
}

void DrawPolygonComponent::Draw(SDL_Renderer *renderer){
    // Set draw color to green
    SDL_SetRenderDrawColor(renderer, mColor[0], mColor[1], mColor[2], mColor[3]);

    Vector2 pos = mOwner->GetPosition();

    // Render vertices as lines
    for(int i = 0; i < mVertices.size() - 1; i++) {
        SDL_RenderDrawLine(renderer, pos.x + mVertices[i].x,
                                     pos.y + mVertices[i].y,
                                     pos.x + mVertices[i+1].x,
                                     pos.y + mVertices[i+1].y);
    }

    // Close geometry
    SDL_RenderDrawLine(renderer, pos.x + mVertices[mVertices.size() - 1].x,
                                 pos.y + mVertices[mVertices.size() - 1].y,
                                 pos.x + mVertices[0].x,
                                 pos.y + mVertices[0].y);
}