#include "MESH_DATA.h"

HRESULT MESH_DATA::Make_MeshData(const MODEL_TYPE& In_eModelType, aiMesh* In_pAiMesh, const _fmatrix& In_TransformMatrix, MESH_VTX_INFO* In_pVertexInfo)
{
	szName = In_pAiMesh->mName.C_Str();
	eModelType = In_eModelType;
	iNumVertices = In_pAiMesh->mNumVertices;
	iNumFaces = In_pAiMesh->mNumFaces;
	iNumBones = In_pAiMesh->mNumBones;
	iMaterialIndex = In_pAiMesh->mMaterialIndex;

	// 애니메이션
	if (MODEL_TYPE::ANIM == In_eModelType)
	{
		for (_uint i(0); i < iNumBones; i++)
		{
			BONE_DATA* pBoneData = new BONE_DATA;
			pBoneData->Make_BoneData(In_pAiMesh->mBones[i]);
			Bone_Datas.push_back(pBoneData);
		}

		pAnimVertices = new VTXANIMMESH[iNumVertices];

		for (_uint i(0); i < iNumVertices; ++i)
		{
			memcpy(&pAnimVertices[i].vPosition, &In_pAiMesh->mVertices[i], sizeof(_float3));
			//XMStoreFloat3(&pAnimVertices[i].vPosition, XMVector3TransformCoord(XMLoadFloat3(&pAnimVertices[i].vPosition), In_TransformMatrix));

			memcpy(&pAnimVertices[i].vNormal, &In_pAiMesh->mNormals[i], sizeof(_float3));
			XMStoreFloat3(&pAnimVertices[i].vNormal, XMVector3Normalize(XMVector3TransformNormal(XMLoadFloat3(&pAnimVertices[i].vNormal), In_TransformMatrix)));

			memcpy(&pAnimVertices[i].vTexcoord, &In_pAiMesh->mTextureCoords[0][i], sizeof(_float2));
			memcpy(&pAnimVertices[i].vTangent, &In_pAiMesh->mTangents[i], sizeof(_float3));

			Check_Position(In_pVertexInfo->vMax, pAnimVertices[i].vPosition, [](_float _fLeft, _float _fRight)->_bool { return _fLeft < _fRight; });
			Check_Position(In_pVertexInfo->vMin, pAnimVertices[i].vPosition, [](_float _fLeft, _float _fRight)->_bool { return _fLeft > _fRight; });
		}

		for (_uint i(0); i < iNumBones; ++i)
		{
			aiBone* pAIBone = In_pAiMesh->mBones[i];
			/* pAIBone->mNumWeights : 이 뼈는 몇개의 정점에 영향릉 주는지 */
			for (_uint j(0); j < pAIBone->mNumWeights; ++j)
			{
				/* pAIBone->mWeights[j].mVertexId : 그 중에 j번째 정점의 인덱스는 뭐였는지?  */
				/* pAIBone->mWeights[j].mWeight : j번째 정점에게 적용해야할 가중치. */

				if (0 == pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.x)
				{
					pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendIndices.x = i;
					pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.x = pAIBone->mWeights[j].mWeight;
				}

				else if (0 == pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.y)
				{
					pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendIndices.y = i;
					pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.y = pAIBone->mWeights[j].mWeight;
				}

				else if (0 == pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.z)
				{
					pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendIndices.z = i;
					pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.z = pAIBone->mWeights[j].mWeight;
				}

				else
				{
					pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendIndices.w = i;
					pAnimVertices[pAIBone->mWeights[j].mVertexId].vBlendWeights.w = pAIBone->mWeights[j].mWeight;
				}
			}
		}


	}

	// 애니메이션이 아님
	else if (MODEL_TYPE::NONANIM == In_eModelType)
	{
		pVertices = new VTXMESH[iNumVertices];
		pPosVertices = new VTXPOS[iNumVertices];

		for (_uint i(0); i < iNumVertices; ++i)
		{
			memcpy(&pVertices[i].vPosition, &In_pAiMesh->mVertices[i], sizeof(_float3));
			XMStoreFloat3(&pVertices[i].vPosition, XMVector3TransformCoord(XMLoadFloat3(&pVertices[i].vPosition), In_TransformMatrix));
			memcpy(&pPosVertices[i].vPosition, &pVertices[i].vPosition, sizeof(_float3));

			memcpy(&pVertices[i].vNormal, &In_pAiMesh->mNormals[i], sizeof(_float3));
			XMStoreFloat3(&pVertices[i].vNormal, XMVector3Normalize(XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vNormal), In_TransformMatrix)));

			if (In_pAiMesh->mTextureCoords[0])
				memcpy(&pVertices[i].vTexcoord, &In_pAiMesh->mTextureCoords[0][i], sizeof(_float2));
			else
				pVertices[i].vTexcoord = { 0.f, 0.f };

			if (In_pAiMesh->mTangents)
				memcpy(&pVertices[i].vTangent, &In_pAiMesh->mTangents[i], sizeof(_float3));
			else
				pVertices[i].vTangent = { 0.f, 0.f, 0.f };

			Check_Position(In_pVertexInfo->vMax, pVertices[i].vPosition, [](_float _fLeft, _float _fRight)->_bool { return _fLeft < _fRight; });
			Check_Position(In_pVertexInfo->vMin, pVertices[i].vPosition, [](_float _fLeft, _float _fRight)->_bool { return _fLeft > _fRight; });
		}
	}
