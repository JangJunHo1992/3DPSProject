#include "..\Public\Navigation.h"
#include "Cell.h"
#include "NavigationPoint.h"
#include "GameInstance.h"
#include "Transform.h"

_float4x4 CNavigation::m_WorldMatrix = { };

CNavigation::CNavigation(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CComponent(pDevice, pContext)
{

}

CNavigation::CNavigation(const CNavigation& rhs)
	: CComponent(rhs)
	, m_Cells(rhs.m_Cells)
	, m_Points(rhs.m_Points)
#ifdef _DEBUG
	, m_pShader(rhs.m_pShader)
#endif
{
	for (auto& pCell : m_Cells)
		Safe_AddRef(pCell);
	for (auto& pPoint : m_Points)
		Safe_AddRef(pPoint);
#ifdef _DEBUG
	Safe_AddRef(m_pShader);
#endif

}

CCell* CNavigation::Get_CurrentCell()
{
	if (m_iCurrentIndex == -1)
		return nullptr;

	for (CCell* pCell : m_Cells) 
	{
		if (pCell->Get_Index() == m_iCurrentIndex)
			return pCell;
	}

	return nullptr;
}

_float CNavigation::Get_CurrentHeight(_fvector vPosition)
{
	CCell* pCell = Get_CurrentCell();

	if (nullptr == pCell)
		return 100.0f;

	return pCell->Calc_Height(vPosition);
}

HRESULT CNavigation::Initialize_Prototype(const wstring& strNavigationFilePath)
{
	XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());

	HANDLE		hFile = CreateFile(strNavigationFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (0 == hFile)
		return E_FAIL;

	_ulong		dwByte = { 0 };

	while (true)
	{
		_float3		vPoints[3];

		ReadFile(hFile, vPoints, sizeof(_float3) * 3, &dwByte, nullptr);
		if (0 == dwByte)
			break;

		//_uint iCellIndex = m_Cells.size();

		//CCell* pCell = CCell::Create(m_pDevice, m_pContext, vPoints, iCellIndex);
		//if (nullptr == pCell)
		//	return E_FAIL;

		//m_Cells.push_back(pCell);

		vector<CNavigationPoint*> _pPointsOfCell;

		for (_uint i = 0; i < 3; ++i)
		{
			CNavigationPoint::NAVIGATION_POINT_DESC desc = {};
			desc.vPos = vPoints[i];

			CNavigationPoint* pPoint = Make_Point(vPoints[i]);

			if (nullptr == pPoint)
				return E_FAIL;


			//pPoint->Add_ParentIndex(m_iCellIndex++);
			//pPoint->Set_Index(m_iPointIndex++);

			//m_Points.push_back(pPoint);
			_pPointsOfCell.push_back(pPoint);
		}

		if (FAILED(Make_Cell_By_Points(_pPointsOfCell[0], _pPointsOfCell[1], _pPointsOfCell[2])))
			return E_FAIL;



	}

	CloseHandle(hFile);

	//{
	//	//_uint iPointSize = m_Points.size();
	//	CNavigationPoint* pPoint1 = m_Points[m_Points.size() - 2];
	//	CNavigationPoint* pPoint2 = m_Points.back();
	//	CNavigationPoint* pNewPoint = Make_Point(_float3(20.f, 0.0f, -10.f));
	//	m_Points.push_back(pNewPoint);

	//	//_float3 vPos1 = pPoint1->Get_TransformComp()->Get_Pos();
	//	//_float3 vPos2 = pPoint2->Get_TransformComp()->Get_Pos();

	//	if (FAILED(Make_Cell_By_Points(pPoint1, pPoint2, pNewPoint)))
	//		return E_FAIL;
	//}

	//{
	//	//_uint iPointSize = m_Points.size();
	//	CNavigationPoint* pPoint2 = m_Points[m_Points.size() - 2];
	//	CNavigationPoint* pPoint1 = m_Points.back();
	//	CNavigationPoint* pNewPoint = Make_Point(_float3(10.f, 0.0f, -10.f));
	//	m_Points.push_back(pNewPoint);

	//	//_float3 vPos1 = pPoint1->Get_TransformComp()->Get_Pos();
	//	//_float3 vPos2 = pPoint2->Get_TransformComp()->Get_Pos();

	//	if (FAILED(Make_Cell_By_Points(pPoint1, pPoint2, pNewPoint)))
	//		return E_FAIL;
	//}



	//_bool test = false;

	if (FAILED(Make_Neighbors()))
		return E_FAIL;

#ifdef _DEBUG
	m_pShader = CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Navigation.hlsl"), VTXPOS::Elements, VTXPOS::iNumElements);
	if (nullptr == m_pShader)
		return E_FAIL;
#endif

	return S_OK;
}

HRESULT CNavigation::Initialize(void* pArg)
{
	if (nullptr != pArg)
		m_iCurrentIndex = ((NAVI_DESC*)pArg)->iCurrentIndex;

	return S_OK;
}



HRESULT CNavigation::Render()
{
#ifdef _DEBUG
	/* 셀들의 위치가 월드상에 존재한다. */
	_float4		vColor = { 0.0f, 0.f, 0.f, 1.f };

	m_WorldMatrix.m[3][1] = m_iCurrentIndex == -1 ? m_WorldMatrix.m[3][1] : m_WorldMatrix.m[3][1] + 0.1f;

	if (FAILED(m_pShader->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	vColor = m_iCurrentIndex == -1 ? _float4(0.f, 1.f, 0.f, 1.f) : _float4(1.f, 0.f, 0.f, 1.f);

	m_pShader->Bind_RawValue("g_vColor", &vColor, sizeof(_float4));

	m_pShader->Begin(0);

	if (-1 != m_iCurrentIndex)
	{
		m_Cells[m_iCurrentIndex]->Render(m_pShader);
		goto Exit;
	}


	for (auto& pCell : m_Cells)
	{
		if (nullptr != pCell)
			pCell->Render(m_pShader);
	}

	for (auto& pPoint : m_Points)
	{
		if (nullptr != pPoint)
			pPoint->Render();

	}


Exit:
#endif
	return S_OK;

}

HRESULT CNavigation::Make_Cell_By_Points(CNavigationPoint* pPoint0, CNavigationPoint* pPoint1, CNavigationPoint* pPoint2)
{

	_float3		vPoints[3];

	vPoints[0] = pPoint0->Get_TransformComp()->Get_State(CTransform::STATE_POSITION);
	vPoints[1] = pPoint1->Get_TransformComp()->Get_State(CTransform::STATE_POSITION);
	vPoints[2] = pPoint2->Get_TransformComp()->Get_State(CTransform::STATE_POSITION);

	_bool bIsCounterclockwise;
	vector<_float3> ccw = Make_Points_Clockwise(vPoints, bIsCounterclockwise);
	vPoints[0] = ccw[0];
	vPoints[1] = ccw[1];
	vPoints[2] = ccw[2];

	_uint iParentIndex = m_iCellIndex++;

	CCell* pCell = CCell::Create(m_pDevice, m_pContext, vPoints, iParentIndex);
	if (nullptr == pCell)
		return E_FAIL;

	if (bIsCounterclockwise)
	{
		pCell->Add_ChildIndex(pPoint0->Get_Index());
		pCell->Add_ChildIndex(pPoint2->Get_Index());
		pCell->Add_ChildIndex(pPoint1->Get_Index());

	}
	else
	{
		pCell->Add_ChildIndex(pPoint0->Get_Index());
		pCell->Add_ChildIndex(pPoint1->Get_Index());
		pCell->Add_ChildIndex(pPoint2->Get_Index());
	}

	pPoint0->Add_ParentIndex(iParentIndex);
	pPoint1->Add_ParentIndex(iParentIndex);
	pPoint2->Add_ParentIndex(iParentIndex);

	m_Cells.push_back(pCell);

	return S_OK;
}





void CNavigation::Update(_fmatrix WorldMatrix, _float fTimeDelta)
{
	XMStoreFloat4x4(&m_WorldMatrix, WorldMatrix);

	for (auto& pPoint : m_Points)
	{
		if (nullptr != pPoint)
			pPoint->Tick(fTimeDelta);

	}
}

_bool CNavigation::isMove(_fvector vPosition)
{
	_int		iNeighborIndex = { -1 };

	if (true == m_Cells[m_iCurrentIndex]->isIn(vPosition, XMLoadFloat4x4(&m_WorldMatrix), &iNeighborIndex))
		return true;

	else
	{
		if (-1 != iNeighborIndex)
		{
			while (true)
			{
				if (-1 == iNeighborIndex)
					return false;
				if (true == m_Cells[iNeighborIndex]->isIn(vPosition, XMLoadFloat4x4(&m_WorldMatrix), &iNeighborIndex))
				{
					m_iCurrentIndex = iNeighborIndex;
					return true;
				}
			}
		}
		else
			return false;
	}
}

HRESULT CNavigation::Make_Neighbors()
{
	for (auto& pSourCell : m_Cells)
	{
		for (auto& pDestCell : m_Cells)
		{
			if (pSourCell == pDestCell)
				continue;

			if (true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_A), pSourCell->Get_Point(CCell::POINT_B)))
			{
				pSourCell->SetUp_Neighbor(CCell::LINE_AB, pDestCell);
			}
			if (true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_B), pSourCell->Get_Point(CCell::POINT_C)))
			{
				pSourCell->SetUp_Neighbor(CCell::LINE_BC, pDestCell);
			}
			if (true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_C), pSourCell->Get_Point(CCell::POINT_A)))
			{
				pSourCell->SetUp_Neighbor(CCell::LINE_CA, pDestCell);
			}

		}
	}

	return S_OK;
}

