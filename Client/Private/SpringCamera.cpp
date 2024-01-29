#include "stdafx.h"
#include "SpringCamera.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Covus.h"
#include "Varg.h"
#include "Magician.h"

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

	m_CameraOffsetY = 2.f;
	m_CameraOffsetZ = -5.f;
	m_pPlayer = dynamic_cast<CCovus*>(m_pGameInstance->Get_Player());
	m_pVarg = dynamic_cast<CVarg*>(m_pGameInstance->Get_Player());
	m_pMagician = dynamic_cast<CMagician*>(m_pGameInstance->Get_Player());
	m_ptarget = dynamic_cast<CTransform*>(m_pPlayer->Get_TransformComp());

	_vector cameraOffset = XMVectorSet(m_CameraOffsetX, m_CameraOffsetY, m_CameraOffsetZ, 0.0f);
	

	if (nullptr == pArg)
		return E_FAIL;

	SPRING_CAMERA_DESC* pDesc = (SPRING_CAMERA_DESC*)pArg;

	m_fMouseSensor = pDesc->fMouseSensor;
	pDesc->vEye = m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE_POSITION)+cameraOffset;

	if (FAILED(__super::Initialize(pDesc)))
		return E_FAIL;

	{
		DampConstant = 2.f * sqrt(SpringConstant);

		hDist = 1.f; //Z 축 카메라와 플레이어 거리
		vDist = 1.f; //Y 축 카메라와 플레이어 거리
		//m_CameraOffsetX = 5.f;
		
		

		_vector vTargetPos = m_ptarget->Get_State(CTransform::STATE_POSITION);
		_matrix rotationMatrix = XMMatrixRotationRollPitchYaw(0.f, 0.0f, 0.0f);
		 // 카메라의 초기 위치
 		cameraOffset = XMVector3TransformCoord(cameraOffset, rotationMatrix);
		ActualPosition = vTargetPos + cameraOffset;//m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		m_pTransformCom->Set_WorldMatrix(m_pPlayer->Get_TransformComp()->Get_WorldMatrix());
		if (m_pPlayer->Get_CurrentLevel() == 2)
		{
//  			_matrix rotationMatrix = XMMatrixRotationRollPitchYaw(0.f, XM_PI, 0.0f);
// 	
//  			XMVECTOR cameraOffset = XMVectorSet(m_CameraOffsetX, m_CameraOffsetY, m_CameraOffsetZ, 0.0f);  // 카메라의 초기 위치
//  			cameraOffset = XMVector3TransformCoord(cameraOffset, rotationMatrix);
// 
// 			//최악의 경우수
// 			_vector Temp = XMVectorSet(141.805038f, -3.57046294f, -11.9469032f, 0.0f);
// 			m_pTransformCom->Set_Position(m_ptarget->Get_State(CTransform::STATE_POSITION) + cameraOffset * hDist);

			m_pPlayer = dynamic_cast<CCovus*>(m_pGameInstance->Get_Player());
			m_ptarget = dynamic_cast<CTransform*>(m_pGameInstance->Get_Player()->Get_TransformComp());
		}
		else if (m_pPlayer->Get_CurrentLevel() == 6)
		{
// 			_matrix rotationMatrix = XMMatrixRotationRollPitchYaw(0.f, XM_PI, 0.0f);
// 			m_pTransformCom->Set_WorldMatrix(rotationMatrix * XMMatrixTranslationFromVector(m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE_POSITION)));

			m_pPlayer = dynamic_cast<CCovus*>(m_pGameInstance->Get_Player());
			m_ptarget = dynamic_cast<CTransform*>(m_pGameInstance->Get_Player()->Get_TransformComp());
			list<CGameObject*>* monsterList = m_pGameInstance->Get_GameObjects(LEVEL_BOSS1, TEXT("Layer_Monster"));

			if (monsterList)
			{
				for (auto& pGameObject : *monsterList)
				{
					m_pVarg = dynamic_cast<CVarg*>(pGameObject);
					if (m_pVarg)
					{
						m_pVarg = dynamic_cast<CVarg*>(m_pGameInstance->Get_Varg());
					}
				}
			}
		}
		else if (m_pPlayer->Get_CurrentLevel() == 7)
		{
// 			_matrix rotationMatrix = XMMatrixRotationRollPitchYaw(0.f, XM_PI, 0.0f);
// 			m_pTransformCom->Set_WorldMatrix(rotationMatrix * XMMatrixTranslationFromVector(m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE_POSITION)));
			m_pPlayer = dynamic_cast<CCovus*>(m_pGameInstance->Get_Player());
			m_ptarget = dynamic_cast<CTransform*>(m_pGameInstance->Get_Player()->Get_TransformComp());
			list<CGameObject*>* monsterList = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Monster"));

			if (monsterList)
			{
				for (auto& pGameObject : *monsterList)
				{
					m_pMagician = dynamic_cast<CMagician*>(pGameObject);
					if (m_pVarg)
					{
						m_pMagician = dynamic_cast<CMagician*>(m_pGameInstance->Get_Magician());
					}
				}
			}
		}
	}
	ShowCursor(FALSE);
	return S_OK;
}

