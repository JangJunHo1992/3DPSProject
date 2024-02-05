#include "stdafx.h"
#include "Loader.h"
#include "GameInstance.h"
#include "BackGround.h"
#include "Navigation.h"
#include "Sky.h"
#include "Camera_Dynamic.h"
#include "Camera_Dynamic_Tool.h"
#include "SpringCamera.h"
#include "VIBuffer_Static_Terrain.h"
#include "VIBuffer_Dynamic_Plane.h"
#include "Terrain_Tool.h"
#include "Terrain_GamePlay.h"
#include "ForkLift_Tool.h"
#include "ForkLift_GamePlay.h"
#include "Monster_Tool.h"
#include "Monster_GamePlay.h"
#include "Player_GamePlay.h"
#include "Player_Tool.h"
#include "Weapon_Player.h"
#include "Body_Player.h"

// #include "Particle_Blue.h"
// #include "Particle_Red.h"
#include "Particle_Custom.h"
#include "Particle_Custom_EffectTool.h"

#include "VIBuffer_Trail.h"
#include "Effect_Fire.h"
#include "Effect_Trail.h"
#include "Effect_Monster_Trail.h"

#include "Covus_Tool.h"
#include "Covus_GamePlay.h"
#include "Covus_Body_GamePlay.h"
#include "Covus_Body_Tool.h"
#include "Covus_Weapon_Saber_GamePlay.h"
#include "Covus_Weapon_Saber_Tool.h"
#include "Covus_Weapon_Saber_EffectTool.h"
#include "Covus_Weapon_Dagger_GamePlay.h"
#include "Covus_Weapon_Dagger_Tool.h"

#include "Magician_Tool.h"
#include "Magician_GamePlay.h"
#include "Magician_Body_GamePlay.h"
#include "Magician_Body_Tool.h"
#include "Magician_Cane_GamePlay.h"
#include "Magician_Cane_Tool.h"
#include "Magician_Card_GamePlay.h"
#include "Magician_Card_Tool.h"
#include "Magician_Card_Bullet_GamePlay.h"

#include "Varg_Tool.h"
#include "Varg_GamePlay.h"
#include "Varg_Body_GamePlay.h"
#include "Varg_Body_Tool.h"
#include "Varg_Weapon_GamePlay.h"
#include "Varg_Weapon_Tool.h"

#include "JobMob1_Tool.h"
#include "JobMob1_GamePlay.h"
#include "JobMob1_Body_GamePlay.h"
#include "JobMob1_Body_Tool.h"
#include "JobMob1_Weapon_GamePlay.h"
#include "JobMob1_Weapon_Tool.h"

#include "JobMob2_Tool.h"
#include "JobMob2_GamePlay.h"
#include "JobMob2_Body_GamePlay.h"
#include "JobMob2_Body_Tool.h"
#include "JobMob2_Weapon_GamePlay.h"
#include "JobMob2_Weapon_Tool.h"

#include "Model_Tool.h"
#include "Model_GamePlay.h"

#include "Map_GamePlay.h"
#include "Map_Tool.h"

#include "Map2_GamePlay.h"
#include "Map2_Tool.h"

#include "Map3_GamePlay.h"
#include "Map3_Tool.h"
#include <process.h>



