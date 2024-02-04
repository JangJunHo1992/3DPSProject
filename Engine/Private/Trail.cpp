#include "..\..\..\3DPSProject\Engine\Public\Trail.h"
#include "..\..\..\3DPSProject\Engine\Public\Trail.h"
#include "..\..\..\3DPSProject\Engine\Public\Trail.h"
#include "..\..\..\3DPSProject\Engine\Public\Trail.h"
#include "Engine_Defines.h"
#include "Trail.h"


CTrail::CTrail(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVIBuffer(pDevice, pContext)
{
}


CTrail::CTrail(const CTrail& _pPrototype)
	: CVIBuffer(_pPrototype)
{
}

CTrail::~CTrail()
{
	CVIBuffer::Free();
}

HRESULT CTrail::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTrail::Initialize(void* _pInfo)
{
	m_Traildesc = *(TRAILDESC*)_pInfo;

	m_iVertex_Count = m_Traildesc._iVertex_Count * m_iCatmullRomSize - m_Traildesc._iVertex_Count;
	m_iVertex_Size = sizeof(VTXNORTEX);
	m_dwVectex_FVF = FVF_TEX;

	m_vecCatStart.reserve(m_iVertex_Count / 2 - m_Traildesc._iVertex_Count);
	m_vecCatEnd.reserve(m_iVertex_Count / 2 - m_Traildesc._iVertex_Count);

	m_iTri_Count = m_iVertex_Count - 2;
	m_iTri_Size = sizeof(TRAILINDEX16);
	m_eFormat = D3DFMT_INDEX16;

	if (FAILED(CVIBuffer::Initialize_Prototype()))
		return E_FAIL;

	m_vecCatStart.assign(m_iVertex_Count / 2 - m_Traildesc._iVertex_Count, (_vec3)&m_Traildesc.worldmat.m[3][0]);
	m_vecCatEnd.assign(m_iVertex_Count / 2 - m_Traildesc._iVertex_Count, (_vec3)&m_Traildesc.worldmat.m[3][0] + (_vec3)&m_Traildesc.worldmat.m[0][0] * 0.45f);

	m_vecStart.assign(m_Traildesc._iVertex_Count / 2, (_vec3)&m_Traildesc.worldmat.m[3][0]);
	m_vecEnd.assign(m_Traildesc._iVertex_Count / 2, (_vec3)&m_Traildesc.worldmat.m[3][0] + (_vec3)&m_Traildesc.worldmat.m[0][0] * 0.45f);

	TRAILINDEX16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	for (_uint i = 0; i < m_iTri_Count / 2; ++i)
	{
		pIndices[i]._0 = i;
		pIndices[i]._1 = i + 1;
		pIndices[i]._2 = i + 2;
		pIndices[i]._3 = i + 3;
	}

	m_pIB->Unlock();


	return S_OK;
}

HRESULT CTrail::Render_Trail()
{
	if (false == m_bIsRender)
		return S_OK;

	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_iVertex_Size);
	m_pGraphicDev->SetFVF(m_dwVectex_FVF);
	m_pGraphicDev->SetIndices(m_pIB);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_iVertex_Count, 0, m_iTri_Count);

	return S_OK;
}

void CTrail::Trail_Update(_matrix matWorld, _float3 vDir, _float fLength)
{
	Trail_NoFull(matWorld, vDir, fLength);

	VTXNORTEX* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	for (_uint i = 0; i < m_iVertex_Count - m_Traildesc._iVertex_Count; ++i)
	{
		if (0 == i % 2)
		{
			pVertices[i].vPos = m_vecCatStart[i / 2];
			//pVertices[i].vTex = _vec2(((_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count)), ((_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count)));
			pVertices[i].vTex = _vec2(1.f, (1.f - (_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count) * 4));
			//pVertices[i].vTex = _vec2(((_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count)), ((_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count)));
			//pVertices[i].vTex = _vec2(0.f, 0.f);
		}
		else
		{
			pVertices[i].vPos = m_vecCatEnd[(i - 1) / 2];
			//pVertices[i].vTex = _vec2((0.f/*(_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count) * 4*/), 0.f);
			pVertices[i].vTex = _vec2(0.f, (1.f - (_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count) * 4));
			//pVertices[i].vTex = _vec2(((_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count)), ((_float)i / (m_iVertex_Count - m_Traildesc._iVertex_Count)));
			//pVertices[i].vTex = _vec2(1.f, 1.f);
		}
	}

	m_pVB->Unlock();
}

