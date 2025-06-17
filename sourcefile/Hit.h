#pragma once

#include "Float2.h"

//	座標や四角の大きさに Float2 を渡すバージョン
bool CheckCircleHit(Float2 circle1, float radius1, Float2 circle2, float radius2);
bool CheckPointCircleHit(Float2 point, Float2 circle, float radius);
bool CheckBoxHit(Float2 box_pos1, Float2 box_size1, Float2 box_pos2, Float2 box_size2);
bool CheckPointBoxHit(Float2 point, Float2 box_pos, Float2 box_size);
bool CheckCircleBoxHit(Float2 circle, float radius, Float2 box_pos, Float2 box_size);

//	今までのバージョン
float GetDistance(float x1, float y1, float x2, float y2);
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2);
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r);
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h);
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h);
