#include "Magician_Card.h"
#include "Bone.h"
#include "GameInstance.h"
#include "Covus.h"
CMagician_Card::CMagician_Card(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Weapon(pDevice, pContext)
{
}

CMagician_Card::CMagician_Card(const CMagician_Card& rhs)
	: CMagician_Weapon(rhs)
{
}


HRESULT CMagician_Card::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype())) {
		return E_FAIL;
	}
	m_fAttackSpeed = 5.f;

	return S_OK;
}

HRESULT CMagician_Card::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	
	list<CGameObject*>* _pTargets = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));

	if (nullptr == _pTargets)
		return false;

	for (CGameObject* pGameObject : *_pTargets)
	{
		m_pPlayer = dynamic_cast<CCharacter*>(pGameObject);
		vPos = m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE_POSITION);
	}
	
	return S_OK;
}

void CMagician_Card::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CMagician_Card::Tick(_float fTimeDelta)
{
	--CardCheckTime;

	__super::Tick(fTimeDelta);

	Update_Ranged_Attack(fTimeDelta);

	Collision_Chcek();

}

void CMagician_Card::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
	if (CardCheckTime == 0)
		Set_isdead(true);
}

HRESULT CMagician_Card::Render()
{
	if (FAILED(__super::Render())) {
		return E_FAIL;
	}

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
	



	return S_OK;
}

HRESULT CMagician_Card::Bind_ShaderResources()
{
	if (FAILED(__super::Bind_ShaderResources()))
		return E_FAIL;
	

	return S_OK;
}


void CMagician_Card::Free()
{

	__super::Free();

}

_bool CMagician_Card::Collision_Chcek()
{
	if (false == m_bIsAttack)
		return false;

	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;

	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));
	for (CGameObject* pGameObject : _Targets)
	{
		if (false == m_bIsAttack)
			break;
		CCharacter* pTarget = dynamic_cast<CCharacter*>(pGameObject);
		
		if (pTarget)
		{
			CCollider* pTargetCollider = pTarget->Get_Collider();
			if (nullptr == pTargetCollider)
				continue;

			for (CCollider* pCollider : m_pColliders)
			{
				_bool isCollision = pCollider->Collision(pTargetCollider);
				if (isCollision)
				{
					if (pTarget->Get_Parry() == false)
					{
						pTarget->Set_Hitted();
						Set_isdead(true);
						Set_IsAttack(false);

					}
					pAlreadyHittedCharacter = pTarget;
					bIsCollision = true;
					break;
				}
			}

		}
	}


	return bIsCollision;
}

void CMagician_Card::Start_Ranged_Attack(const _vector& vDirection)
{
	m_vAttackDirection = vDirection - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	XMVector3Normalize(m_vAttackDirection);
	
	
}

void CMagician_Card::Update_Ranged_Attack(_float fTimeDelta)
{
	// 원거리 공격 중일 때만 업데이트
	
	// 이동할 거리 계산
	_float fMoveDistance = m_fAttackSpeed * fTimeDelta * 0.01f;
	_float3 vCardPos = _float3(0.f, 0.f, 0.f);
	Start_Ranged_Attack(vPos);
	vCardPos += m_vAttackDirection * fMoveDistance;
	m_pTransformCom->Set_Position(m_pTransformCom->Get_Pos()+vCardPos);

		
	
}
