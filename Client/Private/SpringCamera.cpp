#include "stdafx.h"
#include "SpringCamera.h"
#include "GameInstance.h"

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

	SPRING_CAMERA_DESC* pDesc = (SPRING_CAMERA_DESC)pArg;

	m_fMouseSensor = pDesc->fMouseSensor;

	if (FAILED(__super::Initialize(pDesc)))
		return E_FAIL;


	return S_OK;
}

void CSpringCamera::Priority_Tick(_float fTimeDelta)
{
}

void CSpringCamera::Tick(_float fTimeDelta)
{
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
