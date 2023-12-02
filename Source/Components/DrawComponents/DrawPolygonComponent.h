#pragma once
#include "DrawComponent.h"
#include <vector>

class DrawPolygonComponent : public DrawComponent {
public:
    // (Lower draw order corresponds with further back)
    DrawPolygonComponent(Actor* owner, std::vector<Vector2> &vertices, int drawOrder = 100);

    void Draw(SDL_Renderer* renderer) override;
    std::vector<Vector2>& GetVertices() { return mVertices; }
    inline void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
        mColor[0] = r;
        mColor[1] = g;
        mColor[2] = b;
        mColor[3] = a;
    }
protected:
    int mDrawOrder;
    std::vector<Vector2> mVertices;
private:
    Uint8 mColor[4];
};