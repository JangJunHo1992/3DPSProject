#pragma once

#include "Client_Defines.h"
#include "Base.h"

/* 스레드를 생성한다. */
/* 생성한 스레드로 필요한 레벨의 자원을 로딩한다. */

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CLoader final : public CBase
{
private:
	CLoader(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CLoader() = default;

public:
	_bool isFinished() const {
		return m_isFinished;
	}
	void Set_isFinished(_bool _isFinished) { m_isFinished = _isFinished; }
public:	
	HRESULT Initialize(LEVEL eNextLevelID);

	void Print_LoadingText();

public:
	HRESULT Loading();
	HRESULT Loading_For_Logo_Level();

	HRESULT	Loading_For_Level(LEVEL eLEVEL);
	HRESULT Loading_For_GamePlay_Level();
	HRESULT Loading_For_GamePlay_BossStage1();
	HRESULT Loading_For_GamePlay_BossStage2();

	HRESULT Loading_For_Tool_Level();


private:
	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };
	CGameInstance*			m_pGameInstance = { nullptr };

private:
	HANDLE					m_hThread;
	CRITICAL_SECTION		m_CriticalSection;

private:
	LEVEL					m_eNextLevelID = { LEVEL_END };
	_tchar					m_szLoadingText[MAX_PATH] = TEXT("");
	_bool					m_isFinished = { false };
	_bool					m_bCheckgameplay = { false };
	_bool					m_bCheckMapTool = { false };
public:
	static CLoader * Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, LEVEL eNextLevelID);
	virtual void Free() override;
	
};

END


