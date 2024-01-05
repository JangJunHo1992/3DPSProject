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

		hDist = 5.f; //Z 축 카메라와 플레이어 거리
		vDist = 3.f; //Y 축 카메라와 플레이어 거리
		m_ptarget = dynamic_cast<CTransform*>(m_pGameInstance->Get_Player()->Get_TransformComp());
		ActualPosition = m_ptarget->Get_State(CTransform::STATE_POSITION) - XMVector3Normalize(m_ptarget->Get_State(CTransform::STATE_LOOK)) * hDist + XMVector3Normalize(m_ptarget->Get_State(CTransform::STATE_UP)) * vDist;
		m_pTransformCom->Set_Position(ActualPosition);
	}
	return S_OK;
}

void CSpringCamera::Priority_Tick(_float fTimeDelta)
{

}

void CSpringCamera::Tick(_float fTimeDelta)
{
	_float3 idealPosition = m_ptarget->Get_State(CTransform::STATE_POSITION);
	_float3 displacement = ActualPosition - idealPosition;
	_float3 SpringAccel = (-SpringConstant * displacement) - (DampConstant * Velocity);
	Velocity += SpringAccel * fTimeDelta;
	ActualPosition += Velocity * fTimeDelta ;

	m_pTransformCom->Set_Position(ActualPosition - XMVector3Normalize(m_ptarget->Get_State(CTransform::STATE_LOOK)) * hDist + XMVector3Normalize(m_ptarget->Get_State(CTransform::STATE_UP)) * vDist);


	_long	MouseMove = 0;

	if (MouseMove = m_pGameInstance->Get_DIMouseMove(DIMS_X))
	{
		m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), m_fMouseSensor * MouseMove * fTimeDelta);
	}

	if (MouseMove = m_pGameInstance->Get_DIMouseMove(DIMS_Y))
	{
		m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), m_fMouseSensor * MouseMove * fTimeDelta);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	__super::Tick(fTimeDelta);

	
	
}

void CSpringCamera::Late_Tick(_float fTimeDelta)
{
	

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
