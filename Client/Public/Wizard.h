#pragma once

#include "Character_Client.h"


BEGIN(Client)

class CWizard abstract : public CCharacter_Client
{

protected:
	CWizard(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWizard(const CWizard& rhs);
	virtual ~CWizard() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Ready_PartObjects() override;

public:
	virtual void Free() override;

public:
	enum Wizard_State
	{
		ThirdPerson_Jump,
		ThirdPerson_Idle,
		ThirdPerson_Jump_Loop,
		ThirdPerson_Jump_Start,
		ThirdPerson_Run,
		ThirdPerson_Walk,

		Wizard_ATK_Skill01,
		Wizard_ATK_Skill02,
		Wizard_ATK_Skill03,
		Wizard_ATK_Skill04,
		Wizard_ATK_Skill05,
		Wizard_ATK_Skill06,
		Wizard_ATK_Skill07,
		Wizard_ATK_Skill08,
		Wizard_ATK_Skill09,
		Wizard_ATK_Skill10,
		Wizard_ATK_Skill11,
		Wizard_ATK_Skill12,
		Wizard_ATK_Skill13,
		Wizard_ATK_Skill14,
		Wizard_ATK_Skill15,
		Wizard_ATK_Skill16,
		Wizard_ATK_Skill17,
		Wizard_ATK_Skill18,
		Wizard_ATK_Skill19,
		Wizard_ATK_Skill20,
		Wizard_ATK_Skill_Casting_End,
		Wizard_ATK_Skill_Casting_Loop,
		Wizard_ATK_Skill_Casting_Start,
		Wizard_Avoid_Back,
		Wizard_Avoid_Front,
		Wizard_Avoid_Left,
		Wizard_Avoid_Right,
		Wizard_Dead,
		Wizard_Down_End,
		Wizard_Down_Loop,
		Wizard_Down_Start,
		Wizard_Equip,
		Wizard_Hit_Body_Back,
		Wizard_Hit_Body_Front,
		Wizard_Hit_Body_Left,
		Wizard_Hit_Body_Right,
		Wizard_Hit_Bodystrong_Back,
		Wizard_Hit_Bodystrong_Front,
		Wizard_Hit_Bodystrong_Left,
		Wizard_Hit_Bodystrong_Right,
		Wizard_Hit_Head_Back,
		Wizard_Hit_Head_Front,
		Wizard_Hit_Head_Left,
		Wizard_Hit_Head_Right,
		Wizard_Idle00,
		Wizard_Idle00_Reverse,
		Wizard_Idle01,
		Wizard_Idle02,
		Wizard_Idle03,
		Wizard_Idle04,
		Wizard_Idle05,
		Wizard_Idle_Foot_Change,
		Wizard_Jump,
		Wizard_Jump_Landing,
		Wizard_Jump_Loop,
		Wizard_Jump_Start,
		Wizard_Jump_Up,
		Wizard_Jump_UpZ0,
		Wizard_Jump_UpZ1,
		Wizard_JumpZ0,
		Wizard_JumpZ1,
		Wizard_Knockdown_Knee_End,
		Wizard_Knockdown_Knee_Loop,
		Wizard_Knockdown_Knee_Start,
		Wizard_Move_Run,
		Wizard_Move_Strafe_Run_Back,
		Wizard_Move_Strafe_Run_Front,
		Wizard_Move_Strafe_Run_Left,
		Wizard_Move_Strafe_Run_Left135,
		Wizard_Move_Strafe_Run_Left45,
		Wizard_Move_Strafe_Run_Right,
		Wizard_Move_Strafe_Run_Right135,
		Wizard_Move_Strafe_Run_Right45,
		Wizard_Move_Strafe_Walk_Back,
		Wizard_Move_Strafe_Walk_Front,
		Wizard_Move_Strafe_Walk_Left,
		Wizard_Move_Strafe_Walk_Left135,
		Wizard_Move_Strafe_Walk_Left45,
		Wizard_Move_Strafe_Walk_Right,
		Wizard_Move_Strafe_Walk_Right135,
		Wizard_Move_Strafe_Walk_Right45,
		Wizard_Move_Walk_Start,
		Wizard_Move_Walk_Stop,
		Wizard_Pose_Look_C,
		Wizard_Pose_Look_D,
		Wizard_Pose_Look_L,
		Wizard_Pose_Look_LD,
		Wizard_Pose_Look_LU,
		Wizard_Pose_Look_R,
		Wizard_Pose_Look_RD,
		Wizard_Pose_Look_RU,
		Wizard_Pose_Look_U,
		Wizard_Stun_End,
		Wizard_Stun_Loop,
		Wizard_Stun_Start,
		Wizard_Turn_L180,
		Wizard_Turn_L90,
		Wizard_Turn_R180,
		Wizard_Turn_R90,
		Wizard_Unequip,
	};
};

END