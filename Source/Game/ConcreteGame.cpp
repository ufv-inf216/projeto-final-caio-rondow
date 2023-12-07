#include "ConcreteGame.h"
#include "SDL_image.h"
#include "../Components/DrawComponents/DrawComponent.h"    
#include "../Actors/Cursor.h"
#include "../Actors/Block.h"
#include "../Utils/Parser.h"
#include "../Utils/Random.h"

/* PUBLIC METHODS */

/* Constructors */
ConcreteGame::ConcreteGame(uint WindowWidth, uint WindowHeight):
    mTicksCount(0),
    mIsRunning(true),
    mAction(false),
    mWindow(nullptr),
    mCursor(nullptr),
    mRenderer(nullptr),
    mUpdatingActors(false),
    mWindowWidth(WindowWidth),
    mWindowHeight(WindowHeight)
{

}

/* Game Loop */
bool ConcreteGame::InitGame(){
    
    if( SDL_Init(SDL_INIT_VIDEO) != 0 ){
        std::cerr << "In Bool ConcreteGame::InitGame()\n";
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return false;
    }

    /* Create window and renderer*/
    mWindow = SDL_CreateWindow("Twisted Reality", 0, 0, GetWindowWidth(), GetWindowWidth(), 0);
    if(!mWindow){
        std::cerr << "In Bool ConcreteGame::InitGame()\n";
        SDL_Log("Could not initialize SDL window: %s", SDL_GetError());
        return false;
    }
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!mRenderer){
        std::cerr << "In Bool ConcreteGame::InitGame()\n";
        SDL_Log("Could not initialize SDL renderer: %s", SDL_GetError());
        return false;
    }

    Random::Init();

    mAudio = new AudioSystem();
    mAudio->PlaySound("SaveRoom.ogg", true);

    this->InitActors();

    return true;
}

