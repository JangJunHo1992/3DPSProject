#pragma once
#include "Character_Client.h"

BEGIN(Client)

class CJobMob2 abstract : public CCharacter_Client
{
protected:
	CJobMob2(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob2(const CJobMob2& rhs);
	virtual ~CJobMob2() = default;

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
protected:
	CCharacter::CharStat JobMob2Status = {};

public:
	virtual void Free() override;

public:
	enum JobMob2State
	{
		VSTakeExcution,
		Attack1,
		Attack2,
		Attack3,
		Attack4,
		Attack5,
		AttackAfterRun,
		Die1,
		Die2,
		Fall_end,
		Fall_Loop,
		Fall_Ground,
		FallHurt_B,
		HurtCounter,
		HurtFall_end_FaceUp,
		HurtKnockBack,
		HurtKnockDownF,
		HurtKnockUP_Start,
		HrutL_F,
		HurtLieDie_FaceUp,
		HurtLieGetup_FaceDown,
		HurtLieGetup_FaceUP,
		HurtLieLoop_FaceDown,
		HurtLieLoop_FaceUP,
		HrutM_FL,
		HrutM_FR,
		HrutS_FL,
		HrutS_FR,
		HurtStunEnd,
		HurtStunHurt,
		HurtStunLoop,
		HurtStunStart,
		HurtXL_F,
		Idle,
		Parry,
		Run_N,
		RunRoot,
		Sit_Idle,
		SitToIdle,
		SP03,
		SP_Idle1,
		SP_Idle_End,
		TurnL,
		TurnR,
		VSTakeExcutionDead,
		WalkB,
		WalkF,
		WalkL,
		WalkR
		//뒤에 애니메이션 더있지만 굳이 필요 없을거 같음 
	};
};

END