#include "GameInstance.h"
#include "Graphic_Device.h"
#include "TImer_Manager.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Renderer.h"

#include "RapidJson.h"
#include "Mesh_Tool.h"
//#include "Json_Utility.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
{
}

HRESULT CGameInstance::Initialize_Engine(_uint iNumLevels, HINSTANCE hInstance, const GRAPHIC_DESC& GraphicDesc, _Inout_ ID3D11Device** ppDevice, _Inout_ ID3D11DeviceContext** ppContext)
{
	/* 그래픽 디바이스를 초기화 하자.*/
	m_pGraphic_Device = CGraphic_Device::Create(GraphicDesc, ppDevice, ppContext);
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	/* 타이머를 사용할 준비를 하자. */
	m_pTimer_Manager = CTimer_Manager::Create();
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	m_pInput_Device = CInput_Device::Create(hInstance, GraphicDesc.hWnd);
	if (nullptr == m_pInput_Device)
		return E_FAIL;

	m_pLevel_Manager = CLevel_Manager::Create();
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	m_pObject_Manager = CObject_Manager::Create(iNumLevels);
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	m_pComponent_Manager = CComponent_Manager::Create(iNumLevels);
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	m_pRenderer = CRenderer::Create(*ppDevice, *ppContext);
	if (nullptr == m_pRenderer)
		return E_FAIL;

	m_pPipeLine = CPipeLine::Create();
	if (nullptr == m_pPipeLine)
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Tick_Engine(_float fTimeDelta)
{
	if (nullptr == m_pLevel_Manager ||
		nullptr == m_pObject_Manager ||
		nullptr == m_pPipeLine ||
		nullptr == m_pInput_Device)
		return;

	m_pInput_Device->Tick();

	m_pObject_Manager->Priority_Tick(fTimeDelta);

	m_pObject_Manager->Tick(fTimeDelta);

	m_pPipeLine->Tick();

	m_pObject_Manager->Late_Tick(fTimeDelta);

	m_pLevel_Manager->Tick(fTimeDelta);

}

void CGameInstance::Clear(_uint iLevelIndex)
{
	if (nullptr == m_pObject_Manager ||
		nullptr == m_pComponent_Manager)
		return;

	/* 오브젝트 매니져에 레벨별로 구분해 놓은 객체들 중 특정된 객체들을 지운다.  */
	m_pObject_Manager->Clear(iLevelIndex);

	/* 컴포넌트 매니져에 레벨별로 구분해 놓은 컴포넌트들 중 특정된 객체들을 지운다.  */
	m_pComponent_Manager->Clear(iLevelIndex);

}

HRESULT CGameInstance::Render_Engine()
{
	if (nullptr == m_pLevel_Manager || 
		nullptr == m_pRenderer)
		return E_FAIL;

	m_pRenderer->Draw_RenderGroup();


#ifdef _DEBUG
	m_pLevel_Manager->Render();
#endif

	return S_OK;
}



HRESULT CGameInstance::Clear_BackBuffer_View(_float4 vClearColor)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	return m_pGraphic_Device->Clear_BackBuffer_View(vClearColor);
}

HRESULT CGameInstance::Clear_DepthStencil_View()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	return m_pGraphic_Device->Clear_DepthStencil_View();
}

HRESULT CGameInstance::Present()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	return m_pGraphic_Device->Present();
}

HRESULT CGameInstance::Add_Timer(const wstring & strTimeTag)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Add_Timer(strTimeTag);
}

_float CGameInstance::Compute_TimeDelta(const wstring & strTimeTag)
{
	if (nullptr == m_pTimer_Manager)
		return 0.0f;

	return m_pTimer_Manager->Compute_TimeDelta(strTimeTag);
}

HRESULT CGameInstance::Open_Level(_uint iCurrentLevelIndex, CLevel * pNewLevel)
{
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	return m_pLevel_Manager->Open_Level(iCurrentLevelIndex, pNewLevel);
}

