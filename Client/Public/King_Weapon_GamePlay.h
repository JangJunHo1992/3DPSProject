#pragma once

#include "King_Weapon.h"

BEGIN(Client)

class CKing_Weapon_GamePlay final : public CKing_Weapon
{
protected:
	CKing_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKing_Weapon_GamePlay(const CKing_Weapon_GamePlay& rhs);
	virtual ~CKing_Weapon_GamePlay() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CKing_Weapon_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END