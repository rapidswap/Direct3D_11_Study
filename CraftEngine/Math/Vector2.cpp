#include "Vector2.h"
#include <cmath>
#include <cassert>

namespace Craft
{
	// static 변수 설정.
	const Vector2 Vector2::Zero(0.0f,0.0f);
	const Vector2 Vector2::One(1.0f,1.0f);
	const Vector2 Vector2::Right(1.0f,0.0f);
	const Vector2 Vector2::Up(0.0f,1.0f);

	Vector2::Vector2(float x, float y)
		:x(x), y(y)
	{
	}
	float Vector2::Length() const
	{
		// 피타고라스 정리 활용.
		return std::sqrt(x * x + y * y);
	}
	float Vector2::LengthSqared() const
	{
			return x * x + y * y;
	}
	Vector2 Vector2::Normalized() const
	{
		return Vector2();
	}
	float Vector2::Dot(const Vector2& other) const
	{
		return 0.0f;
	}
	bool Vector2::operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}
	bool Vector2::operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}
	Vector2& Vector2::operator=(const Vector2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
}
