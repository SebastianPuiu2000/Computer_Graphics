#include "RenderInfo.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

RenderInfo::RenderInfo() {
    
}

RenderInfo::RenderInfo(float x, float y, float a, float b) {
    width = x;
    height = y;

    translateX = a;
    translateY = b;

}




