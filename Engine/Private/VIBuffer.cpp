#include "VIBuffer.h"
#include "PipeLine.h"
#include "Picking.h"

CVIBuffer::CVIBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CComponent(pDevice, pContext)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
	: CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_BufferDesc(rhs.m_BufferDesc)
	, m_SubResourceData(rhs.m_SubResourceData)
	, m_iNumVertices(rhs.m_iNumVertices)
	, m_iStride(rhs.m_iStride)
	, m_iNumVertexBuffers(rhs.m_iNumVertexBuffers)
	, m_iNumIndices(rhs.m_iNumIndices)
	, m_iIndexStride(rhs.m_iIndexStride)
	, m_eIndexFormat(rhs.m_eIndexFormat)
	, m_eTopology(rhs.m_eTopology)
{


	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);
}

HRESULT CVIBuffer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Render()
{
	m_pContext->DrawIndexed(m_iNumIndices, 0, 0);

	return S_OK;
}

_bool CVIBuffer::Intersect(const _float4x4 _mWorld) const
{
	_float3 vOut;
	return Intersect(vOut, _mWorld);
}

_bool CVIBuffer::Intersect(_Out_ _float3& _vOut, _In_opt_ const _float4x4 _mWorld) const
{
	_bool bCollide = false;

	auto lambda = [this, &_vOut, _mWorld](auto* ptr)
	{
		_uint iNumPrimitive = m_eTopology == D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ? m_iNumIndices / 3 : 0;

		for (_uint iIndices = 0; iIndices < iNumPrimitive; ++iIndices)
		{
			for (_uint iIndex = 0; iIndex < 3; ++iIndex)
			{
				ptr[iIndex] = reinterpret_cast<decltype(ptr)>(m_pIndices.get())[iIndex + iIndices * 3];
			}
			if (CPicking::Get_Instance()->Intersect(_vOut, m_pVertices[ptr[0]], m_pVertices[ptr[1]], m_pVertices[ptr[2]], _mWorld))
			{
				return true;
			}
		}
		return false;
	};
	//스마트 포인트로 싹다 바꿔버리자! 
	return bCollide;
}

HRESULT CVIBuffer::Bind_VIBuffers()
{
	if (nullptr == m_pVB ||
		nullptr == m_pIB)
		return E_FAIL;

	ID3D11Buffer* pVertexBuffers[] = {
		m_pVB,
	};

	_uint				iStrides[] = {
		m_iStride,
	};

	_uint				iOffsets[] = {
		0,
	};


	/* 어떤 버텍스 버퍼들을 이용할거다. */
	m_pContext->IASetVertexBuffers(0, m_iNumVertexBuffers, pVertexBuffers, iStrides, iOffsets);

	/* 어떤 인덱스 버퍼를 이용할거다. */
	m_pContext->IASetIndexBuffer(m_pIB, m_eIndexFormat, 0);

	/* 정점을 어떤식으로 이어서 그릴거다. */
	m_pContext->IASetPrimitiveTopology(m_eTopology);

	///* 장치에게 내가 그릴려고하는 정점의 구성정보를 모두 보여준다. */
	///* DX9기준, 정점의 변환을 장치가 알아서 수행한다(고정기능렌더링파이플아ㅣㄴ)(.*/
	//m_pContext->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);




	return S_OK;
}

HRESULT CVIBuffer::Create_Buffer(_Inout_ ID3D11Buffer** ppBuffer)
{
	return m_pDevice->CreateBuffer(&m_BufferDesc, &m_SubResourceData, ppBuffer);
}


void CVIBuffer::Free()
{
	__super::Free();

	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}
