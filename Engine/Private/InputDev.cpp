#include "InputDev.h"
#include "GameInstance.h"

Engine::CInput_Device::CInput_Device()
{
}

HRESULT CInput_Device::Initialize(HINSTANCE hInst, HWND hWnd)
{
	if (FAILED(Ready_InputDev(hInst, hWnd)))
		return E_FAIL;

	return S_OK;
}

void Engine::CInput_Device::Tick(void)
{
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}
const _bool CInput_Device::Get_PickPos_Window(SimpleMath::Vector2* vPickPos)
{
	if (!m_bFocus) return FALSE;
	
	POINT tMousePos{};

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	{
		HWND	hWnd = pGameInstance->Get_GraphicDesc().hWnd;

		GetCursorPos(&tMousePos);
		ScreenToClient(hWnd, &tMousePos);

		(*vPickPos).x = (_float)tMousePos.x;
		(*vPickPos).y = (_float)tMousePos.y;
	}
	RELEASE_INSTANCE(CGameInstance);

	return TRUE;
}

//_bool CInput_Device::Key_Up(const _int& _iKey)
//{
//	if (!m_bFocus) return FALSE;
//
//	if (m_bKeyState[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
//	{
//		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
//		return true;
//	}
//
//	for (int i = 0; i < VK_MAX; ++i)
//	{
//		if (!m_bKeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
//			m_bKeyState[i] = !m_bKeyState[i];
//	}
//
//	return false;
//}
//
//_bool CInput_Device::Key_Down(const _int& _iKey)
//{
//	if (!m_bFocus) return FALSE;
//
//	if (!m_bKeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
//	{
//		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
//		return true;
//	}
//
//	for (int i = 0; i < VK_MAX; ++i)
//	{
//		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
//			m_bKeyState[i] = !m_bKeyState[i];
//	}
//
//	return false;
//}
//
//_bool CInput_Device::Key_Pressing(const _int& _iKey)
//{
//	if (!m_bFocus) return FALSE;
//
//	if (GetAsyncKeyState(_iKey) & 0x8000)
//		return true;
//
//	return false;
//}

_bool CInput_Device::Key_Pressing(_ubyte byKeyID)
{
	if (m_byKeyState[byKeyID] & 0x80)
		return true;

	return false;
}

_bool CInput_Device::Key_Down(_ubyte byKeyID)
{
	// 이전에 눌린 적이 없고, 지금 눌렸을 때

	if (!m_byKeyStateBF[byKeyID] && (m_byKeyState[byKeyID] & 0x80))
	{
		m_byKeyStateBF[byKeyID] = !m_byKeyStateBF[byKeyID];
		return true;
	}

	for (int i = 0; i < 256; ++i)
	{
		if (m_byKeyStateBF[i] && !(m_byKeyState[i] & 0x80))
			m_byKeyStateBF[i] = !m_byKeyStateBF[i];
	}

	return false;
}

_bool CInput_Device::Key_Up(_ubyte byKeyID)
{
	// 이전에 눌린 적이 있고, 현재는 눌리지 않은 경우
	if (m_byKeyStateBF[byKeyID] && !(m_byKeyState[byKeyID] & 0x80))
	{
		m_byKeyStateBF[byKeyID] = !m_byKeyStateBF[byKeyID];
		return true;
	}

	for (int i = 0; i < 256; ++i)
	{
		if (!m_byKeyStateBF[byKeyID] && (m_byKeyState[byKeyID] & 0x80))
			m_byKeyStateBF[i] = !m_byKeyStateBF[i];
	}

	return false;
}

_bool CInput_Device::Mouse_Pressing(MOUSEKEYSTATE eMouseID)
{
	if (m_tMouseState.Buttons[eMouseID] & 0x80)
		return true;

	return false;
}

_bool CInput_Device::Mouse_Down(MOUSEKEYSTATE eMouseID)
{
	// 이전에 눌린 적이 없고, 지금 눌렸을 때

	if (!m_ubyMouseStateBF[eMouseID] && (m_tMouseState.Buttons[eMouseID] & 0x80))
	{
		m_ubyMouseStateBF[eMouseID] = !m_ubyMouseStateBF[eMouseID];
		return true;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (m_ubyMouseStateBF[i] && !(m_tMouseState.Buttons[i] & 0x80))
			m_ubyMouseStateBF[i] = !m_ubyMouseStateBF[i];
	}

	return false;
}

_bool CInput_Device::Mouse_Up(MOUSEKEYSTATE eMouseID)
{
	// 이전에 눌린 적이 있고, 현재는 눌리지 않은 경우
	if (m_ubyMouseStateBF[eMouseID] && !(m_tMouseState.Buttons[eMouseID] & 0x80))
	{
		m_ubyMouseStateBF[eMouseID] = !m_ubyMouseStateBF[eMouseID];
		return true;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (!m_ubyMouseStateBF[eMouseID] && (m_tMouseState.Buttons[eMouseID] & 0x80))
			m_ubyMouseStateBF[i] = !m_ubyMouseStateBF[i];
	}

	return false;
}

HRESULT Engine::CInput_Device::Ready_InputDev(HINSTANCE hInst, HWND hWnd)
{

	// DInput 컴객체를 생성하는 함수
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		return E_FAIL;

	// 키보드 객체 생성
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;

	// 생성된 키보드 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// 장치에 대한 독점권을 설정해주는 함수, (클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pKeyBoard->Acquire();


	// 마우스 객체 생성
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	// 생성된 마우스 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// 장치에 대한 독점권을 설정해주는 함수, 클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pMouse->Acquire();

	return S_OK;
}

void CInput_Device::Update_InputDev(void)
{
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}


CInput_Device* CInput_Device::Create(HINSTANCE hInst, HWND hWnd)
{
	CInput_Device* pInstance = new CInput_Device();

	if (FAILED(pInstance->Initialize(hInst, hWnd)))
	{
		MSG_BOX("Failed to Created : CInput_Device");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void Engine::CInput_Device::Free(void)
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInput);
}
