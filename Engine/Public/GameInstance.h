#pragma once

#include "Renderer.h"
#include "PipeLine.h"
#include "InputDev.h"
#include "Component_Manager.h"


//#include "Json/json.hpp"
//using namespace nlohmann;

/* Ŭ���̾�Ʈ���� ������ ����� ����ϱ����� �ݵ�� ���ľ��ϴ� ��ü. */

/* DX11�� ���� �ʿ��� ��ü�� �����ϰ� �������ϴ� �۾��� �����Ѵ�. */
/* ���� ������ ����(��)�� �����ϰ� �ʿ信���� ������Ʈ ����. */
/* ���� ������ ��ü���� �����ϰ� ������Ʈ�ϰ� �����Ѵ�. */
/* ���� ������ ���� ������Ʈ���� ������ �����ϰ� �����Ͽ� �����´�. */

BEGIN(Engine)
class CGameObject;
class CLayer;

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* For.Engine */
	/* �������̺귯���� ����ϱ����� �غ� ��� ��ģ��. */
	HRESULT Initialize_Engine(_uint iNumLevels, HINSTANCE hInstance, const GRAPHIC_DESC & GraphicDesc, _Inout_ ID3D11Device * *ppDevice, _Inout_ ID3D11DeviceContext * *ppContext);
	void Tick_Engine(_float fTimeDelta);
	HRESULT  Render_Engine();
	void Clear(_uint iLevelIndex);

public: /* For.Graphic_Device */		
	HRESULT Clear_BackBuffer_View(_float4 vClearColor);
	HRESULT Clear_DepthStencil_View();	
	HRESULT Present();

public: /* For.Timer_Manager */
	HRESULT	Add_Timer(const wstring& strTimeTag);
	_float Compute_TimeDelta(const wstring& strTimeTag);

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iCurrentLevelIndex, class CLevel* pNewLevel);

public: /* For.Object_Manager */
	HRESULT Add_Prototype_Object(const wstring& strPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_CloneObject(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strPrototypeTag, void* pArg = nullptr);
	CGameObject* Clone_Prototype(const wstring & strPrototypeTag, void* pArg = nullptr);
	HRESULT Add_Object(_uint iLevelIndex, const wstring & strLayerTag, class CGameObject* pGameObject, void* pArg = nullptr);
	void Fill_PrototypeTags(vector<string>*_vector);
	void Get_CloneGameObjects(_uint iLevelIndex, vector<CGameObject*>* clonevector);
	list<CGameObject*>* Get_GameObjects(_uint iLevelIndex, const wstring & strLayerTag);
	class CComponent* Get_Component(_uint iLevelIndex, const wstring & strLayerTag, const wstring & strComponentTag, _uint iIndex = 0);
	CGameObject* Get_Player();
	void	Set_Player(CGameObject * _pPlayer);


	HRESULT Save_Objects_With_Json(_uint iLevelIndex, string filePath);
	//HRESULT Load_Objects_With_Json(_uint iLevelIndex, string filePath);


public: /* For.Component_Manager */
	HRESULT Add_Prototype(_uint iLevelIndex, const wstring & strPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iLevelIndex, const wstring & strPrototypeTag, void* pArg);

public: /* For.Renderer */
	HRESULT Add_RenderGroup(CRenderer::RENDERGROUP eGroupID, class CGameObject* pGameObject);
public: /* For.PipeLine */
	void Set_Transform(CPipeLine::D3DTRANSFORMSTATE eState, _fmatrix TransformMatrix);
	void Set_Transform(CPipeLine::D3DTRANSFORMSTATE eState, _float4x4 TransformMatrix);
	_matrix Get_TransformMatrix(CPipeLine::D3DTRANSFORMSTATE eState);
	_float4x4 Get_TransformFloat4x4(CPipeLine::D3DTRANSFORMSTATE eState);
	_matrix Get_TransformMatrixInverse(CPipeLine::D3DTRANSFORMSTATE eState);
	_float4x4 Get_TransformFloat4x4Inverse(CPipeLine::D3DTRANSFORMSTATE eState);
	_float4 Get_CamPosition();
public:/*For. GraphicDesc*/
	GRAPHIC_DESC	Get_GraphicDesc();

public: //For Input_Device
	_byte   Get_DIKeyState(_ubyte byKeyID);
	_byte   Get_DIMouseState(MOUSEKEYSTATE eMouse);
	_long   Get_DIMouseMove(MOUSEMOVESTATE eMouseState);

	_bool	Key_Up(const _int & _iKey);
	_bool	Key_Down(const _int & _iKey);
	_bool	Key_Pressing(const _int & _iKey);

	_bool	Mouse_Pressing(MOUSEKEYSTATE eMouseID);
	_bool	Mouse_Down(MOUSEKEYSTATE eMouseID);
	_bool	Mouse_Up(MOUSEKEYSTATE eMouseID);

public: /* For.Font_Manager */
	HRESULT Add_Font(const wstring & strFontTag, const wstring & strFontFilePath);
	HRESULT Render_Font(const wstring & strFontTag, const wstring & strText, const _float2 & vPosition, _fvector vColor = XMVectorSet(1.f, 1.f, 1.f, 1.f), _float fScale = 1.f, _float2 vOrigin = _float2(0.f, 0.f), _float fRotation = 0.f);


public:
	RAY	Get_MouseRayWorld(HWND g_hWnd, const unsigned int	g_iWinSizeX, const unsigned int	g_iWinSizeY);
	RAY	Get_MouseRayLocal(HWND g_hWnd, const unsigned int	g_iWinSizeX, const unsigned int	g_iWinSizeY, _matrix matWorld);

	_bool		Picking_Mesh(RAY ray, _float3 * out, vector<class CMesh*>* Meshes);
	_bool		Picking_Vertex(RAY ray, _float3 * out, _uint triNum, VTXMESH * pVertices, _uint * pIndices);


	HRESULT		Load_Json(string _strPath, json & pOut);
	HRESULT		Save_Json(string _strPath, json _json);

	void		String_To_WString(string _string, wstring& _wstring);
	void		WString_To_String(wstring _wstring, string& _string);


private:
	class CGraphic_Device*			m_pGraphic_Device = { nullptr };
	class CTimer_Manager*			m_pTimer_Manager = { nullptr };
	class CLevel_Manager*			m_pLevel_Manager = { nullptr };
	class CObject_Manager*			m_pObject_Manager = { nullptr };
	class CComponent_Manager*		m_pComponent_Manager = { nullptr };
	class CRenderer*				m_pRenderer = { nullptr };
	class CPipeLine*				m_pPipeLine = { nullptr };
	class CInput_Device*			m_pInput_Device = { nullptr };
	class CFont_Manager*			m_pFonts_Manager = { nullptr };
public:
	void Release_Manager();
	static void Release_Engine();
};

END