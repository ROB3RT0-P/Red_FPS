/*******************************************
    Written by Robert Parry [RJP] - 2023    
	Refer to red_main.cpp for the license
*******************************************/

#include "red_math.h"

float M_PI = 3.14f;

namespace Math {

	float ToRadians(float degrees) 
	{
		return degrees * (M_PI / 180.0f);
	}

	Vec3 Normalise(const Vec3& vector) 
	{
		float length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		return { vector.x / length, vector.y / length, vector.z / length };
	}

	Mat4 Translate(const Mat4& matrix, const Vec3& translation)
	{
		Mat4 result = matrix;
		result.data[12] += translation.x;
		result.data[13] += translation.y;
		result.data[14] += translation.z;

		return result;
	}

	Mat4 MultiplyMat4(const Mat4& left, const Mat4& right)
	{
		Mat4 result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				float sum = 0.0f;
				for (int i = 0; i < 4; i++)
				{
					sum += left.data[row + i * 4] * right.data[i + column * 4];
				}
				result.data[row + column * 4] = sum;
			}
		}
		return result;
	}

	Mat4 Rotate(const Mat4& matrix, float angle, const Vec3& axis)
	{
		Mat4 result = matrix;

		float radianAngle = ToRadians(angle);
		float c = cos(radianAngle);
		float s = sin(radianAngle);

		Vec3 normalisedAxis = Normalise(axis);
		float ux = normalisedAxis.x;
		float uy = normalisedAxis.y;
		float uz = normalisedAxis.z;

		Mat4 rotation = Identity();

		rotation.data[0] = c + (1 - c) * ux * ux;
		rotation.data[1] = (1 - c) * ux * uy - s * uz;
		rotation.data[2] = (1 - c) * ux * uz - s * uy;

		rotation.data[4] = (1 - c) * uy * ux + s * uz;
		rotation.data[5] = c + (1 - c) * uy * uy;
		rotation.data[6] = (1 - c) * uy * uz - s * ux;

		rotation.data[8] = (1 - c) * uz * ux - s * uy;
		rotation.data[9] = (1 - c) * uz * uy + s * ux;
		rotation.data[10] = c + (1 - c) * uz * uz;

		result = MultiplyMat4( result, rotation );
		return result;
	}



	Mat4 Scale(const Mat4& matrix, const Vec3& scale)
	{
		Mat4 result;
		
		result.data[0] *= scale.x;
		result.data[5] *= scale.y;
		result.data[10] *= scale.z;

		return result;
	}

	Mat4 Perspective(float fov, float aspect, float near, float far)
	{
		Mat4 result;
		 
		float tanHalfFov = tan(fov / 2.0f);
		result.data[0] = 1.0f / (tanHalfFov * aspect);
		result.data[5] = 1.0f / tanHalfFov;
		result.data[10] = -(far + near) / (far - near);
		result.data[11] = 1.0f;
		result.data[14] = -(2.0f * far * near) / (far - near);

		return result;
	}

	Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
	{
		Vec3 forward = Normalise(Subtract(center, eye));
		Vec3 right = Normalise(Cross(forward, up));
		Vec3 newUp = Cross(right, forward);

		Mat4 result = {};
			result.data[0] = right.x;
			result.data[1] = newUp.x;
			result.data[2] = -forward.x;
			result.data[3] = 0.0f;
			result.data[4] = right.y;
			result.data[5] = newUp.y;
			result.data[6] = -forward.y;
			result.data[7] = 0.0f;
			result.data[8] = right.z;
			result.data[9] = newUp.z;
			result.data[10] = -forward.z;
			result.data[11] = 0.0f;
			result.data[12] = -Dot(right, eye);
			result.data[13] = -Dot(newUp, eye);
			result.data[14] = Dot(forward, eye);
			result.data[15] = 1.0f;

		return result;
	}

	Vec3 Subtract(const Vec3& a, const Vec3& b)
	{
		Vec3 result = { a.x - b.x, a.y - b.y, a.z - b.z };

		return result;
	}

	Vec3 Add(const Vec3& a, const Vec3& b)
	{
		Vec3 result = { a.x + b.x, a.y + b.y, a.z + b.z };

		return result;
	}

	float Dot(const Vec3& a, const Vec3& b)
	{
		float result = a.x * b.x + a.y * b.y + a.z * b.z;

		return result;
	}

	Vec3 Multiply(const Vec3& vector, const float scalar)
	{
		Vec3 result = { vector.x * scalar, vector.y * scalar, vector.z * scalar };
		
		return result;
	}

	Mat4 Identity()
	{
		Mat4 result;

		 
		return result;
	}

	Vec3 Cross(const Vec3& a, const Vec3& b)
	{
		Vec3 result;

		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;

		return result;
	}
}