#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CModel;
class CNavigation;
END

BEGIN(Client)

class CMap3 abstract : public CGameObject
{
protected:
	CMap3(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMap3(const CMap3& rhs);
	virtual ~CMap3() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual void Write_Json(json& Out_Json) override;

protected:
	CShader* m_pShaderCom = { nullptr };
	CModel* m_pModelCom = { nullptr };
	CNavigation* m_pNavigationCom = { nullptr };

protected:
	virtual HRESULT Ready_Components() PURE;
	HRESULT Ready_Components_Origin(LEVEL eLEVEL);
	HRESULT Bind_ShaderResources();


public:
	///* 원형객체를 생성한다. */
	//static CMap* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	///* 사본객체를 생성한다. */
	//virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END

