#include "Transform.h"
#include "Shader.h"
#include "Navigation.h"

CTransform::CTransform(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CComponent(pDevice,pContext)
{
}

CTransform::CTransform(const CTransform& rhs)
	: CComponent(rhs)
{
}

void CTransform::Set_Scaling(_float fScaleX, _float fScaleY, _float fScaleZ)
{
	Set_State(STATE_RIGHT, XMVector3Normalize(Get_State(CTransform::STATE_RIGHT)) * fScaleX);
	Set_State(STATE_UP, XMVector3Normalize(Get_State(CTransform::STATE_UP)) * fScaleY);
	Set_State(STATE_LOOK, XMVector3Normalize(Get_State(CTransform::STATE_LOOK)) * fScaleZ);
}

HRESULT CTransform::Initialize_Prototype(_float fSpeedPerSec, _float fRotationPerSec)
{
	m_fSpeedPerSec = fSpeedPerSec;
	m_fRotationPerSec = fRotationPerSec;

	XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());
	_matrix			matTmp;
	/*ex)
	matTmp = XMLoadFloat4x4(&m_WorldMatrix);*/


	/*_float3		vTmp = _float3(0.f, 0.f, 0.f);
	_float4		vTmp2 = _float4(0.f, 0.f, 0.f, 0.f);

	_vector		vTmp1 = XMVectorSet(0.f, 0.f, 0.f, 0.f);
	_vector		vTmp3 = XMVectorSet(0.f, 0.f, 0.f, 0.f);

	XMVector3Normalize(vTmp1);

	_float		fDot = XMVectorGetX(XMVector3Dot(vTmp1, vTmp3));

	_float		fLength = XMVectorGetX(XMVector3Length(vTmp1));

	XMStoreFloat3(&vTmp, vTmp1);
	XMStoreFloat4(&vTmp2, vTmp1);*/
	return S_OK;
}

void CTransform::Move_On_Navigation(_vector vMove, CNavigation* pNavigation)
{
	_vector	vPosition = Get_State(STATE_POSITION);

	vPosition += vMove;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}
	Set_State(STATE_POSITION, vPosition);
}

void CTransform::Go_Straight(_float fTimeDelta, class CNavigation* pNavigation)
{
	_vector vLook = Get_State(STATE_LOOK);
	vLook = XMVector3Normalize(vLook) * m_fSpeedPerSec * fTimeDelta;
	Move_On_Navigation(vLook, pNavigation);

	/*_vector	vPosition = Get_State(STATE_POSITION);
	_vector vLook = Get_State(STATE_LOOK);

	vPosition += XMVector3Normalize(vLook) * m_fSpeedPerSec * fTimeDelta;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION,vPosition);*/
}

void CTransform::Go_Straight_L45(_float fTimeDelta, CNavigation* pNavigation)
{
	_vector vLook = Get_State(STATE_LOOK);
	_vector vRight = Get_State(STATE_RIGHT);
	_vector vResult = XMVector3Normalize(vLook - vRight) * m_fSpeedPerSec * fTimeDelta;
	Move_On_Navigation(vResult, pNavigation);

	//_vector	vPosition = Get_State(STATE_POSITION);
	//_vector vLook = Get_State(STATE_LOOK);
	//_vector vRight = Get_State(STATE_RIGHT);

	//vPosition += XMVector3Normalize(vLook - vRight) * m_fSpeedPerSec * fTimeDelta;

	//if (nullptr != pNavigation)
	//{
	//	if (false == pNavigation->isMove(vPosition))
	//		return;
	//}

	//Set_State(STATE_POSITION, vPosition);
}

void CTransform::Go_Straight_R45(_float fTimeDelta, CNavigation* pNavigation)
{
	_vector vLook = Get_State(STATE_LOOK);
	_vector vRight = Get_State(STATE_RIGHT);
	_vector vResult = XMVector3Normalize(vLook + vRight) * m_fSpeedPerSec * fTimeDelta;
	Move_On_Navigation(vResult, pNavigation);


	/*_vector	vPosition = Get_State(STATE_POSITION);
	_vector vLook = Get_State(STATE_LOOK);
	_vector vRight = Get_State(STATE_RIGHT);

	vPosition += XMVector3Normalize(vLook + vRight) * m_fSpeedPerSec * fTimeDelta;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION, vPosition);*/
}

void CTransform::Go_Left(_float fTimeDelta, class CNavigation* pNavigation)
{
	_vector vRight = Get_State(STATE_RIGHT);
	_vector vResult = XMVector3Normalize(vRight) * m_fSpeedPerSec * fTimeDelta * -1;
	Move_On_Navigation(vResult, pNavigation);

	/*_vector vPosition = Get_State(STATE_POSITION);
	_vector vRight = Get_State(STATE_RIGHT);

	vPosition -= XMVector3Normalize(vRight) * m_fSpeedPerSec * fTimeDelta;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION, vPosition);*/

}

