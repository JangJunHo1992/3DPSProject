#pragma once
#include "Terrain.h"


BEGIN(Client)

class CTerrain_MapTool final : public CTerrain
{

protected:
	CTerrain_MapTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTerrain_MapTool(const CTerrain_MapTool& rhs);
	virtual ~CTerrain_MapTool() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* 원형객체를 생성한다. */
	static CTerrain_MapTool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;
};

END