#include "stdafx.h"
#include "SpringCamera.h"
#include "GameInstance.h"
#include "GameObject.h"

CSpringCamera::CSpringCamera(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CCamera(pDevice,pContext)
{
}

CSpringCamera::CSpringCamera(const CSpringCamera& rhs)
	:CCamera(rhs)
{
}

HRESULT CSpringCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CSpringCamera::Initialize(void* pArg)
{
	m_sName = "Camera";
	m_sLayerTag = "Layer_Camera";

	if (nullptr == pArg)
		return E_FAIL;

	SPRING_CAMERA_DESC* pDesc = (SPRING_CAMERA_DESC*)pArg;

	m_fMouseSensor = pDesc->fMouseSensor;

	if (FAILED(__super::Initialize(pDesc)))
		return E_FAIL;
	{
		DampConstant = 2.f * sqrt(SpringConstant);

		hDist = 1.f; //Z 축 카메라와 플레이어 거리
		vDist = 1.f; //Y 축 카메라와 플레이어 거리
		m_CameraOffsetY = 3.f;
		m_CameraOffsetZ = -5.f;
		m_ptarget = dynamic_cast<CTransform*>(m_pGameInstance->Get_Player()->Get_TransformComp());
		ActualPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION)/* - XMVector3Normalize(m_ptarget->Get_State(CTransform::STATE_LOOK)) * hDist + XMVector3Normalize(m_ptarget->Get_State(CTransform::STATE_UP)) * vDist*/;
		//m_pTransformCom->Set_Position(ActualPosition);
	}
	return S_OK;
}

void CSpringCamera::Priority_Tick(_float fTimeDelta)
{

}

void CSpringCamera::Tick(_float fTimeDelta)
{
	//카메라 움직임은 Late_Tick에 있다!
	_float3 currentCameraPosition = ActualPosition;
	_float3 idealPosition = m_ptarget->Get_State(CTransform::STATE_POSITION);
	_float3 displacement = ActualPosition - idealPosition;
	_float3 SpringAccel = (-SpringConstant * displacement) - (DampConstant * Velocity);
	Velocity += SpringAccel * fTimeDelta;
	ActualPosition += Velocity * fTimeDelta ;
	_long	MouseMoveX = m_pGameInstance->Get_DIMouseMove(DIMS_X);
	_long	MouseMoveY = m_pGameInstance->Get_DIMouseMove(DIMS_Y);
	// 캐릭터 주위를 중심으로 하는 회전을 계산
	m_fAngle += m_fMouseSensor * MouseMoveX * fTimeDelta;
	m_fPitch += m_fMouseSensor * MouseMoveY * fTimeDelta;

	//pitch 각도 제한
	m_fPitch = max(-XM_PIDIV2, min(XM_PIDIV2, m_fPitch));

	// 회전 행렬 계산
	_matrix rotationMatrix = XMMatrixRotationRollPitchYaw(m_fPitch, m_fAngle, 0.0f);

	// 카메라 위치 보간
	currentCameraPosition.x = XMVectorGetX(XMVectorLerp(XMLoadFloat3(&currentCameraPosition), XMLoadFloat3(&idealPosition), 1.0f - expf(-CameraMoveSpeed * fTimeDelta)));
	currentCameraPosition.y = XMVectorGetY(XMVectorLerp(XMLoadFloat3(&currentCameraPosition), XMLoadFloat3(&idealPosition), 1.0f - expf(-CameraMoveSpeed * fTimeDelta)));
	currentCameraPosition.z = XMVectorGetZ(XMVectorLerp(XMLoadFloat3(&currentCameraPosition), XMLoadFloat3(&idealPosition), 1.0f - expf(-CameraMoveSpeed * fTimeDelta)));

	// 캐릭터 주위를 중심으로 하는 카메라 위치 계산
	XMVECTOR cameraOffset = XMVectorSet(m_CameraOffsetX, m_CameraOffsetY, m_CameraOffsetZ, 0.0f);  // 카메라의 초기 위치
	cameraOffset = XMVector3TransformCoord(cameraOffset, rotationMatrix);

	// 캐릭터의 위치 및 회전 적용
	m_pTransformCom->Set_WorldMatrix(rotationMatrix * XMMatrixTranslationFromVector(ActualPosition));
	m_pTransformCom->Set_Position(currentCameraPosition + cameraOffset * hDist);

	__super::Tick(fTimeDelta);

	
	
}

void CSpringCamera::Late_Tick(_float fTimeDelta)
{
	// 카메라가 플레이어랑 같이 Tick에서 위치 계산하고 움직임까지 넣어버리면 화면이 덜덜거림
	//그래서 움직임 코드는 Late_Tick에다가 넣어줬음! 
	_long	MouseMoveX = m_pGameInstance->Get_DIMouseMove(DIMS_X);
	_long	MouseMoveY = m_pGameInstance->Get_DIMouseMove(DIMS_Y);

	if (MouseMoveX != 0)
	{
		m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), m_fMouseSensor * MouseMoveX * fTimeDelta);
	}

	if (MouseMoveY != 0)
	{
		m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), m_fMouseSensor * MouseMoveY * fTimeDelta);
	}

}

void CSpringCamera::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	__super::Write_Json(Out_Json);
}
//이함수는 실제 카메라의 위치와 타깃의 위치를 사용해서 카메라행렬을 계산한다
void CSpringCamera::CameraComputeMatrix()
{
// 	m_ptarget = m_pGameInstance->Get_Player();
// 	CTransform* pTarget = dynamic_cast<CTransform*>(m_ptarget->Get_TransformComp());
// 	//카메라의 방향은 실제 카메라의 위치에서 타깃의 위치로 향한다. 
// 	_float3 cameraForward = pTarget->Get_State(CTransform::STATE_POSITION)- ActualPosition;
// 	XMVector3Normalize(cameraForward);
// 	
// 	
// 	//외적을 사용해서 카메라의 왼쪽을 향하는 벡터를 계산한 뒤에 
// 	//카메라의 위쪽을 향하는 벡터를 계산한다.
// 	_float3 cameraLeft = XMVector3Cross(pTarget->Get_State(CTransform::STATE_UP), cameraForward);
// 	XMVector3Normalize(cameraLeft);
// 	_float3 cameraUp = XMVector3Cross(cameraForward, cameraLeft);
// 	XMVector3Normalize(cameraUp);
// 	
// // 	CreateLookAt에 카메라의 눈, 타깃의 위치, 위쪽을 가리키는 벡터를 전달한다.
// // 		cameraMatrix = m_pTransformCom->Look_At(pTarget->Get_State(CTransform::STATE_POSITION));
// 	
}

void CSpringCamera::CameraRotation()
{

}




CSpringCamera* CSpringCamera::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CSpringCamera* pInstance = new CSpringCamera(pDevice, pContext);
	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CSpringCamera");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CSpringCamera::Clone(void* pArg)
{
	CSpringCamera* pInstance = new CSpringCamera(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CSpringCamera");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSpringCamera::Free()
{
	__super::Free();
}
