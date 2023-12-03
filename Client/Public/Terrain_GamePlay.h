#pragma once
#include "Terrain.h"


BEGIN(Client)

class CTerrain_GamePlay final : public CTerrain
{
protected:
	CTerrain_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTerrain_GamePlay(const CTerrain_GamePlay& rhs);
	virtual ~CTerrain_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* 원형객체를 생성한다. */
	static CTerrain_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

};

END