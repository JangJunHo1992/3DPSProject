#include "Model.h"
#include "Mesh.h"

CModel::CModel(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CComponent(pDevice, pContext)
{
}

CModel::CModel(const CModel& rhs)
	: CComponent(rhs)
	, m_iNumMeshes(rhs.m_iNumMeshes)
	, m_Meshes(rhs.m_Meshes)
{
	for (auto& pMesh : m_Meshes)
	{
		Safe_AddRef(pMesh);
	}
}

HRESULT CModel::Initialize_Prototype(const string& strModelFilePath, _fmatrix PivotMatrix)
{
	/*aiProcess_PreTransformVertices | aiProcess_GlobalScale*/
	m_pAIScene = m_Importer.ReadFile(strModelFilePath, aiProcess_PreTransformVertices | aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast);
	if (nullptr == m_pAIScene)
		return E_FAIL;

	if (FAILED(Ready_Meshes(PivotMatrix)))
		return E_FAIL;

	return S_OK;
}

HRESULT CModel::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CModel::Render()
{
	for (auto& pMesh : m_Meshes)
	{
		if (nullptr != pMesh)
		{
			pMesh->Bind_VIBuffers();
			pMesh->Render();
		}
	}

	return S_OK;
}

HRESULT CModel::Ready_Meshes(_fmatrix PivotMatrix)
{
	m_iNumMeshes = m_pAIScene->mNumMeshes;

	m_Meshes.reserve(m_iNumMeshes);

	for (size_t i = 0; i < m_iNumMeshes; i++)
	{
		CMesh* pMesh = CMesh::Create(m_pDevice, m_pContext, m_pAIScene->mMeshes[i], PivotMatrix);

		if (nullptr == pMesh)
			return E_FAIL;

		m_Meshes.push_back(pMesh);
	}

	return S_OK;
}

CModel* CModel::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const string& strModelFilePath, _fmatrix PivotMatrix)
{
	CModel* pInstance = new CModel(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype(strModelFilePath, PivotMatrix)))
	{
		MSG_BOX("Failed to Created : CModel");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CModel::Clone(void* pArg)
{
	CModel* pInstance = new CModel(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CComponent");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CModel::Free()
{
	__super::Free();

	for (auto& pMesh : m_Meshes)
	{
		Safe_Release(pMesh);
	}
	m_Meshes.clear();

	if (false == m_isCloned)
		m_Importer.FreeScene();
}
