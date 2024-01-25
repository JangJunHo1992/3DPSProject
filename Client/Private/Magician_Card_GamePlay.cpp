#include "Magician_Card_GamePlay.h"

#include "GameInstance.h"
#include "Character.h"
#include "VIBuffer_Dynamic_Plane.h"
CMagician_Card_GamePlay::CMagician_Card_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Card(pDevice, pContext)
{
}

CMagician_Card_GamePlay::CMagician_Card_GamePlay(const CMagician_Card_GamePlay& rhs)
	: CMagician_Card(rhs)
{
}

HRESULT CMagician_Card_GamePlay::Initialize_Prototype()
{
	return __super::Initialize_Prototype();
}

HRESULT CMagician_Card_GamePlay::Initialize(void* pArg)
{
	m_fLifeTime = 600.f;
	m_fAttackSpeed = 3.f;

	list<CGameObject*>* _pTargets = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));

	if (nullptr == _pTargets)
		return false;

	for (CGameObject* pGameObject : *_pTargets)
	{
		m_pPlayer = dynamic_cast<CCharacter*>(pGameObject);
		vPos= m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE_POSITION);
	}

// 	list<CGameObject*>* _pMTargets = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Monster"));
// 
// 	if (nullptr == _pMTargets)
// 		return false;
// 
// 	for (CGameObject* pGameObject : *_pMTargets)
// 	{
// 		m_pMonster = dynamic_cast<CCharacter*>(pGameObject);
// 		vmonPos=m_pMonster->Get_TransformComp()->Get_State(CTransform::STATE_POSITION);
// 	}

	return __super::Initialize(pArg);
}

void CMagician_Card_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CMagician_Card_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	
	Update_Ranged_Attack(fTimeDelta);

	

	Collision_Chcek();
}

void CMagician_Card_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);


	

}

HRESULT CMagician_Card_GamePlay::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	/* 이 셰ㅒ이더에 0번째 패스로 그릴꺼야. */
	m_pShaderCom->Begin(0);

	/* 내가 그릴려고하는 정점, 인덷ㄱ스버퍼를 장치에 바인딩해. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* 바인딩된 정점, 인덱스를 그려. */
	m_pVIBufferCom->Render();


	return __super::Render();
}

_bool CMagician_Card_GamePlay::Collision_Chcek()
{
	const wstring strLayerTag = TEXT("Layer_Player");

	_bool bIsCollision = false;
	CCharacter* pAlreadyHittedCharacter = nullptr;
	list<CGameObject*>* _pTargets = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, strLayerTag);

	if (nullptr == _pTargets)
		return false;

	for (CGameObject* pGameObject : *_pTargets)
	{

		CCharacter* pTarget = dynamic_cast<CCharacter*>(pGameObject);
		if (pTarget)
		{
			CCollider* pTargetCollider = pTarget->Get_Collider();
			if (nullptr == pTargetCollider && pTargetCollider != m_pColliderCom)
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

void CMagician_Card_GamePlay::Start_Ranged_Attack()
{
	m_vAttackDirection = vPos - m_vStartPos;
	XMVector3Normalize(m_vAttackDirection);
}

void CMagician_Card_GamePlay::Update_Ranged_Attack(_float fTimeDelta)
{
	_float fMoveDistance = m_fAttackSpeed * fTimeDelta * 0.01f;

	Start_Ranged_Attack();
	m_vStartPos += m_vAttackDirection * fMoveDistance;
	m_pTransformCom->Set_Position(m_vStartPos);
}

HRESULT CMagician_Card_GamePlay::Ready_Components()
{
	if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_Collider */
	CBounding_Sphere::BOUNDING_SPHERE_DESC		BoundingDesc = {};

	BoundingDesc.fRadius = { 0.1f };
	BoundingDesc.vCenter = m_vStartPos;
	

	if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_Collider_Sphere"),
		TEXT("Com_Collider"), reinterpret_cast<CComponent**>(&m_pColliderCom), &BoundingDesc)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_VIBuffer_Card"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;


	if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_Texture_Card"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	return S_OK;

}

CMagician_Card_GamePlay* CMagician_Card_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Card_GamePlay* pInstance = new CMagician_Card_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Card_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMagician_Card_GamePlay::Clone(void* pArg)
{
	CMagician_Card_GamePlay* pInstance = new CMagician_Card_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Card_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Card_GamePlay::Free()
{
	__super::Free();
}
