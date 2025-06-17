#include "WinMain.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	円同士の当たり判定（Float2 を渡すバージョン）
//---------------------------------------------------------------------------------
bool CheckCircleHit(Float2 circle1, float radius1, Float2 circle2, float radius2)
{
	float distance = GetFloat2Distance(circle1, circle2);
	float radius = radius1 + radius2;
	if (distance <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	点と円の当たり判定（Float2 を渡すバージョン）
//---------------------------------------------------------------------------------
bool CheckPointCircleHit(Float2 point, Float2 circle, float radius)
{
	float distance = GetFloat2Distance(point, circle);
	if (distance <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	四角同士の当たり判定（Float2 を渡すバージョン）
//---------------------------------------------------------------------------------
bool CheckBoxHit(Float2 box_pos1, Float2 box_size1, Float2 box_pos2, Float2 box_size2)
{
	if (box_pos1.x + box_size1.x >= box_pos2.x && box_pos1.x <= box_pos2.x + box_size2.x) {
		if (box_pos1.y + box_size1.y >= box_pos2.y && box_pos1.y <= box_pos2.y + box_size2.y) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	点と四角の当たり判定（Float2 を渡すバージョン）
//---------------------------------------------------------------------------------
bool CheckPointBoxHit(Float2 point, Float2 box_pos, Float2 box_size)
{
	if (point.x >= box_pos.x && point.x <= box_pos.x + box_size.x) {
		if (point.y >= box_pos.y && point.y <= box_pos.y + box_size.y) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	円と四角の当たり判定（Float2 を渡すバージョン）
//---------------------------------------------------------------------------------
bool CheckCircleBoxHit(Float2 circle, float radius, Float2 box_pos, Float2 box_size)
{
	Float2 near_pos;

	near_pos.x = circle.x;
	if (near_pos.x < box_pos.x)				near_pos.x = box_pos.x;
	if (near_pos.x > box_pos.x + box_size.x)	near_pos.x = box_pos.x + box_size.x;

	near_pos.y = circle.y;
	if (near_pos.y < box_pos.y)				near_pos.y = box_pos.y;
	if (near_pos.y > box_pos.y + box_size.y)	near_pos.y = box_pos.y + box_size.y;

	if (CheckPointCircleHit(near_pos, circle, radius)) {
		return true;
	}

	return false;
}

//*********************************************************************************
//	float を渡すバージョン
//*********************************************************************************
//---------------------------------------------------------------------------------
//	２点の長さを取得する関数
//---------------------------------------------------------------------------------
float GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float distance = sqrtf(x * x + y * y);
	return distance;
}
//---------------------------------------------------------------------------------
//	円同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float distance = GetDistance(x1, y1, x2, y2);
	float radius = r1 + r2;
	if (distance <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	点と円の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r)
{
	float distance = GetDistance(point_x, point_y, circle_x, circle_y);
	if (distance <= circle_r) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	四角同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if (x1 + w1 >= x2 && x1 <= x2 + w2) {
		if (y1 + h1 >= y2 && y1 <= y2 + h2) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	点と四角の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h)
{
	if (point_x >= box_x && point_x <= box_x + box_w) {
		if (point_y >= box_y && point_y <= box_y + box_h) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	円と四角の当たり判定
//---------------------------------------------------------------------------------
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h)
{
	float near_x = circle_x;
	if (near_x < box_x)			near_x = box_x;
	if (near_x > box_x + box_w)	near_x = box_x + box_w;

	float near_y = circle_y;
	if (near_y < box_y)			near_y = box_y;
	if (near_y > box_y + box_h)	near_y = box_y + box_h;

	if (CheckPointCircleHit(near_x, near_y, circle_x, circle_y, circle_r)) {
		return true;
	}

	return false;
}