CLoader::CLoader(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: m_pDevice(pDevice)
	, m_pContext(pContext)
	, m_pGameInstance(CGameInstance::GetInstance())
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

// typedef unsigned(__stdcall* _beginthreadex_proc_type)(void*);

_uint APIENTRY LoadingThread(void* pArg)
{
	CoInitializeEx(nullptr, 0);

	CLoader*		pLoader = (CLoader*)pArg;

	pLoader->Loading();
	
	return 0;
}


HRESULT CLoader::Initialize(LEVEL eNextLevelID)
{
	/* 어떤 레벨의 자원을 로드해야하는지? */
	m_eNextLevelID = eNextLevelID;

	InitializeCriticalSection(&m_CriticalSection);

	/* 스레드를 생성한다. */
	/* LoadingThread : 생성한 스레드가 가장 먼저 호출해야할 함수 */
	/* this : 위 함수를 호출하면서 인자로 전달할 데이터. */
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, LoadingThread, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

void CLoader::Print_LoadingText()
{
	SetWindowText(g_hWnd, m_szLoadingText);
}

HRESULT CLoader::Loading()
{
	EnterCriticalSection(&m_CriticalSection);

	HRESULT hr = 0;

	switch (m_eNextLevelID)
	{
	case LEVEL_LOGO:
		hr = Loading_For_Logo_Level();
		break;

	case LEVEL_GAMEPLAY:		
		hr = Loading_For_GamePlay_Level();
		break;
	case LEVEL_STAGE1:
		hr = Loading_For_GamePlay_Level();
		break;
	case LEVEL_BOSS1:
		hr = Loading_For_GamePlay_BossStage1();
		break;
	case LEVEL_BOSS2:
		hr = Loading_For_GamePlay_BossStage2();
		break;
	case LEVEL_TOOL:
		hr = Loading_For_Tool_Level();
		break;
	case LEVEL_EFFECT_TOOL:
		hr = Loading_For_Effect_Tool_Level();
		break;
	}

	if (FAILED(hr))
		return E_FAIL;

	LeaveCriticalSection(&m_CriticalSection);

	return S_OK;
}

HRESULT CLoader::Loading_For_Logo_Level()
{
	/* 로고 레벨에 필요한 자원을 로드하자. */
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로드하는 중입니다."));

	/* For.Prototype_Component_Texture_Logo */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_Logo"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Loading.png"),1))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Dissolve/187.png"), 1))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("모델를(을) 로드하는 중입니다."));
	

	lstrcpy(m_szLoadingText, TEXT("셰이더를(을) 로드하는 중입니다."));
	

	lstrcpy(m_szLoadingText, TEXT("원형객체를(을) 로드하는 중입니다."));

	/* For.Prototype_GameObject_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_BackGround"),
		CBackGround::Create(m_pDevice, m_pContext))))
		return E_FAIL;	

	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_For_Level(LEVEL eLEVEL)
{
	/* 게임플레이 레벨에 필요한 자원을 로드하자. */
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로드하는 중입니다."));

	/* For.Prototype_Component_Texture_Terrain */
// 	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain"),
// 		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Tile%d.dds"), 2))))
// 		return E_FAIL;
// 
// 	/* For.Prototype_Component_Texture_Terrain_Mask */
// 	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain_Mask"),
// 		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/MyMask.dds"), 1))))
// 		return E_FAIL;
// 
// 	/* For.Prototype_Component_Texture_Terrain_Brush */
// 	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain_Brush"),
// 		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Brush.png"), 1))))
// 		return E_FAIL;

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Snow"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Snow/Blood.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Sky */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Sky"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"), 4))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Fire */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Fire"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Fire/96_%d.png"), 36))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Trail */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Trail"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Trail/Varg.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_UVNoise"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Noise/%d.png"), 680))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_UVMask"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Mask/%d.png"), 902))))
		return E_FAIL;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	lstrcpy(m_szLoadingText, TEXT("모델를(을) 로드하는 중입니다."));

	_matrix		PivotMatrix;


	//Player
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus");
			string strFilePath = "../Bin/Resources/Models/Player/Player";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

			if (LEVEL_TOOL == eLEVEL)
			{

				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus_Weapon_Saber");
			string strFilePath = "../Bin/Resources/Models/Player/Weapon/Saber";

 			//_float fRadiusY = 270.0f;
 			//_float fRadiusZ = 90.0f;
			_float fRadiusX = 270.f;
			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX));
 				//* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
 				//* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus_Weapon_Dagger");
			string strFilePath = "../Bin/Resources/Models/Player/Weapon/Weapon";

			// 			_float fRadiusY = 270.0f;
			// 			_float fRadiusZ = 90.0f;

			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f);
			// 				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			// 				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}
	}
	//Magician- boss
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Magician");
			string strFilePath = "../Bin/Resources/Models/MagicianTest/Magician";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

			if (LEVEL_TOOL == eLEVEL)
			{

				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Magician_Cane");
			string strFilePath = "../Bin/Resources/Models/MagicianTest/Cane/MagicianWeapon";

			_float fRadiusX = 180.0f;
			_float fRadiusY = 180.0f;
			_float fRadiusZ = 180.0f;
			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
							* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
			 				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			 				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Magician_Card");
			string strFilePath = "../Bin/Resources/Models/JobMob2/Weapon/Weapon";

			_float fRadiusX = 180.0f;
			_float fRadiusY = 180.0f;
			_float fRadiusZ = 180.0f;
			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}

	}
	//Varg
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Varg");
			string strFilePath = "../Bin/Resources/Models/Varg/Varg";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

			if (LEVEL_TOOL == eLEVEL)
			{

				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Varg_Weapon");
			string strFilePath = "../Bin/Resources/Models/Varg/Weapon/VargWeapon";
						_float fRadiusX = 270.0f;
			 			_float fRadiusY = 180.0f;
			 			_float fRadiusZ = 180.0f;

						PivotMatrix =
							XMMatrixScaling(0.01f, 0.01f, 0.01f) 
							* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
							* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			 				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}
	}
	//JobMob1
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_JobMob1");
			string strFilePath = "../Bin/Resources/Models/JobMob1/JobMob1";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

			if (LEVEL_TOOL == eLEVEL)
			{

				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_JobMob1_Weapon");
			string strFilePath = "../Bin/Resources/Models/JobMob1/Weapon/Weapon";
			_float fRadiusX = 135.0f;
			_float fRadiusY = 180.0f;
			_float fRadiusZ = 180.0f;

			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}
	}
	//JobMob2
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_JobMob2");
			string strFilePath = "../Bin/Resources/Models/JobMob2/JobMob2";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

			if (LEVEL_TOOL == eLEVEL)
			{

				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_JobMob2_Weapon");
			string strFilePath = "../Bin/Resources/Models/JobMob2/Weapon/Weapon";
			_float fRadiusX = 180.0f;
			_float fRadiusY = 270.0f;
			_float fRadiusZ = 180.0f;

			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			}
		}
	}
	{
// 		const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Fiona");

// 		if (LEVEL_TOOL == eLEVEL)
// 		{
// 
// 		}
// 		else
// 		{
// 			/* For.Prototype_Component_Model_Fiona */
// 			PivotMatrix = XMMatrixRotationY(XMConvertToRadians(180.0f));
// 			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_GAMEPLAY, strPrototypeTag,
// 				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, "../Bin/Resources/Models/Fiona/Fiona", PivotMatrix))))
// 				return E_FAIL;
// 		}

	}
	//Map
	{
		const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Map");

		if (LEVEL_TOOL == eLEVEL)
		{
			PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_TOOL, strPrototypeTag,
				CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Stage1/Stage1", PivotMatrix))))
				return E_FAIL;
		}
		else
		{
			/* For.Prototype_Component_Model_Map */
			PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_GAMEPLAY, strPrototypeTag,
				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Stage1/Stage1", PivotMatrix))))
				return E_FAIL;
		}
	}
	//Map2
