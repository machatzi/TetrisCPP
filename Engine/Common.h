#pragma once

enum class MoveDirection {
    RIGHT = 0,
    LEFT,
    DOWN
};

enum class RectangleType {
    SOLID = 0,
    BORDER_ONLY
};

typedef struct SqrPointsLocation_s {
    int y_up_side_indx;
    int y_down_side_indx;
    int y_center_indx;
    int x_indx;
} SqrPointsLocation_t;

typedef struct VectorPosition_s {
    int x;
    int y;
} VectorPosition_t;
