#include "KeyMgr.h"

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyMgr::~CKeyMgr()
{
}

HRESULT CKeyMgr::Initialize(HINSTANCE hInst, HWND hWnd)
{
	// DInput 컴객체를 생성하는 함수
	if (FAILED(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK,
		NULL)))
		return E_FAIL;

	// 키보드 객체 생성
	if (FAILED(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;

	// 생성된 키보드 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// 장치에 대한 독점권을 설정해주는 함수, (클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pKeyBoard->Acquire();

	// 마우스 객체 생성
	if (FAILED(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	// 생성된 마우스 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// 장치에 대한 독점권을 설정해주는 함수, 클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pMouse->Acquire();

	return S_OK;
}


void CKeyMgr::Update_Key()
{
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

void CKeyMgr::LateUpdate_Key()
{
	// m_bKeyState에 대해 키 상태를 업데이트 합니다.
	for (int i = 0; i < MAX_DINPUT_KEY; ++i)
	{
		if (m_bKeyState[i] && !(Get_DIKeyState(i)))
			m_bKeyState[i] = !m_bKeyState[i];
		else if (!m_bKeyState[i] && (Get_DIKeyState(i)))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	for (int i = 0; i < MAX_DINPUT_MOUSE; ++i)
	{
		if (i <= 2)
		{
			if (m_bMouseState[i] && !(Get_DIMouseState((MOUSEKEYSTATE)i)))
				m_bMouseState[i] = !m_bMouseState[i];
			else if (!m_bMouseState[i] && (Get_DIMouseState((MOUSEKEYSTATE)i)))
				m_bMouseState[i] = !m_bMouseState[i];
		}
		else
		{
			switch ((MOUSEKEYSTATE)i)
			{
			case DIM_MWU:
			{
				if (m_bMouseState[i] && !(Get_DIMouseMove(DIMS_Z) > 0L))
					m_bMouseState[i] = !m_bMouseState[i];
				else if (!m_bMouseState[i] && (Get_DIMouseMove(DIMS_Z) > 0L))
					m_bMouseState[i] = !m_bMouseState[i];
				break;
			}
			case DIM_MWD:
			{
				if (m_bMouseState[i] && !(Get_DIMouseMove(DIMS_Z) < 0L))
					m_bMouseState[i] = !m_bMouseState[i];
				else if (!m_bMouseState[i] && (Get_DIMouseMove(DIMS_Z) < 0L))
					m_bMouseState[i] = !m_bMouseState[i];
				break;
			}
			}
		}
	}
}

CKeyMgr* CKeyMgr::Create(HINSTANCE hInst, HWND hWnd)
{
	CKeyMgr* pInstance = new CKeyMgr();

	if (FAILED(pInstance->Initialize(hInst, hWnd)))
	{
		MSG_BOX("Failed to Created : CKeyMgr");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CKeyMgr::Free()
{
	if (m_mapInputKeys.empty())
		return;

	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}