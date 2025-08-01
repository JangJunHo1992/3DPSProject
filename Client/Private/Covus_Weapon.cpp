#include "Covus_Weapon.h"
#include "Bone.h"
#include "Character.h"
#include "GameInstance.h"

CCovus_Weapon::CCovus_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWeapon_Client(pDevice, pContext)
{
}

CCovus_Weapon::CCovus_Weapon(const CCovus_Weapon& rhs)
	: CWeapon_Client(rhs)
	
{
}


HRESULT CCovus_Weapon::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype())) {
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CCovus_Weapon::Initialize(void* pArg)
{
	m_iCurrentLevel = m_pGameInstance->Get_NextLevel();
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CCovus_Weapon::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CCovus_Weapon::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	
	switch (m_iCurrentLevel)
	{
	case 2:
		Collision_Chcek();	
		break;
	case 6:
		Collision_Chcekb1();
		break;
	case 7:
		Collision_Chcekb2();
		break;
	}

}

void CCovus_Weapon::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CCovus_Weapon::Render()
{
	if (FAILED(__super::Render())) {
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CCovus_Weapon::Ready_Components_Origin(LEVEL eLevel)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Covus_Weapon"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;


	/* For.Com_Collider */
	m_iColliderSize = 10;
	m_pColliders.resize(m_iColliderSize);
	//m_pColliders = new CCollider*[m_iColliderSize];

	for (_uint i = 0; i < m_iColliderSize; ++i)
	{
		CBounding_Sphere::BOUNDING_SPHERE_DESC BoundingDesc = {};

		_float fPosZ = 1.2f / m_iColliderSize * (i + 1);
// 		_float fRadiusX = 180.f;
// 		_float fRadiusY = 90.f;
// 		_float fRadiusZ = 180.f;

		_matrix SocketMatrix
			= m_pSocketBone->Get_CombinedTransformationMatrix();
// 			* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ))
// 			* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
// 			* XMMatrixRotationY(XMConvertToRadians(fRadiusY));

		_vector vPos = XMVector3TransformCoord(
			XMLoadFloat3(&_float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ))
			, SocketMatrix
		);
		BoundingDesc.fRadius = 1.2f / m_iColliderSize;
		BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ);
		XMStoreFloat3(&BoundingDesc.vCenter, vPos);
		const wstring strName = TEXT("Com_Collider_") + i;

		if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
			strName, reinterpret_cast<CComponent**>(&m_pColliders[i]), &BoundingDesc)))
			return E_FAIL;
	}



	return S_OK;
}

HRESULT CCovus_Weapon::Bind_ShaderResources()
{
	if (FAILED(__super::Bind_ShaderResources()))
		return E_FAIL;

	return S_OK;
}


void CCovus_Weapon::Free()
{
	__super::Free();
}

_bool CCovus_Weapon::Collision_Chcek()//_uint eLevel
{
	if (false == m_bIsAttack)
		return false;

	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;
	_uint eLevel = m_pGameInstance->Get_NextLevel();
	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));
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
					pTarget->Set_Hitted();
					pAlreadyHittedCharacter = pTarget;
					bIsCollision = true;
					Set_IsAttack(false);
					break;
				}
			}
		}
	}


	return bIsCollision;
}

_bool CCovus_Weapon::Collision_Chcekb1()
{
	if (false == m_bIsAttack)
		return false;

	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;
	_uint eLevel = m_pGameInstance->Get_NextLevel();
	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(LEVEL_BOSS1, TEXT("Layer_Monster"));
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
					pTarget->Set_Hitted();
					pAlreadyHittedCharacter = pTarget;
					bIsCollision = true;
					Set_IsAttack(false);
					break;
				}
			}
		}
	}


	return bIsCollision;
}

_bool CCovus_Weapon::Collision_Chcekb2()
{
	if (false == m_bIsAttack)
		return false;

	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;
	
	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Monster"));
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
					pTarget->Set_Hitted();
					pAlreadyHittedCharacter = pTarget;
					bIsCollision = true;
					Set_IsAttack(false);
					break;
				}
			}
		}
	}


	return bIsCollision;
}
