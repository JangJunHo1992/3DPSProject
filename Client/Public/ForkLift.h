#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CModel;
END

BEGIN(Client)

class CForkLift abstract : public CGameObject
{
protected:
	CForkLift(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CForkLift(const CForkLift& rhs);
	virtual ~CForkLift() = default;

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

	
protected:
	virtual HRESULT Ready_Components() PURE;
	HRESULT Ready_Components_Origin();
	HRESULT Bind_ShaderResources();


public:
	///* ������ü�� �����Ѵ�. */
	//static CForkLift* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	///* �纻��ü�� �����Ѵ�. */
	//virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END