#include "Entity.h"

#include <glm\gtc\matrix_transform.hpp>


int Entity::instanceCounter = 0;

DllExport Entity::Entity(int initPositionX, int initPositionY, int initPositionZ)
{
	translation = glm::vec3(initPositionX, initPositionY, initPositionZ);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	id = instanceCounter;
	instanceCounter++;
	
	UpdateTRSMat();
}

DllExport Entity::~Entity()
{

}

DllExport void Entity::setPosition(glm::vec3 newPosition)
{
	translation = newPosition;
	UpdateTRSMat();
}

DllExport void Entity::setRotation(glm::vec3 newRotation)
{
	rotation = newRotation;
	UpdateTRSMat();
}

DllExport void Entity::setScale(glm::vec3 newScale)
{
	scale = newScale;
	UpdateTRSMat();
}

DllExport glm::vec3 Entity::getPosition()
{
	return translation;
}

DllExport glm::vec3 Entity::getRotation()
{
	return rotation;
}

DllExport glm::vec3 Entity::getScale()
{
	return scale;
}

DllExport void Entity::UpdateTRSMat()
{

	glm::mat4 tras = glm::translate(glm::mat4(1.0f), translation);

	glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 sca = glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 rot = rotX * rotY * rotZ;
	TRS = tras * rot * sca;
}



DllExport void Entity::addPosition(glm::vec3 positionToAdd)
{
	translation += positionToAdd;
	UpdateTRSMat();
}

DllExport void Entity::setPositionX(float posX)
{
	translation.x = posX;
	UpdateTRSMat();
}

DllExport void Entity::setPositionY(float posY)
{
	translation.y = posY;
	UpdateTRSMat();
}

DllExport void Entity::setPositionZ(float posZ)
{
	translation.z = posZ;
	UpdateTRSMat();
}

DllExport float Entity::getPositionX()
{
	return translation.x;
}

DllExport float Entity::getPositionY()
{
	return translation.y;
}

DllExport float Entity::getPositionZ()
{
	return translation.z;
}


DllExport void Entity::setScaleX(float scalX)
{
	scale.x = scalX;
	UpdateTRSMat();
}
DllExport void Entity::setScaleY(float scalY)
{
	scale.y = scalY;
	UpdateTRSMat();
}

DllExport void Entity::setScaleZ(float scalZ)
{
	 scale.z = scalZ;
}
	  
DllExport float Entity::getScaleX()
{
	return scale.x;
}

DllExport float Entity::getScaleY()
{
	return scale.y;
}

float Entity::getScaleZ()
{
	return scale.z;
}

void Entity::setRotationX(float rotX)
{
	rotation.x = rotX;
}

void Entity::setRotationY(float rotY)
{
	rotation.y = rotY;
}

DllExport void Entity::setRotationZ(float rotZ)
{
	rotation.z = rotZ;
	UpdateTRSMat();
}

float Entity::getRotationX()
{
	return rotation.x;
}

float Entity::getRotationY()
{
	return rotation.y;
}

DllExport float Entity::getRotationZ()
{
	return rotation.z;
}