// 	{
// 		const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Map2");
// 
// 		if (LEVEL_TOOL == eLEVEL)
// 		{
// 			PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
// 			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_TOOL, strPrototypeTag,
// 				CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/BossStage1/BossStage1", PivotMatrix))))
// 				return E_FAIL;
// 		}
// 		else
// 		{
// 			
// 			/* For.Prototype_Component_Model_Map2 */
// 			PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
// 			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_BOSS1, strPrototypeTag,
// 				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/BossStage1/BossStage1", PivotMatrix))))
// 				return E_FAIL;
// 		}
// 	}
// 	//Map3
// 	{
// 		const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Map3");
// 
// 		if (LEVEL_TOOL == eLEVEL)
// 		{
// 			PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
// 			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_TOOL, strPrototypeTag,
// 				CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/BossStage2/BossStage2", PivotMatrix))))
// 				return E_FAIL;
// 		}
// 		else
// 		{
// 
// 			/* For.Prototype_Component_Model_Map2 */
// 			PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
// 			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_BOSS2, strPrototypeTag,
// 				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/BossStage2/BossStage2", PivotMatrix))))
// 				return E_FAIL;
// 		}
// 	}
	if (LEVEL_TOOL == eLEVEL) 
	{
		/* For.Prototype_Component_VIBuffer_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Terrain_Tool"),
			CVIBuffer_Dynamic_Terrain::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Height2.bmp")))))
			return E_FAIL;

		/* For.Prototype_Component_VIBuffer_Plane */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Plane_Tool"),
			CVIBuffer_Dynamic_Plane::Create(m_pDevice, m_pContext, 50, 50))))
			return E_FAIL;
	}
	else 
	{
		/* For.Prototype_Component_VIBuffer_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Terrain_GamePlay"),
			CVIBuffer_Static_Terrain::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Height2.bmp")))))
			return E_FAIL;
	}

	if (LEVEL_TOOL == eLEVEL)
	{
	}
	else 
	{
		/* For.Prototype_Component_VIBuffer_Cube */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Cube"),
			CVIBuffer_Cube::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	}
	/* For.Prototype_Component_VIBuffer_Particle_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Particle_Rect"),
		CVIBuffer_Particle_Rect::Create(m_pDevice, m_pContext, 100))))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Particle_Point */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Particle_Point"),
		CVIBuffer_Particle_Point::Create(m_pDevice, m_pContext, 100))))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Terrain */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Trail"),
		CVIBuffer_Trail::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Monster_Trail"),
		CVIBuffer_Trail::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	
	lstrcpy(m_szLoadingText, TEXT("셰이더를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Shader_VtxNorTex */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_VtxNorTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxNorTex.hlsl"), VTXNORTEX::Elements, VTXNORTEX::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Model */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_Model"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Model.hlsl"), VTXMESH::Elements, VTXMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_AnimModel */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_AnimModel"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_AnimModel.hlsl"), VTXANIMMESH::Elements, VTXANIMMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxCube */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_VtxCube"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxCube.hlsl"), VTXCUBE::Elements, VTXCUBE::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Particle_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_Particle_Rect"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Rect.hlsl"), VTX_PARTICLE_RECT::Elements, VTX_PARTICLE_RECT::iNumElements))))
		return E_FAIL;
	/* For.Prototype_Component_Shader_Particle_Point */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_Particle_Point"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Point.hlsl"), VTX_PARTICLE_POINT::Elements, VTX_PARTICLE_POINT::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Particle_Point */
