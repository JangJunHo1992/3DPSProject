#pragma once

#include "Raider.h"

BEGIN(Client)

class CRaider_GamePlay final : public CRaider
{
private:
	CRaider_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_GamePlay(const CRaider_GamePlay& rhs);
	virtual ~CRaider_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CRaider_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CRaider_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END