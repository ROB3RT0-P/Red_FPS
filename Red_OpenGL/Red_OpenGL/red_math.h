/*******************************************
    Written by Robert Parry [RJP] - 2023    
	Refer to red_main.cpp for the license
*******************************************/

#pragma once

#include <cmath>

namespace Math 
{
	struct Vec3 
	{
		float x, y, z;

		Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

		Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	};

	struct Mat4 
	{
		float data[16];
	};


	float ToRadians(float degrees);
	Vec3 Normalise(const Vec3& vector);
	Vec3 Cross(const Vec3& a, const Vec3& b);
	Mat4 Identity();
	Mat4 Translate(const Mat4& matrix, const Vec3& translation);
	Mat4 Rotate(const Mat4& matrix, float angle, const Vec3& axis);
	Mat4 Scale(const Mat4& matrix, const Vec3& scale);
	Mat4 Perspective(float fov, float aspect, float near, float far);
	Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
	Vec3 Add(const Vec3& a, const Vec3& b);
	Vec3 Subtract(const Vec3& a, const Vec3& b);
	float Dot(const Vec3& a, const Vec3& b);
	Vec3 Multiply(const Vec3& vector, const float scalar);
}