#include "GameObject.h"
#include "GameInstance.h"
#include "Transform.h"


_bool		CGameObject::				m_bStartScene		=false;
_bool		CGameObject::				m_bStartScene2		=false;
_bool		CGameObject::				m_bCutSceneDead		=false;
_bool		CGameObject::				m_bCutSceneDead2	=false;	
_bool		CGameObject::				m_bLoadingComplete	=false;

CGameObject::CGameObject(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: m_pDevice(pDevice)
	, m_pContext(pContext)
	, m_pGameInstance(CGameInstance::GetInstance())
	, m_isCloned(false)
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

CGameObject::CGameObject(const CGameObject & rhs)
	: m_pDevice(rhs.m_pDevice)
	, m_pContext(rhs.m_pContext)
	, m_pGameInstance(rhs.m_pGameInstance)
	, m_isCloned(true)
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext); 
}

HRESULT CGameObject::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CGameObject::Initialize(void* pArg)
{
	GAMEOBJECT_DESC		Desc = {  };

	if (nullptr != pArg)
	{
		Desc = *(GAMEOBJECT_DESC*)pArg;
		m_iCurrentLevelIndex = Desc.iLevelIndex;
	}


	m_pTransformCom = CTransform::Create(m_pDevice, m_pContext,Desc.fSpeedPerSec,Desc.fRotationPerSec);
	if (nullptr == m_pTransformCom)
		return E_FAIL;

	if (nullptr != Find_Component(g_pTransformTag))
		return E_FAIL;

	m_Components.emplace(g_pTransformTag, m_pTransformCom);

	return S_OK;
}

void CGameObject::Priority_Tick(_float fTimeDelta)
{
}

void CGameObject::Tick(_float fTimeDelta)
{
}

void CGameObject::Late_Tick(_float fTimeDelta)
{
}

HRESULT CGameObject::Render()
{
	return S_OK;
}

void CGameObject::Set_Position(const _float3& vState)
{
	m_pTransformCom->Set_Position(vState);
}

void CGameObject::Test_ResetPos()
{
	_float3 resetPos = { 0.f, 0.f, 0.f };
	m_pTransformCom->Set_Position(resetPos);
}

void CGameObject::Set_WorldMatrix(_float4x4 matrix)
{
	m_pTransformCom->Set_WorldMatrix(matrix);
}

void CGameObject::Invaildate_Components()
{
	for (auto& elem_List : m_Components)
	{
		elem_List.second->Initialize_Prototype();
	}
}

void CGameObject::Write_Json(json& Out_Json)
{
	
	for (auto& elem_List : m_Components)
	{
		elem_List.second->Write_Json(Out_Json["Component"]);
	}
}

void CGameObject::Load_FromJson(const json& In_Json)
{
	for (auto& elem_List : m_Components)
	{
		elem_List.second->Load_FromJson(In_Json["Component"]);
	}

	_float4x4 WorldMatrix;
	ZeroMemory(&WorldMatrix, sizeof(_float4x4));
	CJson_Utility::Load_JsonFloat4x4(In_Json["Component"]["Transform"], WorldMatrix);
}

HRESULT CGameObject::Add_Component(_uint iLevelIndex, const wstring& strPrototypeTag, const wstring& strComTag, CComponent** ppOut, void* pArg)
{
	if (nullptr != Find_Component(strComTag))
		return E_FAIL;

	CComponent* pComponent = m_pGameInstance->Clone_Component(iLevelIndex, strPrototypeTag, pArg);
	if (nullptr == pComponent)
		return E_FAIL;

	*ppOut = pComponent;
	//복사되서 생성된 컴포넌트를 다시 맵에다가 넣기 때문에 새로운 참조가 생긴거라서 Add_Ref해줘야 함 ! 
	m_Components.emplace(strComTag, pComponent);

	Safe_AddRef(pComponent);

	return S_OK;
}

CComponent* CGameObject::Find_Component(const wstring& strComTag)
{
	auto	iter = m_Components.find(strComTag);

	if (iter == m_Components.end())
		return nullptr;

	return iter->second;
}

void CGameObject::Free()
{
	__super::Free();

	for (auto& Pair : m_Components)
		Safe_Release(Pair.second);

	m_Components.clear();

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}
