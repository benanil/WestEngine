#ifndef CAMERA_H
#define CAMERA_H

#include <glad.h>
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
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;
    
    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class Camera
    {
    private:
        POINT oldPos;
    public:
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // euler Angles
        float Yaw;
        float Pitch;
        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;
    
        // constructor with vectors
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
        {
            oldPos = Input::GeMouseRaw();
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }
    
        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix() const
        {
            return glm::lookAt(Position, Position + Front, Up);
        }

        glm::mat4 GetProjectionMatrix() const
        {
            return glm::perspective(glm::radians(90.0f), (float)Engine::WindowWidth / (float)Engine::WindowHeight, 0.1f, 5000.0f);
        }
    
        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void Update(const bool constrainPitch = true)
        {
            if (!Input::GetMouseButtonPress(GLFW_MOUSE_BUTTON_2)) return;

            float velocity = MovementSpeed * Time::deltaTime;
            if (Input::GetKey(GLFW_KEY_LEFT_SHIFT)) velocity *= 4;

            if (Input::GetKey(GLFW_KEY_W)) Position += Front * velocity;
            if (Input::GetKey(GLFW_KEY_S)) Position -= Front * velocity;
            if (Input::GetKey(GLFW_KEY_A)) Position -= Right * velocity;
            if (Input::GetKey(GLFW_KEY_D)) Position += Right * velocity;
            if (Input::GetKey(GLFW_KEY_Q)) Position -= Up * velocity;
            if (Input::GetKey(GLFW_KEY_E)) Position += Up * velocity;
        
            POINT mousePos = Input::GeMouseRaw();
            POINT dir;
            dir.x = oldPos.x - mousePos.x;
            dir.y = oldPos.y - mousePos.y;

            if (dir.x + dir.y < 200)
            {
                Pitch += dir.y * Time::deltaTime * SPEED;
                Yaw -= dir.x * Time::deltaTime * SPEED;
            }
    
            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch)
            {
                if (Pitch > 89.0f)  Pitch = 89.0f;
                if (Pitch < -89.0f) Pitch = -89.0f;
            }
    
            Input::InfiniteMouse();
            oldPos = Input::GeMouseRaw();
            // update Front, Right and Up Vectors using the updated Euler angles
            updateCameraVectors();
        }
    
        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float yoffset)
        {
            Zoom -= (float)yoffset;
            if (Zoom < 1.0f)
                Zoom = 1.0f;
            if (Zoom > 45.0f)
                Zoom = 45.0f;
        }
    
    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors()
        {
            // calculate the new Front vector
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            // also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = glm::normalize(glm::cross(Right, Front));
        }
    };
}
#endif