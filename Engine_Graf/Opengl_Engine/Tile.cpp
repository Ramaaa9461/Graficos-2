//#include "Tile.h"
//
//Tile::Tile() : _id(0), _walkable(false)
//{
//
//}
//
//Tile::~Tile()
//{
//}
//
//void Tile::setPosX(float posX)
//{
//	setPositionX(posX);
//}
//
//void Tile::setPosY(float posY)
//{
//	setPositionY(posY);
//}
//
//bool Tile::isWalkable()
//{
//	return _walkable;
//}
//
//void Tile::setWalkable(bool Walkable)
//{
//	_walkable = Walkable;
//}
//
//unsigned int Tile::getId()
//{
//	return _id;
//}
//
//void Tile::configureTile(int id, std::string nameImage, bool isWalkable)
//{
//	setTexture(nameImage);
//	_id = id;
//	_walkable = isWalkable;
//}
//
//void Tile::cutTexture(float initPosX, float intPosY, int framesCountX, int framesCountY)
//{
//	float textureWidth = texture->GetWidth();
//	float textureHeigth = texture->GetHeight();
//	float frameWidth = textureWidth / framesCountX;
//	float frameHeigth = textureHeigth / framesCountY;
//
//	tileFrame.uvCoords[0].u = (initPosX / textureWidth);
//	tileFrame.uvCoords[0].v = (intPosY / textureHeigth);
//	//----------------------------------------------------------------
//	tileFrame.uvCoords[1].u = ((initPosX + frameWidth) / textureWidth);
//	tileFrame.uvCoords[1].v = (intPosY / textureHeigth);
//	//----------------------------------------------------------------
//	tileFrame.uvCoords[2].u = (initPosX / textureWidth);
//	tileFrame.uvCoords[2].v = ((intPosY + frameHeigth) / textureHeigth);
//	//----------------------------------------------------------------
//	tileFrame.uvCoords[3].u = ((initPosX + frameWidth) / textureWidth);
//	tileFrame.uvCoords[3].v = ((intPosY + frameHeigth) / textureHeigth);
//
//
//	positions[2] =  tileFrame.uvCoords[0].u;
//	positions[3] =  tileFrame.uvCoords[0].v;
//				    		  
//	positions[6] =  tileFrame.uvCoords[1].u;
//	positions[7] =  tileFrame.uvCoords[1].v;
//				    
//	positions[10] = tileFrame.uvCoords[3].u;
//	positions[11] = tileFrame.uvCoords[3].v;
//				    
//	positions[14] = tileFrame.uvCoords[2].u;
//	positions[15] = tileFrame.uvCoords[2].v;
//
//	vb->updateVertexBufferData(positions, 4 * 4 * sizeof(float));
//}
//
//void Tile::getTextureSize(float& width, float& height)
//{
//	width = texture->GetWidth();
//	height = texture->GetHeight();
//}
