#pragma once

#include "King.h"

BEGIN(Client)

class CKing_Tool final : public CKing
{
private:
	CKing_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKing_Tool(const CKing_Tool& rhs);
	virtual ~CKing_Tool() = default;

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
	/* ������ü�� �����Ѵ�. */
	static CKing_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CKing_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END