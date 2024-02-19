/*******************************************
    Written by Robert Parry [RJP] - 2024    
    Refer to red_main.cpp for the license
*******************************************/

#pragma once

#include "red_includes.h"

class Camera
{
public:
	Camera(Math::Vec3 pos = Math::Vec3(0.0f, 0.0f, 3.0f), Math::Vec3 up = Math::Vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

	Math::Mat4 getViewMatrix();
	void processKeyboard(int direction, float deltaTime);
	void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
	void processMouseScroll(float yOffset);

private:
	const float Speed_ = 2.5f;
	const float Sensitivity_ = 0.1f;
	const float Zoom_ = 45.f;
	float yaw_;
	float pitch_;
	float movementSpeed_;
	float mouseSensitivity_;
	float zoom_;
	Math::Vec3 position_;
	Math::Vec3 front_;
	Math::Vec3 up_;
	Math::Vec3 right_;
	Math::Vec3 worldUp_;

	void updateCameraVectors();

};