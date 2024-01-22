#pragma once
#include "Character_Client.h"

BEGIN(Client)

class CJobMob1 abstract : public CCharacter_Client
{
protected:
	CJobMob1(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob1(const CJobMob1& rhs);
	virtual ~CJobMob1() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual void Set_Hitted() override;
	virtual void Set_Dead() override;

public:
	virtual void Write_Json(json& Out_Json) override;

protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Ready_PartObjects() override;
	//HRESULT Bind_ShaderResources();
private:
	CCharacter::CharStat JobMob1Status;

public:
	virtual void Free() override;

public:
	enum JobMob1State
	{
		ComboA01,
		ComboB01,//달려오면서 어택
		ComboC01,//횡 베기 크게
		Dead,
		HurtCounter,
		HurtLieGetup_FaceDown,
		HurtLieLoop_FaceDown,
		HurtM_FL,
		HurtM_FR,
		HurtS_FL,
		HurtS_FR,
		HurtStunEnd,
		HurtStunLoop,
		HurtStunStart,
		Idle,
		IdleN,
		IdleN2Fight,
		Parry_R,
		RunF,
		Sit_Idle,
		SitToIdle,
		SP_Idle1,
		SP_Idle_End,
		TurnL,
		TurnLN,
		TurnR,
		TurnRN,
		VSTakeExcution1,
		VSTakeExcution3,
		VSTakeExcution4,
		WalkB,
		WalkBL,
		WalkBR,
		WalkF,
		WalkFL,
		WalkFN,
		WalkFR,
		WalkL,
		WalkR,

	};
};

END