#include "Matrix3x3Function.h"

Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result;
	float buf;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			buf = 0;
			for (int k = 0; k < 3; k++) {
				buf = buf + matrix1.m[i][k] * matrix2.m[k][j];
				result.m[i][j] = buf;
			}
		}
	}
	return result;
}

Matrix3x3 Inverse(Matrix3x3 matrix) {
	Matrix3x3 result;
	float determinant = 1 / (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] - matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);
	if (determinant != 0) {
		result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) * determinant;
		result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) * determinant;
		result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) * determinant;
		result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) * determinant;
		result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) * determinant;
		result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) * determinant;
		result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * determinant;
		result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) * determinant;
		result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) * determinant;
	}
	return result;
}

Matrix3x3 MakeTransrateMatrix(Vector2 transrate) {
	Matrix3x3 result;
	result.m[0][0] = 1; result.m[0][1] = 0; result.m[0][2] = 0;
	result.m[1][0] = 0; result.m[1][1] = 1; result.m[1][2] = 0;
	result.m[2][0] = transrate.x; result.m[2][1] = transrate.y; result.m[2][2] = 1;
	return result;
}

Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 m1;
	m1.m[0][0] = cosf(theta);  m1.m[0][1] = sinf(theta); m1.m[0][2] = 0;
	m1.m[1][0] = -sinf(theta); m1.m[1][1] = cosf(theta); m1.m[1][2] = 0;
	m1.m[2][0] = 0;            m1.m[2][1] = 0;           m1.m[2][2] = 1;
	return m1;
}

Matrix3x3 MakeScaleMatrix(Vector2 scale) {
	Matrix3x3 result;
	result.m[0][0] = scale.x; result.m[0][1] = 0; result.m[0][2] = 0;
	result.m[1][0] = 0; result.m[1][1] = scale.y; result.m[1][2] = 0;
	result.m[2][0] = 0; result.m[2][1] = 0; result.m[2][2] = 1;
	return result;
}

Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 transrate) {
	Matrix3x3 m1;
	m1.m[0][0] = scale.x * cosf(theta);  m1.m[0][1] = scale.x * sinf(theta); m1.m[0][2] = 0;
	m1.m[1][0] = scale.y * -sinf(theta); m1.m[1][1] = scale.y * cosf(theta); m1.m[1][2] = 0;
	m1.m[2][0] = transrate.x;			 m1.m[2][1] = transrate.y;			 m1.m[2][2] = 1;
	return m1;
}

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 result;
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;
	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1;
	return result;
}

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 result;
	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0;
	result.m[2][0] = left + (width / 2.0f);
	result.m[2][1] = top + (height / 2.0f);
	result.m[2][2] = 1;
	return result;
}