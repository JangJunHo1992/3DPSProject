#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CVIBuffer_Dynamic_Terrain_Origin;

END

BEGIN(Client)

class CTerrain abstract : public CGameObject
{
public:
	enum TEXTURE { TYPE_DIFFUSE, TYPE_MASK, TYPE_BRUSH, TYPE_END };
	
protected:
	CTerrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTerrain(const CTerrain& rhs);
	virtual ~CTerrain() = default;

public:
	virtual HRESULT Initialize_Prototype(_bool bIsPlane = false);
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	
	virtual void Write_Json(json& Out_Json) override;

protected:
	CShader*							m_pShaderCom = { nullptr };
	CTexture*							m_pTextureCom[TYPE_END] = { nullptr };
	CVIBuffer_Dynamic_Terrain_Origin*	m_pVIBufferCom = { nullptr };


	_bool								m_bIsPlane = false;

	

protected:
	virtual HRESULT Ready_Components() = 0;
	HRESULT Ready_Components_Origin(LEVEL eLEVEL);
	virtual HRESULT Bind_ShaderResources() = 0;
	HRESULT Bind_ShaderResources_Origin();


//public:
//	/* 원형객체를 생성한다. */
//	static CTerrain* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
//
//	/* 사본객체를 생성한다. */
//	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

	//// CGameObject을(를) 통해 상속됨
	//virtual CGameObject* Clone(void* pArg) override;
};

END