// 	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_Particle_Point"),
// 		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Point.hlsl"), VTX_PARTICLE_POINT::Elements, VTX_PARTICLE_POINT::iNumElements))))
// 		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("네비게이션를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Navigation */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pContext, TEXT("../Bin/DataFiles/Stage1.dat")))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("콜리이더를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Collider_AABB */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Collider_AABB"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_AABB))))
		return E_FAIL;

	/* For.Prototype_Component_Collider_OBB */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Collider_OBB"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_OBB))))
		return E_FAIL;

	/* For.Prototype_Component_Collider_Sphere */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Collider_Sphere"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_SPHERE))))
		return E_FAIL;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	lstrcpy(m_szLoadingText, TEXT("원형객체를(을) 로드하는 중입니다."));

	/* For.Prototype_GameObject_Body_Player */
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Body_Player"),
		CBody_Player::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Weapon_Player */
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Weapon_Player"),
		CWeapon_Player::Create(m_pDevice, m_pContext))))
		return E_FAIL;


	{
		const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Player");


		if (LEVEL_TOOL == eLEVEL)
		{
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CPlayer_Tool::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
		else
		{
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CPlayer_GamePlay::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
	}

	{
		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Covus_Body");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CCovus_Body_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CCovus_Body_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Covus_Weapon_Dagger");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CCovus_Weapon_Dagger_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CCovus_Weapon_Dagger_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}
		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Covus_Weapon_Saber");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CCovus_Weapon_Saber_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CCovus_Weapon_Saber_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}
		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Covus");

			if (LEVEL_TOOL == eLEVEL)
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CCovus_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CCovus_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}
	}
	//Magician-boss
	{
		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Magician_Body");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CMagician_Body_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CMagician_Body_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Magician_Cane");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CMagician_Cane_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CMagician_Cane_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Magician_Card");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CMagician_Card_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CMagician_Card_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Magician_Card_Bullet");

		
			
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CMagician_Card_Bullet_GamePlay::Create(m_pDevice, m_pContext))))
				return E_FAIL;
			
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Magician");

			if (LEVEL_TOOL == eLEVEL)
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CMagician_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CMagician_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}
	}
	//Varg
	{
		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Varg_Body");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CVarg_Body_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CVarg_Body_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Varg_Weapon");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CVarg_Weapon_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CVarg_Weapon_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Varg");

			if (LEVEL_TOOL == eLEVEL)
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CVarg_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CVarg_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}
	}
	//JobMob1
	{
		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_JobMob1_Body");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob1_Body_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob1_Body_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_JobMob1_Weapon");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob1_Weapon_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob1_Weapon_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_JobMob1");

			if (LEVEL_TOOL == eLEVEL)
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob1_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob1_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}
	}
	//JobMob2
	{
		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_JobMob2_Body");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob2_Body_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob2_Body_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_JobMob2_Weapon");

			if (LEVEL_TOOL == eLEVEL)
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob2_Weapon_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob2_Weapon_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_GameObject_JobMob2");

			if (LEVEL_TOOL == eLEVEL)
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob2_Tool::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
			else
			{
				/* For.Prototype_GameObject_Raider */
				if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
					CJobMob2_GamePlay::Create(m_pDevice, m_pContext))))
					return E_FAIL;
			}
		}
	}

