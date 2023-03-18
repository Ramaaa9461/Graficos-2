//#pragma once
//
//#include "Entity2d.h"
//#include "CollisionManager.h"
//#include "Tile.h"
//
//#include "glm/glm.hpp"
//
//class TileMap
//{
//
//private:
//	std::vector<Tile*> tilePallet;
//	Tile** _tileMapGrid;
//
//	 unsigned int _width;
//	 unsigned int _height;
//
//	float _tileWidth = 64;
//	float _tileHeight= 64;
//
//	int _initPositionX;
//	int _initPositionY;
//	
//	int _framesCountX; 
//	int _framesCountY;
//	
//
//	float convertedPosX;
//	float convertedPosY;
//
//	std::string _imageName;
//
//	glm::vec3 normal;
//	float depth;
//
//
//public:
//	DllExport TileMap(std::string imageName, int initPositionX, int initPositionY, int framesCountX, int framesCountY);
//	DllExport ~TileMap();
//
//	DllExport const Tile& getTile(unsigned int uiId);
//	DllExport void setTile(int id, bool isWalkeable, float cellsToMoveInX, float initPcellsToMoveInYosY);
//	DllExport void setMapTileId(unsigned int uiCol, unsigned int uiRow, unsigned int uiId);
//
//	DllExport void setDimensions(const int tilesAmountX, const int tileAmountY);
//	DllExport void setTileDimensions(float tileWidth, float tileHeight);
//
//	DllExport void draw();
//
//	DllExport void checkCollision(Entity2d& object);
//};
//