void CTransform::Go_Right(_float fTimeDelta, class CNavigation* pNavigation)
{
	_vector vRight = Get_State(STATE_RIGHT);
	_vector vResult = XMVector3Normalize(vRight) * m_fSpeedPerSec * fTimeDelta;
	Move_On_Navigation(vResult, pNavigation);

	/*_vector vPosition = Get_State(STATE_POSITION);
	_vector vRight = Get_State(STATE_RIGHT);

	vPosition += XMVector3Normalize(vRight) * m_fSpeedPerSec * fTimeDelta;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION, vPosition);*/
}

void CTransform::Knockback(_float fTimeDelta, CNavigation* pNavigation)
{
	_vector vLook = Get_State(STATE_LOOK);
	_vector vResult = XMVector3Normalize(vLook) * 2 * fTimeDelta * -1;
	Move_On_Navigation(vResult, pNavigation);

	/*_vector	vPosition = Get_State(STATE_POSITION);
	_vector vLook = Get_State(STATE_LOOK);

	vPosition -= XMVector3Normalize(vLook) * 2 * fTimeDelta;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION, vPosition);*/
}


void CTransform::Go_Backward(_float fTimeDelta, class CNavigation* pNavigation)
{
	_vector vLook = Get_State(STATE_LOOK);
	_vector vResult = XMVector3Normalize(vLook) * m_fSpeedPerSec * fTimeDelta * -1;
	Move_On_Navigation(vResult, pNavigation);

	/*_vector	vPosition = Get_State(STATE_POSITION);
	_vector vLook = Get_State(STATE_LOOK);

	vPosition -= XMVector3Normalize(vLook) * m_fSpeedPerSec * fTimeDelta;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION, vPosition);*/
}

void CTransform::Go_Backward_L45(_float fTimeDelta, CNavigation* pNavigation)
{
	_vector vLook = Get_State(STATE_LOOK);
	_vector vRight = Get_State(STATE_RIGHT);
	_vector vResult = XMVector3Normalize(vLook + vRight) * m_fSpeedPerSec * fTimeDelta * -1;
	Move_On_Navigation(vResult, pNavigation);

	/*_vector	vPosition = Get_State(STATE_POSITION);
	_vector vLook = Get_State(STATE_LOOK);
	_vector vRight = Get_State(STATE_RIGHT);

	vPosition -= XMVector3Normalize(vLook + vRight) * m_fSpeedPerSec * fTimeDelta;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION, vPosition);*/
}

void CTransform::Go_Backward_R45(_float fTimeDelta, CNavigation* pNavigation)
{
	_vector vLook = Get_State(STATE_LOOK);
	_vector vRight = Get_State(STATE_RIGHT);
	_vector vResult = XMVector3Normalize(vLook - vRight) * m_fSpeedPerSec * fTimeDelta * -1;
	Move_On_Navigation(vResult, pNavigation);

	/*_vector	vPosition = Get_State(STATE_POSITION);
	_vector vLook = Get_State(STATE_LOOK);
	_vector vRight = Get_State(STATE_RIGHT);

	vPosition -= XMVector3Normalize(vLook - vRight) * m_fSpeedPerSec * fTimeDelta;

	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION, vPosition);*/
}

void CTransform::Turn(_fvector vAxis, _float fTimeDelta)
{
	//이 함수는 동적으로 움직는 회전을 뜻하는 함수임 로테이션과 헷갈리지말것!
	_vector vRight =	Get_State(STATE_RIGHT);
	_vector vUp =		Get_State(STATE_UP);
	_vector vLook =		Get_State(STATE_LOOK);

	_matrix	RotationMatrix = XMMatrixRotationAxis(vAxis, m_fRotationPerSec * fTimeDelta);

	Set_State(CTransform::STATE_RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
	Set_State(CTransform::STATE_UP, XMVector3TransformNormal(vUp, RotationMatrix));
	Set_State(CTransform::STATE_LOOK, XMVector3TransformNormal(vLook, RotationMatrix));
}

void CTransform::Rotation(_fvector vAxis, _float fRadian)
{
	//이 함수는 정적으로 움직는 회전을 뜻하는 함수임 턴과 헷갈리지말것!
	_float3		vScale = Get_Scaled();

	_vector		vRight = XMVectorSet(1.f, 0.f, 0.f, 0.f) * vScale.x;
	_vector		vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f) * vScale.y;
	_vector		vLook = XMVectorSet(0.f, 0.f, 1.f, 0.f) * vScale.z;

	_matrix		RotationMatrix = XMMatrixRotationAxis(vAxis, fRadian);

	Set_State(CTransform::STATE_RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
	Set_State(CTransform::STATE_UP, XMVector3TransformNormal(vUp, RotationMatrix));
	Set_State(CTransform::STATE_LOOK, XMVector3TransformNormal(vLook, RotationMatrix));
}

void CTransform::Go_Target(_fvector vTargetPos, _float fTimeDelta, _float fSpare)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vDir = vTargetPos - vPosition;

	_float		fDistance = XMVectorGetX(XMVector3Length(vDir));

	if (fDistance >= fSpare)
		vPosition += XMVector3Normalize(vDir) * m_fSpeedPerSec * fTimeDelta;

	Set_State(STATE_POSITION, vPosition);
}

