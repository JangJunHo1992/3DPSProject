#include "VIBuffer_Dynamic_Terrain_Origin.h"
#include "GameInstance.h"


CVIBuffer_Dynamic_Terrain_Origin::CVIBuffer_Dynamic_Terrain_Origin(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CVIBuffer_Terrain(pDevice, pContext)
{
}

CVIBuffer_Dynamic_Terrain_Origin::CVIBuffer_Dynamic_Terrain_Origin(const CVIBuffer_Dynamic_Terrain_Origin& rhs)
	: CVIBuffer_Terrain(rhs)
	, m_pVertices(rhs.m_pVertices)
	, m_pIndices(rhs.m_pIndices)
{

}

HRESULT CVIBuffer_Dynamic_Terrain_Origin::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

_bool CVIBuffer_Dynamic_Terrain_Origin::Picking(RAY ray, _float3* out)
{
	_uint triNum = m_iNumIndices / 3;

	return m_pGameInstance->Picking_Vertex(ray, out, triNum, m_pVertices, m_pIndices);
}

void CVIBuffer_Dynamic_Terrain_Origin::Invalidate_Terrain(_vector _vMousePos, _float _fRadious, _float _fPower, _int _iMode)
{
	_float fInterval = 1.f;

	D3D11_MAPPED_SUBRESOURCE      SubResource;

	m_pContext->Map(m_pVB, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

	_float3 vPickedPos;
	XMStoreFloat3(&vPickedPos, _vMousePos);

	_int2   iPickIndex = { _int(_vMousePos.m128_f32[0] / fInterval), _int(_vMousePos.m128_f32[2] / fInterval) };
	_int   iRoundIndx = (_int)(_fRadious / fInterval);

	_int2   iBeginIndex, iEndIndex;
	iBeginIndex.x = (0 > iPickIndex.x - iRoundIndx) ? (0) : (iPickIndex.x - iRoundIndx);
	iBeginIndex.y = (0 > iPickIndex.y - iRoundIndx) ? (0) : (iPickIndex.y - iRoundIndx);

	iEndIndex.x = ((_int)m_iNumVerticesX < iPickIndex.x + iRoundIndx) ? (m_iNumVerticesX) : (iPickIndex.x + iRoundIndx);
	iEndIndex.y = ((_int)m_iNumVerticesZ < iPickIndex.y + iRoundIndx) ? (m_iNumVerticesZ) : (iPickIndex.y + iRoundIndx);

	for (_uint iZ(iBeginIndex.y); iZ < (_uint)iEndIndex.y; ++iZ)
	{
		for (_uint iX(iBeginIndex.x); iX < (_uint)iEndIndex.x; ++iX)
		{
			_ulong   iIndex = iZ * m_iNumVerticesX + iX;

			_float3 vPos = ((VTXMESH*)SubResource.pData)[iIndex].vPosition;
			_float  fLength = XMVectorGetX(XMVector3Length(XMLoadFloat3(&vPos) - _vMousePos));

			switch (_iMode)
			{
			case 0:
			{
				if (_fRadious < fLength)
					continue;

				((VTXMESH*)SubResource.pData)[iIndex].vPosition.y += _fPower;
				m_pVertices[iIndex].vPosition = ((VTXMESH*)SubResource.pData)[iIndex].vPosition;
			}
			break;
			case 1:
			{
				if (_fRadious < fLength)
					continue;

				_float fLerpPower = _fPower * (1.f - pow((fLength / _fRadious), 2.f));

				((VTXMESH*)SubResource.pData)[iIndex].vPosition.y += fLerpPower;
				m_pVertices[iIndex].vPosition = ((VTXMESH*)SubResource.pData)[iIndex].vPosition;
			}
			break;

			case 2:
			{
				((VTXMESH*)SubResource.pData)[iIndex].vPosition.y = _fPower;
				m_pVertices[iIndex].vPosition = ((VTXMESH*)SubResource.pData)[iIndex].vPosition;
			}
			break;
			}
		}
	}

	for (_uint iZ(iBeginIndex.y); iZ < (_uint)iEndIndex.y; ++iZ)
	{
		for (_uint iX(iBeginIndex.x); iX < (_uint)iEndIndex.x; ++iX)
		{
			_ulong   iIndex = iZ * m_iNumVerticesX + iX;

			_long  iAdjacency[] =
			{
				_long(iIndex + m_iNumVerticesX),   // 위
				_long(iIndex + 1),               // 오른쪽
				_long(iIndex - m_iNumVerticesX),   // 아래
				_long(iIndex - 1)               // 왼쪽
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



//CVIBuffer_Dynamic_Terrain_Origin* CVIBuffer_Dynamic_Terrain_Origin::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strHeightMapFilePath)
//{
//	CVIBuffer_Dynamic_Terrain_Origin* pInstance = new CVIBuffer_Dynamic_Terrain_Origin(pDevice, pContext);
//
//	/* 원형객체를 초기화한다.  */
//	if (FAILED(pInstance->Initialize_Prototype(strHeightMapFilePath)))
//	{
//		MSG_BOX("Failed to Created : CVIBuffer_Dynamic_Terrain_Origin");
//		Safe_Release(pInstance);
//	}
//	return pInstance;
//}
//
//CComponent* CVIBuffer_Dynamic_Terrain_Origin::Clone(void* pArg)
//{
//	CVIBuffer_Dynamic_Terrain_Origin* pInstance = new CVIBuffer_Dynamic_Terrain_Origin(*this);
//
//	/* 원형객체를 초기화한다.  */
//	if (FAILED(pInstance->Initialize(pArg)))
//	{
//		MSG_BOX("Failed to Cloned : CVIBuffer_Dynamic_Terrain_Origin");
//		Safe_Release(pInstance);
//	}
//	return pInstance;
//}


void CVIBuffer_Dynamic_Terrain_Origin::Free()
{
	if (false == m_isCloned)
	{
		Safe_Delete_Array(m_pIndices);
		Safe_Delete_Array(m_pVertices);
	}

	Safe_Release(m_pGameInstance);

	__super::Free();
}
