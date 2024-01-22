#pragma once

#include "JobMob2.h"

BEGIN(Client)

class CJobMob2_Tool final : public CJobMob2
{
private:
	CJobMob2_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob2_Tool(const CJobMob2_Tool& rhs);
	virtual ~CJobMob2_Tool() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	virtual HRESULT Ready_Components() override;

public:
	virtual _bool Pick(_float3* out) override;



public:
	/* 원형객체를 생성한다. */
	static CJobMob2_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CJobMob2_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END