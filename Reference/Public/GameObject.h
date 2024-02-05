#pragma once

#include "Base.h"

BEGIN(Engine)
class CGameInstance;
class CTransform;
class CComponent;
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
	virtual HRESULT Render_Shadow() { return S_OK; }
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
	void Set_CheckAnimDead(_bool _bcheckAnimDead) { m_bcheckAnimDead = _bcheckAnimDead; }
	_bool Get_CheckAnimDead() { return m_bcheckAnimDead; }
	//start
	void Set_StartScene(_bool _bStartScene) { m_bStartScene = _bStartScene; }
	_bool Get_StartScene() { return m_bStartScene; }
	void Set_StartScene2(_bool _bStartScene2) { m_bStartScene2 = _bStartScene2; }
	_bool Get_StartScene2() { return m_bStartScene2; }
	//end
	void Set_CutSceneDead(_bool _bCutSceneDead) { m_bCutSceneDead = _bCutSceneDead; }
	_bool Get_CutSceneDead() { return m_bCutSceneDead; }
	void Set_CutSceneDead2(_bool _bCutSceneDead2) { m_bCutSceneDead2 = _bCutSceneDead2; }
	_bool Get_CutSceneDead2() { return m_bCutSceneDead2; }
	
	void	Set_HasBeenHit(_bool _bHasBeenHit) { m_bHasBeenHit = _bHasBeenHit; }
	_bool	Get_HasBeenHit() { return m_bHasBeenHit; }
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
	map<const wstring, CComponent*>	m_Components;
protected:
	_bool						m_isCloned = { false };
	_bool						m_bisdead = false;
	_bool						m_bcheckAnimDead = false;
	_bool						m_bCheckCard = false;
public:
	//Start
	static _bool				m_bStartScene ;
	static _bool				m_bStartScene2;
	//End
	static _bool				m_bCutSceneDead;
	static _bool				m_bCutSceneDead2;

	//static _bool				m_bLoadingComplete;

	_bool						m_bHasBeenHit = false;
protected:
	string						m_sName = "";
	string						m_sLayerTag = "";
	_uint						m_iCurrentLevelIndex = -1;
	_uint						m_iCheckHitTime = 0;
protected:
	HRESULT	Add_Component(_uint iLevelIndex, const wstring& strPrototypeTag,
							const wstring& strComTag, _Inout_ CComponent** ppOut, void* pArg = nullptr);
	
public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END