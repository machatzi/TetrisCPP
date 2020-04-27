#pragma once

enum class MoveDirection {
    RIGHT = 0,
    LEFT,
    DOWN
};

typedef struct VectorPosition_s {
    int x;
    int y;
} VectorPosition_t;