// 	{
// 		const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Monster");
// 
// 		if (LEVEL_TOOL == eLEVEL)
// 		{
// 
// 		}
// 		else
// 		{
// 			/* For.Prototype_GameObject_Monster */
// 			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
// 				CMonster_GamePlay::Create(m_pDevice, m_pContext))))
// 				return E_FAIL;
// 		}
// 	}

	//Map
	{
		const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Map");

		if (LEVEL_TOOL == eLEVEL)
		{
			/* For.Prototype_GameObject_ForkLift */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CMap_Tool::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
		else
		{
			/* For.Prototype_GameObject_ForkLift */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CMap_GamePlay::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
	}
	//Map2
	{
		const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Map2");

		if (LEVEL_TOOL == eLEVEL)
		{
			/* For.Prototype_GameObject_ForkLift */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CMap2_Tool::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
		else
		{
			/* For.Prototype_GameObject_ForkLift */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CMap2_GamePlay::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
	}
	//Map3
	{
		const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Map3");

		if (LEVEL_TOOL == eLEVEL)
		{
			/* For.Prototype_GameObject_ForkLift */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CMap3_Tool::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
		else
		{
			/* For.Prototype_GameObject_ForkLift */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CMap3_GamePlay::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
	}


	{
		const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Terrain");

		if (LEVEL_TOOL == eLEVEL)
		{
			/* For.Prototype_GameObject_Terrain */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CTerrain_Tool::Create(m_pDevice, m_pContext))))
				return E_FAIL;

			/* For.Prototype_GameObject_Terrain */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Plane"),
				CTerrain_Tool::Create(m_pDevice, m_pContext, true))))
				return E_FAIL;
		}
		else
		{
// 			/* For.Prototype_GameObject_Terrain */
// 			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
// 				CTerrain_GamePlay::Create(m_pDevice, m_pContext))))
// 				return E_FAIL;
		}
	}
	

	{
		const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Camera_Dynamic");

		if (LEVEL_TOOL == eLEVEL)
		{
			/* For.Prototype_GameObject_Camera_Dynamic */
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CCamera_Dynamic_Tool::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
		else
		{
			/* For.Prototype_GameObject_Camera_Dynamic */
// 			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
// 				CCamera_Dynamic::Create(m_pDevice, m_pContext))))
// 				return E_FAIL;
			if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
				CSpringCamera::Create(m_pDevice, m_pContext))))
				return E_FAIL;
		}
	}



	/* For.Prototype_GameObject_Sky */
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Sky"),
		CSky::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Particle_Blue */
// 	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Particle_Blue"),
// 		CParticle_Blue::Create(m_pDevice, m_pContext))))
// 		return E_FAIL;

	/* For.Prototype_GameObject_Particle_Red */
// 	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Particle_Red"),
// 		CParticle_Red::Create(m_pDevice, m_pContext))))
// 		return E_FAIL;
// 
// 	   	/* For.Prototype_GameObject_Particle_Custom*/
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Particle_Custom"),
		CParticle_Custom::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Fire*/
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Fire"),
		CEffect_Fire::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Trail*/
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Trail"),
		CEffect_Trail::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Monster_Trail*/
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Monster_Trail"),
		CEffect_Monster_Trail::Create(m_pDevice, m_pContext))))
		return E_FAIL;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;
	
	return S_OK;
}

HRESULT CLoader::Loading_For_GamePlay_Level()
{
	return Loading_For_Level(LEVEL_GAMEPLAY);
}

