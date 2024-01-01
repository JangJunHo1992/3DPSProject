#include "..\Public\Raider_Sword_01_Tool.h"


CRaider_Sword_01_Tool::CRaider_Sword_01_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider_Sword_01(pDevice, pContext)
{
}

CRaider_Sword_01_Tool::CRaider_Sword_01_Tool(const CRaider_Sword_01_Tool& rhs)
	: CRaider_Sword_01(rhs)
{
}

HRESULT CRaider_Sword_01_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_Sword_01_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CRaider_Sword_01_Tool* CRaider_Sword_01_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Sword_01_Tool* pInstance = new CRaider_Sword_01_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Sword_01_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CRaider_Sword_01_Tool::Clone(void* pArg)
{
	CRaider_Sword_01_Tool* pInstance = new CRaider_Sword_01_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Sword_01_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Sword_01_Tool::Free()
{
	__super::Free();
}
