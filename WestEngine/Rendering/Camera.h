#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"
#include "Time.h"
#include "WestEngine.h"
#include "Input.h"

namespace WestEngine
{
    // Default camera values
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 50.5f;
    const float SENSITIVITY = 50.0f;
    const float ZOOM = 45.0f;
    
    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class Camera
    {
    private:
        POINT oldPos;
    public:
        // camera Attributes
        
        
        
        vec3 Position;
        Math::vec3 Front;
        Math::vec3 Up;
        Math::vec3 Right;
        Math::vec3 WorldUp;
        // euler Angles
        float Yaw;
        float Pitch;
        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;
    
        // constructor with vectors
        Camera(Math::vec3 position = Math::vec3(0.0f, 0.0f, 0.0f), 
               Math::vec3 up = Math::vec3(0.0f, 1.0f, 0.0f),
               float yaw = YAW, float pitch = PITCH);
    
        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        Math::mat4 GetViewMatrix() const
        {
            return Math::lookAt(Position, Position + Front, Up);
        }

        Math::mat4 GetProjectionMatrix() const
        {
            return Math::perspective(Math::radians(90.0f), (float)Engine::WindowWidth / (float)Engine::WindowHeight, 0.1f, 5000.0f);
        }
    
        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void Update(const bool constrainPitch = true);
    
        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float yoffset);
    
    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors();
    };
}
#endif