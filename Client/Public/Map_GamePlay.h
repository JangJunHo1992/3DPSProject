#pragma once

#include "Map.h"

BEGIN(Client)

class CMap_GamePlay final : public CMap
{
private:
	CMap_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMap_GamePlay(const CMap_GamePlay& rhs);
	virtual ~CMap_GamePlay() = default;

private:
	HRESULT Ready_Components();


public:
	/* ������ü�� �����Ѵ�. */
	static CMap_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CMap_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;
};

END