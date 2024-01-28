#include "Magician_Cane.h"
#include "GameInstance.h"
#include "Bone.h"

CMagician_Cane::CMagician_Cane(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CMagician_Weapon(pDevice, pContext)
{
}

CMagician_Cane::CMagician_Cane(const CMagician_Cane& rhs)
	: CMagician_Weapon(rhs)
{
}

HRESULT CMagician_Cane::Ready_Components_Origin(LEVEL eLevel)
{
	if (FAILED(__super::Ready_Components_Origin(eLevel)))
		return E_FAIL;

	/* For.Com_Model */
	
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Magician_Cane"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	
		/* For.Com_Collider */
	m_iColliderSize = 6;
	m_pColliders.resize(m_iColliderSize);
	//m_pColliders = new CCollider*[m_iColliderSize];

	for (_uint i = 0; i < m_iColliderSize; ++i)
	{
		CBounding_Sphere::BOUNDING_SPHERE_DESC BoundingDesc = {};

		_float fPosZ = 1.f / m_iColliderSize * (i + 1);

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
		BoundingDesc.fRadius = 1.f / m_iColliderSize;
		BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius / 2.f, fPosZ);
		XMStoreFloat3(&BoundingDesc.vCenter, vPos);

		const wstring strName = TEXT("Com_Collider_") + i;

		if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
			strName, reinterpret_cast<CComponent**>(&m_pColliders[i]), &BoundingDesc)))
			return E_FAIL;
	}
}
