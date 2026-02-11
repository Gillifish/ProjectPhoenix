#include <GameEngine.h>
#include "ExampleScene.h"

int main(int argc, char const *argv[])
{
    std::unique_ptr<GameEngine> engine (new GameEngine("config/assets.txt"));

    engine->changeScene("EXAMPLESCENE", std::make_shared<ExampleScene>(engine.get()));

    engine->run();
    return 0;
}
