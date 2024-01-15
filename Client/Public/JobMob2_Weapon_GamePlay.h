#pragma once

#include "JobMob2_Weapon.h"

BEGIN(Client)

class CJobMob2_Weapon_GamePlay final : public CJobMob2_Weapon
{
protected:
	CJobMob2_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob2_Weapon_GamePlay(const CJobMob2_Weapon_GamePlay& rhs);
	virtual ~CJobMob2_Weapon_GamePlay() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CJobMob2_Weapon_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END