#pragma once

#include "Character_Client.h"

BEGIN(Client)

class CKnightGuard abstract : public CCharacter_Client
{


protected:
	CKnightGuard(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKnightGuard(const CKnightGuard& rhs);
	virtual ~CKnightGuard() = default;

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
	enum KnightGuard_State
	{
		
		Spear_Shield_Attack_01,
		Spear_Shield_Attack_02,
		Spear_Shield_Attack_03,
		Spear_Shield_Attack_04,
		Spear_Shield_Attack_05_Kick,
		Spear_Shield_Attack_Shield,
		Spear_Shield_Attack_Shield02,
		Spear_Shield_Attack_Shield03,
		Spear_Shield_Attack_Shield04,
		Spear_Shield_Attack_Shield05,
		Spear_Shield_Attack_StingDown,
		Spear_Shield_Attack_Swing,
		Spear_Shield_Attacker_Idle,
		Spear_Shield_Avoid_Back,
		Spear_Shield_Avoid_Front,
		Spear_Shield_Avoid_Left,
		Spear_Shield_Avoid_Right,
		Spear_Shield_Buff_01,
		Spear_Shield_Buff_02,
		Spear_Shield_Buff_03,
		Spear_Shield_Combo_Stings,
		Spear_Shield_Combo_Stings_01,
		Spear_Shield_Combo_Stings_02,
		Spear_Shield_Combo_Stings_03,
		Spear_Shield_Combo_Stings_04,
		Spear_Shield_Dash_Sting,
		Spear_Shield_Dead_01,
		Spear_Shield_Dead_02,
		Spear_Shield_Dead_03,
		Spear_Shield_Dead_04,
		Spear_Shield_Dead_05,
		Spear_Shield_Defence,
		Spear_Shield_Defence_Breaked,
		Spear_Shield_Defence_Mode_End,
		Spear_Shield_Defence_Mode_Loop,
		Spear_Shield_Defence_Mode_Start,
		Spear_Shield_Defence_Strafe_Run_Back,
		Spear_Shield_Defence_Strafe_Run_Back_L45,
		Spear_Shield_Defence_Strafe_Run_Back_R45,
		Spear_Shield_Defence_Strafe_Run_Front,
		Spear_Shield_Defence_Strafe_Run_Front_L45,
		Spear_Shield_Defence_Strafe_Run_Front_R45,
		Spear_Shield_Defence_Strafe_Run_Left,
		Spear_Shield_Defence_Strafe_Run_Right,
		Spear_Shield_Defence_Strafe_Walk_Back,
		Spear_Shield_Defence_Strafe_Walk_Back_L45,
		Spear_Shield_Defence_Strafe_Walk_Back_R45,
		Spear_Shield_Defence_Strafe_Walk_Front,
		Spear_Shield_Defence_Strafe_Walk_Front_L45,
		Spear_Shield_Defence_Strafe_Walk_Front_R45,
		Spear_Shield_Defence_Strafe_Walk_Left,
		Spear_Shield_Defence_Strafe_Walk_Right,
		Spear_Shield_Down_Bound_Down,
		Spear_Shield_Down_Bound_Down_High,
		Spear_Shield_Down_Bound_Up,
		Spear_Shield_Down_Bound_Up_High,
		Spear_Shield_Down_Knockdown_Down,
		Spear_Shield_Down_Knockdown_Up01,
		Spear_Shield_Down_Knockdown_Up02,
		Spear_Shield_Down_Knockdown_Up03,
		Spear_Shield_Down_Liedown_Hit,
		Spear_Shield_Down_Liedown_Idle_Down,
		Spear_Shield_Down_Liedown_Idle_Up,
		Spear_Shield_Down_Wall_Liedown_Down,
		Spear_Shield_Down_Wall_Liedown_Up,
		Spear_Shield_Equip,
		Spear_Shield_Finisher01_A,
		Spear_Shield_Finisher01_B,
		Spear_Shield_Finisher02_A,
		Spear_Shield_Finisher02_B,
		Spear_Shield_Hit_Body_Back,
		Spear_Shield_Hit_Body_Front,
		Spear_Shield_Hit_Body_Left,
		Spear_Shield_Hit_Body_Right,
		Spear_Shield_Hit_Head_Back,
		Spear_Shield_Hit_Head_Front,
		Spear_Shield_Hit_Head_Left,
		Spear_Shield_Hit_Head_Right,
		Spear_Shield_Hit_Heavy_Back,
		Spear_Shield_Hit_Heavy_Front,
		Spear_Shield_Hit_Heavy_Left,
		Spear_Shield_Hit_Heavy_Right,
		Spear_Shield_Jump,
		Spear_Shield_JumpZ1,
		Spear_Shield_Move_Run_Sprint,
		Spear_Shield_Pose_Look_C,
		Spear_Shield_Pose_Look_D,
		Spear_Shield_Pose_Look_L,
		Spear_Shield_Pose_Look_LD,
		Spear_Shield_Pose_Look_LU,
		Spear_Shield_Pose_Look_R,
		Spear_Shield_Pose_Look_RD,
		Spear_Shield_Pose_Look_RU,
		Spear_Shield_Pose_Look_U,
		Spear_Shield_Rise_01,
		Spear_Shield_Rise_02,
		Spear_Shield_Rise_03,
		Spear_Shield_Rise_04,
		Spear_Shield_Rise_Down,
		Spear_Shield_Roll_Back,
		Spear_Shield_Roll_Front,
		Spear_Shield_Roll_Left,
		Spear_Shield_Roll_Right,
		Spear_Shield_Run_Strafe_Back,
		Spear_Shield_Run_Strafe_Back_L45,
		Spear_Shield_Run_Strafe_Back_R45,
		Spear_Shield_Run_Strafe_Front,
		Spear_Shield_Run_Strafe_Front_L45,
		Spear_Shield_Run_Strafe_Front_R45,
		Spear_Shield_Run_Strafe_Left,
		Spear_Shield_Run_Strafe_Right,
		Spear_Shield_Shield_Dash1,
		Spear_Shield_Shield_Dash2,
		Spear_Shield_Shield_Dash3,
		Spear_Shield_Stun,
		Spear_Shield_Throw_Spear01,
		Spear_Shield_Turn_90L,
		Spear_Shield_Turn_90R,
		Spear_Shield_Unequip,
		Spear_Shield_Victim_Idle,
		Spear_Shield_Walk_Strafe_Back,
		Spear_Shield_Walk_Strafe_Back_L45,
		Spear_Shield_Walk_Strafe_Back_R45,
		Spear_Shield_Walk_Strafe_Front,
		Spear_Shield_Walk_Strafe_Front_L45,
		Spear_Shield_Walk_Strafe_Front_R45,
		Spear_Shield_Walk_Strafe_Left,
		Spear_Shield_Walk_Strafe_Right,
	};
};

END