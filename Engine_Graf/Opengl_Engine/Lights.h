#pragma once

#include "Shader.h"

/// <summary>
/// esta va a ser la clase padre de las luces
/// </summary>
class Lights
{
private:


public:

	DllExport virtual void  setUniforms(Shader* shader) = 0;
};


