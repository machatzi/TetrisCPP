#pragma once

enum class MoveDirection {
    RIGHT = 0,
    LEFT,
    DOWN
};

typedef struct BorderWidths_s {
    int top;
    int left;
    int right;
    int bottom;
} BorderWidths_t;