HRESULT CGameInstance::Add_Prototype_Object(const wstring & strPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_Prototype_Object(strPrototypeTag, pPrototype);
}

HRESULT CGameInstance::Add_CloneObject(_uint iLevelIndex, const wstring & strLayerTag, const wstring & strPrototypeTag, void * pArg)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_CloneObject(iLevelIndex, strLayerTag, strPrototypeTag, pArg);
}

HRESULT CGameInstance::Add_Object(_uint iLevelIndex, const wstring& strLayerTag, CGameObject* pGameObject, void* pArg)
{
	return m_pObject_Manager->Add_Object(iLevelIndex, strLayerTag, pGameObject, pArg);
}

list<class CGameObject*>* CGameInstance::Get_GameObjects(_uint iLevelIndex, const wstring& strLayerTag)
{
	return m_pObject_Manager->Get_GameObjects(iLevelIndex, strLayerTag);
}

HRESULT CGameInstance::Save_Objects_With_Json(_uint iLevelIndex, string filePath)
{
	m_pObject_Manager->Save_Objects_With_Json(iLevelIndex, filePath);

	return S_OK;
}

//HRESULT CGameInstance::Load_Objects_With_Json(_uint iLevelIndex, string filePath)
//{
//	m_pObject_Manager->Load_Objects_With_Json(iLevelIndex, filePath);
//
//	return S_OK;
//}

HRESULT CGameInstance::Add_Prototype(_uint iLevelIndex, const wstring& strPrototypeTag, CComponent* pPrototype)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	return m_pComponent_Manager->Add_Prototype(iLevelIndex, strPrototypeTag, pPrototype);
}

CComponent* CGameInstance::Clone_Component(_uint iLevelIndex, const wstring& strPrototypeTag, void* pArg)
{
	if (nullptr == m_pComponent_Manager)
		return nullptr;

	return m_pComponent_Manager->Clone_Component(iLevelIndex, strPrototypeTag, pArg);
}

HRESULT CGameInstance::Add_RenderGroup(CRenderer::RENDERGROUP eGroupID, CGameObject * pGameObject)
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Add_RenderGroup(eGroupID, pGameObject);
}

void CGameInstance::Set_Transform(CPipeLine::D3DTRANSFORMSTATE eState, _fmatrix TransformMatrix)
{
	if (nullptr == m_pPipeLine)
		return;
	m_pPipeLine->Set_Transform(eState, TransformMatrix);
}

void CGameInstance::Set_Transform(CPipeLine::D3DTRANSFORMSTATE eState, _float4x4 TransformMatrix)
{
	if (nullptr == m_pPipeLine)
		return;
	m_pPipeLine->Set_Transform(eState, TransformMatrix);
}

_matrix CGameInstance::Get_TransformMatrix(CPipeLine::D3DTRANSFORMSTATE eState)
{
	if (nullptr == m_pPipeLine)
		return XMMatrixIdentity();

	return m_pPipeLine->Get_TransformMatrix(eState);
}

_float4x4 CGameInstance::Get_TransformFloat4x4(CPipeLine::D3DTRANSFORMSTATE eState)
{
	if (nullptr == m_pPipeLine)
		return _float4x4();

	return m_pPipeLine->Get_TransformFloat4x4(eState);
}

_matrix CGameInstance::Get_TransformMatrixInverse(CPipeLine::D3DTRANSFORMSTATE eState)
{
	if (nullptr == m_pPipeLine)
		return XMMatrixIdentity();

	return m_pPipeLine->Get_TransformMatrixInverse(eState);
}

_float4x4 CGameInstance::Get_TransformFloat4x4Inverse(CPipeLine::D3DTRANSFORMSTATE eState)
{
	if (nullptr == m_pPipeLine)
		return _float4x4();

	return m_pPipeLine->Get_TransformFloat4x4Inverse(eState);
}

