#include "..\Public\Golem_Tool.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Hit_Front.h"

CGolem_Tool::CGolem_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGolem(pDevice, pContext)
{
}

CGolem_Tool::CGolem_Tool(const CGolem_Tool& rhs)
	: CGolem(rhs)
{
}

HRESULT CGolem_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CGolem_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CGolem_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CGolem_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CGolem_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CGolem_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CGolem_Tool::Set_Hitted()
{
	CGolem::Golem_State eHitted = CGolem::Golem_State::Giant_Golem_Hit_Light_Front;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

_bool CGolem_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CGolem_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CGolem_Tool* CGolem_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CGolem_Tool* pInstance = new CGolem_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CGolem_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGolem_Tool* CGolem_Tool::Clone(void* pArg)
{
	CGolem_Tool* pInstance = new CGolem_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CGolem_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGolem_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
