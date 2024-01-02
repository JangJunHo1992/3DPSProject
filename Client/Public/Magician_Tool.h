#pragma once

#include "Magician.h"

BEGIN(Client)

class CMagician_Tool final : public CMagician
{
private:
	CMagician_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Tool(const CMagician_Tool& rhs);
	virtual ~CMagician_Tool() = default;

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
	static CMagician_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CMagician_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END