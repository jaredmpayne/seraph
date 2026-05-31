#include <memory>

#include <demos/gravity/App.hpp>
#include <demos/gravity/MyScene.hpp>

int main(int argc, const char **argv) {
    App.set_scene(std::make_shared<MyScene>());
    return App.run();
}