// 
// 	else if (MODEL_TYPE::NAVI == In_eModelType)
// 	{
// 		pPosVertices = shared_ptr<VTXPOS[]>(DBG_NEW VTXPOS[iNumVertices]);
// 
// 		for (_uint i(0); i < iNumVertices; ++i)
// 		{
// 			memcpy(&pVertices[i].vPosition, &In_pAiMesh->mVertices[i], sizeof(_float3));
// 			XMStoreFloat3(&pVertices[i].vPosition, XMVector3TransformCoord(XMLoadFloat3(&pVertices[i].vPosition), In_TransformMatrix));
// 		}
// 	}

	

	pIndices = new FACEINDICES32[iNumFaces];

	for (_uint i(0); i < iNumFaces; ++i)
	{
		pIndices[i]._1 = In_pAiMesh->mFaces[i].mIndices[0];
		pIndices[i]._2 = In_pAiMesh->mFaces[i].mIndices[1];
		pIndices[i]._3 = In_pAiMesh->mFaces[i].mIndices[2];
	}

	return S_OK;
}

void MESH_DATA::Bake_Binary(ofstream& os)
{
	write_typed_data(os, szName.size());
	os.write(&szName[0], szName.size());

	write_typed_data(os, eModelType);
	write_typed_data(os, iNumVertices);
	write_typed_data(os, iNumFaces);
	write_typed_data(os, iNumBones);
	write_typed_data(os, iMaterialIndex);

	if (MODEL_TYPE::ANIM == eModelType)
	{
		for (_uint i(0); i < iNumBones; i++)
			Bone_Datas[i]->Bake_Binary(os);

		for (_uint i(0); i < iNumVertices; ++i)
			write_typed_data(os, pAnimVertices[i]);
	}

	else if (MODEL_TYPE::NONANIM == eModelType)
	{
		for (_uint i(0); i < iNumVertices; ++i)
			write_typed_data(os, pVertices[i]);
	}

// 	else if (MODEL_TYPE::NAVI == eModelType)
// 	{
// 		for (_uint i(0); i < iNumVertices; ++i)
// 			write_typed_data(os, pPosVertices[i]);
// 	}

	

	for (_uint i(0); i < iNumFaces; ++i)
		write_typed_data(os, pIndices[i]);

}

void MESH_DATA::Load_FromBinary(ifstream& is)
{
	size_t istringSize;
	read_typed_data(is, istringSize);
	szName.resize(istringSize);
	is.read(&szName[0], istringSize);

	read_typed_data(is, eModelType);
	read_typed_data(is, iNumVertices);
	read_typed_data(is, iNumFaces);
	read_typed_data(is, iNumBones);
	read_typed_data(is, iMaterialIndex);

	if (MODEL_TYPE::ANIM == eModelType)
	{
		for (_uint i(0); i < iNumBones; i++)
		{
			BONE_DATA* pBoneData = new BONE_DATA();
			pBoneData->Load_FromBinary(is);
			Bone_Datas.push_back(pBoneData);
		}

		pAnimVertices = new VTXANIMMESH[iNumVertices];

		for (_uint i(0); i < iNumVertices; ++i)
		{
			read_typed_data(is, pAnimVertices[i]);
		}

	}

	else if (MODEL_TYPE::NONANIM == eModelType)
	{
		pVertices = new VTXMESH[iNumVertices];
		pPosVertices = new VTXPOS[iNumVertices];

		for (_uint i(0); i < iNumVertices; ++i)
		{
			read_typed_data(is, pVertices[i]);
			memcpy(&pPosVertices[i].vPosition, &pVertices[i].vPosition, sizeof(_float3));
		}
	}

// 	else if (MODEL_TYPE::NAVI == eModelType)
// 	{
// 		pPosVertices = shared_ptr<VTXPOS[]>(DBG_NEW VTXPOS[iNumVertices]);
// 
// 		for (_uint i(0); i < iNumVertices; ++i)
// 		{
// 			read_typed_data(is, pPosVertices[i]);
// 		}
// 	}
// 
// 	else if (MODEL_TYPE::GROUND == eModelType)
// 	{
// 		pGroundVertices = shared_ptr<VTXGROUND[]>(DBG_NEW VTXGROUND[iNumVertices]);
// 
// 		for (_uint i(0); i < iNumVertices; ++i)
// 		{
// 			read_typed_data(is, pGroundVertices[i]);
// 		}
// 	}

	pIndices = new FACEINDICES32[iNumFaces];

	for (_uint i(0); i < iNumFaces; ++i)
	{
		read_typed_data(is, pIndices[i]);
	}

}

void MESH_DATA::Check_Position(_float3& _vRecodePosion, _float3 _vValue, _bool(*_pFncPtr)(_float, _float))
{
	if (_pFncPtr(_vRecodePosion.x, _vValue.x))
		_vRecodePosion.x = _vValue.x;

	if (_pFncPtr(_vRecodePosion.y, _vValue.y))
		_vRecodePosion.y = _vValue.y;

	if (_pFncPtr(_vRecodePosion.z, _vValue.z))
		_vRecodePosion.z = _vValue.z;
}