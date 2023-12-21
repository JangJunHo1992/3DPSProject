#include "VIBuffer_Dynamic_Plane.h"
#include "GameInstance.h"


CVIBuffer_Dynamic_Plane::CVIBuffer_Dynamic_Plane(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CVIBuffer_Dynamic_Terrain_Origin(pDevice, pContext)
{
}

CVIBuffer_Dynamic_Plane::CVIBuffer_Dynamic_Plane(const CVIBuffer_Dynamic_Plane& rhs)
	: CVIBuffer_Dynamic_Terrain_Origin(rhs)
	, m_iSizeX(rhs.m_iSizeX)
	, m_iSizeZ(rhs.m_iSizeZ)
{

}

HRESULT CVIBuffer_Dynamic_Plane::Initialize_Prototype()
{
	m_iNumVerticesX = m_iSizeX;
	m_iNumVerticesZ = m_iSizeZ;

	m_iNumVertexBuffers = 1;
	m_iNumVertices = m_iNumVerticesX * m_iNumVerticesZ;
	m_iStride = sizeof(VTXMESH);

	m_iNumIndices = (m_iNumVerticesX - 1) * (m_iNumVerticesZ - 1) * 2 * 3;
	m_iIndexStride = 4;// m_iNumVertices >= 65535 ? 4 : 2;
	m_eIndexFormat = DXGI_FORMAT_R32_UINT;//m_iIndexStride == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
	m_eTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


#pragma region VERTEX_BUFFER

	m_pVertices = new VTXMESH[m_iNumVertices];

	for (size_t i = 0; i < m_iNumVerticesZ; i++)
	{
		for (size_t j = 0; j < m_iNumVerticesX; j++)
		{
			_uint		iIndex = i * m_iNumVerticesX + j;

			/*		11111111 10010011 10010011 10010011

				&	00000000 00000000 00000000 11111111

					00000000 00000000 00000000 10010011*/

			m_pVertices[iIndex].vPosition = _float3(j, 0, i);
			m_pVertices[iIndex].vNormal = _float3(0.0f, 0.0f, 0.f);
			m_pVertices[iIndex].vTexcoord = _float2(j / (m_iNumVerticesX - 1.0f), i / (m_iNumVerticesZ - 1.0f));
			m_pVertices[iIndex].vTangent = _float3(1.f, 0.f, 0.f);

		}
	}

#pragma endregion

#pragma region INDEX_BUFFER

	ZeroMemory(&m_SubResourceData, sizeof m_SubResourceData);

	m_pIndices = new _uint[m_iNumIndices];

	_uint		iNumIndices = 0;

	for (size_t i = 0; i < m_iNumVerticesZ - 1; i++)
	{
		for (size_t j = 0; j < m_iNumVerticesX - 1; j++)
		{
			_uint		iIndex = i * m_iNumVerticesX + j;

			_uint		iIndices[4] = {
				iIndex + m_iNumVerticesX,
				iIndex + m_iNumVerticesX + 1,
				iIndex + 1,
				iIndex
			};

			_vector		vSourDir, vDestDir, vNormal;

			m_pIndices[iNumIndices++] = iIndices[0];
			m_pIndices[iNumIndices++] = iIndices[1];
			m_pIndices[iNumIndices++] = iIndices[2];

			vSourDir = XMLoadFloat3(&m_pVertices[iIndices[1]].vPosition) - XMLoadFloat3(&m_pVertices[iIndices[0]].vPosition);
			vDestDir = XMLoadFloat3(&m_pVertices[iIndices[2]].vPosition) - XMLoadFloat3(&m_pVertices[iIndices[1]].vPosition);
			vNormal = XMVector3Cross(vSourDir, vDestDir);

			vNormal = XMLoadFloat3(&m_pVertices[iIndices[0]].vNormal) + vNormal;
			XMStoreFloat3(&m_pVertices[iIndices[0]].vNormal, XMVector3Normalize(vNormal));

			vNormal = XMLoadFloat3(&m_pVertices[iIndices[1]].vNormal) + vNormal;
			XMStoreFloat3(&m_pVertices[iIndices[1]].vNormal, XMVector3Normalize(vNormal));

			vNormal = XMLoadFloat3(&m_pVertices[iIndices[2]].vNormal) + vNormal;
			XMStoreFloat3(&m_pVertices[iIndices[2]].vNormal, XMVector3Normalize(vNormal));

			m_pIndices[iNumIndices++] = iIndices[0];
			m_pIndices[iNumIndices++] = iIndices[2];
			m_pIndices[iNumIndices++] = iIndices[3];


			vSourDir = XMLoadFloat3(&m_pVertices[iIndices[2]].vPosition) - XMLoadFloat3(&m_pVertices[iIndices[0]].vPosition);
			vDestDir = XMLoadFloat3(&m_pVertices[iIndices[3]].vPosition) - XMLoadFloat3(&m_pVertices[iIndices[2]].vPosition);
			vNormal = XMVector3Cross(vSourDir, vDestDir);

			vNormal = XMLoadFloat3(&m_pVertices[iIndices[0]].vNormal) + vNormal;
			XMStoreFloat3(&m_pVertices[iIndices[0]].vNormal, XMVector3Normalize(vNormal));

			vNormal = XMLoadFloat3(&m_pVertices[iIndices[2]].vNormal) + vNormal;
			XMStoreFloat3(&m_pVertices[iIndices[2]].vNormal, XMVector3Normalize(vNormal));

			vNormal = XMLoadFloat3(&m_pVertices[iIndices[3]].vNormal) + vNormal;
			XMStoreFloat3(&m_pVertices[iIndices[3]].vNormal, XMVector3Normalize(vNormal));
		}
	}

#pragma endregion
	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);

	m_BufferDesc.ByteWidth = m_iStride * m_iNumVertices;
	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_BufferDesc.MiscFlags = 0;
	m_BufferDesc.StructureByteStride = m_iStride;

	ZeroMemory(&m_SubResourceData, sizeof m_SubResourceData);
	m_SubResourceData.pSysMem = m_pVertices;

	if (FAILED(__super::Create_Buffer(&m_pVB)))
		return E_FAIL;

	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
	m_BufferDesc.ByteWidth = m_iIndexStride * m_iNumIndices;
	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_BufferDesc.MiscFlags = 0;
	m_BufferDesc.StructureByteStride = 0;

	ZeroMemory(&m_SubResourceData, sizeof m_SubResourceData);
	m_SubResourceData.pSysMem = m_pIndices;

	if (FAILED(__super::Create_Buffer(&m_pIB)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer_Dynamic_Plane::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer_Dynamic_Plane::Set_Size(_ushort _iSizeX, _ushort _iSizeZ)
{
	m_iSizeX = _iSizeX;
	m_iSizeZ = _iSizeZ;
}


CVIBuffer_Dynamic_Plane* CVIBuffer_Dynamic_Plane::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, _ushort x, _ushort z)
{
	CVIBuffer_Dynamic_Plane* pInstance = new CVIBuffer_Dynamic_Plane(pDevice, pContext);
	pInstance->Set_Size(x, z);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Dynamic_Plane");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CVIBuffer_Dynamic_Plane::Clone(void* pArg)
{
	CVIBuffer_Dynamic_Plane* pInstance = new CVIBuffer_Dynamic_Plane(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CVIBuffer_Dynamic_Plane");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CVIBuffer_Dynamic_Plane::Free()
{
	__super::Free();
}
