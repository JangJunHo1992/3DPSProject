#pragma once
#include "Character_Client.h"

BEGIN(Client)

class CVarg abstract : public CCharacter_Client
{
protected:
	CVarg(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVarg(const CVarg& rhs);
	virtual ~CVarg() = default;

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
	enum VargState
	{
		Add_NUll,
		AddUp_Block,
		AddUp_Defance_POSE,
		AvoidAttack1,
		AvoidB,
		AvoidL,
		AvoidR,
		ComboAttack1_1,
		ComboAttack1_2,
		ComboAttack1_3,
		ComboAttack2_1,
		ComboAttack2_2,
		ComboAttack2_2b,
		ComboAttack2_2b1,
		ComboAttack3_1,
		Dead,
		Dead_Pose,
		FightStart_Demo,
		HurtF,
		Idle,
		IdleGeneral,
		RaidAttack1,
		RaidAttack2,
		RunF,
		RunF_1,
		RunF_Start,
		Seq_BossFightStart,
		Seq_TutorialBossFightStart,
		SPAttack1_Catch,
		SPAttack1_CatchSeq1,
		SPAttack1_Fail,
		SPAttack1_Roar,
		SPAttack1_Roar_GetUp,
		SPAttack1_Run,
		StunEnd,
		StunLoop,
		StunStart,
		TakeExecution_Dead,
		TakeExecution_End,
		TakeExecution_Loop,
		TakeExecution_NoDeadEnd,
		TakeExecution_Start_FIX,
		TakeParry_FIX,
		TurnAttack1,
		TurnL90,
		TurnR90,
		WalkB,
		WalkF,
		WalkL,
		WalkR
	};
};

END