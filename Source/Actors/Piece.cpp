#include "../Utils/Parser.h"
#include "Piece.h"
#include "Table.h"
#include "Block.h"
#include "Cursor.h"
#include "Peg.h"
#include <map>

static const std::map<char, Vector2> PieceDim = {
    {'L' , Vector2(64,96)},
    {'Z' , Vector2(64,96)},
    {'I' , Vector2(32,128)},
    {'b' , Vector2(64,96)},
    {'c' , Vector2(64,64)},
    {'T' , Vector2(96,64)},
    {'f' , Vector2(96,96)},
    {'i' , Vector2(32,96)},
    {'P' , Vector2(32,32)}
};

static const std::vector<Vector2> offset = {
    Vector2(0,0),
    Vector2(0,32),
    Vector2(0,64),
    Vector2(32,64)
};

Piece::Piece(InterfaceGame *game, float x, float y, char PieceType, float rotation, bool flip):
    Actor(game),
    mCanProcessInput(false),
    mPieceType(PieceType),
    mIsEnabled(false),
    mCanPlace(false),
    mAABBColliderComponent(nullptr),
    mDrawSpriteComponent(nullptr),
    mDrawPolygonComponent(nullptr),
    mDrawComponent(nullptr)
{
    /* piece start position */
    SetPosition(Vector2(x,y));

    /* Load Piece Components */
    if(PieceType != char()){ /* if not a block */

        auto it = PieceDim.find(PieceType);
        if(it == PieceDim.end()){
            std::cerr << "Invalid type of piece : " << PieceType << "\n";
            std::cerr << "valid types are: P,L,Z,I,b,c,T,f,i\n";
            exit(EXIT_FAILURE);
        }

        this->SetWidth(PieceDim.at(PieceType).x);
        this->SetHeight(PieceDim.at(PieceType).y);
   
        /* Ajust piece */
        this->Rotate(rotation);

        uint width  = this->GetWidth();
        uint height = this->GetHeight();

        std::string PieceTexture = "../Assets/Sprite/Pieces/" + std::string(1,PieceType) + ".png";

        for(int i=0; i<4; i++){ /* ATENTION - CHANGE THIS SIZE DYNAMICALLY */

            auto collider = new AABBColliderComponent(this,offset[i],BLOCK_SIZE,BLOCK_SIZE,ColliderLayer::PIECE);
            mColliders.emplace_back(collider);
        
            /* PIECE COLLIDER - DEBUG ONLY */
            std::vector<Vector2> vertices;
            vertices.push_back(Vector2(offset[i].x,offset[i].y));
            vertices.push_back(Vector2(offset[i].x+BLOCK_SIZE,offset[i].y));
            vertices.push_back(Vector2(offset[i].x+BLOCK_SIZE,offset[i].y+BLOCK_SIZE));
            vertices.push_back(Vector2(offset[i].x,offset[i].y+BLOCK_SIZE));
            auto polygon = new DrawPolygonComponent(this, vertices);
            polygon->SetColor(0,0,255,255);
            mDrawPolygons.emplace_back(polygon);
            /* PIECE COLLIDER - DEBUG ONLY */
        }
        
        mDrawSpriteComponent = new DrawSpriteComponent(this, PieceTexture, width, height, 10);
    }
}

void Piece::Move(const Vector2&UnitVec){
    
    Vector2 CurrPos = GetPosition();
    /* calculate the next position */
    Vector2 NewPos = CurrPos + UnitVec*BLOCK_SIZE;
    SetPosition(NewPos);

    /* check wall collision */
    std::vector<AABBColliderComponent*> other;
    for(Wall *wall : mGame->GetWalls()){
        other.push_back( wall->GetComponent<AABBColliderComponent>() );
    }
    for(AABBColliderComponent *collider : mColliders)
        collider->DetectCollision(other);
}

void Piece::Rotate(float theta){
    
    int i=0;
    for(auto collider : mColliders){
        
        Vector2 offset = collider->GetOffset();
        double x = offset.x;
        double y = offset.y;
        
        if(theta < 0){
            RotateClockWise(x,y,0,0,90.0f);
        }
        else{
            RotateCounterClockWise(x, y, 0, 0, 90.0f);
        }

        collider->SetOffset(Vector2(x,y));
        mDrawPolygons[i++]->SetVertices(Vector2(x,y));
    }

    SetRotation( GetRotation() - theta );
}

void Piece::Flip(){
    SetFlip(!mFlip);
}

void Piece::OnUpdate(float DeltaTime){
    mCanProcessInput = IsEnabled() ? !mGame->GetAction() : false;
}

void Piece::OnProcessInput(const Uint8 *KeyState){
    if(!IsEnabled() || !mCanProcessInput)
        return;
    if(KeyState[SDL_SCANCODE_W])
        Move(Vector2::NegUnitY);
    if(KeyState[SDL_SCANCODE_A])
        Move(Vector2::NegUnitX);
    if(KeyState[SDL_SCANCODE_S])
        Move(Vector2::UnitY);
    if(KeyState[SDL_SCANCODE_D])
        Move(Vector2::UnitX);
    if(KeyState[SDL_SCANCODE_E])
        Rotate(90.0f);
    if(KeyState[SDL_SCANCODE_Q])
        Rotate(-90.0f);
    if(KeyState[SDL_SCANCODE_F])
        Flip();
    if(KeyState[SDL_SCANCODE_SPACE])
        Place();
}

void Piece::Place(){

    std::vector<AABBColliderComponent*> other;

    for(Piece *piece : mGame->GetBoard()->GetPieces()){
        other.push_back( piece->GetComponent<AABBColliderComponent>() );
    }
    for(Piece *piece : mGame->GetStash()->GetPieces()){
        other.push_back( piece->GetComponent<AABBColliderComponent>() );
    }
    for(Peg *peg : mGame->GetBoard()->GetPegs()){
        other.push_back( peg->GetComponent<AABBColliderComponent>() );
    }
    
    /* check collision for piece multiple colliders */
    for(AABBColliderComponent *collider : mColliders){
        collider->DetectCollision(other);
        if(mCanPlace == false) /* if at least one collided, break */ 
            break;
    }

    if(mCanPlace){
        Cursor *cursor = mGame->GetCursor();
        cursor->Enable();
        cursor->SetPosition(GetPosition());
        this->Disable();
    }
}

 void Piece::OnCollision(const std::vector<Actor*>&responses){
    mCanPlace = responses.empty() ? true : false;
}

void Piece::RotateCounterClockWise(double& x, double& y, double cx, double cy, double theta){
    x -= cx;
    y -= cy;
    double radianTheta = theta * M_PI / 180.0;
    int newX = x*(int)cos(radianTheta)+y*(int)sin(radianTheta);
    int newY = -x*(int)sin(radianTheta)+y*(int)cos(radianTheta);
    x = newX + cx;
    y = newY + cy;
}

void Piece::RotateClockWise(double& x, double& y, double cx, double cy, double theta){
    x -= cx;
    y -= cy;
    double radianTheta = theta * M_PI / 180.0;
    int newX = x*(int)cos(radianTheta)-y*(int)sin(radianTheta);
    int newY = x*(int)sin(radianTheta)+y*(int)cos(radianTheta);
    x = newX + cx;
    y = newY + cy;
}