void ConcreteGame::EnterMainLoop(){
    while(mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void ConcreteGame::ShutDown(){
    while(!mActors.empty()){
        delete mActors.back();
    }
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void ConcreteGame::Quit(){
    mIsRunning = false;
}

/* Game Window */
uint ConcreteGame::GetWindowWidth() const{
    return mWindowWidth;
}

uint ConcreteGame::GetWindowHeight() const{
    return mWindowHeight;
}

/* Actors */
void ConcreteGame::AddActor(Actor *actor){
    if(mUpdatingActors){
        mPendingActors.emplace_back(actor);
    } else{
        mActors.emplace_back(actor);
    }
}

void ConcreteGame::RemoveActor(Actor *actor){
    auto it = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if(it != mPendingActors.end()){
        std::iter_swap(it, mPendingActors.end()-1);
        mPendingActors.pop_back();
    }

    it = std::find(mActors.begin(), mActors.end(), actor);
    if(it != mActors.end()){
        std::iter_swap(it, mActors.end()-1);
        mActors.pop_back();
    }
}

/* Drawables */
void ConcreteGame::AddDrawable(DrawComponent *drawable){
    mDrawables.emplace_back(drawable);
    std::sort(mDrawables.begin(), mDrawables.end(),[](DrawComponent* a, DrawComponent* b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void ConcreteGame::RemoveDrawable(DrawComponent *drawable){
    auto it = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    mDrawables.erase(it);
}

void ConcreteGame::DrawLast(DrawComponent *drawable){
    auto it = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    if(it != mDrawables.end()){
        std::iter_swap(it, mDrawables.end()-1);
    }
}


/* Load methods */
SDL_Texture *ConcreteGame::LoadTexture(const std::string&TextureFile) const{
    SDL_Surface *surface = IMG_Load(TextureFile.c_str());
    if(surface == nullptr){
        std::cerr << "In SDL_Texture* ConcreteGame::LoadTexture(const std::string& texturePath)\n";
        std::cerr << "Could not load " << TextureFile << " surface.\n";
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    if(texture == nullptr){
        std::cerr << "In SDL_Texture* ConcreteGame::LoadTexture(const std::string& texturePath)\n";
        std::cerr << "Could not load " << TextureFile << " texture.\n";
        return nullptr;
    }
    return texture;
}

void ConcreteGame::LoadLevel(const std::string&StartLevel, const std::string&EndLevel){

    Vector2 BoardOrigin = Vector2(BOARD_ORIGIN_X, BOARD_ORIGIN_Y);
    Vector2 StashOrigin = Vector2(STASH_ORIGIN_X, STASH_ORIGIN_Y);

    mBoard  = new Table(this, BoardOrigin, BOARD_WIDTH, BOARD_HEIGHT);
    mStash  = new Table(this, StashOrigin, STASH_WIDTH, STASH_HEIGHT);
    mCursor = new Cursor(this, BOARD_ORIGIN_X, BOARD_ORIGIN_Y, true);

    parser::RaiseWalls(this, mWalls);
    parser::LoadTable(StartLevel, *mBoard, *mStash);
    parser::LoadAnwser(EndLevel, mAnswer);
}

/* PRIVATE METHODS */
void ConcreteGame::ProcessInput(){

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            Quit();
            break;
        case SDL_KEYDOWN:
            mAction = true;
            break;
        case SDL_KEYUP:
            mAction = false;
            break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    
    for(auto actor : mActors){
        if(mAction)
            actor->ProcessInput(state);
    }
}

void ConcreteGame::UpdateGame(){
    
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float DeltaTime = (float)(SDL_GetTicks() - mTicksCount) / 1000.0f;
    if(DeltaTime > 0.05f)
        DeltaTime = 0.05f;
    mTicksCount = SDL_GetTicks();

    mAudio->Update(DeltaTime);

    UpdateActors(DeltaTime);
}

void ConcreteGame::GenerateOutput(){
    /* Set draw color */
    SDL_SetRenderDrawColor(mRenderer, 0x0, 0x0, 0x0, 0xFF);
    /* Clear the current rendering */
    SDL_RenderClear(mRenderer);

    for(auto drawable : mDrawables){
        if(drawable->IsComponentEnabled()){
            drawable->Draw(mRenderer);   
        }
    }

    /* Swap front and back buffers - actually rendering */
    SDL_RenderPresent(mRenderer);
}

void ConcreteGame::InitActors(){
    LoadLevel(
        "../Assets/Level/Start/example0.csv",
        "../Assets/Level/End/example0.csv"
    );
}

bool ConcreteGame::IsOnBoard(const Vector2 &pos) const{
    return ( 
        pos.x < BOARD_WIDTH*BLOCK_SIZE + BOARD_ORIGIN_X && 
        pos.x >= BOARD_ORIGIN_X &&
        pos.y < BOARD_HEIGHT*BLOCK_SIZE + BOARD_ORIGIN_Y &&
        pos.y >= BOARD_ORIGIN_Y
    );
            
}

bool ConcreteGame::IsLevelComplete() const{
    
    if(mBoard->GetPieces().size() != NUMBER_OF_PIECES){
        return false;
    }

    /* compare the current board state with the answer */
    for(Piece *p : mBoard->GetPieces()){

        for(AABBColliderComponent *collider : p->GetColliders()){
            
            char type = p->GetPieceType();
            int i = (int)(collider->GetMin().y-BOARD_ORIGIN_Y)/BLOCK_SIZE;
            int j = (int)(collider->GetMin().x-BOARD_ORIGIN_X)/BLOCK_SIZE;

            if(type != mAnswer[i][j])
                return false;
        }
    }

    return true;
}

void ConcreteGame::UpdateActors(float DeltaTime){
    
    mUpdatingActors = true;

    for(auto actor : mActors){
        actor->Update(DeltaTime);
    }

    mUpdatingActors = false;

    for(auto pending : mPendingActors){
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor*> DeadActors;
    for(auto actor : mActors){
        if(actor->GetActorState() == ActorState::DESTROY){
            DeadActors.emplace_back(actor);
        }
    }
    
    for(auto actor : DeadActors){
        delete actor;
    }
}