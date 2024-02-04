#include "Varg_Weapon.h"
#include "Bone.h"
#include "Character.h"
#include "GameInstance.h"
#include "Effect_Monster_Trail.h"

CVarg_Weapon::CVarg_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWeapon_Client(pDevice, pContext)
{
}

CVarg_Weapon::CVarg_Weapon(const CVarg_Weapon& rhs)
	: CWeapon_Client(rhs)
{
}


HRESULT CVarg_Weapon::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype())) {
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CVarg_Weapon::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	TRAIL_DESC TrailDesc;
	ZeroMemory(&TrailDesc, sizeof(TRAIL_DESC));

	TrailDesc.iMaxCnt = 16;
	TrailDesc.vPos_0 = _float3(0.f, 0.f, 0.f);
	TrailDesc.vPos_1 = _float3(0.f, 0.f, 2.5f);

	
	
	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_BOSS1, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Monster_Trail"), &TrailDesc)))
		return E_FAIL;

	m_pMonsterTrailDiffuse = dynamic_cast<CEffect_Monster_Trail*>(m_pGameInstance->Get_GameObjects(LEVEL_BOSS1, TEXT("Layer_Effect"))->back());

	if (nullptr == m_pMonsterTrailDiffuse)
		return E_FAIL;

	m_pMonsterTrailDiffuse->Set_OwnerDesc(m_WorldMatrix);
	//m_pMonsterTrailDiffuse->Set_TextureIndex(1, 693, 0);
	m_pMonsterTrailDiffuse->Set_Use(true);
	


	return S_OK;
}

void CVarg_Weapon::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CVarg_Weapon::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	Collision_Chcek();

}

void CVarg_Weapon::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CVarg_Weapon::Render()
{
	if (FAILED(__super::Render())) {
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CVarg_Weapon::Ready_Components_Origin(LEVEL eLevel)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Varg_Weapon"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;


	/* For.Com_Collider */
	m_iColliderSize = 12;
	m_pColliders.resize(m_iColliderSize);
	//m_pColliders = new CCollider*[m_iColliderSize];

	for (_uint i = 0; i < m_iColliderSize; ++i)
	{
		CBounding_Sphere::BOUNDING_SPHERE_DESC BoundingDesc = {};

		_float fPosZ = 2.5f / m_iColliderSize * (i + 1);

		_float fRadiusX = 180.0f;
		_float fRadiusY = 180.0f;
		_float fRadiusZ = 90.0f;

		_matrix SocketMatrix
			= m_pSocketBone->Get_CombinedTransformationMatrix()
			* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
			* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));
			

		_vector vPos = XMVector3TransformCoord(
			XMLoadFloat3(&_float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ))
			, SocketMatrix
		);
		BoundingDesc.fRadius = 2.5f / m_iColliderSize;
		BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ);
		XMStoreFloat3(&BoundingDesc.vCenter, vPos);
		const wstring strName = TEXT("Com_Collider_") + i;

		if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
			strName, reinterpret_cast<CComponent**>(&m_pColliders[i]), &BoundingDesc)))
			return E_FAIL;
	}



	return S_OK;
}

HRESULT CVarg_Weapon::Bind_ShaderResources()
{
	if (FAILED(__super::Bind_ShaderResources()))
		return E_FAIL;

	return S_OK;
}


void CVarg_Weapon::Free()
{

	__super::Free();

}

_bool CVarg_Weapon::Collision_Chcek()
{
	if (false == m_bIsAttack)
		return false;

	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;

	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(LEVEL_BOSS1, TEXT("Layer_Player"));
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
				if (isCollision && pTarget->Get_HasBeenHit() == false)
				{
					if (pTarget->Get_Parry() == false)
					{
						pTarget->Set_Hitted();
					}

					pAlreadyHittedCharacter = pTarget;
					bIsCollision = true;
					pTarget->Set_HasBeenHit(true);
					Set_IsAttack(false);
					return bIsCollision;

				}
			}
		}
	}


	return bIsCollision;
}
