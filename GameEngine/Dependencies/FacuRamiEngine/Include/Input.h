#pragma once

#include "DDLExport.h"

static class Input
{

private:


protected:

	DllExport static bool IsKeyPressedImpl(int keycode) ;

public:

	DllExport inline static bool getKeyPressed(int keycode) { return IsKeyPressedImpl(keycode);  };
	

};