HRESULT CLoader::Loading_For_GamePlay_BossStage1()
{
	/* 게임플레이 레벨에 필요한 자원을 로드하자. */
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로드하는 중입니다."));

	/* For.Prototype_Component_Texture_Terrain */
// 	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain"),
// 		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Tile%d.dds"), 2))))
// 		return E_FAIL;
// 
// 	/* For.Prototype_Component_Texture_Terrain_Mask */
// 	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain_Mask"),
// 		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/MyMask.dds"), 1))))
// 		return E_FAIL;
// 
// 	/* For.Prototype_Component_Texture_Terrain_Brush */
// 	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain_Brush"),
// 		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Brush.png"), 1))))
// 		return E_FAIL;

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Texture_Snow"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Snow/Blood.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Sky */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Texture_Sky"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"), 4))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Trail */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Texture_Trail"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Trail/Varg.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Texture_UVNoise"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Noise/%d.png"), 680))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Texture_UVMask"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Mask/%d.png"), 902))))
		return E_FAIL;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	lstrcpy(m_szLoadingText, TEXT("모델를(을) 로드하는 중입니다."));

	_matrix		PivotMatrix;

	//Player
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus");
			string strFilePath = "../Bin/Resources/Models/Player/Player";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

		
			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, strPrototypeTag,
				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
				return E_FAIL;
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus_Weapon_Saber");
			string strFilePath = "../Bin/Resources/Models/Player/Weapon/Saber";

			//_float fRadiusY = 270.0f;
			//_float fRadiusZ = 90.0f;
			_float fRadiusX = 270.f;
			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX));
			//* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			//* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			
				if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus_Weapon_Dagger");
			string strFilePath = "../Bin/Resources/Models/Player/Weapon/Weapon";

			// 			_float fRadiusY = 270.0f;
			// 			_float fRadiusZ = 90.0f;

			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f);
			// 				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			// 				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

		
				if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			
		}
	}
	
	//Varg
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Varg");
			string strFilePath = "../Bin/Resources/Models/Varg/Varg";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		
			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, strPrototypeTag,
				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
				return E_FAIL;
			
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Varg_Weapon");
			string strFilePath = "../Bin/Resources/Models/Varg/Weapon/VargWeapon";
			_float fRadiusX = 270.0f;
			_float fRadiusY = 180.0f;
			_float fRadiusZ = 180.0f;

			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			
			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, strPrototypeTag,
				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
				return E_FAIL;
			
		}
	}


	//Map
	
	//Map2
	{
		const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Map2");

		
		/* For.Prototype_Component_Model_Map2 */
		PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_BOSS1, strPrototypeTag,
			CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/BossStage1/BossStage1", PivotMatrix))))
			return E_FAIL;
		
	}
	

	
		/* For.Prototype_Component_VIBuffer_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_VIBuffer_Terrain_GamePlay"),
			CVIBuffer_Static_Terrain::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Height2.bmp")))))
			return E_FAIL;

	
		/* For.Prototype_Component_VIBuffer_Cube */
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_VIBuffer_Cube"),
			CVIBuffer_Cube::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	
	/* For.Prototype_Component_VIBuffer_Particle_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_VIBuffer_Particle_Rect"),
		CVIBuffer_Particle_Rect::Create(m_pDevice, m_pContext, 100))))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Particle_Point */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_VIBuffer_Particle_Point"),
		CVIBuffer_Particle_Point::Create(m_pDevice, m_pContext, 100))))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Terrain */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_VIBuffer_Trail"),
		CVIBuffer_Trail::Create(m_pDevice, m_pContext))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_VIBuffer_Monster_Trail"),
		CVIBuffer_Trail::Create(m_pDevice, m_pContext))))
		return E_FAIL;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	lstrcpy(m_szLoadingText, TEXT("셰이더를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Shader_VtxNorTex */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Shader_VtxNorTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxNorTex.hlsl"), VTXNORTEX::Elements, VTXNORTEX::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Model */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Shader_Model"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Model.hlsl"), VTXMESH::Elements, VTXMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_AnimModel */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Shader_AnimModel"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_AnimModel.hlsl"), VTXANIMMESH::Elements, VTXANIMMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxCube */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Shader_VtxCube"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxCube.hlsl"), VTXCUBE::Elements, VTXCUBE::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Particle_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Shader_Particle_Rect"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Rect.hlsl"), VTX_PARTICLE_RECT::Elements, VTX_PARTICLE_RECT::iNumElements))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Shader_Particle_Point"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Point.hlsl"), VTX_PARTICLE_POINT::Elements, VTX_PARTICLE_POINT::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Particle_Point */
// 	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_Particle_Point"),
// 		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Point.hlsl"), VTX_PARTICLE_POINT::Elements, VTX_PARTICLE_POINT::iNumElements))))
// 		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("네비게이션를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Navigation */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pContext, TEXT("../Bin/DataFiles/Stage2.dat")))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("콜리이더를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Collider_AABB */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Collider_AABB"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_AABB))))
		return E_FAIL;

	/* For.Prototype_Component_Collider_OBB */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Collider_OBB"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_OBB))))
		return E_FAIL;

	/* For.Prototype_Component_Collider_Sphere */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS1, TEXT("Prototype_Component_Collider_Sphere"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_SPHERE))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;
	return S_OK;
}

