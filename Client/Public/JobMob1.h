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

	//public:
	//	virtual void Write_Json(json& Out_Json) override;

protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Ready_PartObjects() override;
	//HRESULT Bind_ShaderResources();


public:
	virtual void Free() override;

public:
	enum JobMob1State
	{
		Idle,
		RunF,
		TurnL,
		TurnR,
		Attack1,
		Attack2,
		Attack3,
		Attack4,
		Attack5,
		Attack6,
		Die,
		Fall_end,
		Fall_Loop,
		Fall_Ground,
		FallHurt_B,
		HurtCounter,
		HurtFall_end_FaceUp,
		HurtKnockBack,
		HurtKnockDownB,
		HurtKnockUP_Start,
		HrutL_F,
		HurtLieGetup_FaceDown,
		HurtLieGetup_FaceUP,
		HurtLieLoop_FaceDown,
		HurtLieLoop_FaceUP,
		HurtS_FL,
		HurtS_FR,
		HurtStunEnd,
		HurtStunLoop,
		HurtStunStart,
		IdleGeneral,
		Sit_cough,
		Sit_Idle,
		SitToIdle,
		SP01,
		SP01_Attack01,
		SP_Idle1,
		SP_Idle_End,
		VSAmbushedDead,
		VSTakeExcution,
		VSTakeExcutionDead,
		WalkB,
		WalkBL,
		WalkF,
		WalkFL,
		WalkFR,
		WalkL,
		WalkR,
		Parry

	};
};

END