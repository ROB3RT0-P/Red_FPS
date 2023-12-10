/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#pragma once

#include "red_math.h"

class Camera {
public:
    Camera(Vec3 position, Vec3 up, float yaw, float pitch);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    Mat4 GetViewMatrix() const;
    void ProcessKeyboard(int direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    float GetZoom() const { return zoom; }
    Vec3 GetPosition() const { return position; }
    Vec3 GetFront() const { return front; }

private:
    void UpdateCameraVectors();

    Vec3 position;
    Vec3 up;
    Vec3 front;
    Vec3 right;
    Vec3 worldUp;

    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
};