#pragma once

BEGIN(Client)

class IPick
{
public:
	virtual ~IPick() {};

public:
	virtual void pick() = 0;
};

END