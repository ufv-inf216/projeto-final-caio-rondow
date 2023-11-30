cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SKIP_RPATH ON)
set(PROJECT_NAME "twisted-reality")

project(${PROJECT_NAME})
add_executable(
    ${PROJECT_NAME}
    Source/Main.cpp
    Source/Utils/Math.cpp
    Source/Game/ConcreteGame.cpp
    
    Source/Actors/Actor.cpp
    Source/Actors/Block.cpp
    Source/Actors/Piece.cpp
    Source/Actors/Table.cpp

    Source/Components/Component.cpp
    Source/Components/DrawComponents/DrawComponent.cpp
    Source/Components/DrawComponents/DrawSpriteComponent.cpp
    Source/Components/DrawComponents/DrawAnimatedComponent.cpp
    Source/Components/ColliderComponents/AABBColliderComponent.cpp
)

find_package(SDL2 2.28.2 EXACT REQUIRED)
find_package(SDL2_image REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