HRESULT CLoader::Loading_For_GamePlay_BossStage2()
{
	/* 게임플레이 레벨에 필요한 자원을 로드하자. */
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로드하는 중입니다."));

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Texture_Snow"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Snow/Blood.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Sky */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Texture_Sky"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"), 4))))
		return E_FAIL;
	//----------------------------------------------------------------------------------------------------
	/* For.Prototype_Component_Texture_Trail */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Texture_Trail"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Trail/Varg.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Texture_UVNoise"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Noise/%d.png"), 680))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Texture_UVMask"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Mask/%d.png"), 902))))
		return E_FAIL;
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	lstrcpy(m_szLoadingText, TEXT("모델를(을) 로드하는 중입니다."));

	_matrix		PivotMatrix;

	//Player
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus");
			string strFilePath = "../Bin/Resources/Models/Player/Player";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

	
				if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus_Weapon_Saber");
			string strFilePath = "../Bin/Resources/Models/Player/Weapon/Saber";

			//_float fRadiusY = 270.0f;
			//_float fRadiusZ = 90.0f;
			_float fRadiusX = 270.f;
			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX));
			//* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			//* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			
				if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus_Weapon_Dagger");
			string strFilePath = "../Bin/Resources/Models/Player/Weapon/Weapon";

			// 			_float fRadiusY = 270.0f;
			// 			_float fRadiusZ = 90.0f;

			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f);
			// 				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
			// 				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

			
				if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			
		}
	}
	//Magician- boss
	{

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Magician");
			string strFilePath = "../Bin/Resources/Models/MagicianTest/Magician";
			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));


				if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Magician_Cane");
			string strFilePath = "../Bin/Resources/Models/MagicianTest/Cane/MagicianWeapon";

			_float fRadiusX = 180.0f;
			_float fRadiusY = 180.0f;
			_float fRadiusZ = 180.0f;
			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));


				if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, strPrototypeTag,
					CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
					return E_FAIL;
			
		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Magician_Card");
			string strFilePath = "../Bin/Resources/Models/JobMob2/Weapon/Weapon";

			_float fRadiusX = 180.0f;
			_float fRadiusY = 180.0f;
			_float fRadiusZ = 180.0f;
			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));


			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, strPrototypeTag,
				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
				return E_FAIL;

		}

		{
			const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Magician_Card_Bullet");
			string strFilePath = "../Bin/Resources/Models/JobMob2/Weapon/Weapon";

			_float fRadiusX = 180.0f;
			_float fRadiusY = 270.0f;
			_float fRadiusZ = 180.0f;
			PivotMatrix =
				XMMatrixScaling(0.01f, 0.01f, 0.01f)
				* XMMatrixRotationX(XMConvertToRadians(fRadiusX))
				* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
				* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));


			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, strPrototypeTag,
				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
				return E_FAIL;

		}
	
	}
	
	//Map3
	{
		const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Map3");

	
			/* For.Prototype_Component_Model_Map3 */
			PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
			if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_BOSS2, strPrototypeTag,
				CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/BossStage2/BossStage2", PivotMatrix))))
				return E_FAIL;
		
	}


		/* For.Prototype_Component_VIBuffer_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_VIBuffer_Terrain_GamePlay"),
			CVIBuffer_Static_Terrain::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Height2.bmp")))))
			return E_FAIL;
	

	
		/* For.Prototype_Component_VIBuffer_Cube */
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_VIBuffer_Cube"),
			CVIBuffer_Cube::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	
	/* For.Prototype_Component_VIBuffer_Particle_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_VIBuffer_Particle_Rect"),
		CVIBuffer_Particle_Rect::Create(m_pDevice, m_pContext, 100))))
		return E_FAIL;


// 	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Plane_Tool"),
// 		CVIBuffer_Dynamic_Plane::Create(m_pDevice, m_pContext, 50, 50))))
// 		return E_FAIL;
	/* For.Prototype_Component_VIBuffer_Particle_Point */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_VIBuffer_Particle_Point"),
		CVIBuffer_Particle_Point::Create(m_pDevice, m_pContext, 100))))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Terrain */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_VIBuffer_Trail"),
		CVIBuffer_Trail::Create(m_pDevice, m_pContext))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_VIBuffer_Monster_Trail"),
		CVIBuffer_Trail::Create(m_pDevice, m_pContext))))
		return E_FAIL;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	lstrcpy(m_szLoadingText, TEXT("셰이더를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Shader_VtxNorTex */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Shader_VtxNorTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxNorTex.hlsl"), VTXNORTEX::Elements, VTXNORTEX::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Model */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Shader_Model"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Model.hlsl"), VTXMESH::Elements, VTXMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_AnimModel */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Shader_AnimModel"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_AnimModel.hlsl"), VTXANIMMESH::Elements, VTXANIMMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxCube */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Shader_VtxCube"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxCube.hlsl"), VTXCUBE::Elements, VTXCUBE::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Particle_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Shader_Particle_Rect"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Rect.hlsl"), VTX_PARTICLE_RECT::Elements, VTX_PARTICLE_RECT::iNumElements))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Shader_Particle_Point"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Point.hlsl"), VTX_PARTICLE_POINT::Elements, VTX_PARTICLE_POINT::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Particle_Point */
