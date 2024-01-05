#pragma once

#include "Raider_Sword_01.h"

BEGIN(Client)

class CRaider_Sword_01_Tool final : public CRaider_Sword_01
{
protected:
	CRaider_Sword_01_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Sword_01_Tool(const CRaider_Sword_01_Tool& rhs);
	virtual ~CRaider_Sword_01_Tool() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CRaider_Sword_01_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END