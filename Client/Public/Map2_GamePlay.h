#pragma once

#include "Map2.h"

BEGIN(Client)

class CMap2_GamePlay final : public CMap2
{
private:
	CMap2_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMap2_GamePlay(const CMap2_GamePlay& rhs);
	virtual ~CMap2_GamePlay() = default;

private:
	HRESULT Ready_Components();


public:
	/* ������ü�� �����Ѵ�. */
	static CMap2_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CMap2_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;
};

END