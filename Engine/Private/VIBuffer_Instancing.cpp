#include "..\Public\VIBuffer_Instancing.h"

CVIBuffer_Instancing::CVIBuffer_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVIBuffer(pDevice, pContext)
{
}

CVIBuffer_Instancing::CVIBuffer_Instancing(const CVIBuffer_Instancing& rhs)
	: CVIBuffer(rhs)
	, m_iNumInstance(rhs.m_iNumInstance)
	, m_iInstanceStride(rhs.m_iInstanceStride)
	, m_iIndexCountPerInstance(rhs.m_iIndexCountPerInstance)
	, m_RandomNumber(rhs.m_RandomNumber)

	, m_pSpeeds(rhs.m_pSpeeds)
	//, m_pOrigianlSpeeds(rhs.m_pOrigianlSpeeds)
	//, m_pAccelerations(rhs.m_pAccelerations)
	, m_pLifeTimes(rhs.m_pLifeTimes)
	, m_InstancingDesc(rhs.m_InstancingDesc)
{
}

HRESULT CVIBuffer_Instancing::Initialize_Prototype()
{
	m_RandomNumber = mt19937_64(m_RandomDevice());

	return S_OK;
}

HRESULT CVIBuffer_Instancing::Initialize(void* pArg)
{
	m_InstancingDesc = *(INSTANCING_DESC*)pArg;

	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);

	m_BufferDesc.ByteWidth = m_iInstanceStride * m_iNumInstance;
	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_BufferDesc.MiscFlags = 0;
	m_BufferDesc.StructureByteStride = m_iInstanceStride;

	ZeroMemory(&m_SubResourceData, sizeof m_SubResourceData);

	VTXINSTANCE* pVertices = new VTXINSTANCE[m_iNumInstance];

	_vector				vDir = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	_float				fLength = { 0.0f };

	uniform_real_distribution<float>	RandomRange(m_InstancingDesc.vRange.x, m_InstancingDesc.vRange.y);
	uniform_real_distribution<float>	RandomRotationX(XMConvertToRadians(m_InstancingDesc.vRotationX.x), XMConvertToRadians(m_InstancingDesc.vRotationX.y));
	uniform_real_distribution<float>	RandomRotationY(XMConvertToRadians(m_InstancingDesc.vRotationY.x), XMConvertToRadians(m_InstancingDesc.vRotationY.y));
	uniform_real_distribution<float>	RandomRotationZ(XMConvertToRadians(m_InstancingDesc.vRotationZ.x), XMConvertToRadians(m_InstancingDesc.vRotationZ.y));
	uniform_real_distribution<float>	RandomScaleX(m_InstancingDesc.vScaleX.x, m_InstancingDesc.vScaleX.y);
	uniform_real_distribution<float>	RandomScaleY(m_InstancingDesc.vScaleY.x, m_InstancingDesc.vScaleY.y);
	uniform_real_distribution<float>	RandomSpeed(m_InstancingDesc.vSpeed.x, m_InstancingDesc.vSpeed.y);
	uniform_real_distribution<float>	RandomLifeTime(m_InstancingDesc.vLifeTime.x, m_InstancingDesc.vLifeTime.y);

	m_fAccelerations = m_InstancingDesc.fAcceleration;

	for (size_t i = 0; i < m_iNumInstance; i++)
	{
		//m_pOrigianlSpeeds[i] = RandomSpeed(m_RandomNumber);
		m_pSpeeds[i] = RandomSpeed(m_RandomNumber);
		m_pLifeTimes[i] = RandomLifeTime(m_RandomNumber);

		_float	fScaleX = RandomScaleX(m_RandomNumber);
		_float	fScaleY = RandomScaleY(m_RandomNumber);

		pVertices[i].vRight = _float4(fScaleX, 0.f, 0.f, 0.f);
		pVertices[i].vUp = _float4(0.f, fScaleY, 0.f, 0.f);
		pVertices[i].vLook = _float4(0.f, 0.f, 1.f, 0.f);

		vDir = XMVector3Normalize(vDir) * RandomRange(m_RandomNumber);

		_vector		vRotation = XMQuaternionRotationRollPitchYaw(
			RandomRotationX(m_RandomNumber),
			RandomRotationY(m_RandomNumber),
			RandomRotationZ(m_RandomNumber));

		_matrix		RotationMatrix = XMMatrixRotationQuaternion(vRotation);

		XMStoreFloat4(&pVertices[i].vPosition, XMLoadFloat3(&m_InstancingDesc.vCenter) + XMVector3TransformNormal(vDir, RotationMatrix));
		pVertices[i].vPosition.w = 1.f;
		pVertices[i].vColor = _float4(1.f, 1.f, 1.f, 1.f);
	}

	m_SubResourceData.pSysMem = pVertices;

	if (FAILED(__super::Create_Buffer(&m_pVBInstance)))
		return E_FAIL;

	Safe_Delete_Array(pVertices);


	return S_OK;
}

