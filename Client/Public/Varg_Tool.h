#pragma once

#include "Varg.h"

BEGIN(Client)

class CVarg_Tool final : public CVarg
{
private:
	CVarg_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVarg_Tool(const CVarg_Tool& rhs);
	virtual ~CVarg_Tool() = default;

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
	static CVarg_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CVarg_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END