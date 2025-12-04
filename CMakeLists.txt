cmake_minimum_required(VERSION 3.30)
project(seraph)
set(CMAKE_CXX_STANDARD 23)

add_library(
    seraph

    STATIC

    seraph/action/FunctionAction.cpp
    seraph/action/InfiniteAction.cpp
    seraph/action/MoveAction.cpp
    seraph/action/ParallelAction.cpp
    seraph/action/RepeatAction.cpp
    seraph/action/RotateAction.cpp
    seraph/action/ScaleAction.cpp
    seraph/action/SequenceAction.cpp
    seraph/action/WaitAction.cpp
    
    seraph/core/Game.cpp
    seraph/core/Window.cpp

    seraph/hash/SipHasher.cpp

    seraph/node/LabelNode.cpp
    seraph/node/MusicNode.cpp
    seraph/node/Node.cpp
    seraph/node/Scene.cpp
    seraph/node/ShapeNode.cpp
    seraph/node/SoundNode.cpp
    seraph/node/SpriteNode.cpp

    seraph/physics/PhysicsWorld.cpp
    seraph/physics/RectanglePhysicsBody.cpp
)
target_include_directories(
    seraph
    PRIVATE
    .
)

add_executable(
    gravity
    demos/gravity/main.cpp
)
target_include_directories(
    gravity
    PRIVATE
    .
)
target_link_libraries(
    gravity
    PRIVATE
    seraph
    -lsfml-audio
    -lsfml-graphics
    -lsfml-system
    -lsfml-window
)

# enable_testing()

# add_executable(
#     seraph_tests
#     tests/main.cpp
# )
# target_include_directories(
#     seraph_tests
#     PRIVATE
#     .
# )
# target_link_libraries(
#     seraph_tests
#     PRIVATE
#     seraph
# )
# add_test(seraph_tests seraph_tests)
