#include "VIBuffer_Dynamic_Terrain.h"
#include <DirectXCollision.h>

CVIBuffer_Dynamic_Terrain::CVIBuffer_Dynamic_Terrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CVIBuffer(pDevice, pContext)
{
}

CVIBuffer_Dynamic_Terrain::CVIBuffer_Dynamic_Terrain(const CVIBuffer_Dynamic_Terrain& rhs)
	: CVIBuffer(rhs)
	, m_pIndices(rhs.m_pIndices)
	, m_pVertices(rhs.m_pVertices)
	, m_iNumVerticesX(rhs.m_iNumVerticesX)
	, m_iNumVerticesZ(rhs.m_iNumVerticesZ)

	//, m_pPos(rhs.m_pPos)
{

}

HRESULT CVIBuffer_Dynamic_Terrain::Initialize_Prototype(const wstring& strHeightMapFilePath)
{
	_ulong		dwByte = 0;
	HANDLE		hFile = CreateFile(strHeightMapFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (0 == hFile)
		return E_FAIL;

	BITMAPFILEHEADER		fh;
	ReadFile(hFile, &fh, sizeof fh, &dwByte, nullptr);

	BITMAPINFOHEADER		ih;
	ReadFile(hFile, &ih, sizeof ih, &dwByte, nullptr);

	_ulong* pPixel = new _ulong[ih.biWidth * ih.biHeight];
	ReadFile(hFile, pPixel, sizeof(_ulong) * ih.biWidth * ih.biHeight, &dwByte, nullptr);

	CloseHandle(hFile);

	m_iNumVerticesX = ih.biWidth;
	m_iNumVerticesZ = ih.biHeight;

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

			m_pVertices[iIndex].vPosition = _float3(j, (pPixel[iIndex] & 0x000000ff) / 5.f, i);
			m_pVertices[iIndex].vNormal = _float3(0.0f, 0.0f, 0.f);
			m_pVertices[iIndex].vTexcoord = _float2(j / (m_iNumVerticesX - 1.0f), i / (m_iNumVerticesZ - 1.0f));
			m_pVertices[iIndex].vTangent = _float3(1.f, 0.f, 0.f);

		}
	}

	Safe_Delete_Array(pPixel);

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

HRESULT CVIBuffer_Dynamic_Terrain::Initialize(void* pArg)
{
	return S_OK;
}

_bool CVIBuffer_Dynamic_Terrain::Picking(RAY ray, _float3* out)
{
	_vector		vPickedPos;
	_vector		vVec0, vVec1, vVec2;


	_vector		vRayPos = XMLoadFloat4(&ray.vPosition);
	_vector		vRayDir = XMLoadFloat3(&ray.vDirection);
	_float		fDist = 0.f;


	_uint triNum = m_iNumIndices / 3;

	for (_uint i = 0; i < triNum / 3; ++i)
	{
		_int iStartIndex = i * 3;
		_float3 vVtxPos1 = m_pVertices[m_pIndices[iStartIndex + 0]].vPosition;
		_float3 vVtxPos2 = m_pVertices[m_pIndices[iStartIndex + 1]].vPosition;
		_float3 vVtxPos3 = m_pVertices[m_pIndices[iStartIndex + 2]].vPosition;

		vVec0 = XMLoadFloat3(&vVtxPos1);
		vVec1 = XMLoadFloat3(&vVtxPos2);
		vVec2 = XMLoadFloat3(&vVtxPos3);

		if (DirectX::TriangleTests::Intersects(
			vRayPos, vRayDir,
			vVec0, vVec1, vVec2,
			fDist))
		{
			vPickedPos = vRayPos + XMVector3Normalize(vRayDir) * fDist;
			XMStoreFloat3(out, vPickedPos);
			return true;
		}
	}
	return false;
}

