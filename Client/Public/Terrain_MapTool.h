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
	/* ������ü�� �����Ѵ�. */
	static CTerrain_MapTool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;
};

END