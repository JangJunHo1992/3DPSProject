#include "JobMob1_Weapon_Tool.h"


CJobMob1_Weapon_Tool::CJobMob1_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob1_Weapon(pDevice, pContext)
{
}

CJobMob1_Weapon_Tool::CJobMob1_Weapon_Tool(const CJobMob1_Weapon_Tool& rhs)
	: CJobMob1_Weapon(rhs)
{
}

HRESULT CJobMob1_Weapon_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob1_Weapon_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CJobMob1_Weapon_Tool* CJobMob1_Weapon_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob1_Weapon_Tool* pInstance = new CJobMob1_Weapon_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob1_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CJobMob1_Weapon_Tool::Clone(void* pArg)
{
	CJobMob1_Weapon_Tool* pInstance = new CJobMob1_Weapon_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob1_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob1_Weapon_Tool::Free()
{
	__super::Free();
}
