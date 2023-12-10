/*******************************************
	Written by Robert Parry [RJP] - 2023
	Refer to red_main.cpp for the license
*******************************************/

#include "red_camera.h"

Camera::Camera(Vec3 position, Vec3 up, float yaw, float pitch)
    : front(Vec3(0.0f, 0.0f, -1.0f)), yaw(yaw), pitch(pitch), movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f) {
    this->position = position;
    this->up = up;
    worldUp = Vec3(0.0f, 1.0f, 0.0f);
    UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : front(Vec3(0.0f, 0.0f, -1.0f)), yaw(yaw), pitch(pitch), movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f) {
    position = Vec3(posX, posY, posZ);
    up = Vec3(upX, upY, upZ);
    worldUp = Vec3(0.0f, 1.0f, 0.0f);
    UpdateCameraVectors();
}

Mat4 Camera::GetViewMatrix() const {
    return Math::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(int direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction & 1) {
        position += front * velocity;
    }
    if (direction & 2) {
        position -= front * velocity;
    }
    if (direction & 4) {
        position -= right * velocity;
    }
    if (direction & 8) {
        position += right * velocity;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    if (zoom >= 1.0f && zoom <= 45.0f) {
        zoom -= yoffset;
    }
    if (zoom <= 1.0f) {
        zoom = 1.0f;
    }
    if (zoom >= 45.0f) {
        zoom = 45.0f;
    }
}

void Camera::UpdateCameraVectors() {
    Vec3 newFront;
    newFront.x = cos(Math::ToRadians(yaw)) * cos(Math::ToRadians(pitch));
    newFront.y = sin(Math::ToRadians(pitch));
    newFront.z = sin(Math::ToRadians(yaw)) * cos(Math::ToRadians(pitch));
    front = Math::Normalize(newFront);
    right = Math::Normalize(Math::Cross(front, worldUp));
    up = Math::Normalize(Math::Cross(right, front));
}