_float4 CGameInstance::Get_CamPosition()
{
	if (nullptr == m_pPipeLine)
		return _float4();

	return m_pPipeLine->Get_CamPosition();
}

GRAPHIC_DESC CGameInstance::Get_GraphicDesc()
{
	if (nullptr == m_pGraphic_Device)
		return GRAPHIC_DESC{};

	return m_pGraphic_Device->Get_GraphicDesc();
}

_byte CGameInstance::Get_DIKeyState(_ubyte byKeyID)
{
	if (nullptr == m_pInput_Device)
		return _byte();

	return m_pInput_Device->Get_DIKeyState(byKeyID);
}

_byte CGameInstance::Get_DIMouseState(MOUSEKEYSTATE eMouse)
{
	if (nullptr == m_pInput_Device)
		return _byte();

	return m_pInput_Device->Get_DIMouseState(eMouse);
}

_long CGameInstance::Get_DIMouseMove(MOUSEMOVESTATE eMouseState)
{
	if (nullptr == m_pInput_Device)
		return _long();

	return m_pInput_Device->Get_DIMouseMove(eMouseState);
}

_bool CGameInstance::Key_Up(const _int& _iKey)
{
	return m_pInput_Device->Key_Up(_iKey);
}

_bool CGameInstance::Key_Down(const _int& _iKey)
{
	return m_pInput_Device->Key_Down(_iKey);
}

_bool CGameInstance::Key_Pressing(const _int& _iKey)
{
	return m_pInput_Device->Key_Pressing(_iKey);
}

_bool CGameInstance::Mouse_Pressing(MOUSEKEYSTATE eMouseID)
{
	return m_pInput_Device->Mouse_Pressing(eMouseID);
}

_bool CGameInstance::Mouse_Down(MOUSEKEYSTATE eMouseID)
{
	return m_pInput_Device->Mouse_Down(eMouseID);
}

_bool CGameInstance::Mouse_Up(MOUSEKEYSTATE eMouseID)
{
	return m_pInput_Device->Mouse_Up(eMouseID);
}

RAY CGameInstance::Get_MouseRayWorld(HWND g_hWnd, const unsigned int	g_iWinSizeX, const unsigned int	g_iWinSizeY)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	_vector vProjPos(XMVectorSet(pt.x / (g_iWinSizeX * 0.5f) - 1.f, pt.y / -(g_iWinSizeY * 0.5f) + 1.f, 0.f, 0.f));

	_matrix ProjMatrixInv = Get_TransformMatrixInverse(CPipeLine::D3DTRANSFORMSTATE::D3DTS_PROJ);

	_vector vViewPos(XMVector3TransformCoord(vProjPos, ProjMatrixInv));

	_vector vRayDir(vViewPos);
	_vector vRayPos(XMVectorSet(0.f, 0.f, 0.f, 1.f));

	_matrix ViewMatrixInv = Get_TransformMatrixInverse(CPipeLine::D3DTRANSFORMSTATE::D3DTS_VIEW);

	RAY MouseRay;
	ZeroMemory(&MouseRay, sizeof(RAY));

	XMStoreFloat3(&MouseRay.vDirection, XMVector3Normalize(XMVector3TransformNormal(vRayDir, ViewMatrixInv)));
	XMStoreFloat4(&MouseRay.vPosition, XMVector3TransformCoord(vRayPos, ViewMatrixInv));

	MouseRay.fLength = 1000000.0f;
	return MouseRay;
}

