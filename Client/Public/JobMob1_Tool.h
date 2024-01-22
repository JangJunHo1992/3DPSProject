#pragma once

#include "JobMob1.h"

BEGIN(Client)

class CJobMob1_Tool final : public CJobMob1
{
private:
	CJobMob1_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob1_Tool(const CJobMob1_Tool& rhs);
	virtual ~CJobMob1_Tool() = default;

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
	/* ������ü�� �����Ѵ�. */
	static CJobMob1_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CJobMob1_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END