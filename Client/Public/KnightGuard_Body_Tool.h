#pragma once

#include "KnightGuard_Body.h"

BEGIN(Client)

class CKnightGuard_Body_Tool final : public CKnightGuard_Body
{
private:
	CKnightGuard_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKnightGuard_Body_Tool(const CKnightGuard_Body_Tool& rhs);
	virtual ~CKnightGuard_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CKnightGuard_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END