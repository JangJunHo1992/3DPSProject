#pragma once

#include "Monster.h"

BEGIN(Client)

class CMonster_GamePlay final : public CMonster
{
private:
	CMonster_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMonster_GamePlay(const CMonster_GamePlay& rhs);
	virtual ~CMonster_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CMonster_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CMonster_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END