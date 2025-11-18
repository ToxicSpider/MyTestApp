#ifndef COMMON_H
#define COMMON_H

#include <string>


/*
This header file contains constants that are needed in various classes, so I placed it in a separate file.
*/

constexpr float PI = 3.14f;
constexpr float MIN_COORD = -1.0f;
constexpr float MAX_COORD = 1.0f;
constexpr float MIN_ANGLE = -PI;
constexpr float MAX_ANGLE = PI;

const std::string TASK10_NAME = "Task10";
const std::string TASK20_NAME = "Task20";
const std::string TASK40_NAME = "Task40";

#endif // COMMON_H