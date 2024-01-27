#include "Magician_Card.h"
#include "GameInstance.h"
#include "Bone.h"
#include "Character.h"
CMagician_Card::CMagician_Card(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CMagician_Weapon(pDevice, pContext)
{
}

CMagician_Card::CMagician_Card(const CMagician_Card& rhs)
	: CMagician_Weapon(rhs)
{
}

HRESULT CMagician_Card::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CMagician_Card::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	list<CGameObject*>* _pTargets = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));

	if (nullptr == _pTargets)
		return E_FAIL;

	for (CGameObject* pGameObject : *_pTargets)
	{
		CCharacter* m_pPlayer = dynamic_cast<CCharacter*>(pGameObject);
		m_vPlayerPos = m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE_POSITION);
	}


	m_pTransformCom->Look_At(m_vPlayerPos);


	return S_OK;
}

void CMagician_Card::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CMagician_Card::Tick(_float fTimeDelta)
{
	m_pTransformCom->Go_Straight(fTimeDelta*0.25);
	__super::Tick(fTimeDelta);
}

void CMagician_Card::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CMagician_Card::Render()
{
	//if (FAILED(__super::Render())) {
	//	return E_FAIL;
	//}

	return S_OK;
}



HRESULT CMagician_Card::Ready_Components_Origin(LEVEL eLevel)
{
	if (FAILED(__super::Ready_Components_Origin(eLevel)))
		return E_FAIL;

	/* For.Com_Model */

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Magician_Card"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;


	/* For.Com_Collider */
	m_iColliderSize = 1;
	m_pColliders.resize(m_iColliderSize);
	//m_pColliders = new CCollider*[m_iColliderSize];

	for (_uint i = 0; i < m_iColliderSize; ++i)
	{
		CBounding_Sphere::BOUNDING_SPHERE_DESC BoundingDesc = {};

		_float fPosZ = 1.2f / m_iColliderSize * (i + 1);

		_float fRadiusX = 180.f;
		_float fRadiusY = 90.f;
		_float fRadiusZ = 180.f;

		_matrix SocketMatrix
			= m_pSocketBone->Get_CombinedTransformationMatrix()
			* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ))
			* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
			* XMMatrixRotationY(XMConvertToRadians(fRadiusY));

		_vector vPos = XMVector3TransformCoord(
			XMLoadFloat3(&_float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ))
			, SocketMatrix
		);
		BoundingDesc.fRadius = 0.8f / m_iColliderSize;
		BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ);
		XMStoreFloat3(&BoundingDesc.vCenter, vPos);

		const wstring strName = TEXT("Com_Collider_") + i;

		if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
			strName, reinterpret_cast<CComponent**>(&m_pColliders[i]), &BoundingDesc)))
			return E_FAIL;
	}
}
