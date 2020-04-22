#pragma once

#define BOARD_WIDTH_IN_RECTANGLES 10
#define BOARD_HEIGHT_IN_RECTANGLES 20

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
