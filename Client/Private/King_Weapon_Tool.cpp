#include "..\Public\King_Weapon_Tool.h"


CKing_Weapon_Tool::CKing_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKing_Weapon(pDevice, pContext)
{
}

CKing_Weapon_Tool::CKing_Weapon_Tool(const CKing_Weapon_Tool& rhs)
	: CKing_Weapon(rhs)
{
}

HRESULT CKing_Weapon_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CKing_Weapon_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CKing_Weapon_Tool* CKing_Weapon_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKing_Weapon_Tool* pInstance = new CKing_Weapon_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKing_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CKing_Weapon_Tool::Clone(void* pArg)
{
	CKing_Weapon_Tool* pInstance = new CKing_Weapon_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKing_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKing_Weapon_Tool::Free()
{
	__super::Free();
}