HRESULT CVIBuffer_Instancing::Bind_VIBuffers()
{
	if (nullptr == m_pVB ||
		nullptr == m_pIB)
		return E_FAIL;

	ID3D11Buffer* pVertexBuffers[] = {
		m_pVB,
		m_pVBInstance,
	};

	_uint				iStrides[] = {
		m_iStride,
		m_iInstanceStride

	};

	_uint				iOffsets[] = {
		0,
		0,
	};


	/* 어떤 버텍스 버퍼들을 이용할거다. */
	m_pContext->IASetVertexBuffers(0, m_iNumVertexBuffers, pVertexBuffers, iStrides, iOffsets);

	/* 어떤 인덱스 버퍼를 이용할거다. */
	m_pContext->IASetIndexBuffer(m_pIB, m_eIndexFormat, 0);

	/* 정점을 어떤식으로 이어서 그릴거다. */
	m_pContext->IASetPrimitiveTopology(m_eTopology);

	return S_OK;
}

void CVIBuffer_Instancing::Update(_float fTimeDelta)
{

	m_fTimeAcc += fTimeDelta;

	D3D11_MAPPED_SUBRESOURCE			SubResource = {};

	m_pContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

	VTXINSTANCE* pVertices = ((VTXINSTANCE*)SubResource.pData);

	for (size_t i = 0; i < m_iNumInstance; i++)
	{
		_float		fAlpha = max(m_pLifeTimes[i] - m_fTimeAcc, 0.f);

		pVertices[i].vColor.w = fAlpha;

		//_vector		vDir = XMVector3Normalize(XMLoadFloat3(&m_InstancingDesc.vDestination) - (XMLoadFloat4(&pVertices[i].vPosition) - XMLoadFloat3(&m_InstancingDesc.vCulling)));
		_vector		vDir = XMVector3Normalize((XMLoadFloat4(&pVertices[i].vPosition) - XMLoadFloat3(&m_InstancingDesc.vCulling)));

		vDir = XMVectorSetW(vDir, 0.f);

		_float fAcceleration = m_fAccelerations * m_fTimeAcc;
		_float fSpeed = m_pSpeeds[i] + fAcceleration > 0 ? m_pSpeeds[i] + fAcceleration : 0;

		XMStoreFloat4(&pVertices[i].vPosition, XMLoadFloat4(&pVertices[i].vPosition) + vDir * fSpeed * fTimeDelta);
	}

	m_pContext->Unmap(m_pVBInstance, 0);
}

HRESULT CVIBuffer_Instancing::Render()
{
	m_pContext->DrawIndexedInstanced(m_iIndexCountPerInstance, m_iNumInstance, 0, 0, 0);

	return S_OK;
}



void CVIBuffer_Instancing::Free()
{
	__super::Free();

	if (false == m_isCloned)
	{
		//Safe_Delete_Array(m_pOrigianlSpeeds);
		Safe_Delete_Array(m_pSpeeds);
		//Safe_Delete_Array(m_pAccelerations);
		Safe_Delete_Array(m_pLifeTimes);
	}

	Safe_Release(m_pVBInstance);
}
