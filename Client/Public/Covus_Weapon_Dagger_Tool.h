#pragma once

#include "Covus_Weapon_Dagger.h"

BEGIN(Client)

class CCovus_Weapon_Dagger_Tool final : public CCovus_Weapon_Dagger
{
protected:
	CCovus_Weapon_Dagger_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus_Weapon_Dagger_Tool(const CCovus_Weapon_Dagger_Tool& rhs);
	virtual ~CCovus_Weapon_Dagger_Tool() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CCovus_Weapon_Dagger_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END
