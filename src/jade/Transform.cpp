#include "jade/Transform.hpp"

Transform::Transform() : position(), scale()
{
}

Transform::Transform(glm::vec2 position) : position(position), scale()
{
}

Transform::Transform(glm::vec2 position, glm::vec2 scale) : position(position), scale(scale)
{
}

void Transform::init(glm::vec2 position, glm::vec2 scale)
{
    this->position = position;
    this->scale = scale;
}
