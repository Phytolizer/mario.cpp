#include "jade/Transform.hpp"

Transform::Transform() = default;

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

void Transform::saveState(proto::Transform* serial) const
{
    proto::Vec2* pos = serial->mutable_position();
    pos->set_x(position.x);
    pos->set_y(position.y);
    proto::Vec2* sc = serial->mutable_scale();
    sc->set_x(scale.x);
    sc->set_y(scale.y);
}