CNavigationPoint* CNavigation::Make_Point(_float3 vPos)
{
	CNavigationPoint::NAVIGATION_POINT_DESC desc = {};
	desc.vPos = vPos;

	CNavigationPoint* pPoint = CNavigationPoint::Create(m_pDevice, m_pContext, &desc);
	if (nullptr == pPoint)
		return nullptr;

	pPoint->Set_Index(m_iPointIndex++);
	m_Points.push_back(pPoint);

	return pPoint;
}

CNavigationPoint* CNavigation::Select_Point(RAY ray)
{
	for (CNavigationPoint* pPoint : m_Points) 
	{
		if (pPoint->IsSelected(ray)) 
		{
			return pPoint;
		}
	}

	return nullptr;
}



HRESULT CNavigation::Save_All()
{
	HANDLE		hFile = CreateFile(TEXT("../Bin/DataFiles/Navigation.dat"), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (0 == hFile)
		return E_FAIL;

	_ulong		dwByte = { 0 };

	for (CCell* pCell : m_Cells) 
	{
		pCell->Write_Cell(hFile, dwByte);
	}

	CloseHandle(hFile);

	return S_OK;
}


vector<_float3> CNavigation::Make_Points_Clockwise(_float3 vPoints[3], _bool& bIsCounterclockwise)
{
	vector<_float3> result;

	for (_uint i = 0; i < 3; ++i)
	{
		result.push_back(vPoints[i]);
	}


	_float ccw = (result[1].x - result[0].x) * (result[2].z - result[0].z) - (result[2].x - result[0].x) * (result[1].z - result[0].z);

	bIsCounterclockwise = 0 < ccw;
	if (bIsCounterclockwise)
	{
		result[0] = vPoints[0];
		result[1] = vPoints[2];
		result[2] = vPoints[1];
	}

	return result;
}

CNavigation* CNavigation::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strNavigationFilePath)
{
	CNavigation* pInstance = new CNavigation(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype(strNavigationFilePath)))
	{
		MSG_BOX("Failed to Created : CNavigation");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CNavigation::Clone(void* pArg)
{
	CNavigation* pInstance = new CNavigation(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CNavigation");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CNavigation::Free()
{
	__super::Free();

	for (auto& pCell : m_Cells)
		Safe_Release(pCell);

	m_Cells.clear();

	for (auto& pPoint : m_Points)
		Safe_Release(pPoint);

	m_Points.clear();

#ifdef _DEBUG
	Safe_Release(m_pShader);
#endif
}
