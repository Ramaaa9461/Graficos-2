#pragma once

#include "Entity2d.h"
#include <vector>

class Sprite : public Entity2d
{


private:
	TextureImporter* textura;



	int width, height;
	unsigned int indices[6];

	DllExport void setVertices();
	DllExport void setVerticesSpriteSheet();
	DllExport void setIndixs();
	DllExport void calculateVertices();

protected:

	float positions[16];

public:

	DllExport Sprite(std::string imageName, int initPositionX, int initPositionY);
	DllExport Sprite();
	DllExport ~Sprite();

	DllExport void setTexture(std::string imageName);
	
	DllExport void drawTexture();


};

