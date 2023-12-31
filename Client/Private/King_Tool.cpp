#include "..\Public\King_Tool.h"
#include "GameInstance.h"

CKing_Tool::CKing_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKing(pDevice, pContext)
{
}

CKing_Tool::CKing_Tool(const CKing_Tool& rhs)
	: CKing(rhs)
{
}

HRESULT CKing_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CKing_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CKing_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CKing_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CKing_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CKing_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CKing_Tool::Set_Hitted()
{
	CKing::King_State eHitted = CKing::King_State::TwoHandedHammerSet_Hit_Body_Front;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

_bool CKing_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CKing_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CKing_Tool* CKing_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKing_Tool* pInstance = new CKing_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKing_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CKing_Tool* CKing_Tool::Clone(void* pArg)
{
	CKing_Tool* pInstance = new CKing_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKing_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKing_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
