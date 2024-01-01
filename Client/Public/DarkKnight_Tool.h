#pragma once

#include "DarkKnight.h"

BEGIN(Client)

class CDarkKnight_Tool final : public CDarkKnight
{
private:
	CDarkKnight_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CDarkKnight_Tool(const CDarkKnight_Tool& rhs);
	virtual ~CDarkKnight_Tool() = default;

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
	static CDarkKnight_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CDarkKnight_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END