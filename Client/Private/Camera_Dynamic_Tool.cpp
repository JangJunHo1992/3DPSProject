#include "stdafx.h"
#include "Camera_Dynamic_Tool.h"
#include "GameInstance.h"


CCamera_Dynamic_Tool::CCamera_Dynamic_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCamera(pDevice, pContext)
{
}

CCamera_Dynamic_Tool::CCamera_Dynamic_Tool(const CCamera_Dynamic_Tool& rhs)
	: CCamera(rhs)
{
}

HRESULT CCamera_Dynamic_Tool::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera_Dynamic_Tool::Initialize(void* pArg)
{
	m_sName = "Camera";
	m_sLayerTag = "Layer_Camera";

	if (nullptr == pArg)
		return E_FAIL;

	DYNAMIC_CAMERA_DESC* pDesc = (DYNAMIC_CAMERA_DESC*)pArg;

	m_fMouseSensor = pDesc->fMouseSensor;

	if (FAILED(__super::Initialize(pDesc)))
		return E_FAIL;

	

	return S_OK;
}

void CCamera_Dynamic_Tool::Priority_Tick(_float fTimeDelta)
{
}

void CCamera_Dynamic_Tool::Tick(_float fTimeDelta)
{
	if (GetKeyState('A') & 0x8000)
	{
		m_pTransformCom->Go_Left(fTimeDelta);
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_pTransformCom->Go_Right(fTimeDelta);
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_pTransformCom->Go_Straight(fTimeDelta);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_pTransformCom->Go_Backward(fTimeDelta);
	}
	//마우스 회전//
	_long	MouseMove = 0;
	
	if (MouseMove = m_pGameInstance->Get_DIMouseState(DIM_RB))
	{
		if (MouseMove = m_pGameInstance->Get_DIMouseMove(DIMS_X))
		{
			m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), m_fMouseSensor * MouseMove * fTimeDelta);
		}

		if (MouseMove = m_pGameInstance->Get_DIMouseMove(DIMS_Y))
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), m_fMouseSensor * MouseMove * fTimeDelta);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	__super::Tick(fTimeDelta);
}

void CCamera_Dynamic_Tool::Late_Tick(_float fTimeDelta)
{
}

void CCamera_Dynamic_Tool::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	__super::Write_Json(Out_Json);
}

CCamera_Dynamic_Tool* CCamera_Dynamic_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCamera_Dynamic_Tool* pInstance = new CCamera_Dynamic_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCamera_Dynamic_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCamera_Dynamic_Tool::Clone(void* pArg)
{
	CCamera_Dynamic_Tool* pInstance = new CCamera_Dynamic_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCamera_Dynamic_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCamera_Dynamic_Tool::Free()
{
	__super::Free();

}