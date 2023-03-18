#ifndef ENTITY_H
#define ENTITY_H

#include "DDLExport.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

	class Entity
	{
	private:

		static int instanceCounter;
		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale;

	protected:

		int id;
		Renderer* renderer = Renderer::getRenderer();
		glm::mat4 TRS = glm::mat4(1);

	public:
		DllExport Entity(int initPositionX, int initPositionY);
		DllExport ~Entity();

		DllExport void setPosition(glm::vec3 newPosition);
		DllExport void setRotation(glm::vec3 newRotation);
		DllExport void setScale(glm::vec3 newScale);

		DllExport glm::vec3 getPosition();
		DllExport glm::vec3 getRotation();
		DllExport glm::vec3 getScale();

		DllExport void UpdateTRSMat();

		DllExport virtual void draw() = 0;

		DllExport void addPosition(glm::vec3 positionToAdd);
	
		DllExport void setPositionX(float posX);
		DllExport void setPositionY(float posY);

		DllExport float getPositionX();
		DllExport float getPositionY();

		DllExport void  setScaleX(float scalX);
		DllExport void  setScaleY(float scalY);
				 
		DllExport float getScaleX();
		DllExport float getScaleY();

		DllExport void  setRotationZ(float rotZ);
		DllExport float getRotationZ();
	};

#endif

