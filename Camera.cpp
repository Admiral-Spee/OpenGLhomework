#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position  =  position;
	Position2 =  position;
	WorldUp   =  worldup;
	Forward   =  glm::normalize(target - position);
	Right     =  glm::normalize(glm::cross(Forward, WorldUp));
	Up        =  glm::normalize(glm::cross(Forward, Right));
	
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position   =  position;
	Position2  =  position;
	WorldUp    =  worldup;
	Pitch      =  pitch;
	Yaw        =  yaw;
	Forward.x  =  glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y  =  glm::sin(Pitch);
	Forward.z  =  glm::cos(Pitch) * glm::sin(Yaw);
	Right      =  glm::normalize(glm::cross(Forward, WorldUp));
	Up         =  glm::normalize(glm::cross(Forward, Right));
}

glm::mat4 Camera::GetViewMatrix() 
{
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::cos(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::sin(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));

}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) 
{
	Pitch += deltaY * SenseX;
	Yaw += deltaX * SenseY;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPos()
{
	
	Position += (Forward * speedZ * 0.1f) + (glm::normalize(glm::cross(Forward, WorldUp)) * speedX * 0.1f);
	

}