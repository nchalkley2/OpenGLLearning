#pragma once
#include "delegate.h"

class Engine
{
public:
	static int Go();

	// Delegates
	static Delegate<> OpenGLInit;
	static Delegate<> OpenGLDraw;
	static Delegate<> OpenGLTerminate;
};