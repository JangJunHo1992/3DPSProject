#pragma once

#include "Golem.h"

BEGIN(Client)

class CGolem_Tool final : public CGolem
{
private:
	CGolem_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGolem_Tool(const CGolem_Tool& rhs);
	virtual ~CGolem_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CGolem_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGolem_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END