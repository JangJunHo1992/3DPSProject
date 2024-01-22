#include "JobMob1_Body_Tool.h"


CJobMob1_Body_Tool::CJobMob1_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob1_Body(pDevice, pContext)
{
}

CJobMob1_Body_Tool::CJobMob1_Body_Tool(const CJobMob1_Body_Tool& rhs)
	: CJobMob1_Body(rhs)
{
}

HRESULT CJobMob1_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob1_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CJobMob1_Body_Tool* CJobMob1_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob1_Body_Tool* pInstance = new CJobMob1_Body_Tool(pDevice, pContext);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob1_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CJobMob1_Body_Tool::Clone(void* pArg)
{
	CJobMob1_Body_Tool* pInstance = new CJobMob1_Body_Tool(*this);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob1_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob1_Body_Tool::Free()
{
	__super::Free();
}
