#pragma once

#include "Raider_Weapon.h"

BEGIN(Client)

class CRaider_Sword_02_Tool final : public CRaider_Weapon
{
protected:
	CRaider_Sword_02_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Sword_02_Tool(const CRaider_Sword_02_Tool& rhs);
	virtual ~CRaider_Sword_02_Tool() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CRaider_Sword_02_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END