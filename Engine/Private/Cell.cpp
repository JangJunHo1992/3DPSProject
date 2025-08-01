#include "..\Public\Cell.h"
#include "Shader.h"
#include "VIBuffer_Cell.h"

CCell::CCell(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: m_pDevice(pDevice)
	, m_pContext(pContext)

{
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);


}

HRESULT CCell::Initialize(const _float3* pPoints, _uint iIndex)
{
	memcpy(m_vPoints, pPoints, sizeof(_float3) * POINT_END);

	m_iIndex = iIndex;

	_vector		vLine = XMLoadFloat3(&m_vPoints[POINT_B]) - XMLoadFloat3(&m_vPoints[POINT_A]);
	XMStoreFloat3(&m_vNormals[LINE_AB], XMVectorSet(XMVectorGetZ(vLine) * -1.f, 0.f, XMVectorGetX(vLine), 0.f));

	vLine = XMLoadFloat3(&m_vPoints[POINT_C]) - XMLoadFloat3(&m_vPoints[POINT_B]);
	XMStoreFloat3(&m_vNormals[LINE_BC], XMVectorSet(XMVectorGetZ(vLine) * -1.f, 0.f, XMVectorGetX(vLine), 0.f));

	vLine = XMLoadFloat3(&m_vPoints[POINT_A]) - XMLoadFloat3(&m_vPoints[POINT_C]);
	XMStoreFloat3(&m_vNormals[LINE_CA], XMVectorSet(XMVectorGetZ(vLine) * -1.f, 0.f, XMVectorGetX(vLine), 0.f));

#ifdef _DEBUG


	m_pVIBuffer = CVIBuffer_Cell::Create(m_pDevice, m_pContext, pPoints);
	if (nullptr == m_pVIBuffer)
		return E_FAIL;
#endif

	return S_OK;
}

_bool CCell::Compare_Points(const _float3* pSourPoint, const _float3* pDestPoint)
{
	if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_A]), XMLoadFloat3(pSourPoint)))
	{
		if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_B]), XMLoadFloat3(pDestPoint)))
			return true;

		if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_C]), XMLoadFloat3(pDestPoint)))
			return true;
	}
	if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_B]), XMLoadFloat3(pSourPoint)))
	{
		if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_C]), XMLoadFloat3(pDestPoint)))
			return true;

		if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_A]), XMLoadFloat3(pDestPoint)))
			return true;
	}
	if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_C]), XMLoadFloat3(pSourPoint)))
	{
		if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_A]), XMLoadFloat3(pDestPoint)))
			return true;

		if (true == XMVector3Equal(XMLoadFloat3(&m_vPoints[POINT_B]), XMLoadFloat3(pDestPoint)))
			return true;
	}

	return false;
}

_bool CCell::isIn(_fvector vPosition, _fmatrix WorldMatrix, _int* pNeighborIndex)
{
	for (size_t i = 0; i < LINE_END; i++)
	{
		_vector	vStartPoint = XMVector3TransformCoord(XMLoadFloat3(&m_vPoints[i]), WorldMatrix);
		_vector	vNormal = XMVector3TransformNormal(XMLoadFloat3(&m_vNormals[i]), WorldMatrix);

		_vector	vSourDir = vPosition - vStartPoint;

		if (0 < XMVectorGetX(XMVector3Dot(XMVector3Normalize(vSourDir),
			XMVector3Normalize(vNormal))))
		{
			*pNeighborIndex = m_iNeighbors[i];
			return false;
		}
	}

	return true;
}

void CCell::Update(_fmatrix WorldMatrix)
{

}

void CCell::Write_Cell(HANDLE& hFile, _ulong dwByte)
{
	if (0 == hFile)
		return;

	WriteFile(hFile, m_vPoints, sizeof(_float3) * 3, &dwByte, nullptr);
}

_float CCell::Calc_Height(_fvector vPosition)
{
	_float3 vPos;
	XMStoreFloat3(&vPos, vPosition);

	_vector   vPlane = XMPlaneFromPoints(
		m_vPoints[0]
		, m_vPoints[1]
		, m_vPoints[2]
	);

	_float4 Plane;
	XMStoreFloat4(&Plane, vPlane);

	return (-Plane.x * vPos.x - Plane.z * vPos.z - Plane.w) / Plane.y;
}

_bool CCell::Has_Point(_uint iPointIndex)
{
	for (_uint iIndex : m_ChildIndexes)
	{
		if (iIndex == iPointIndex)
		{
			return true;
		}
	}
	return false;
}

#ifdef _DEBUG

HRESULT CCell::Render(class CShader* pShader)
{


	m_pVIBuffer->Bind_VIBuffers();

	m_pVIBuffer->Render();

	return S_OK;

}
#endif


CCell* CCell::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _float3* pPoints, _uint iIndex)
{
	CCell* pInstance = new CCell(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pPoints, iIndex)))
	{
		MSG_BOX("Failed to Created : CCell");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CCell::Free()
{
#ifdef _DEBUG	
	Safe_Release(m_pVIBuffer);
#endif	

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}
