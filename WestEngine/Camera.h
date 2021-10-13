#ifndef CAMERA_H
#define CAMERA_H

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Common.h"
#include <vector>
#include "Input.h"
#include <iostream>

namespace WestEngine
{
    typedef int Camera_Movement;
    
    // Default camera values
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 9;
    const float ZOOM = 45.0f;
    
    class Camera
    {
    public:
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // euler Angles
        float Pitch ,Yaw;
        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;
        float Fov;
    
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),  float yaw = YAW, float pitch = PITCH, float Fov = 90) 
              : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
        {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }
    
        glm::mat4 GetViewMatrix() const {
            return glm::lookAt(Position, Position + Front, Up);
        }
    
        glm::mat4 GetProjectionMatrix(const int& width, const int& height) const {
            return glm::perspective<float>(glm::radians(Fov), std::max(width, 1) / std::max(height,1), 0.1, 3000);
        }
    
        void ProcessKeyboard() 
        {
            const float velocity = MovementSpeed * Time::deltaTime;
            if (Input::GetKey(GLFW_KEY_W)) Position += Front * velocity;
            if (Input::GetKey(GLFW_KEY_A)) Position -= Right * velocity;
            if (Input::GetKey(GLFW_KEY_S)) Position -= Front * velocity;
            if (Input::GetKey(GLFW_KEY_D)) Position += Right * velocity;
        }
    
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
        {
            xoffset *= MouseSensitivity * Time::deltaTime;
            yoffset *= MouseSensitivity * Time::deltaTime;
    
            Yaw += xoffset;
            Pitch += yoffset;
    
            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch) {
                if (Pitch > 89.0f)  Pitch = 89.0f;
                if (Pitch < -89.0f) Pitch = -89.0f;
            }
    
            updateCameraVectors();
        }
    
        void ProcessMouseScroll(const float& yoffset)
        {
            Zoom -= yoffset;
            if (Zoom < 1.0f ) Zoom = 1.0f;
            if (Zoom > 45.0f) Zoom = 45.0f;
        }
    
    private:
        void updateCameraVectors()
        {
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = glm::normalize(glm::cross(Right, Front));
        }
    };
}
#endif