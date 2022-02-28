#pragma once

#include "utils/glm_utils.h"


namespace Transform3D
{
    // Translate matrix
    inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
    {
        return glm::mat4(1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            translateX, translateY, translateZ, 1.f);

    }

    // Scale matrix
    inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
    {
        return glm::mat4(scaleX, 0.f, 0.f, 0.f,
            0.f, scaleY, 0.f, 0.f,
            0.f, 0.f, scaleZ, 0.f,
            0.f, 0.f, 0.f, 1.f);

    }

    // Rotate matrix relative to the OZ axis
    inline glm::mat4 RotateOZ(float radians)
    {

        float cosinus = cos(radians);
        float sinus = sin(radians);
        return glm::mat4(cosinus, sinus, 0.f, 0.f,
            -sinus, cosinus, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f);

    }

    // Rotate matrix relative to the OY axis
    inline glm::mat4 RotateOY(float radians)
    {

        float cosinus = cos(radians);
        float sinus = sin(radians);
        return glm::mat4(cosinus, 0.f, -sinus, 0.f,
            0.f, 1.f, 0.f, 0.f,
            sinus, 0.f, cosinus, 0.f,
            0.f, 0.f, 0.f, 1.f);

    }

    // Rotate matrix relative to the OX axis
    inline glm::mat4 RotateOX(float radians)
    {

        float cosinus = cos(radians);
        float sinus = sin(radians);
        return glm::mat4(1.f, 0.f, 0.f, 0.f,
            0.f, cosinus, sinus, 0.f,
            0.f, -sinus, cosinus, 0.f,
            0.f, 0.f, 0.f, 1.f);

    }
}   // namespace transform3D
