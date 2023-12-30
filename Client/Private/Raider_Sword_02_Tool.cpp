#include "..\Public\Raider_Sword_02_Tool.h"


CRaider_Sword_02_Tool::CRaider_Sword_02_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider_Weapon(pDevice, pContext)
{
}

CRaider_Sword_02_Tool::CRaider_Sword_02_Tool(const CRaider_Sword_02_Tool& rhs)
	: CRaider_Weapon(rhs)
{
}

HRESULT CRaider_Sword_02_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_Sword_02_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CRaider_Sword_02_Tool* CRaider_Sword_02_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Sword_02_Tool* pInstance = new CRaider_Sword_02_Tool(pDevice, pContext);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Sword_02_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CRaider_Sword_02_Tool::Clone(void* pArg)
{
	CRaider_Sword_02_Tool* pInstance = new CRaider_Sword_02_Tool(*this);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Sword_02_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Sword_02_Tool::Free()
{
	__super::Free();
}
