#include "Engine/Engine.h"
#include "Objects/BlackHole.h"
#include "Objects/StarSkybox.h"
#include "Objects/Grid.h"

int main()
{
    Engine engine(1920, 1080, "Test Engine");
    engine.AddObject(std::make_unique<Grid>(50, 1.0f));
    engine.AddObject(std::make_unique<StarSkybox>(1000));
    engine.Run();
    return 0;
}
