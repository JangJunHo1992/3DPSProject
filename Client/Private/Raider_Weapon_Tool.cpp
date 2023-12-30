#include "..\Public\Raider_Weapon_Tool.h"


CRaider_Weapon_Tool::CRaider_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider_Weapon(pDevice, pContext)
{
}

CRaider_Weapon_Tool::CRaider_Weapon_Tool(const CRaider_Weapon_Tool& rhs)
	: CRaider_Weapon(rhs)
{
}

HRESULT CRaider_Weapon_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_Weapon_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CRaider_Weapon_Tool* CRaider_Weapon_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Weapon_Tool* pInstance = new CRaider_Weapon_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CRaider_Weapon_Tool::Clone(void* pArg)
{
	CRaider_Weapon_Tool* pInstance = new CRaider_Weapon_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Weapon_Tool::Free()
{
	__super::Free();
}
