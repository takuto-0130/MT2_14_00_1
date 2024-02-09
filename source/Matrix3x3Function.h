#pragma once
#include "Vector2Class.h"
#include <assert.h>
#define USE_MATH_DEFINES
#include <math.h>

struct Matrix3x3 {
	float m[3][3];
};

Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

Matrix3x3 Inverse(Matrix3x3 matrix);

Matrix3x3 MakeTransrateMatrix(Vector2 transrate);

Matrix3x3 MakeRotateMatrix(float theta);

Matrix3x3 MakeScaleMatrix(Vector2 scale);

Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 transrate);

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);
