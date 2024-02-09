#include "Vector2Class.h"
#include <math.h>
#define USE_MATH_DEFINES

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(const float& inputX, const float& inputY) {
	x = inputX;
	y = inputY;
}

Vector2::Vector2(const Vector2& input) {
	x = input.x;
	y = input.y;
}

Vector2::~Vector2() {
}

Vector2 Vector2::Normalize() {
	float denominator = sqrtf(x * x + y * y);
	Vector2 result = { 0,0 };
	if (denominator != 0) {
		result = { x / denominator, y / denominator };
	}
	return result;
}

float Vector2::Length(const Vector2& b) {
	return sqrtf((b.x - x) * (b.x - x) + (b.y - y) * (b.y - y));
}

float Vector2::Length() {
	return sqrtf(x * x + y * y );
}