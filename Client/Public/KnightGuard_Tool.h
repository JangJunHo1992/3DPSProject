#pragma once

#include "KnightGuard.h"

BEGIN(Client)

class CKnightGuard_Tool final : public CKnightGuard
{
private:
	CKnightGuard_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKnightGuard_Tool(const CKnightGuard_Tool& rhs);
	virtual ~CKnightGuard_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CKnightGuard_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CKnightGuard_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END