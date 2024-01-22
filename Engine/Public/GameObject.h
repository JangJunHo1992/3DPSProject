#pragma once

#include "Base.h"

BEGIN(Engine)
class CGameInstance;
class CTransform;

class ENGINE_DLL CGameObject abstract : public CBase
{
public:
	typedef struct tagGameObjectDesc
	{
		tagGameObjectDesc() {}
		tagGameObjectDesc(_float fSpeed, _float fRotation)
			: fSpeedPerSec(fSpeed), fRotationPerSec(fRotation) {}

		_float	fSpeedPerSec = 0.f;
		_float	fRotationPerSec = 0.f;
		_uint   iLevelIndex = -1;

	}GAMEOBJECT_DESC;
protected:
	CGameObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Tick(_float fTimeDelta);
	virtual void Tick(_float fTimeDelta);
	virtual void Late_Tick(_float fTimeDelta);
	virtual HRESULT Render();

public:
	class CComponent* Find_Component(const wstring& strComTag);

public:
	void Set_Position(const _float3& vState);
	void Test_ResetPos();
	void Set_WorldMatrix(_float4x4 matrix);
	void Invaildate_Components();

public:
	CTransform* Get_TransformComp() { return m_pTransformCom; }
public:
	virtual _bool Pick(_float3* out) { return false; }

public:
	void Set_isdead(_bool _bisdead) { m_bisdead = _bisdead; }
	_bool Get_isdead() { return m_bisdead; }
public:
	virtual void Write_Json(json& Out_Json) override;
	virtual void Load_FromJson(const json& In_Json) override;

protected:
	ID3D11Device*				m_pDevice = { nullptr };
	ID3D11DeviceContext*		m_pContext = { nullptr };

protected:
	CGameInstance*		m_pGameInstance = { nullptr };
	CTransform*			m_pTransformCom = { nullptr };
protected:
	map<const wstring, class CComponent*>	m_Components;
protected:
	_bool						m_isCloned = { false };
	_bool						m_bisdead = false;
protected:
	string						m_sName = "";
	string						m_sLayerTag = "";
	_uint						m_iCurrentLevelIndex = -1;

protected:
	HRESULT	Add_Component(_uint iLevelIndex, const wstring& strPrototypeTag,
							const wstring& strComTag, _Inout_ CComponent** ppOut, void* pArg = nullptr);
	
public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END