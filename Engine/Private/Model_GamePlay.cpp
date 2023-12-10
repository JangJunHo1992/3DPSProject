#include "..\Public\Model_GamePlay.h"
#include "Mesh_GamePlay.h"

CModel_GamePlay::CModel_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CModel(pDevice, pContext)
{
}

CModel_GamePlay::CModel_GamePlay(const CModel_GamePlay& rhs)
	: CModel(rhs)
{
}

HRESULT CModel_GamePlay::Ready_Meshes(_fmatrix PivotMatrix)
{
	return Ready_Meshes_Origin<CMesh_GamePlay>(PivotMatrix);
}

CModel_GamePlay* CModel_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, TYPE eType, const string& strModelFilePath, _fmatrix PivotMatrix)
{
	CModel_GamePlay* pInstance = new CModel_GamePlay(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype(eType, strModelFilePath, PivotMatrix)))
	{
		MSG_BOX("Failed to Created : CModel_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CModel_GamePlay::Clone(void* pArg)
{
	CModel_GamePlay* pInstance = new CModel_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CModel_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CModel_GamePlay::Free()
{
	__super::Free();
}
