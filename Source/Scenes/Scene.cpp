#include "Scene.h"

Scene::Scene(InterfaceGame *game):
    mGame(game)
{

}

void Scene::Load(){

}

void ProcessInput(const Uint8 *KeyState){
    
}

InterfaceGame *Scene::GetGame() const{
    return mGame;
}