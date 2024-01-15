#include "JobMob2_Body_Tool.h"


CJobMob2_Body_Tool::CJobMob2_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob2_Body(pDevice, pContext)
{
}

CJobMob2_Body_Tool::CJobMob2_Body_Tool(const CJobMob2_Body_Tool& rhs)
	: CJobMob2_Body(rhs)
{
}

HRESULT CJobMob2_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob2_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CJobMob2_Body_Tool* CJobMob2_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob2_Body_Tool* pInstance = new CJobMob2_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob2_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CJobMob2_Body_Tool::Clone(void* pArg)
{
	CJobMob2_Body_Tool* pInstance = new CJobMob2_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob2_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob2_Body_Tool::Free()
{
	__super::Free();
}
