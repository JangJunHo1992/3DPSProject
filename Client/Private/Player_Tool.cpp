#include "stdafx.h"
#include "..\Public\Player_Tool.h"

#include "GameInstance.h"


CPlayer_Tool::CPlayer_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CPlayer(pDevice, pContext)
{

}

CPlayer_Tool::CPlayer_Tool(const CPlayer_Tool& rhs)
	: CPlayer(rhs)
{
}

HRESULT CPlayer_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CPlayer_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CPlayer_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CPlayer_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CPlayer_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}


CPlayer_Tool* CPlayer_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CPlayer_Tool* pInstance = new CPlayer_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CPlayer_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CPlayer_Tool::Clone(void* pArg)
{
	CPlayer_Tool* pInstance = new CPlayer_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CPlayer_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayer_Tool::Free()
{
	__super::Free();
}

