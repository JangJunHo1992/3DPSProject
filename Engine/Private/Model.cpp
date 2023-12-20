#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Bone.h"
#include "Animation.h"
#include "Channel.h"

CModel::CModel(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CComponent(pDevice,pContext)
{
}

CModel::CModel(const CModel& rhs)
	: CComponent(rhs)
	, m_PivotMatrix(rhs.m_PivotMatrix)
	, m_eModelType(rhs.m_eModelType)
	, m_iNumMeshes(rhs.m_iNumMeshes)
	, m_Meshes(rhs.m_Meshes)
	, m_iNumMaterials(rhs.m_iNumMaterials)
	, m_Materials(rhs.m_Materials)
	, m_iNumAnimations(rhs.m_iNumAnimations)
{
	for (auto& pPrototypeAnimation : rhs.m_Animations)
		m_Animations.push_back(pPrototypeAnimation->Clone());

	for (auto& pPrototypeBone : rhs.m_Bones)
		m_Bones.push_back(pPrototypeBone->Clone());

	for (auto& MaterialDesc : m_Materials)
	{
		for (auto& pTexture : MaterialDesc.pMtrlTextures)
			Safe_AddRef(pTexture);
	}

	for (auto& pMesh : m_Meshes)
	{
		Safe_AddRef(pMesh);
	}
}


HRESULT CModel::Initialize_Prototype(const MODEL_TYPE eType, const string& strModelFilePath, _fmatrix PivotMatrix)
{
	//! ModelData

	m_eModelType = eType;

// 	_uint	iFlag = aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast;
// 
// 	if (TYPE_NONANIM == eType)
// 		iFlag |= aiProcess_PreTransformVertices;
// 
// 	m_pAIScene = m_Importer.ReadFile(strModelFilePath, iFlag);
// 
// 	if (nullptr == m_pAIScene)
// 		return E_FAIL;
	m_pAIScene = new MODEL_DATA;

	if (FAILED(m_pAIScene->Make_ModelData(strModelFilePath.c_str(), m_eModelType, PivotMatrix)))
		return E_FAIL;

	XMStoreFloat4x4(&m_PivotMatrix, PivotMatrix);

	if (FAILED(Ready_Bones(m_pAIScene->RootNode, -1)))
		return E_FAIL;

	if (FAILED(Ready_Meshes(PivotMatrix)))
		return E_FAIL;

	if (FAILED(Ready_Materials(strModelFilePath)))
		return E_FAIL;

	if (FAILED(Ready_Animations()))
		return E_FAIL;

	return S_OK;
}

HRESULT CModel::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CModel::Render(_uint iMeshIndex)
{
	if (iMeshIndex >= m_iNumMeshes)
		return E_FAIL;

	m_Meshes[iMeshIndex]->Bind_VIBuffers();
	m_Meshes[iMeshIndex]->Render();

	return S_OK;
}

HRESULT CModel::Bind_BoneMatrices(CShader* pShader, const _char* pConstantName, _uint iMeshIndex)
{
	return m_Meshes[iMeshIndex]->Bind_BoneMatrices(pShader, pConstantName, m_Bones);
}

HRESULT CModel::Bind_ShaderResource(CShader* pShader, const _char* pConstantName, _uint iMeshIndex, TextureType eTextureType)
{
	_uint		iMaterialIndex = m_Meshes[iMeshIndex]->Get_MaterialIndex();
	if (iMaterialIndex >= m_iNumMaterials)
		return E_FAIL;

	return m_Materials[iMaterialIndex].pMtrlTextures[eTextureType]->Bind_ShaderResource(pShader, pConstantName);
}

void CModel::Play_Animation(_float fTimeDelta)
{
	if (m_iCurrentAnimIndex >= m_iNumAnimations)
		return;

	m_bIsAnimEnd = m_Animations[m_iCurrentAnimIndex]->Invalidate_TransformationMatrix(m_eAnimState, fTimeDelta, m_Bones);
		
	for (auto& pBone : m_Bones)
	{
		pBone->Invalidate_CombinedTransformationMatrix(m_Bones, XMLoadFloat4x4(&m_PivotMatrix));
	}

}

void CModel::Set_Animation(_uint _iAnimationIndex, CModel::ANIM_STATE _eAnimState, _bool _bIsTransition, _float _fTransitionDuration)
{
	m_eAnimState = _eAnimState;

	if (_iAnimationIndex != m_iCurrentAnimIndex)
	{
		Reset_Animation(_iAnimationIndex);
		
		if (_bIsTransition)
		{
			Set_Animation_Transition(_iAnimationIndex, _fTransitionDuration);
		}
		else 
		{
			m_iCurrentAnimIndex = _iAnimationIndex;
		}
	}
}

void CModel::Set_Animation_Transition(_uint _iAnimationIndex, _float _fTransitionDuration)
{
	CAnimation* currentAnimation = m_Animations[m_iCurrentAnimIndex];
	CAnimation* targetAnimation = m_Animations[_iAnimationIndex];

	_float fCurrentTrackPosition = m_Animations[m_iCurrentAnimIndex]->Get_TrackPosition();
	_float fTransitionDuration = _fTransitionDuration > 0.f ? _fTransitionDuration : 0.2f;

	_float fTransitionDuration_Start = 0.0f;
	_float fTransitionDuration_End = 0.0f;
	


	vector<CChannel*> currentChannels = *currentAnimation->Get_Channels();

	for (CChannel* currnetChannel : currentChannels)
	{
		_uint	targetBoneIndex = currnetChannel->Get_BoneIndex();
		
		CChannel* targetChannel = targetAnimation->Get_Channel_By_BoneIndex(targetBoneIndex);
		if (nullptr == targetChannel)
		{
			_uint test = targetBoneIndex;
		}
		else
		{
			KEYFRAME startFrame = currnetChannel->Make_NowFrame(fCurrentTrackPosition);
			KEYFRAME endFrame = targetChannel->Get_First_KeyFrame();
			targetChannel->Set_Transition(startFrame, endFrame, &fTransitionDuration);
			fTransitionDuration_End = endFrame.fTrackPosition;
		}
	}
	fTransitionDuration_Start = fTransitionDuration_End - fTransitionDuration;

	m_iCurrentAnimIndex = _iAnimationIndex;

	m_Animations[m_iCurrentAnimIndex]->Set_IsTransition_True();
	//m_Animations[m_iCurrentAnimIndex]->Set_TransitionDuration(0.0f);
	m_Animations[m_iCurrentAnimIndex]->Set_TransitionDuration(&fTransitionDuration_End);
	//m_Animations[m_iCurrentAnimIndex]->Set_TrackPosition(-0.2f);
	m_Animations[m_iCurrentAnimIndex]->Set_TrackPosition(&fTransitionDuration_Start);
	_bool test = false;

}

void CModel::Reset_Animation(_int iAnimIndex)
{
	if (iAnimIndex == -1)
		m_Animations[m_iCurrentAnimIndex]->Reset_Animation(m_Bones);
	else
		m_Animations[iAnimIndex]->Reset_Animation(m_Bones);
}



template<class T>
HRESULT CModel::Ready_Meshes_Origin(_fmatrix PivotMatrix)
{
	m_iNumMeshes = m_pAIScene->iNumMeshs;

	m_Meshes.reserve(m_iNumMeshes);

	for (size_t i = 0; i < m_iNumMeshes; i++)
	{
		T* pMesh = T::Create(m_pDevice, m_pContext, m_eModelType, m_pAIScene->Mesh_Datas[i], PivotMatrix, m_Bones);

		if (nullptr == pMesh)
			return E_FAIL;

		m_Meshes.push_back(pMesh);
	}

	return S_OK;
}

HRESULT CModel::Ready_Materials(const string& strModelFilePath)
{
	m_iNumMaterials = m_pAIScene->iNumMaterials;
	
	for (size_t i = 0; i < m_iNumMaterials; i++)
	{
		m_pAIMaterial = m_pAIScene->Material_Datas[i];

		MATERIAL_DESC			MaterialDesc = {  };

		for (size_t j = 1; j < TextureType::Type_UNKNOWN; j++)
		{
			_char		szDrive[MAX_PATH] = "";
			_char		szDirectory[MAX_PATH] = "";

			_splitpath_s(strModelFilePath.c_str(), szDrive, MAX_PATH, szDirectory, MAX_PATH, nullptr, 0, nullptr, 0);

			string		strPath;
// 			if (FAILED(m_pAIMaterial->GetTexture(TextureType(j), 0, &strPath)))
// 				continue;
			strPath = m_pAIMaterial->szTextureName[TextureType(j)].c_str();

			if(strPath == "")
				continue;

			_char		szFileName[MAX_PATH] = "";
			_char		szEXT[MAX_PATH] = "";

			_splitpath_s(strPath.c_str(), nullptr, 0, nullptr, 0, szFileName, MAX_PATH, szEXT, MAX_PATH);

			_char		szTmp[MAX_PATH] = "";
			strcpy_s(szTmp, szDrive);
			strcat_s(szTmp, szDirectory);
			strcat_s(szTmp, szFileName);
			strcat_s(szTmp, szEXT);

			//_char szTest[MAX_PATH] = ".dds";
			//strcat_s(szTmp, szTest);

			_tchar		szFullPath[MAX_PATH] = TEXT("");

			MultiByteToWideChar(CP_ACP, 0, szTmp, strlen(szTmp), szFullPath, MAX_PATH);


			MaterialDesc.pMtrlTextures[j] = CTexture::Create(m_pDevice, m_pContext, szFullPath, 1);
			if (nullptr == MaterialDesc.pMtrlTextures[j])
				return E_FAIL;
		}

		m_Materials.push_back(MaterialDesc);
	}

	return S_OK;
}

HRESULT CModel::Ready_Bones(NODE_DATA* pAINode, _int iParentIndex)
{
	CBone* pBone = CBone::Create(pAINode, iParentIndex);
	if (nullptr == pBone)
		return E_FAIL;

	m_Bones.push_back(pBone);

	_int		iParentIdx = m_Bones.size() - 1;

	for (size_t i = 0; i < pAINode->iNumChildren; i++)
	{
		Ready_Bones(pAINode->pChildren[i], iParentIdx);
	}

	return S_OK;
}

HRESULT CModel::Ready_Animations()
{
	m_iNumAnimations = m_pAIScene->iNumAnimations;

	for (size_t i = 0; i < m_iNumAnimations; i++)
	{
		CAnimation* pAnimation = CAnimation::Create(m_pAIScene->Animation_Datas[i], m_Bones);
		if (nullptr == pAnimation)
			return E_FAIL;

		m_Animations.push_back(pAnimation);
	}

	return S_OK;
}


void CModel::Free()
{
	__super::Free();

	for (auto& pAnimation : m_Animations)
		Safe_Release(pAnimation);

	for (auto& pBone : m_Bones)
		Safe_Release(pBone);

	m_Bones.clear();

	for (auto& MaterialDesc : m_Materials)
	{
		for (auto& pTexture : MaterialDesc.pMtrlTextures)
			Safe_Release(pTexture);
	}
	m_Materials.clear();

	for (auto& pMesh : m_Meshes)
	{
		Safe_Release(pMesh);
	}
	m_Meshes.clear();

// 	if (false == m_isCloned)
// 		m_Importer.FreeScene();

}
