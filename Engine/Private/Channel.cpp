#include "..\Public\Channel.h"
#include "Bone.h"

CChannel::CChannel()
{
}

HRESULT CChannel::Initialize(const aiNodeAnim* pChannel, const CModel::BONES& Bones)
{
	strcpy_s(m_szName, pChannel->mNodeName.data);

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

	m_iBoneIndex = iBoneIndex;

	m_iNumKeyFrames = max(pChannel->mNumScalingKeys, pChannel->mNumRotationKeys);
	m_iNumKeyFrames = max(pChannel->mNumPositionKeys, m_iNumKeyFrames);

	_float3		vScale;
	_float4		vRotation;
	_float3		vPosition;

	for (size_t i = 0; i < m_iNumKeyFrames; i++)
	{
		KEYFRAME			KeyFrame = {};

		if (i < pChannel->mNumScalingKeys)
		{
			memcpy(&vScale, &pChannel->mScalingKeys[i].mValue, sizeof(_float3));
			KeyFrame.fTrackPosition = pChannel->mScalingKeys[i].mTime;
		}
		if (i < pChannel->mNumRotationKeys)
		{
			// memcpy(&vRotation, &pChannel->mRotationKeys[i].mValue, sizeof(_float4));
			vRotation.x = pChannel->mRotationKeys[i].mValue.x;
			vRotation.y = pChannel->mRotationKeys[i].mValue.y;
			vRotation.z = pChannel->mRotationKeys[i].mValue.z;
			vRotation.w = pChannel->mRotationKeys[i].mValue.w;
			KeyFrame.fTrackPosition = pChannel->mRotationKeys[i].mTime;
		}
		if (i < pChannel->mNumPositionKeys)
		{
			memcpy(&vPosition, &pChannel->mPositionKeys[i].mValue, sizeof(_float3));
			KeyFrame.fTrackPosition = pChannel->mPositionKeys[i].mTime;
		}

		KeyFrame.vScale = vScale;
		KeyFrame.vRotation = vRotation;
		KeyFrame.vPosition = vPosition;

		m_KeyFrames.push_back(KeyFrame);
	}

	ZeroMemory(&m_StartFrame, sizeof(m_StartFrame));
	ZeroMemory(&m_EndFrame, sizeof(m_EndFrame));

	return S_OK;
}

void CChannel::Invalidate_TransformationMatrix(_float fCurrentTrackPosition, const CModel::BONES& Bones, _uint* pCurrentKeyFrameIndex)
{
	if (0.0f == fCurrentTrackPosition)
		*pCurrentKeyFrameIndex = 0;

	//m_fCurrentTrackPosition = fCurrentTrackPosition;

	if (m_bTransition) 
	{
		Invalidate_TransformationMatrix_Transition(fCurrentTrackPosition, Bones);
	}
	else 
	{
		Invalidate_TransformationMatrix_Normal(fCurrentTrackPosition, Bones, pCurrentKeyFrameIndex);
	}


}

void CChannel::Invalidate_TransformationMatrix_Normal(_float fCurrentTrackPosition, const CModel::BONES& Bones, _uint* pCurrentKeyFrameIndex)
{
	_bool bIsNotEndKeyFrame = Update_KeyFrame(fCurrentTrackPosition, pCurrentKeyFrameIndex);

	_float	fRatio = Calc_Ratio(fCurrentTrackPosition);

	_matrix		TransformationMatrix;

	if (!bIsNotEndKeyFrame)
	{
		TransformationMatrix = Make_EndFrame_TransformationMatrix();
	}
	else 
	{
		TransformationMatrix = Make_TransformationMatrix(fRatio);
	}

	Bones[m_iBoneIndex]->Set_TransformationMatrix(TransformationMatrix);

}

void CChannel::Invalidate_TransformationMatrix_Transition(_float fCurrentTrackPosition, const CModel::BONES& Bones)
{
	_float fRatio = Calc_Ratio(fCurrentTrackPosition);

	_matrix		TransformationMatrix;

	_bool bIsEnd = (1.0f <= fRatio);

	if (bIsEnd)
	{
		m_bTransition = false;
	}

	TransformationMatrix = Make_TransformationMatrix(fRatio);
	
	Bones[m_iBoneIndex]->Set_TransformationMatrix(TransformationMatrix);
}

void CChannel::Reset_Channel(_float fCurrentTrackPosition, const CModel::BONES& Bones, _uint* pCurrentKeyFrameIndex)
{
	m_bTransition = false;
	//Invalidate_TransformationMatrix(fCurrentTrackPosition, Bones, pCurrentKeyFrameIndex);
}


