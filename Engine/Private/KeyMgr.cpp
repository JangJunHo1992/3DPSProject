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
	// DInput �İ�ü�� �����ϴ� �Լ�
	if (FAILED(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK,
		NULL)))
		return E_FAIL;

	// Ű���� ��ü ����
	if (FAILED(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;

	// ������ Ű���� ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// ��ġ�� ���� �������� �������ִ� �Լ�, (Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pKeyBoard->Acquire();

	// ���콺 ��ü ����
	if (FAILED(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
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
	// m_bKeyState�� ���� Ű ���¸� ������Ʈ �մϴ�.
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