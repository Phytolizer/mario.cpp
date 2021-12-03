#pragma once

#include <Level.pb.h>
#include <glm/vec2.hpp>

class Transform
{
  public:
    glm::vec2 position;
    glm::vec2 scale;

    Transform();
    explicit Transform(glm::vec2 position);
    Transform(glm::vec2 position, glm::vec2 scale);
    void init(glm::vec2 position, glm::vec2 scale);

    constexpr bool operator==(const Transform& other) const
    {
        return position == other.position && scale == other.scale;
    }

    void saveState(proto::Transform* serial) const;
    static Transform fromSerial(const proto::Transform& serial);
};
