/*******************************************
	Written by Robert Parry [RJP] - 2024
	Refer to red_main.cpp for the license
*******************************************/

#include "red_camera.h"

Camera::Camera(Math::Vec3 position, Math::Vec3 up, float yaw, float pitch)
    : front_({ 0.0f, 0.0f, -1.0f }), movementSpeed_(Speed_), mouseSensitivity_(Sensitivity_),
    zoom_(Zoom_), position_(position), worldUp_(up), yaw_(yaw), pitch_(pitch) {
    updateCameraVectors();
}

Math::Mat4 Camera::getViewMatrix() {
    Math::Vec3 center = Math::Add(position_, front_);
    Math::Vec3 up = up_;

    Math::Vec3 z = Math::Normalise(Math::Subtract(position_, center));
    Math::Vec3 x = Math::Normalise(Math::Cross(up, z));
    Math::Vec3 y = Math::Cross(z, x);

    Math::Mat4 viewMatrix;

    viewMatrix.data[0] = x.x;
    viewMatrix.data[1] = y.x;
    viewMatrix.data[2] = -z.x;
    viewMatrix.data[3] = 0.0f;

    viewMatrix.data[4] = x.y;
    viewMatrix.data[5] = y.y;
    viewMatrix.data[6] = -z.y;
    viewMatrix.data[7] = 0.0f;

    viewMatrix.data[8] = x.z;
    viewMatrix.data[9] = y.z;
    viewMatrix.data[10] = -z.z;
    viewMatrix.data[11] = 0.0f;

    viewMatrix.data[12] = -Math::Dot(x, position_);
    viewMatrix.data[13] = -Math::Dot(y, position_);
    viewMatrix.data[14] = Math::Dot(z, position_);
    viewMatrix.data[15] = 1.0f;

    return viewMatrix;
}

void Camera::processKeyboard(int direction, float deltaTime) {
    float velocity = movementSpeed_ * deltaTime;
    if (direction == GLFW_KEY_W)
        position_ = Math::Add(position_, Math::Multiply(front_, velocity));
    if (direction == GLFW_KEY_S)
        position_ = Math::Subtract(position_, Math::Multiply(front_, velocity));
    if (direction == GLFW_KEY_A)
        position_ = Math::Subtract(position_, Math::Multiply(right_, velocity));
    if (direction == GLFW_KEY_D)
        position_ = Math::Add(position_, Math::Multiply(right_, velocity));

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset)
{

}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= mouseSensitivity_;
    yoffset *= mouseSensitivity_;

    yaw_ += xoffset;
    pitch_ += yoffset;

    if (constrainPitch) {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    Math::Vec3 front = Math::Vec3{ 0.0f,0.0f,0.0f }; //init
    front.x = cos(Math::ToRadians(yaw_)) * cos(Math::ToRadians(pitch_));
    front.y = sin(Math::ToRadians(pitch_));
    front.z = sin(Math::ToRadians(yaw_)) * cos(Math::ToRadians(pitch_));
    front_ = Math::Normalise(front);
    right_ = Math::Normalise(Math::Cross(front_, worldUp_));
    up_ = Math::Normalise(Math::Cross(right_, front_));
}