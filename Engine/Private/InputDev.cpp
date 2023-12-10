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
	// ������ ���� ���� ����, ���� ������ ��

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
	// ������ ���� ���� �ְ�, ����� ������ ���� ���
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
	// ������ ���� ���� ����, ���� ������ ��

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
	// ������ ���� ���� �ְ�, ����� ������ ���� ���
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

	// DInput �İ�ü�� �����ϴ� �Լ�
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		return E_FAIL;

	// Ű���� ��ü ����
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;

	// ������ Ű���� ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// ��ġ�� ���� �������� �������ִ� �Լ�, (Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pKeyBoard->Acquire();


	// ���콺 ��ü ����
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
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
