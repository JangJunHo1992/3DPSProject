#include "..\Public\DarkKnight_Tool.h"
#include "GameInstance.h"

//#include "Massive_Greate_Sword_Hit_Front.h"

CDarkKnight_Tool::CDarkKnight_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CDarkKnight(pDevice, pContext)
{
}

CDarkKnight_Tool::CDarkKnight_Tool(const CDarkKnight_Tool& rhs)
	: CDarkKnight(rhs)
{
}

HRESULT CDarkKnight_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CDarkKnight_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CDarkKnight_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CDarkKnight_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CDarkKnight_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CDarkKnight_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CDarkKnight_Tool::Set_Hitted()
{
	CDarkKnight::DarkKnight_State eHitted = CDarkKnight::DarkKnight_State::Massive_Greate_Sword_Hit_Front;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

_bool CDarkKnight_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CDarkKnight_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CDarkKnight_Tool* CDarkKnight_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CDarkKnight_Tool* pInstance = new CDarkKnight_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CDarkKnight_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CDarkKnight_Tool* CDarkKnight_Tool::Clone(void* pArg)
{
	CDarkKnight_Tool* pInstance = new CDarkKnight_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CDarkKnight_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDarkKnight_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
