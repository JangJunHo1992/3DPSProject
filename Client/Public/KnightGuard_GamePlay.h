#pragma once

#include "KnightGuard.h"

BEGIN(Client)

class CKnightGuard_GamePlay final : public CKnightGuard
{
private:
	CKnightGuard_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKnightGuard_GamePlay(const CKnightGuard_GamePlay& rhs);
	virtual ~CKnightGuard_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CKnightGuard_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CKnightGuard_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END