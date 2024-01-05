#pragma once

#include "Varg_Weapon.h"

BEGIN(Client)

class CVarg_Weapon_Tool final : public CVarg_Weapon
{
protected:
	CVarg_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVarg_Weapon_Tool(const CVarg_Weapon_Tool& rhs);
	virtual ~CVarg_Weapon_Tool() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CVarg_Weapon_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END