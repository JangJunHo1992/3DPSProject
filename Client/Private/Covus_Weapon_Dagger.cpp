#include "Covus_Weapon_Dagger.h"
#include "GameInstance.h"

CCovus_Weapon_Dagger::CCovus_Weapon_Dagger(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CCovus_Weapon(pDevice,pContext)
{
}

CCovus_Weapon_Dagger::CCovus_Weapon_Dagger(const CCovus_Weapon_Dagger& rhs)
	:CCovus_Weapon(rhs)
{
}

HRESULT CCovus_Weapon_Dagger::Ready_Components_Origin(LEVEL eLevel)
{
	if (FAILED(__super::Ready_Components_Origin(eLevel)))
		return E_FAIL;

	/* For.Com_Model */
	//if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Covus_Weapon_Dagger"),
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Covus_Weapon_Dagger"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	/* For.Com_Collider */
	m_iColliderSize = 12;
	m_pColliders.resize(m_iColliderSize);

	for (_uint i = 0; i < m_iColliderSize; ++i)
	{
		CBounding_Sphere::BOUNDING_SPHERE_DESC BoundingDesc = {};

		_float fPosZ = 1.2f / m_iColliderSize * (i + 1);

		BoundingDesc.fRadius = 1.2f / m_iColliderSize;
		BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ);

		const wstring strName = TEXT("Com_Collider_") + i;

		if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
			strName, reinterpret_cast<CComponent**>(&m_pColliders[i]), &BoundingDesc)))
			return E_FAIL;
	}
}
