#include "JobMob2_Weapon_Tool.h"


CJobMob2_Weapon_Tool::CJobMob2_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob2_Weapon(pDevice, pContext)
{
}

CJobMob2_Weapon_Tool::CJobMob2_Weapon_Tool(const CJobMob2_Weapon_Tool& rhs)
	: CJobMob2_Weapon(rhs)
{
}

HRESULT CJobMob2_Weapon_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob2_Weapon_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CJobMob2_Weapon_Tool* CJobMob2_Weapon_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob2_Weapon_Tool* pInstance = new CJobMob2_Weapon_Tool(pDevice, pContext);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob2_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CJobMob2_Weapon_Tool::Clone(void* pArg)
{
	CJobMob2_Weapon_Tool* pInstance = new CJobMob2_Weapon_Tool(*this);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob2_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob2_Weapon_Tool::Free()
{
	__super::Free();
}
