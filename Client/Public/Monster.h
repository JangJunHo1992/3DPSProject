#pragma once

#include "Client_Defines.h"
//#include "GameObject.h"
#include "Character.h"


BEGIN(Engine)
class CShader;
class CModel;
class CCollider;
END

BEGIN(Client)

class CMonster abstract : public CCharacter
{
protected:
	CMonster(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMonster(const CMonster& rhs);
	virtual ~CMonster() = default;

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
	CShader*		m_pShaderCom = { nullptr };
	//CModel*			m_pModelCom = { nullptr };
	CCollider*		m_pColliderCom = { nullptr };

	

protected:
	virtual HRESULT Ready_Components() PURE;
	HRESULT Ready_Components_Origin(LEVEL eLevel);
	HRESULT Bind_ShaderResources();


public:
	virtual void Free() override;
};

END