_bool CChannel::Update_KeyFrame(_float fCurrentTrackPosition, _uint* pCurrentKeyFrameIndex)
{
	KEYFRAME	LastKeyFrame = m_KeyFrames.back();
	if (fCurrentTrackPosition >= LastKeyFrame.fTrackPosition)
	{
		m_StartFrame = m_EndFrame = m_KeyFrames.back();
		return false;
	}
	else
	{
		while (fCurrentTrackPosition >= m_KeyFrames[*pCurrentKeyFrameIndex + 1].fTrackPosition)
			++* pCurrentKeyFrameIndex;

		m_StartFrame = m_KeyFrames[*pCurrentKeyFrameIndex];
		m_EndFrame = m_KeyFrames[*pCurrentKeyFrameIndex + 1];
		return true;
	}
}

_float CChannel::Calc_Ratio(_float fCurrentTrackPosition)
{
	_float	fStart = m_StartFrame.fTrackPosition;
	_float	fNow = fCurrentTrackPosition;
	_float	fEnd = m_EndFrame.fTrackPosition;

	if (fEnd <= fStart)
		return 1.0f;

	return min(((fNow - fStart) / (fEnd - fStart)), 1);
}

void CChannel::Calc_Now_Transform(_vector& vScale, _vector& vRotation, _vector& vPosition, _float fRatio)
{
	_float3		vSourScale, vDestScale;
	_float4		vSourRotation, vDestRotation;
	_float3		vSourPosition, vDestPosition;

	vSourScale = m_StartFrame.vScale;
	vSourRotation = m_StartFrame.vRotation;
	vSourPosition = m_StartFrame.vPosition;

	vDestScale = m_EndFrame.vScale;
	vDestRotation = m_EndFrame.vRotation;
	vDestPosition = m_EndFrame.vPosition;

	vScale = XMVectorLerp(XMLoadFloat3(&vSourScale), XMLoadFloat3(&vDestScale), fRatio);
	vRotation = XMQuaternionSlerp(XMLoadFloat4(&vSourRotation), XMLoadFloat4(&vDestRotation), fRatio);
	vPosition = XMVectorLerp(XMLoadFloat3(&vSourPosition), XMLoadFloat3(&vDestPosition), fRatio);

}

_matrix CChannel::Make_TransformationMatrix(_float fRatio)
{
	_vector		vScale;
	_vector		vRotation;
	_vector		vPosition;

	Calc_Now_Transform(vScale, vRotation, vPosition, fRatio);

	_matrix		TransformationMatrix = XMMatrixAffineTransformation(vScale, XMVectorSet(0.f, 0.f, 0.f, 1.f), vRotation, vPosition);

	return TransformationMatrix;
}

_matrix CChannel::Make_EndFrame_TransformationMatrix()
{
	KEYFRAME	LastKeyFrame = m_KeyFrames.back();

	_vector		vScale;
	_vector		vRotation;
	_vector		vPosition;

	vScale		= XMLoadFloat3(&LastKeyFrame.vScale);
	vRotation	= XMLoadFloat4(&LastKeyFrame.vRotation);
	vPosition	= XMLoadFloat3(&LastKeyFrame.vPosition);

	_matrix		TransformationMatrix = XMMatrixAffineTransformation(vScale, XMVectorSet(0.f, 0.f, 0.f, 1.f), vRotation, vPosition);

	return TransformationMatrix;
}

KEYFRAME CChannel::Make_NowFrame(_float fCurrentTrackPosition)
{
	KEYFRAME result;

	_vector		vScale;
	_vector		vRotation;
	_vector		vPosition;
	_float		fRatio = Calc_Ratio(fCurrentTrackPosition);
	
	Calc_Now_Transform(vScale, vRotation, vPosition, fRatio);

	XMStoreFloat3(&result.vPosition, vPosition);
	XMStoreFloat4(&result.vRotation, vRotation);
	XMStoreFloat3(&result.vScale, vScale);

	return result;
}

void CChannel::Set_Transition(KEYFRAME _StartFrame, KEYFRAME _EndFrame, _float* _fTransitionDuration)
{
	m_bTransition = true;

	m_StartFrame.vPosition		= _StartFrame.vPosition;
	m_StartFrame.vRotation		= _StartFrame.vRotation;
	m_StartFrame.vScale			= _StartFrame.vScale;

	m_EndFrame.fTrackPosition	= _EndFrame.fTrackPosition;
	m_EndFrame.vPosition		= _EndFrame.vPosition;
	m_EndFrame.vRotation		= _EndFrame.vRotation;
	m_EndFrame.vScale			= _EndFrame.vScale;

	
	m_StartFrame.fTrackPosition = _EndFrame.fTrackPosition - *_fTransitionDuration;

	_bool test = false;
}



CChannel* CChannel::Create(const aiNodeAnim* pChannel, const CModel::BONES& Bones)
{
	CChannel* pInstance = new CChannel();

	if (FAILED(pInstance->Initialize(pChannel, Bones)))
	{
		MSG_BOX("Failed to Created : CChannel");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CChannel::Free()
{
}