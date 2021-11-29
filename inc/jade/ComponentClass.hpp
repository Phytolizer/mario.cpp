#pragma once

#define COMPONENT_CLASSES_ \
    X(SPRITE_RENDERER) \
    X(FONT_RENDERER)

enum class ComponentClass
{
#define X(x) x,
    COMPONENT_CLASSES_
#undef X
};