void CTransform::Look_At(_fvector vTargetPos)
{
	_float3		vScale = Get_Scaled();

	_vector		vPosition = Get_State(CTransform::STATE_POSITION);

	_vector		vLook = XMVector3Normalize(vTargetPos - vPosition) * vScale.z;
	_vector		vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook)) * vScale.x;
	_vector		vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight)) * vScale.y;

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);
}

void CTransform::Look_At_OnLand(_fvector vTargetPos)
{
	_float3		vScale = Get_Scaled();

	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vLook = vTargetPos - vPosition;

	_vector		vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook)) * vScale.x;

	vLook = XMVector3Normalize(XMVector3Cross(vRight, XMVectorSet(0.f, 1.f, 0.f, 0.f))) * vScale.z;

	_vector		vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f) * vScale.y;

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);
}

void CTransform::Look_At_Around(_fvector vTargetPos, _float fTimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vRotatedPosition = XMVector3TransformCoord(vTargetPos, Get_RotationMatrix(Get_WorldMatrix()));

	_float3		vPitchYawRoll = Extract_PitchYawRollFromRotationMatrix(Get_RotationMatrix(Get_WorldMatrix()));
	_vector		vPitchyawRollFromVector = XMLoadFloat3(&vPitchYawRoll);

	vPosition = XMVectorAdd(vPosition, vRotatedPosition  /*(In_bReverse ? -1.f : 1.f)*/);
	vPosition.m128_f32[3] = 1.f;
	
	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Add_RootBone_Position(const _float3& vPos, CNavigation* pNavigation)
{
	_vector vRootMove = XMVector3TransformNormal(XMLoadFloat3(&vPos), m_WorldMatrix);
	_vector vResult = vRootMove;
	Move_On_Navigation(vResult, pNavigation);

	/*_vector	vPosition = Get_State(STATE_POSITION);
	_vector vRootMove = XMVector3TransformNormal(XMLoadFloat3(&vPos), m_WorldMatrix);

	vPosition += vRootMove;


	if (nullptr != pNavigation)
	{
		if (false == pNavigation->isMove(vPosition))
			return;
	}

	Set_State(STATE_POSITION, vPosition);*/
}

_matrix CTransform::Get_RotationMatrix(FXMMATRIX Mat)
{
	_matrix ResultMat(XMMatrixIdentity());
	for (int i(0); i < 3; i++)
		ResultMat.r[i] = XMVector3Normalize(Mat.r[i]);

	return ResultMat;
}

_float3 CTransform::Extract_PitchYawRollFromRotationMatrix(FXMMATRIX Mat)
{
	XMFLOAT4X4 MatFrom4x4;
	XMStoreFloat4x4(&MatFrom4x4, Mat);

	float pitch(DirectX::XMScalarASin(-MatFrom4x4._32));

	DirectX::XMVECTOR from(DirectX::XMVectorSet(MatFrom4x4._12, MatFrom4x4._31, 0.f, 0.f));
	DirectX::XMVECTOR to(DirectX::XMVectorSet(MatFrom4x4._22, MatFrom4x4._33, 0.f, 0.f));
	DirectX::XMVECTOR res(DirectX::XMVectorATan2(from, to));

	float roll(DirectX::XMVectorGetX(res));
	float yaw(DirectX::XMVectorGetY(res));

	return XMFLOAT3(pitch, yaw, roll);
}

HRESULT CTransform::Bind_ShaderResource(CShader* pShader, const _char* pConstantName)
{
	return pShader->Bind_Matrix(pConstantName,&m_WorldMatrix);
}

void CTransform::Write_Json(json& Out_Json)
{
	//Out_Json.clear();

	Out_Json.emplace("Transform", m_WorldMatrix.m);
}

void CTransform::Load_FromJson(const json& In_Json)
{
	if (In_Json.find("Transform") == In_Json.end())
	{
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_WorldMatrix.m[i][j] = In_Json["Transform"][i][j];
		}
	}
}



CTransform* CTransform::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, _float fSpeedPerSec, _float fRotationPerSec)
{
	CTransform* pInstance = new CTransform(pDevice, pContext);

	//원형객체 초기화
	if (FAILED(pInstance->Initialize_Prototype(fSpeedPerSec,fRotationPerSec)))
	{
		MSG_BOX("Failed to Create : CTransform");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CTransform::Clone(void* pArg)
{
	CTransform* pInstance = new CTransform(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Create : CTransform");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTransform::Free()
{
	__super::Free();
}
