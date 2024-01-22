#include "Covus_Weapon_Saber.h"
#include "GameInstance.h"
#include "Bone.h"

CCovus_Weapon_Saber::CCovus_Weapon_Saber(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CCovus_Weapon(pDevice, pContext)
{
}

CCovus_Weapon_Saber::CCovus_Weapon_Saber(const CCovus_Weapon_Saber& rhs)
	: CCovus_Weapon(rhs)
{
}

HRESULT CCovus_Weapon_Saber::Ready_Components_Origin(LEVEL eLevel)
{
	if (FAILED(__super::Ready_Components_Origin(eLevel)))
		return E_FAIL;

	/* For.Com_Model */
	//if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Covus_Weapon_Saber"),
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Covus_Weapon_Saber"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	/* For.Com_Collider */
	m_iColliderSize = 7;
	m_pColliders.resize(m_iColliderSize);

	for (_uint i = 0; i < m_iColliderSize; ++i)
	{
		CBounding_Sphere::BOUNDING_SPHERE_DESC BoundingDesc = {};

		_float fPosZ = 1.2f / m_iColliderSize * (i + 1);

		_float fRadiusX =90.0f;
		_float fRadiusY =0.0f;
		_float fRadiusZ =90.0f;

		_matrix SocketMatrix
			= m_pSocketBone->Get_CombinedTransformationMatrix()
			* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
			* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

		_vector vPos = XMVector3TransformCoord(
			XMLoadFloat3(&_float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ))
			, SocketMatrix);

		BoundingDesc.fRadius = 1.2f / m_iColliderSize;
		BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ);
		XMStoreFloat3(&BoundingDesc.vCenter, vPos);

		const wstring strName = TEXT("Com_Collider_") + i;

		if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
			strName, reinterpret_cast<CComponent**>(&m_pColliders[i]), &BoundingDesc)))
			return E_FAIL;
	}
}
