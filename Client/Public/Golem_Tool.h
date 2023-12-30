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
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual void Set_Hitted() override;

private:
	virtual HRESULT Ready_Components() override;

public:
	virtual _bool Pick(_float3* out) override;



public:
	/* 원형객체를 생성한다. */
	static CGolem_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGolem_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END