RAY CGameInstance::Get_MouseRayLocal(HWND g_hWnd, const unsigned int	g_iWinSizeX, const unsigned int	g_iWinSizeY, _matrix matWorld)
{
	RAY vMouseRayLocal;
	ZeroMemory(&vMouseRayLocal, sizeof(vMouseRayLocal));

	RAY vMouseRayWorld = Get_MouseRayWorld(g_hWnd, g_iWinSizeX, g_iWinSizeY);
	
	_vector vMousePos = XMLoadFloat4(&vMouseRayWorld.vPosition);
	_vector vMouseDir = XMLoadFloat3(&vMouseRayWorld.vDirection);

	_matrix matWorldInv = XMMatrixInverse(nullptr, matWorld);
	vMousePos = XMVector3TransformCoord(vMousePos, matWorldInv);
	vMouseDir = XMVector3Normalize(XMVector3TransformNormal(vMouseDir, matWorldInv));

	XMStoreFloat4(&vMouseRayLocal.vPosition, vMousePos);
	XMStoreFloat3(&vMouseRayLocal.vDirection, vMouseDir);
	vMouseRayLocal.fLength = 1000000.0f;

	return vMouseRayLocal;
}

_bool CGameInstance::Picking_Mesh(RAY ray, _float3* out, vector<class CMesh*>* Meshes)
{
	_vector		vPickedPos;
	_vector		vVec0, vVec1, vVec2;

	_vector		vRayPos = XMLoadFloat4(&ray.vPosition);
	_vector		vRayDir = XMLoadFloat3(&ray.vDirection);
	_float		fDist = 0.f;

	for (CMesh* mesh : *Meshes) 
	{
		CMesh_Tool* pMesh_Tool = dynamic_cast<CMesh_Tool*>(mesh);
		if (nullptr == pMesh_Tool)
			return false;

		if (pMesh_Tool->Picking(ray, out))
			return true;
	}


	return false;
}

_bool CGameInstance::Picking_Vertex(RAY ray, _float3* out, _uint triNum, VTXMESH* pVertices, _uint* pIndices)
{
	_vector		vPickedPos;
	_vector		vVec0, vVec1, vVec2;

	_vector		vRayPos = XMLoadFloat4(&ray.vPosition);
	_vector		vRayDir = XMLoadFloat3(&ray.vDirection);
	_float		fDist = 0.f;

	for (_uint i = 0; i < triNum; ++i)
	{
		_int iStartIndex = i * 3;

		_float3 vVtxPos1 = pVertices[pIndices[iStartIndex + 0]].vPosition;
		_float3 vVtxPos2 = pVertices[pIndices[iStartIndex + 1]].vPosition;
		_float3 vVtxPos3 = pVertices[pIndices[iStartIndex + 2]].vPosition;

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


HRESULT CGameInstance::Load_Json(string _strPath, json& pOut)
{
	json JsonTemp;

	ifstream fin;
	
	
	string	directoryPath = "../Bin/RapidJson/";

	string filePath = directoryPath + _strPath;

	fin.open(filePath.c_str());

	if (fin.is_open())
	{
		fin >> (JsonTemp);
	}
	else
	{
		return E_FAIL;
	}

	fin.close();
	pOut = JsonTemp;

	return S_OK;
}

HRESULT CGameInstance::Save_Json(string _strPath, json _json)
{
	ofstream fout;

	string directoryPath = "../Bin/RapidJson/";

	string filePath = directoryPath + _strPath;

	fout.open(filePath.c_str());

	if (fout.is_open())
	{
		fout << _json << endl;
	}
	else
		return E_FAIL;

	fout.close();

	return S_OK;
}

void CGameInstance::String_To_WString(string _string, wstring& _wstring)
{
	_wstring.assign(_string.begin(), _string.end());
}

void CGameInstance::WString_To_String(wstring _wstring, string& _string)
{
	_string.assign(_wstring.begin(), _wstring.end());
}


void CGameInstance::Release_Manager()
{
	Safe_Release(m_pPipeLine);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pComponent_Manager);
	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pInput_Device);
	Safe_Release(m_pGraphic_Device);
}

void CGameInstance::Release_Engine()
{
	CGameInstance::GetInstance()->Release_Manager();
	CGameInstance::GetInstance()->DestroyInstance();
}
