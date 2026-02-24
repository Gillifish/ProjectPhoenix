#include <GameEngine.h>
#include "ExampleScene.h"
#include "Logger.h"
#include <Editor.h>

int main()
{
    Logger::getInstance();

    Logger::log(Logger::INFO, "Testing logger...");

    std::unique_ptr<GameEngine> engine (new GameEngine("config/assets.txt"));

    //engine->changeScene("EXAMPLESCENE", std::make_shared<ExampleScene>(engine.get()));
    engine->changeScene("EDITOR", std::make_shared<Editor>(engine.get()));

    engine->run();

    Logger::destroy();

    return 0;
}