void CVIBuffer_Dynamic_Terrain::Update_Terrain(_vector _vMousePos, _float _fRadious, _float _fPower)
{
	_float fInterval = 1.f;

	D3D11_MAPPED_SUBRESOURCE		SubResource;

	m_pContext->Map(m_pVB, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

	_float3 vPickedPos;
	XMStoreFloat3(&vPickedPos, _vMousePos);

	_int2	iPickIndex = { _int(_vMousePos.m128_f32[0] / fInterval), _int(_vMousePos.m128_f32[2] / fInterval) };
	_int	iRoundIndx = (_int)(_fRadious / fInterval);

	_int2	iBeginIndex, iEndIndex;
	iBeginIndex.x = (0 > iPickIndex.x - iRoundIndx) ? (0) : (iPickIndex.x - iRoundIndx);
	iBeginIndex.y = (0 > iPickIndex.y - iRoundIndx) ? (0) : (iPickIndex.y - iRoundIndx);

	iEndIndex.x = ((_int)m_iNumVerticesX < iPickIndex.x + iRoundIndx) ? (m_iNumVerticesX) : (iPickIndex.x + iRoundIndx);
	iEndIndex.y = ((_int)m_iNumVerticesZ < iPickIndex.y + iRoundIndx) ? (m_iNumVerticesZ) : (iPickIndex.y + iRoundIndx);

	for (_uint iZ(iBeginIndex.y); iZ < (_uint)iEndIndex.y; ++iZ)
	{
		for (_uint iX(iBeginIndex.x); iX < (_uint)iEndIndex.x; ++iX)
		{
			_ulong	iIndex = iZ * m_iNumVerticesX + iX;

			_float3 vPos = ((VTXMESH*)SubResource.pData)[iIndex].vPosition;
			_float  fLength = XMVectorGetX(XMVector3Length(XMLoadFloat3(&vPos) - _vMousePos));

			if (_fRadious < fLength)
				continue;

			_float fLerpPower = _fPower * (1.f - pow((fLength / _fRadious), 2.f));

			((VTXMESH*)SubResource.pData)[iIndex].vPosition.y += fLerpPower;
			m_pVertices[iIndex].vPosition = ((VTXMESH*)SubResource.pData)[iIndex].vPosition;

		}
	}

	for (_uint iZ(iBeginIndex.y); iZ < (_uint)iEndIndex.y; ++iZ)
	{
		for (_uint iX(iBeginIndex.x); iX < (_uint)iEndIndex.x; ++iX)
		{
			_ulong	iIndex = iZ * m_iNumVerticesX + iX;

			_long  iAdjacency[] =
			{
				_long(iIndex + m_iNumVerticesX),	// 위
				_long(iIndex + 1),					// 오른쪽
				_long(iIndex - m_iNumVerticesX),	// 아래
				_long(iIndex - 1)					// 왼쪽
			};

			if (0 == iX)
				iAdjacency[3] = -1;

			if (m_iNumVerticesX - 1 == iX)
				iAdjacency[1] = -1;

			if (0 == iZ)
				iAdjacency[2] = -1;

			if (m_iNumVerticesZ - 1 == iZ)
				iAdjacency[0] = -1;


			_float3 vNorm = m_pVertices[iIndex].vNormal;

			// 노말 벡터 계산
			_vector vComputeNorm = XMVectorSet(0.f, 0.f, 0.f, 0.f);

			for (_uint i = 0; i < 4; ++i)
			{
				_uint iNext = (3 == i) ? (0) : (i + 1);

				if (0 > iAdjacency[i] || 0 > iAdjacency[iNext])
					continue;

				_vector vLine_no1 = XMLoadFloat3(&m_pVertices[iAdjacency[i]].vPosition) - XMLoadFloat3(&m_pVertices[iIndex].vPosition);
				_vector vLine_no2 = XMLoadFloat3(&m_pVertices[iAdjacency[iNext]].vPosition) - XMLoadFloat3(&m_pVertices[iIndex].vPosition);
				_vector vLingNorm = XMVector3Normalize(XMVector3Cross(vLine_no1, vLine_no2));

				vComputeNorm = XMVector3Normalize(vComputeNorm + vLingNorm);
			}

			XMStoreFloat3(&vNorm, vComputeNorm);

			m_pVertices[iIndex].vNormal = vNorm;
			((VTXMESH*)SubResource.pData)[iIndex].vNormal = vNorm;

			if (0 > iAdjacency[1])
				continue;

			// 탄젠트 벡터 계산
			_float3 vTempTangent;
			XMStoreFloat3(&vTempTangent, XMVector3Normalize(XMLoadFloat3(&m_pVertices[iAdjacency[1]].vPosition) - XMLoadFloat3(&m_pVertices[iIndex].vPosition)));

			m_pVertices[iIndex].vTangent = vTempTangent;
			((VTXMESH*)SubResource.pData)[iIndex].vTangent = vTempTangent;
		}
	}

	m_pContext->Unmap(m_pVB, 0);

}

CVIBuffer_Dynamic_Terrain* CVIBuffer_Dynamic_Terrain::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strHeightMapFilePath)
{
	CVIBuffer_Dynamic_Terrain* pInstance = new CVIBuffer_Dynamic_Terrain(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype(strHeightMapFilePath)))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Dynamic_Terrain");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CVIBuffer_Dynamic_Terrain::Clone(void* pArg)
{
	CVIBuffer_Dynamic_Terrain* pInstance = new CVIBuffer_Dynamic_Terrain(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CVIBuffer_Dynamic_Terrain");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CVIBuffer_Dynamic_Terrain::Free()
{
	if (false == m_isCloned)
	{
		Safe_Delete_Array(m_pIndices);
		Safe_Delete_Array(m_pVertices);
	}




	__super::Free();
}
