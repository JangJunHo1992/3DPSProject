#include "..\Public\Raider_Sword_02.h"

CRaider_Sword_02::CRaider_Sword_02(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider_Weapon(pDevice, pContext)
{
}

CRaider_Sword_02::CRaider_Sword_02(const CRaider_Sword_02& rhs)
	: CRaider_Weapon(rhs)
{
}

HRESULT CRaider_Sword_02::Ready_Components_Origin(LEVEL eLevel)
{
	if (FAILED(__super::Ready_Components_Origin(eLevel)))
		return E_FAIL;


	/* For.Com_Model */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Raider_Sword_02"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}
