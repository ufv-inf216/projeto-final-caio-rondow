#include "Table.h"
#include "Block.h"
#include "Piece.h"
#include "../Game/ConcreteGame.h"

#define INPUT_DELAY 0.085
#define BLOCK_OFFSET 32

Table::Table(InterfaceGame *game, uint width, uint height):
    Actor(game),
    mTableWidth(width),
    mTableHeight(height),
    mTimesPassed(0.0f),
    mTable(height, std::vector<Block*>(width, nullptr)),
    mCanProcessInput(true),
    mIsAction(false)
{   
    /* Create table */
    for(int i=0; i<mTableHeight; i++){
        for(int j=0; j<mTableWidth; j++){
            mTable[i][j] = new Block(game);
        }
    }
    /* Create table walls */
    mWalls.emplace_back(new Block(game, mTableWidth*BLOCK_OFFSET, BLOCK_OFFSET, ColliderLayer::WALL));
    mWalls.emplace_back(new Block(game, mTableWidth*BLOCK_OFFSET, BLOCK_OFFSET, ColliderLayer::WALL));

    /* LINK BLOCKS */
    for(int i=0; i<mTableHeight; i++){
        for(int j=0; j<mTableWidth; j++){
            
            Block *CurrentBlock = mTable[i][j];

            if(i > 0){
                CurrentBlock->Link(mTable[i-1][j], UP);
            }

            if(i < mTableHeight-1){
                CurrentBlock->Link(mTable[i+1][j], DOWN);
            }

            if(j > 0){
                CurrentBlock->Link(mTable[i][j-1], LEFT);
            }

            if(j < mTableWidth-1){
                CurrentBlock->Link(mTable[i][j+1], RIGHT);
            }
        }
    }
}

void Table::OnUpdate(float DeltaTime){
    
    mTimesPassed += DeltaTime;
    if(mTimesPassed >= INPUT_DELAY){
        mTimesPassed = 0.0f;
        mCanProcessInput = true;
    }

    if(mIsAction){
        Block *cursor = mGame->GetCursor();
        cursor->GetComponent<AABBColliderComponent>()->DetectCollision();
    }

    mIsAction = false;
}

void Table::OnProcessInput(const Uint8 *KeyState){

    Block *cursor = mGame->GetCursor();

    if(cursor == nullptr || mCanProcessInput == false)
        return;

    if(KeyState[SDL_SCANCODE_SPACE]){
        mIsAction = true;
    }
    if(KeyState[SDL_SCANCODE_W] && (*cursor)[UP] != nullptr){
        cursor->SetSelected(false);
        cursor = (*cursor)[UP];
    }
    if(KeyState[SDL_SCANCODE_A] && (*cursor)[LEFT] != nullptr){
        cursor->SetSelected(false);
        cursor = (*cursor)[LEFT];
    }
    if(KeyState[SDL_SCANCODE_S] && (*cursor)[DOWN] != nullptr){
        cursor->SetSelected(false);
        cursor = (*cursor)[DOWN];
    }
    if(KeyState[SDL_SCANCODE_D] && (*cursor)[RIGHT] != nullptr){
        cursor->SetSelected(false);
        cursor = (*cursor)[RIGHT];
    }
    cursor->SetSelected(true);
    mGame->SetCursor(cursor);
    mCanProcessInput = false;
}

void Table::SetTablePosition(const Vector2&pos){
    SetPosition(pos);
    int i=0, j=0;
    for(auto row : mTable){
        for(auto col : row){
            float x = j*BLOCK_OFFSET + GetPosition().x;
            float y = i*BLOCK_OFFSET + GetPosition().y;
            col->SetPosition(Vector2(x,y));
            j++;
        }
        i++;
        j=0;
    }
    mWalls[0]->SetPosition(GetPosition()+Vector2(0,-BLOCK_OFFSET));
    mWalls[1]->SetPosition(GetPosition()+Vector2(0,mTableHeight*BLOCK_OFFSET));
    
}

void Table::Link(Table *other, uint side){
    switch (side)
    {
    case RIGHT:
        for(int i=0; i<other->mTableHeight; i++){
            Block *prev = other->mTable[i][0];
            Block *next = mTable[i%mTableHeight][mTableWidth-1];
            prev->Link(next, LEFT);
            next->Link(prev, RIGHT);
        }
        break;
    /* add other cases if needed */
    default:
        break;
    }
}

void Table::AddPiece(Piece *piece){
    Vector2 pos = piece->GetPosition();
    piece->SetPosition( Vector2((GetPosition().x+32*pos.x), (GetPosition().y+32*pos.y)) );
    mPieces.emplace_back(piece);
    std::cout << piece->GetPosition().x << " " << piece->GetPosition().y << "\n";
    auto collider = piece->GetComponent<AABBColliderComponent>();
    std::cout << collider->GetMin().x << " " << collider->GetMin().y << "\n";
    std::cout << collider->GetMax().x << " " << collider->GetMax().y << "\n";
}

void Table::RemovePiece(Piece *piece){
    /* does not lose *piece reference.
    When a new piece is created, game add it
    on Actors to be deleted on ShutDown() */
    auto it = std::find(mPieces.begin(), mPieces.end(), piece);
    if(it != mPieces.end()){
        std::iter_swap(it, mPieces.end()-1);
        mPieces.pop_back();
    }
}

// void Table::DetectCollision(){

//     Block *cursor = mGame->GetCursor();

//     std::vector<Actor*> actors;
//     std::vector<AABBColliderComponent*> colliders;

//     /* detect collision for every piece in the table */
//     for(auto piece : mPieces){
//         for(auto collider : piece->GetCollider())
//             colliders.push_back(collider);
//     }
//     for(auto wall : mWalls){
//         colliders.push_back(wall->GetComponent<AABBColliderComponent>());
//     }
//     cursor->GetComponent<AABBColliderComponent>()->DetectCollision(colliders);
// }