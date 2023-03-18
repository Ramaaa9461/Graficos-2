#pragma once

#include "DDLExport.h"

struct UVCoords 
{
	float u, v;
};


class Frame
{


public:

	DllExport Frame();
	DllExport ~Frame();

	UVCoords uvCoords[4];
};

