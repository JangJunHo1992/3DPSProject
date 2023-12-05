#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class IPick
{
public:
	virtual ~IPick() {};

public:
	virtual void pick() = 0;
};

END