void CTrail::Trail_NoFull(_matrix matWorld, _float3 vDir, _float fLength)
{
	_float catmul_s = 0.f;

	if (0 == m_Traildesc.TrailType)
	{
		for (_int i = (_int)m_vecStart.size() - 1; i > 0; --i)
		{
			_vec3  Temp = m_vecStart[i - 1] - m_vecEnd[i - 1];
			D3DXVec3Normalize(&(Temp), &(Temp));
			m_vecStart[i] = m_vecStart[i - 1] - Temp * (_float)i / ((_float)m_vecStart.size() * 4.f);
			m_vecEnd[i] = m_vecEnd[i - 1];
		}
	}
	else
	{
		for (_int i = (_int)m_vecStart.size() - 1; i > 0; --i)
		{
			_vec3  Temp = m_vecStart[i - 1] - m_vecEnd[i - 1];
			D3DXVec3Normalize(&(Temp), &(Temp));
			m_vecStart[i] = m_vecStart[i - 1];
			m_vecEnd[i] = m_vecEnd[i - 1];
		}
	}

	m_vecStart[0] = (_vec3)&matWorld.m[3][0];
	m_vecEnd[0] = (_vec3)&matWorld.m[3][0] + vDir * fLength;

	m_vecCatStart.clear();
	m_vecCatEnd.clear();

	for (_int i = 0; i < m_vecStart.size() - 1; ++i)
	{
		catmul_s = 0.f;

		while (true)
		{
			D3DXVECTOR3 Out;
			_int befor = i - 1;
			_int after = i + 2;
			if (befor < 0)
				befor = 0;
			if (after >= m_vecStart.size())
				after = (_int)m_vecStart.size() - 1; //== i+1

			if (catmul_s + 1.f / m_iCatmullRomSize > 1.f)
				break;

			D3DXVec3CatmullRom(&Out, &((m_vecStart)[befor]), &((m_vecStart)[i]), &((m_vecStart)[i + 1]), &((m_vecStart)[after]), catmul_s);
			m_vecCatStart.emplace_back(Out);

			D3DXVec3CatmullRom(&Out, &((m_vecEnd)[befor]), &((m_vecEnd)[i]), &((m_vecEnd)[i + 1]), &((m_vecEnd)[after]), catmul_s);
			m_vecCatEnd.emplace_back(Out);

			catmul_s += 1.f / m_iCatmullRomSize;
		}
	}

	catmul_s = 0.f;

	while (true)
	{
		D3DXVECTOR3 Out;
		if (catmul_s + 1.f / m_iCatmullRomSize > 1.f)
			break;

		D3DXVec3CatmullRom(&Out, &((m_vecStart)[m_Traildesc._iVertex_Count / 2 - 3]), &((m_vecStart)[m_Traildesc._iVertex_Count / 2 - 2]), &((m_vecStart)[m_Traildesc._iVertex_Count / 2 - 1]), &((m_vecStart)[m_Traildesc._iVertex_Count / 2 - 1]), catmul_s);
		m_vecCatStart.emplace_back(Out);

		D3DXVec3CatmullRom(&Out, &((m_vecEnd)[m_Traildesc._iVertex_Count / 2 - 3]), &((m_vecEnd)[m_Traildesc._iVertex_Count / 2 - 2]), &((m_vecEnd)[m_Traildesc._iVertex_Count / 2 - 1]), &((m_vecEnd)[m_Traildesc._iVertex_Count / 2 - 1]), catmul_s);
		m_vecCatEnd.emplace_back(Out);

		catmul_s += 1.f / m_iCatmullRomSize;
	}
}



CTrail* CTrail::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTrail* pInstance = new CTrail(pDevice,pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("CTrail Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CTrail::Clone(void* _pInfo)
{
	CTrail* pInstance = new CTrail(*this);

	if (FAILED(pInstance->Initialize(_pInfo)))
	{
		MSG_BOX("CTrail Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTrail::Free()
{
	//Safe_Delete_Array(m_pLocal_Pos);
}
