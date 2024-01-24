#pragma once

#include "Map3.h"

BEGIN(Client)

class CMap3_GamePlay final : public CMap3
{
private:
	CMap3_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMap3_GamePlay(const CMap3_GamePlay& rhs);
	virtual ~CMap3_GamePlay() = default;

private:
	HRESULT Ready_Components();


public:
	/* 원형객체를 생성한다. */
	static CMap3_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CMap3_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;
};

END