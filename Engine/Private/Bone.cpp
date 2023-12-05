#include "Bone.h"

CBone::CBone()
{
}

HRESULT CBone::Initialize(aiNode* pAINode, _int iParentIndex)
{
	m_iParentIndex = iParentIndex;

	strcpy_s(m_szName, pAINode->mName.data);

	memcpy(&m_TransformationMatrix, &pAINode->mTransformation, sizeof(_float4x4));

	XMStoreFloat4x4(&m_TransformationMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_TransformationMatrix)));

	XMStoreFloat4x4(&m_CombindTransformationMatrix, XMMatrixIdentity());

	return S_OK;
}

void CBone::Invalidate_CombinedTransformationMatrix(CModel::BONES& Bones)
{
	if (-1 == m_iParentIndex)
		m_CombindTransformationMatrix = m_TransformationMatrix;

	XMStoreFloat4x4(&m_CombindTransformationMatrix,
		XMLoadFloat4x4(&m_TransformationMatrix) * XMLoadFloat4x4(&Bones[m_iParentIndex]->m_CombindTransformationMatrix));

}

CBone* CBone::Create(aiNode* pAINode, _int iParentIndex)
{
	CBone* pInstance = new CBone();

	if (FAILED(pInstance->Initialize(pAINode, iParentIndex)))
	{
		MSG_BOX("Failed to Created : CBone");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CBone::Free()
{
}
