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
	/* ������ü�� �����Ѵ�. */
	static CTerrain_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

};

END