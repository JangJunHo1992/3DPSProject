#pragma once

#include "Monster.h"

BEGIN(Client)

class CMonster_Tool final : public CMonster
{
private:
	CMonster_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMonster_Tool(const CMonster_Tool& rhs);
	virtual ~CMonster_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	virtual HRESULT Ready_Components() override;


public:
	/* ������ü�� �����Ѵ�. */
	static CMonster_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CMonster_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance*		m_pGameInstance = nullptr;


};

END