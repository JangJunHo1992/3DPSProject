#pragma once

#include "Component.h"
#include "Transform.h"
#include "VIBuffer_Terrain.h"

BEGIN(Engine)

class ENGINE_DLL CPicking : public CBase
{
	DECLARE_SINGLETON(CPicking)
private:
	CPicking();
	virtual ~CPicking() = default;

public:
	SimpleMath::Vector4 TerrainPicking(POINT pt, CTransform* trans, CVIBuffer_Terrain* buffer);
public:
	virtual void Free() override;
};

END