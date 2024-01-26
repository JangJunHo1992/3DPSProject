#pragma once
#include "Character_Client.h"

BEGIN(Client)

class CMagician abstract : public CCharacter_Client
{
protected:
	CMagician(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician(const CMagician& rhs);
	virtual ~CMagician() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
public:
	_bool Collision_Chcek(LEVEL eLevel);
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
	CCharacter::CharStat MagicianStatus = {};


public:
	virtual void Free() override;

public:
	enum MagicianState
	{
		Appear_B,
		Appear_F,
		Appear_L,
		Appear_R,
		CaneAttack03,
		CaneAttack1Appear,
		CaneAttack02,
		Disappear,
		DisappearMove_B,
		DisappearMove_BShort,
		DisappearMove_F,
		DisappearMove_L,
		DisappearMove_LShort,
		DisappearMove_R,
		DisappearMove_RShort,
		DisappearIdle,
		HurtCounter,
		HurtDisappear,
		HurtFL,
		HurtFR,
		HurtSL,
		HurtSR,
		Idle,
		Idle2,
		JumpAppear,
		KickCombo,
		Parry01,
		ParryAttack01,
		ParryAttack01_2,
		ParryJump,
		Shoot1,
		Shoot2,
		Shoot3,
		Shoot_2_V1,
		ShootCombo1_1,
		ShootCombo1_2,
		shotJump,
		SPAttack1,
		SPAttack1_Suc,
		SPAttack2,
		SPAttack2_start,
		SPAttack2_Suc,
		Sprinkle,
		Stage2_Attack02,
		Stage2_Attack03,
		Stage2_Attack04,
		Stage2_Attack05,
		Stage2_Attack01,
		Stage2_Cane2Sword,
		Stage2_JumpAppear,
		Stage2_SwordAttackCombo,
		StunEnd_Cane,
		StunEnd_Sword,
		StunLoop_Cane,
		StunLoop_Sword,
		StunStart_Cane,
		StunStart_Sword,
		SwordAttack1,
		SwordAttack1Appear,
		SwordAttack2,
		SwordAttack2_V2,
		SwordAttack2Disappear,
		VSCorvus_TakeExecution,
		VSCorvus_TakeExecutionDisappear,
		Walk2F,
		Walk2L,
		Walk2R,
		WalkB,
		WalkBDisappear,
		WalkF,
		WalkFDisappear,
		WalkL,
		WalkLDisappear,
		WalkR,
		WalkRDisappear,
		BossfightStart

	};
};

END