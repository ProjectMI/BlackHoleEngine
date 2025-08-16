#pragma once
#include "Objects/SceneObject.h"


class Grid : public SceneObject
{
public:
    Grid(int size, float step);
    ~Grid() = default;
};
