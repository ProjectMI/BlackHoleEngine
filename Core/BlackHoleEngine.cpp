#include "Engine/Engine.h"
#include "Objects/Grid.h"
#include "Objects/BlackHole.h"
#include "Objects/StarSkybox.h"
#include "Objects/BlackHoleLensEffect.h"

int main()
{
    Engine engine(1920, 1080, "Test Engine");
    engine.AddObject(std::make_unique<StarSkybox>(1000, engine.Width, engine.Height));
    engine.AddObject(std::make_unique<BlackHole>(4.f));
    engine.GetObject(1)->SetPosition(Vector3D(10, 5, 5));
    engine.AddObject(std::make_unique<BlackHoleLensEffect>(dynamic_cast<BlackHole*>(engine.GetObject(1)), dynamic_cast<StarSkybox*>(engine.GetObject(0))));
    engine.AddObject(std::make_unique<Grid>(50, 1.0f, dynamic_cast<BlackHole*>(engine.GetObject(1)), 15.f));   
    engine.Run();
    return 0;
}
