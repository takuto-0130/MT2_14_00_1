#pragma once

class Vector2 final
{
public:
	float x;
	float y;

public:
	Vector2();
	Vector2(const float& inputX, const float& inputY);
	Vector2(const Vector2& input);
	~Vector2();

public:

	constexpr inline Vector2& operator=(const Vector2& input) noexcept;
	inline Vector2& operator+=(const Vector2& input) noexcept;
	inline Vector2& operator-=(const Vector2& input) noexcept;
	inline Vector2& operator*=(const Vector2& input) noexcept;
	inline Vector2& operator/=(const Vector2& input);
	inline const Vector2 operator+(const Vector2& input) const noexcept;
	inline const Vector2 operator-(const Vector2& input) const noexcept;
	inline const Vector2 operator*(const Vector2& input) const noexcept;
	inline const Vector2 operator*(const float& input) const noexcept;
	inline const Vector2 operator/(const Vector2& input) const noexcept;
	inline const Vector2 operator/(const float& input) const noexcept;

public:

	Vector2 Normalize();
	float Length(const Vector2& b);
	float Length();

};





// 演算子のオーバーロード
constexpr inline  Vector2& Vector2::operator=(const Vector2& input) noexcept {
	x = input.x;
	y = input.y;
	return *this;
}

inline Vector2& Vector2::operator+=(const Vector2& input) noexcept {
	x += input.x;
	y += input.y;
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& input) noexcept {
	x -= input.x;
	y -= input.y;
	return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& input) noexcept {
	x *= input.x;
	y *= input.y;
	return *this;
}

inline Vector2& Vector2::operator/=(const Vector2& input) {
	x /= input.x;
	y /= input.y;
	return *this;
}



inline const Vector2 Vector2::operator+(const Vector2& input) const noexcept {
	return { x + input.x, y + input.y };
}

inline const Vector2 Vector2::operator-(const Vector2& input) const noexcept {
	return { x - input.x,y - input.y };
}

inline const Vector2 Vector2::operator*(const Vector2& input) const noexcept {
	return { x * input.x,y * input.y };
}

inline const Vector2 Vector2::operator*(const float& input) const noexcept {
	return { x * input,y * input };
}

inline const Vector2 Vector2::operator/(const Vector2& input) const noexcept {
	return { x / input.x,y / input.y };
}

inline const Vector2 Vector2::operator/(const float& input) const noexcept {
	return { x / input,y / input };
}


