#pragma once

#include "JobMob2_Weapon.h"

BEGIN(Client)

class CJobMob2_Weapon_Tool final : public CJobMob2_Weapon
{
protected:
	CJobMob2_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob2_Weapon_Tool(const CJobMob2_Weapon_Tool& rhs);
	virtual ~CJobMob2_Weapon_Tool() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CJobMob2_Weapon_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END