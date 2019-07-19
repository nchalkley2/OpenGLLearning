#pragma once
#include "delegate.h"

class Engine
{
public:
	static int Go();

	// Delegates
	static Delegate<> onOpenGLInit;
	static Delegate<> onOpenGLDraw;
	static Delegate<> onOpenGLTerminate;
};