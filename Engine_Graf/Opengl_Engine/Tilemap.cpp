//#include "Tilemap.h"
//
//TileMap::TileMap(std::string imageName, int initPositionX, int initPositionY, int framesCountX, int framesCountY)
//{
//	_imageName = imageName;
//	_initPositionX = initPositionX;
//	_initPositionY = initPositionY;
//
//	_framesCountX = framesCountX;
//	_framesCountY = framesCountY;
//
// }
//
//TileMap::~TileMap()
//{
//	for (int i = 0; i < tilePallet.size(); i++)
//	{
//		delete &tilePallet[i];
//	}
//
//	delete[] _tileMapGrid;
//
//}
//
//const Tile& TileMap::getTile(unsigned int uiId)
//{
//	Tile* NoTile = nullptr;
//
//	for (int i = 0; i < tilePallet.size(); i++)
//	{
//		if (uiId == tilePallet[i]->getId()) 
//		{
//			return *tilePallet[i];
//		}
//	}
//
//	return *NoTile;
//}
//
//void TileMap::setTile(int id, bool isWalkeable, float cellsToMoveInX, float cellsToMoveInY)
//{
//	Tile* newTile = new Tile();
//	newTile->configureTile(id, _imageName, isWalkeable);
//
//	newTile->getTextureSize(_tileWidth, _tileHeight);
//	_tileWidth /= _framesCountX;
//	_tileHeight /= _framesCountY;
//
//	newTile->cutTexture(cellsToMoveInX * _tileWidth, cellsToMoveInY * _tileHeight, _framesCountX, _framesCountY);
//
//	tilePallet.push_back(newTile);
//}
//
//void TileMap::setMapTileId(unsigned int uiCol, unsigned int uiRow, unsigned int uiId)
//{
//	_tileMapGrid[uiCol][uiRow] = getTile(uiId);
//}
//
//void TileMap::setTileDimensions(float tileWidth, float tileHeight)
//{
//	_tileWidth = tileWidth;
//	_tileHeight = tileHeight;
//}
//
//void TileMap::setDimensions(const int tilesAmountX, const int tileAmountY)
//{
//	_width = tilesAmountX;
//	_height = tileAmountY;
//
//	//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
//
//	_tileMapGrid = new Tile* [tileAmountY];
//
//	for (int i = 0; i < tileAmountY; i++)
//	{
//		_tileMapGrid[i] = new Tile[tilesAmountX];
//	}
//
//} //https://es.stackoverflow.com/questions/51771/crear-una-matriz-de-objetos-din%C3%A1mica-en-c
//
//void TileMap::draw()
//{
//	float mapWidth = _width * _tileWidth;
//	float mapHeight = _height * _tileHeight;
//
//	for (int i = 0; i < _height; i++)
//	{
//		for (int j = 0; j < _width; j++)
//		{
//			//_tileMapGrid[i][j].setPosX( _initPositionX +_tileWidth * i);
//			//_tileMapGrid[i][j].setPosY(_initPositionY +_tileHeight * j);
//			
//			_tileMapGrid[i][j].setPosX(mapWidth +  (_tileWidth * i));
//			_tileMapGrid[i][j].setPosY(mapHeight - (_tileHeight * j));
//			_tileMapGrid[i][j].draw();
//		}
//	}
//
//}
//
//void TileMap::checkCollision(Entity2d& object)
//{
//	//convertedPosX = object.getPositionX() + (_width / 2) * _tileWidth;
//	//convertedPosY = object.getPositionY() - (_height / 2) * _tileHeight;
//
//	//int left_tile = convertedPosX / _tileWidth;
//	//int right_tile = (convertedPosX + object.getScaleX()) / _tileWidth;
//
//	//int top_tile = (convertedPosY / _tileHeight) * -1;
//	//int bottom_tile = ((convertedPosY - object.getScaleY()) / _tileHeight) * -1; // Se resta porque el eje Y crece hacia arriba
//
//	//if (left_tile < 0)
//	//	left_tile = 0;
//
//	//if (right_tile >= _width)
//	//	right_tile = _width - 1;
//
//	//if (top_tile < 0)
//	//	top_tile = 0;
//
//	//if (bottom_tile >= _height)
//	//	bottom_tile = _height - 1;
//
//	///*
//	//cout << "converted X: " << convertedPosX << endl;
//	//cout << "converted Y: " << convertedPosY << endl;
//
//	//cout << "left: " <<left_tile << endl;
//	//cout << "right: "<<right_tile << endl;
//	//cout << "top: " << top_tile << endl;
//	//cout << "bottom: "<<bottom_tile << endl;
//	//*/
//
//	////for (int i = left_tile; i <= right_tile; i++) {
//
//	////	for (int j = top_tile; j <= bottom_tile; j++) {
//
//	////		for (int k = 0; k < _tileMapGrid.size(); k++) {
//	////			//cout << "caminable " << "[" << k << "]" << "[" << j << "]" << "[" << i << "] : "<< _tileMapGrid[k][j][i].isWalkable() << endl; // true == 1  ; false == 0
//	////			//cout << true << endl;
//	////			if (!_tileMapGrid[k][j][i].isWalkable())
//	////			{
//	////			
//	////				if (CollisionManager::IntersectPolygons(_tileMapGrid[k][j][i].getVertices(), 4, object.getVertices(), 4, normal, depth))
//	////				{
//	////					
//	////				}
//	////				//if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionHorizontalRight ||
//	////				//	_tileMapGrid[k][j][i].checkCollision(object) == CollisionHorizontalLeft)
//	////				//{
//	////				//object.returnToPreviusPosH();
//	////				//}
//
//	////				//if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionVerticalUp)
//	////				//{
//	////				//object.returnToPreviusPos(object.posX(), object.previusPosY() + 0.2);
//	////				//}
//
//	////				//else if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionVerticalDown)
//	////				//{
//	////				//object.returnToPreviusPos(object.posX(), object.previusPosY() - 0.2);
//	////				//}
//	////					
//	////			}
//	////		}
//	////	}
//	////}
//}
