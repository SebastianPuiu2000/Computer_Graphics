#include "EnemyInfo.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

EnemyInfo::EnemyInfo() {

}

EnemyInfo::EnemyInfo(bool alive, float x, float y, float z) {

    isAlive = alive;

    positionX = x;

    positionY = y;

    positionZ = z;

}




