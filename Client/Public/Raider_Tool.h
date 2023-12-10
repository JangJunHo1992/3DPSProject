#pragma once

#include "Raider.h"

BEGIN(Client)

class CRaider_Tool final: public CRaider
{
private:
	CRaider_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Tool(const CRaider_Tool& rhs);
	virtual ~CRaider_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CRaider_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CRaider_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance*	m_pGameInstance = nullptr;


};

END