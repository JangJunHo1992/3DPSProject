#pragma once


namespace Engine
{
	typedef struct tagGraphicDesc
	{
		enum WINMODE { WINMODE_FULL, WINMODE_WIN, WINMODE_END };

		WINMODE			eWinMode;
		HWND			hWnd;
		unsigned int	iBackBufferSizeX;
		unsigned int	iBackBufferSizeY;

	}GRAPHIC_DESC;

	typedef struct ENGINE_DLL tagVertex_Position_Texcoord
	{
		XMFLOAT3		vPosition;
		XMFLOAT2		vTexcoord;

		static const unsigned int					iNumElements = 2;
		static const D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	}VTXPOSTEX;

	typedef struct ENGINE_DLL tagVertex_Position_Normal_Texcoord
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexcoord;

		static const unsigned int					iNumElements = 3;
		static const D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	}VTXNORTEX;

	typedef struct _DIMOUSESTATE {
		_long      lX;
		_long      lY;
		_long      lZ;
		BYTE      Buttons[4];
	} DIMOUSESTATE, * LPDIMOUSESTATE;

	typedef struct ENGINE_DLL tagVTXMESH
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexcoord;
		XMFLOAT3		vTangent;

		static const unsigned int					iNumElements = 4;
		static const D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	}VTXMESH;

	typedef struct tagRayDesc
	{
		_float4	vOrigin;
		_float3	vDirection;
		float	fLength;
	}RAY;
}