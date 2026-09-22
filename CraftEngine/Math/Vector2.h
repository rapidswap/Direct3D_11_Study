#pragma once

#include <Core/Core.h>

namespace Craft
{
	class Vector2
	{
	public:
		Vector2(float x = 0.0f, float y = 0.0f);

		// 내적/길이 함수.
		float Length() const;
		float LengthSqared() const;
		Vector2 Normalized() const;
		float Dot(const Vector2& other) const;

		// 연산자 오버로딩.
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		Vector2& operator=(const Vector2& other);
	public:
		float x = 0.0f;
		float y = 0.0f;

		// 자주 사용할 값 static으로 선언.
		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 Right;
		static const Vector2 Up;
	};
}

