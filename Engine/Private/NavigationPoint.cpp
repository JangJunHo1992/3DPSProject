#include "..\Public\NavigationPoint.h"

#include "GameInstance.h"


CNavigationPoint::CNavigationPoint(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CNavigationPoint::CNavigationPoint(const CNavigationPoint& rhs)
	: CGameObject(rhs)
{
}


_bool CNavigationPoint::IsSelected(RAY ray)
{
	CBounding_Sphere* pBoundingBox = dynamic_cast<CBounding_Sphere*>(m_pColliderCom->Get_Bounding());
	if (nullptr == pBoundingBox)
		return false;

	const BoundingSphere* pBoundingSphere = pBoundingBox->Get_Bounding();

	_vector vOrigin = XMLoadFloat4(&ray.vPosition);
	_vector vDir = XMLoadFloat3(&ray.vDirection);
	_float fDist;

	_bool bResult = pBoundingSphere->Intersects(vOrigin, vDir, fDist);

	return bResult;
}

HRESULT CNavigationPoint::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CNavigationPoint::Initialize(void* pArg)
{
	{
		GAMEOBJECT_DESC Desc = {};
		if (FAILED(__super::Initialize(&Desc)))
			return E_FAIL;
	}


	NAVIGATION_POINT_DESC* Desc = reinterpret_cast<NAVIGATION_POINT_DESC*>(pArg);
	_float3 _vPos = Desc->vPos;
	_vector _vVecPos = XMLoadFloat3(&_vPos);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _vVecPos);


	/* For.Com_Collider */
	CBounding_Sphere::BOUNDING_SPHERE_DESC		BoundingDesc = {};

	BoundingDesc.fRadius = 0.5f;

	m_pColliderCom = CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE::TYPE_SPHERE);

	if (FAILED(m_pColliderCom->Initialize(&BoundingDesc)))
		return E_FAIL;

	return S_OK;
}

void CNavigationPoint::Priority_Tick(_float fTimeDelta)
{

}

void CNavigationPoint::Tick(_float fTimeDelta)
{
	m_pColliderCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CNavigationPoint::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
		return;
}


HRESULT CNavigationPoint::Render()
{

#ifdef _DEBUG
	if (nullptr == m_pColliderCom)
		return E_FAIL;

	m_pColliderCom->Render();
#endif

	return S_OK;
}

CNavigationPoint* CNavigationPoint::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, void* pArg)
{
	CNavigationPoint* pInstance = new CNavigationPoint(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CNavigationPoint");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CNavigationPoint* CNavigationPoint::Clone(void* pArg)
{
	CNavigationPoint* pInstance = new CNavigationPoint(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CNavigationPoint");
		Safe_Release(pInstance);
	}
	return pInstance;
}



void CNavigationPoint::Free()
{
	__super::Free();

	Safe_Release(m_pColliderCom);
}
