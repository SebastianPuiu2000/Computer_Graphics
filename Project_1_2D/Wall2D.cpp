#include "Wall2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Wall2D::Wall2D() {
    
}

Wall2D::Wall2D(float x, float y, std::string z, float a, float b, bool f, glm::vec3 c) {
    width = x;
    height = y;

    leftBottomCorner = glm::vec3(0, 0, 0);
    color = c;
    fill = f;

    name = z;
}

Mesh* Wall2D::CreateWall()
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* obstacle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        obstacle->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    obstacle->InitFromData(vertices, indices);
    return obstacle;

}

void Wall2D::SetColorRed() {
    color = glm::vec3(1, 0, 0);
}





