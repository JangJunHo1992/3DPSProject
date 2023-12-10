#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CInput_Device : public CBase
{

private:
	CInput_Device();
	virtual ~CInput_Device() = default;

public:
	HRESULT Initialize(HINSTANCE hInst, HWND hWnd);
	void   Tick();
public:
	const _bool Is_Focus() const { return m_bFocus ? TRUE : FALSE; }
	const _bool Get_PickPos_Window(_Inout_ SimpleMath::Vector2* vPickPos);
public:
	_byte   Get_DIKeyState(_ubyte byKeyID)
	{
		return m_byKeyState[byKeyID];
	}

	_byte   Get_DIMouseState(MOUSEKEYSTATE eMouse)
	{
		return m_tMouseState.Buttons[eMouse];
	}

	_long   Get_DIMouseMove(MOUSEMOVESTATE eMouseState)
	{
		return *(((_long*)&m_tMouseState) + eMouseState);
	}
public:
	//_bool	Key_Up(const _int& _iKey);
	//_bool	Key_Down(const _int& _iKey);
	//_bool	Key_Pressing(const _int& _iKey);

	_bool	Key_Pressing(_ubyte byKeyID);
	_bool	Key_Down(_ubyte byKeyID);
	_bool	Key_Up(_ubyte byKeyID);

	_bool	Mouse_Pressing(MOUSEKEYSTATE eMouseID);
	_bool	Mouse_Down(MOUSEKEYSTATE eMouseID);
	_bool	Mouse_Up(MOUSEKEYSTATE eMouseID);

public:
	HRESULT Ready_InputDev(HINSTANCE hInst, HWND hWnd);
	void	Update_InputDev(void);

private:
	IDirectInput8* m_pInput = nullptr;

private:
	IDirectInputDevice8* m_pKeyBoard = nullptr;
	IDirectInputDevice8* m_pMouse = nullptr;

private:
	_byte               m_byKeyState[256];      // 키보드에 있는 모든 키값을 저장하기 위한 변수
	_byte				m_byKeyStateBF[256];
	DIMOUSESTATE        m_tMouseState;
	_byte				m_ubyMouseStateBF[4];


	//_bool				m_bKeyState[VK_MAX];
	HWND				m_bFocus{};
public:
	static CInput_Device* Create(HINSTANCE hInst, HWND hWnd);
	virtual void   Free(void);

};
END
