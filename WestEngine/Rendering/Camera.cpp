#include "Camera.h"

namespace WestEngine
{
    Camera::Camera(glm::vec3 position, glm::vec3 up ,
        float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        oldPos = Input::GeMouseRaw();
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    void Camera::Update(const bool constrainPitch)
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
            Pitch += dir.y * Time::deltaTime * MouseSensitivity;
            Yaw -= dir.x * Time::deltaTime * MouseSensitivity;
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

    void Camera::ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    void Camera::updateCameraVectors()
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
}