// 	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_Particle_Point"),
// 		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Point.hlsl"), VTX_PARTICLE_POINT::Elements, VTX_PARTICLE_POINT::iNumElements))))
// 		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("네비게이션를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Navigation */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pContext, TEXT("../Bin/DataFiles/Stage3.dat")))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("콜리이더를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Collider_AABB */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Collider_AABB"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_AABB))))
		return E_FAIL;

	/* For.Prototype_Component_Collider_OBB */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Collider_OBB"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_OBB))))
		return E_FAIL;

	/* For.Prototype_Component_Collider_Sphere */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_BOSS2, TEXT("Prototype_Component_Collider_Sphere"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_SPHERE))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_For_Effect_Tool_Level()
{
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로드하는 중입니다."));
	/* For.Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_Texture_Snow"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Particle/0.png"), 1))))
		return E_FAIL;

	///* For.Prototype_Component_Texture_Sky */
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_Texture_Night"),
	//	CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/SkyBox/Night.dds"), 1))))
	//	return E_FAIL;


	lstrcpy(m_szLoadingText, TEXT("모델를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_VIBuffer_Particle_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_VIBuffer_Particle_Rect"),
		CVIBuffer_Particle_Rect::Create(m_pDevice, m_pContext, 100))))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Particle_Point */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_VIBuffer_Particle_Point"),
		CVIBuffer_Particle_Point::Create(m_pDevice, m_pContext, 100))))
		return E_FAIL;
	//대상이 되는 무기 

	{
		const wstring& strPrototypeTag = TEXT("Prototype_Component_Model_Covus_Weapon_Saber");
		string strFilePath = "../Bin/Resources/Models/Player/Weapon/Saber";

		//_float fRadiusY = 270.0f;
		//_float fRadiusZ = 90.0f;
		_float fRadiusX = 270.f;
		_matrix PivotMatrix =
			XMMatrixScaling(0.01f, 0.01f, 0.01f)
			* XMMatrixRotationX(XMConvertToRadians(fRadiusX));
		//* XMMatrixRotationY(XMConvertToRadians(fRadiusY))
		//* XMMatrixRotationZ(XMConvertToRadians(fRadiusZ));

		
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_EFFECT_TOOL, strPrototypeTag,
			CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, strFilePath, PivotMatrix))))
			return E_FAIL;
		
	}

	lstrcpy(m_szLoadingText, TEXT("셰이더를(을) 로드하는 중입니다."));

	/* For.Prototype_Component_Shader_Particle_Point */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_Shader_Particle_Point"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Particle_Point.hlsl"), VTX_PARTICLE_POINT::Elements, VTX_PARTICLE_POINT::iNumElements))))
		return E_FAIL;


	/* For.Prototype_Component_Shader_Model */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_Shader_Model"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Model.hlsl"), VTXMESH::Elements, VTXMESH::iNumElements))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("원형객체를(을) 로드하는 중입니다."));


	/* For.Prototype_GameObject_Particle_Custom*/
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Particle_Custom"),
		CParticle_Custom_EffectTool::Create(m_pDevice, m_pContext))))
		return E_FAIL;


	const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Camera_Dynamic");
	/* For.Prototype_GameObject_Camera_Dynamic */
	if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
		CCamera_Dynamic_Tool::Create(m_pDevice, m_pContext))))
		return E_FAIL;
// 
	//원형 객체
	{
		const wstring& strPrototypeTag = TEXT("Prototype_GameObject_Covus_Weapon_Saber");

		if (FAILED(m_pGameInstance->Add_Prototype_Object(strPrototypeTag,
			CCovus_Weapon_Saber_EffectTool::Create(m_pDevice, m_pContext))))
			return E_FAIL;

	}

	//if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Sky"),
	//	CSky::Create(m_pDevice, m_pContext))))
	//	return E_FAIL;


	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_For_Tool_Level()
{
	return Loading_For_Level(LEVEL_TOOL);
}

CLoader * CLoader::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, LEVEL eNextLevelID)
{
	CLoader*		pInstance = new CLoader(pDevice, pContext);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	DeleteObject(m_hThread);

	CloseHandle(m_hThread);

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}
