#pragma once

#include "Raider_Body.h"

BEGIN(Client)

class CRaider_Body_Tool final : public CRaider_Body
{
private:
	CRaider_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Body_Tool(const CRaider_Body_Tool& rhs);
	virtual ~CRaider_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CRaider_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END