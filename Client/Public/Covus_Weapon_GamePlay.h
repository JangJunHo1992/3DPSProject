#pragma once

#include "Covus_Weapon.h"

BEGIN(Client)

class CCovus_Weapon_GamePlay final : public CCovus_Weapon
{
protected:
	CCovus_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus_Weapon_GamePlay(const CCovus_Weapon_GamePlay& rhs);
	virtual ~CCovus_Weapon_GamePlay() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CCovus_Weapon_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END