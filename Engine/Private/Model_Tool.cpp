#include "..\Public\Model_Tool.h"
#include "Mesh_Tool.h"

CModel_Tool::CModel_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CModel(pDevice, pContext)
{
}

CModel_Tool::CModel_Tool(const CModel_Tool& rhs)
	: CModel(rhs)
{
}

HRESULT CModel_Tool::Ready_Meshes(_fmatrix PivotMatrix)
{
	return Ready_Meshes_Origin<CMesh_Tool>(PivotMatrix);
}

CModel_Tool* CModel_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, TYPE eType, const string& strModelFilePath, _fmatrix PivotMatrix)
{
	CModel_Tool* pInstance = new CModel_Tool(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype(eType, strModelFilePath, PivotMatrix)))
	{
		MSG_BOX("Failed to Created : CModel_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CModel_Tool::Clone(void* pArg)
{
	CModel_Tool* pInstance = new CModel_Tool(*this);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CModel_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CModel_Tool::Free()
{
	__super::Free();
}
