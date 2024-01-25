#include "Magician_Card.h"
#include "Bone.h"
#include "GameInstance.h"
#include "Covus.h"
CMagician_Card::CMagician_Card(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{
}

CMagician_Card::CMagician_Card(const CMagician_Card& rhs)
	: CGameObject(rhs)
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
	
	list<CGameObject*>* playerList = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));
	m_pPlayer = dynamic_cast<CCharacter*>((*playerList).back());
	m_pGameInstance->Set_Player(m_pPlayer);

	vPos = m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE::STATE_POSITION);
	
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
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_Model */
// 	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Magician_Card"),
// 		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
// 		return E_FAIL;

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Magician_Card"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	/* For.Com_Collider */
	CBounding_Sphere::BOUNDING_SPHERE_DESC		BoundingDesc = {};

	BoundingDesc.fRadius = { 0.7f };
	BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius / 2.f, 0.f);

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
		TEXT("Com_Collider"), reinterpret_cast<CComponent**>(&m_pColliderCom), &BoundingDesc)))
		return E_FAIL;
	



	return S_OK;
}

HRESULT CMagician_Card::Bind_ShaderResources()
{
// 	if (FAILED(__super::Bind_ShaderResources()))
// 		return E_FAIL;
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->Bind_ShaderResources(m_pShaderCom, "g_Texture")))
		return E_FAIL;

	return S_OK;
}


void CMagician_Card::Free()
{

	__super::Free();

}

_bool CMagician_Card::Collision_Chcek()
{

	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;

	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));
	for (CGameObject* pGameObject : _Targets)
	{

		CCharacter* pTarget = dynamic_cast<CCharacter*>(pGameObject);
		
		if (pTarget)
		{
			CCollider* pTargetCollider = pTarget->Get_Collider();
			if (nullptr == pTargetCollider)
				continue;

		
			_bool isCollision = m_pColliderCom->Collision(pTargetCollider);
			if (isCollision)
			{
				if (pTarget->Get_Parry() == false)
				{
					pTarget->Set_Hitted();
					Set_isdead(true);

				}
				pAlreadyHittedCharacter = pTarget;
				bIsCollision = true;
				break;
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
	_float fMoveDistance = m_fAttackSpeed * fTimeDelta;
	
	Start_Ranged_Attack(vPos);
	// 이동할 거리만큼 현재 위치 업데이트
	Set_Position(m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_vAttackDirection * fMoveDistance);

		
	
}
