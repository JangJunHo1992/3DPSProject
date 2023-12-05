#pragma once
#include "base.h"

BEGIN(Engine)

class ENGINE_DLL IPickableObject
{
public:
	virtual void Picking() = 0;

};
END