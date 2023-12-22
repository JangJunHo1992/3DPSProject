#include "Mesh.h"
#include "Shader.h"
#include "Bone.h"
#include "BONE_DATA.h"

CMesh::CMesh(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CVIBuffer(pDevice,pContext)
{
}

CMesh::CMesh(const CMesh& rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CMesh::Initialize_Prototype_Origin(const MODEL_TYPE eModelType, const MESH_DATA* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones)
{
	m_iMaterialIndex = pAIMesh->iMaterialIndex;
	strcpy_s(m_szName, pAIMesh->szName.c_str());
	m_iNumVertexBuffers = 1;
	m_iNumVertices = pAIMesh->iNumVertices;
	m_iNumIndices = pAIMesh->iNumFaces * 3;//�ﰢ���� ���� �ε����� ������ *3 �Ѱ���
	m_iIndexStride = 4;
	m_eIndexFormat = m_iIndexStride == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
	m_eTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

#pragma region VERTEX_BUFFER
	HRESULT		hr = MODEL_TYPE::NONANIM == eModelType ? Ready_Vertices_NonAnim(pAIMesh, PivotMatrix) : Ready_Vertices_Anim(pAIMesh, Bones);

	if (FAILED(hr))
		return E_FAIL;

#pragma endregion


#pragma region INDEX_BUFFER
	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
	m_BufferDesc.ByteWidth = m_iIndexStride * m_iNumIndices;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT /*D3D11_USAGE_DYNAMIC*/;
	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = 0;
	m_BufferDesc.MiscFlags = 0;
	m_BufferDesc.StructureByteStride = 0;

	ZeroMemory(&m_SubResourceData, sizeof m_SubResourceData);

	m_pIndices = new _uint[m_iNumIndices];

	_uint		iNumIndices = { 0 };

	for (size_t i = 0; i < pAIMesh->iNumFaces; i++)
	{
		m_pIndices[iNumIndices++] = pAIMesh->pIndices[i]._1;
		m_pIndices[iNumIndices++] = pAIMesh->pIndices[i]._2;
		m_pIndices[iNumIndices++] = pAIMesh->pIndices[i]._3;
	}

	m_SubResourceData.pSysMem = m_pIndices;

	if (FAILED(__super::Create_Buffer(&m_pIB)))
		return E_FAIL;


#pragma endregion

	//Safe_Delete_Array(m_pIndices);

	return S_OK;
}

HRESULT CMesh::Initialize(void* pArg)
{
	return S_OK;
}


HRESULT CMesh::Bind_BoneMatrices(CShader* pShader, const _char* pConstantName, const vector<CBone*>& Bones)
{
	_float4x4		BoneMatrices[256];

	for (size_t i = 0; i < m_iNumBones; i++)
	{
		XMStoreFloat4x4(&BoneMatrices[i], XMLoadFloat4x4(&m_OffsetMatrices[i]) * Bones[m_BoneIndices[i]]->Get_CombinedTransformationMatrix());
	}



	return pShader->Bind_Matrices(pConstantName, BoneMatrices, 256);
}


HRESULT CMesh::Ready_Vertices_NonAnim_Origin(const MESH_DATA* pAIMesh, _fmatrix PivotMatrix)
{
	m_iStride = sizeof(VTXMESH);

	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);

	m_BufferDesc.ByteWidth = m_iStride * m_iNumVertices;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT /*D3D11_USAGE_DYNAMIC*/;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = 0;
	m_BufferDesc.MiscFlags = 0;
	m_BufferDesc.StructureByteStride = m_iStride;

	ZeroMemory(&m_SubResourceData, sizeof m_SubResourceData);

	m_pVertices = new VTXMESH[m_iNumVertices];
	m_pPosVertices = new VTXPOS[m_iNumVertices];
	for (size_t i = 0; i < m_iNumVertices; i++)
	{
		memcpy(&m_pVertices[i].vPosition, &pAIMesh->pVertices[i], sizeof(_float3));
		XMStoreFloat3(&m_pVertices[i].vPosition, XMVector3TransformCoord(XMLoadFloat3(&m_pVertices[i].vPosition), PivotMatrix));
		memcpy(&m_pPosVertices[i].vPosition, &m_pVertices[i].vPosition, sizeof(_float3));

		memcpy(&m_pVertices[i].vNormal, &pAIMesh->pVertices[i].vNormal, sizeof(_float3));
		XMStoreFloat3(&m_pVertices[i].vNormal, XMVector3TransformNormal(XMLoadFloat3(&m_pVertices[i].vNormal), PivotMatrix));

		memcpy(&m_pVertices[i].vTexcoord, &pAIMesh->pVertices[i].vTexcoord, sizeof(_float2));
		memcpy(&m_pVertices[i].vTangent, &pAIMesh->pVertices[i].vTangent, sizeof(_float3));
	}


	m_SubResourceData.pSysMem = m_pVertices;

	/* pVertices�� �Ҵ��Ͽ� ä������ �������� ������ ID3D11Buffer�� �Ҵ��� ������ �����Ͽ� ä���ִ´�. */
	if (FAILED(__super::Create_Buffer(&m_pVB)))
		return E_FAIL;

	//Safe_Delete_Array(m_pVertices);

	return S_OK;
}

HRESULT CMesh::Ready_Vertices_Anim_Origin(const MESH_DATA* pAIMesh, const vector<class CBone*>& Bones)
{
	m_iStride = sizeof(VTXANIMMESH);

	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);

	m_BufferDesc.ByteWidth = m_iStride * m_iNumVertices;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT /*D3D11_USAGE_DYNAMIC*/;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = 0;
	m_BufferDesc.MiscFlags = 0;
	m_BufferDesc.StructureByteStride = m_iStride;

	ZeroMemory(&m_SubResourceData, sizeof m_SubResourceData);

	m_pAnimVertices = new VTXANIMMESH[m_iNumVertices];
	ZeroMemory(m_pAnimVertices, sizeof(VTXANIMMESH) * m_iNumVertices);

	for (size_t i = 0; i < m_iNumVertices; i++)
	{
		memcpy(&m_pAnimVertices[i].vPosition, &pAIMesh->pAnimVertices[i].vPosition, sizeof(_float3));
		memcpy(&m_pAnimVertices[i].vNormal, &pAIMesh->pAnimVertices[i].vNormal, sizeof(_float3));
		memcpy(&m_pAnimVertices[i].vTexcoord, &pAIMesh->pAnimVertices[i].vTexcoord, sizeof(_float2));
		memcpy(&m_pAnimVertices[i].vTangent, &pAIMesh->pAnimVertices[i].vTangent, sizeof(_float3));
		memcpy(&m_pAnimVertices[i].vBlendIndices, &pAIMesh->pAnimVertices[i].vBlendIndices, sizeof(XMUINT4));
		memcpy(&m_pAnimVertices[i].vBlendWeights, &pAIMesh->pAnimVertices[i].vBlendWeights, sizeof(XMFLOAT4));


	}

	m_iNumBones = pAIMesh->iNumBones;

	/* �� �޽ÿ��� ������ �ִ� ���� ��ȸ�ϸ鼭 ������ ���� � �����鿡�� ������ �ִ��� �ľ��Ѵ�.*/
	for (size_t i = 0; i < pAIMesh->iNumBones; i++)
	{
		BONE_DATA*		pAIBone = pAIMesh->Bone_Datas[i];

		_float4x4		OffsetMatrix;
		memcpy(&OffsetMatrix, &pAIBone->OffsetMatrix, sizeof(_float4x4));
		XMStoreFloat4x4(&OffsetMatrix, XMMatrixTranspose(XMLoadFloat4x4(&OffsetMatrix)));

		m_OffsetMatrices.push_back(OffsetMatrix);

		_uint		iBoneIndex = { 0 };

		auto	iter = find_if(Bones.begin(), Bones.end(), [&](CBone* pBone)
			{
				if (false == strcmp(pAIBone->szName.c_str(), pBone->Get_Name()))
				{
					return true;
				}

				++iBoneIndex;

				return false;
			});

		if (iter == Bones.end())
			return E_FAIL;

		m_BoneIndices.push_back(iBoneIndex);

// 		/* �� ���� ��� �������� ������ �ִ°�?! */
// 		for (size_t j = 0; j < pAIBone->mNumWeights; j++)
// 		{
// 			/* pAIBone->mWeights[j].mVertexId : �� ���� ������ �ִ� j��° ������ �ε��� */
// 
// 			if(0.0f == m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.x)
// 			{
// 				m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendIndices.x = i;
// 				m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.x = pAIBone->mWeights[j].mWeight;
// 			}
// 
// 			else if (0.0f == m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.y)
// 			{
// 				m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendIndices.y = i;
// 				m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.y = pAIBone->mWeights[j].mWeight;
// 			}
// 
// 			else if (0.0f == m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.z)
// 			{
// 				m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendIndices.z = i;
// 				m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.z = pAIBone->mWeights[j].mWeight;
// 			}
// 
// 			else if (0.0f == m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.w)
// 			{
// 				m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendIndices.w = i;
// 				m_pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.w = pAIBone->mWeights[j].mWeight;
// 			}
// 		}		
	};

	m_SubResourceData.pSysMem = m_pAnimVertices;

	/* pVertices�� �Ҵ��Ͽ� ä������ �������� ������ ID3D11Buffer�� �Ҵ��� ������ �����Ͽ� ä���ִ´�. */
	if (FAILED(__super::Create_Buffer(&m_pVB)))
		return E_FAIL;

	//Safe_Delete_Array(m_pAnimVertices);

	if (0 == m_iNumBones)
	{
		m_iNumBones = 1;

		_uint		iBoneIndex = { 0 };

		auto	iter = find_if(Bones.begin(), Bones.end(), [&](CBone* pBone)
			{
				if (false == strcmp(m_szName, pBone->Get_Name()))
				{
					return true;
				}

				++iBoneIndex;

				return false;
			});

		if (iter == Bones.end())
			return E_FAIL;

		m_BoneIndices.push_back(iBoneIndex);

		_float4x4		OffsetMatrix;
		XMStoreFloat4x4(&OffsetMatrix, XMMatrixIdentity());
		m_OffsetMatrices.push_back(OffsetMatrix);
	}

	return S_OK;
}

void CMesh::Free()
{
	//Safe_Delete_Array(m_pIndices);
	//Safe_Delete_Array(m_pVertices);
	//Safe_Delete_Array(m_pAnimVertices);

	__super::Free();
}
