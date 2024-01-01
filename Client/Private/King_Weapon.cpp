#include "..\Public\King_Weapon.h"

#include "GameInstance.h"

CKing_Weapon::CKing_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWeapon_Client(pDevice, pContext)
{
}

CKing_Weapon::CKing_Weapon(const CKing_Weapon& rhs)
	: CWeapon_Client(rhs)
{
}


HRESULT CKing_Weapon::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype())) {
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CKing_Weapon::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CKing_Weapon::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CKing_Weapon::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CKing_Weapon::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CKing_Weapon::Render()
{
	if (FAILED(__super::Render())) {
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CKing_Weapon::Ready_Components_Origin(LEVEL eLevel)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_King_Weapon"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;


	return S_OK;
}

HRESULT CKing_Weapon::Bind_ShaderResources()
{
	if (FAILED(__super::Bind_ShaderResources()))
		return E_FAIL;

	return S_OK;
}


void CKing_Weapon::Free()
{
	__super::Free();
}

Engine::_bool CKing_Weapon::Collision_Chcek()
{
	return false;
}
