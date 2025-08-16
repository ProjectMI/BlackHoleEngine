#include "Engine.h"

int main()
{
    Engine engine(800, 600, "Test Engine");
    engine.AddObject(std::make_unique<Grid>(50, 1.0f));
    engine.Run();
    return 0;
}