void CSpringCamera::Priority_Tick(_float fTimeDelta)
{


	
	if (Get_StartScene() == true)
	{
		m_pVarg = dynamic_cast<CVarg*>(m_pGameInstance->Get_Varg());
		m_ptarget = dynamic_cast<CTransform*>(m_pVarg->Get_TransformComp());
	}
	else if (Get_StartScene2() == true)
	{
		m_pMagician = dynamic_cast<CMagician*>(m_pGameInstance->Get_Magician());
		m_ptarget = dynamic_cast<CTransform*>(m_pMagician->Get_TransformComp());
	}
	else
	{
		m_pPlayer = dynamic_cast<CCovus*>(m_pGameInstance->Get_Player());

		m_ptarget = dynamic_cast<CTransform*>(m_pPlayer->Get_TransformComp());
	}
	
// 	m_pPlayer = dynamic_cast<CCovus*>(m_pGameInstance->Get_Player());
// 
// 	m_ptarget = dynamic_cast<CTransform*>(m_pGameInstance->Get_Player()->Get_TransformComp());
}

void CSpringCamera::Tick(_float fTimeDelta)
{
//  	if (m_bfirst)
// 	{
// 		_matrix rotationMatrix = XMMatrixRotationRollPitchYaw(0.f, XM_PI, 0.0f);
// 
// 		XMVECTOR cameraOffset = XMVectorSet(m_CameraOffsetX, m_CameraOffsetY, m_CameraOffsetZ, 0.0f);  // 카메라의 초기 위치
// 		cameraOffset = XMVector3TransformCoord(cameraOffset, rotationMatrix);
// 
// 		//최악의 경우수
// 		_float3 Temp = _float3(143.48080444335938f, -1.57047700881958f, -6.841729164123535f);
// 		//ActualPosition = Temp;
// 		m_pTransformCom->Set_Position(Temp);
// 		m_bfirst = false;
// 	}

	CameraRotation(fTimeDelta);
	//Player가 앞키를 누르면 카메라 회전했던 방향쪽에서 회전값을 받아서 카메라가 바라보고 있는 방향으로 플레이어도 쳐다 보게 만듬 
	if (true == m_pPlayer->Get_CheckRotatePlayer())
	{
		RotatePlayer();
	}

	if (m_pGameInstance->Get_DIKeyState(DIK_TAB))
	{
		
		if (m_bFix)
		{
			m_bFix = false;
			m_bCheck = false;
		}
		else
		{
			m_bFix = true;
			m_bCheck = true;
		}
	}
	if (m_bCheck == false)
		ShowCursor(FALSE);
	else
		ShowCursor(TRUE);
		

	if (false == m_bFix)
		return;
	if (true == m_bFix)
	{
		Mouse_Fix();
	}
	
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

// void CSpringCamera::Write_Json(json& Out_Json)
// {
// 	Out_Json["Name"] = m_sName;
// 	__super::Write_Json(Out_Json);
// }


void CSpringCamera::CameraRotation(_float fTimeDelta)
{
	//카메라 움직임은 Late_Tick에 있다!

	_float3 currentCameraPosition = ActualPosition;
	_float3 idealPosition = m_ptarget->Get_State(CTransform::STATE_POSITION);
	_float3 displacement = ActualPosition - idealPosition;
	_float3 SpringAccel = (-SpringConstant * displacement) - (DampConstant * Velocity);
	Velocity += SpringAccel * fTimeDelta;
	ActualPosition += Velocity * fTimeDelta;
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
	m_pTransformCom->Set_Position(ActualPosition + cameraOffset);
}



void CSpringCamera::RotatePlayer()
{
	_matrix rotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, m_fAngle, 0.0f);
	
	m_pPlayer->Set_CheckRotatePlayer(false);
	
	m_ptarget->Set_WorldMatrix(rotationMatrix* XMMatrixTranslationFromVector(m_ptarget->Get_State(CTransform::STATE_POSITION)));
}

void CSpringCamera::Mouse_Fix()
{
	POINT   pt{ g_iWinSizeX >> 1, g_iWinSizeY >> 1 };

	ClientToScreen(g_hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
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
