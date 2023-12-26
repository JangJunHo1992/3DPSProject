#pragma once

#include "Client_Defines.h"
#include "Character.h"

BEGIN(Engine)
class CShader;
class CModel;
END

BEGIN(Client)

class CRaider abstract : public CCharacter
{
public:
	enum Raider_State 
	{
		Great_DualBlade_anim_attack_01			,
		Great_DualBlade_anim_attack_02			,
		Great_DualBlade_anim_attack_03			,
		Great_DualBlade_anim_attack_04			,
		Great_DualBlade_anim_avoid_back			,
		Great_DualBlade_anim_avoid_front		,
		Great_DualBlade_anim_avoid_left			,
		Great_DualBlade_anim_avoid_right		,
		Great_DualBlade_anim_buff				,
		Great_DualBlade_anim_combo_01			,
		Great_DualBlade_anim_combo_01_1			,
		Great_DualBlade_anim_combo_01_2			,
		Great_DualBlade_anim_combo_01_3			,
		Great_DualBlade_anim_combo_01_4			,
		Great_DualBlade_anim_combo_01_5			,
		Great_DualBlade_anim_combo_02			,
		Great_DualBlade_anim_combo_02_1			,
		Great_DualBlade_anim_combo_02_2			,
		Great_DualBlade_anim_combo_02_3			,
		Great_DualBlade_anim_combo_02_4			,
		Great_DualBlade_anim_combo_03			,
		Great_DualBlade_anim_combo_03_1			,
		Great_DualBlade_anim_combo_03_2			,
		Great_DualBlade_anim_combo_03_3			,
		Great_DualBlade_anim_combo_03_4			,
		Great_DualBlade_anim_combo_03_5			,
		Great_DualBlade_anim_combo_04			,
		Great_DualBlade_anim_combo_04_1			,
		Great_DualBlade_anim_combo_04_2			,
		Great_DualBlade_anim_combo_04_3			,
		Great_DualBlade_anim_combo_05			,
		Great_DualBlade_anim_combo_05_1			,
		Great_DualBlade_anim_combo_05_2			,
		Great_DualBlade_anim_combo_05_3			,
		Great_DualBlade_anim_combo_05_4			,
		Great_DualBlade_anim_combo_05_5			,
		Great_DualBlade_anim_dead_01			,
		Great_DualBlade_anim_dead_02			,
		Great_DualBlade_anim_dead_03			,
		Great_DualBlade_anim_dead_04			,
		Great_DualBlade_anim_dead_05			,
		Great_DualBlade_anim_defense			,
		Great_DualBlade_anim_defense_end		,
		Great_DualBlade_anim_defense_loop		,
		Great_DualBlade_anim_defense_start		,
		Great_DualBlade_anim_down_01			,  
		Great_DualBlade_anim_down_02			,  
		Great_DualBlade_anim_equip				,  
		Great_DualBlade_anim_hit01				,  
		Great_DualBlade_anim_hit02				,  
		Great_DualBlade_anim_hit_head_back		,  
		Great_DualBlade_anim_hit_head_front		,   
		Great_DualBlade_anim_hit_head_left		,  
		Great_DualBlade_anim_hit_head_right		,   
		Great_DualBlade_anim_idle				,  
		Great_DualBlade_anim_jump				,  
		Great_DualBlade_anim_jumpZ				,  
		Great_DualBlade_anim_rise_01			,  
		Great_DualBlade_anim_rise_02			,  
		Great_DualBlade_anim_rise_left_up		,
		Great_DualBlade_anim_rise_right_up		,
		Great_DualBlade_anim_roll_back			,
		Great_DualBlade_anim_roll_front			,
		Great_DualBlade_anim_roll_left			,
		Great_DualBlade_anim_roll_right			,
		Great_DualBlade_anim_run_back			,
		Great_DualBlade_anim_run_backL45		,
		Great_DualBlade_anim_run_backR45		,
		Great_DualBlade_anim_run_front			,
		Great_DualBlade_anim_run_frontL45		,
		Great_DualBlade_anim_run_frontR45		,
		Great_DualBlade_anim_run_left			,
		Great_DualBlade_anim_run_right			,
		Great_DualBlade_anim_unequip			,
		Great_DualBlade_anim_walk_back			,
		Great_DualBlade_anim_walk_backL45		,
		Great_DualBlade_anim_walk_backR45		,
		Great_DualBlade_anim_walk_front			,
		Great_DualBlade_anim_walk_frontL45		,
		Great_DualBlade_anim_walk_frontR45		,
		Great_DualBlade_anim_walk_left			,
		Great_DualBlade_anim_walk_right			,
		Great_DualBlade_pose_lookC				, 
		Great_DualBlade_pose_lookD				, 
		Great_DualBlade_pose_lookL				, 
		Great_DualBlade_pose_lookLD				,
		Great_DualBlade_pose_lookLU				,
		Great_DualBlade_pose_lookR				, 
		Great_DualBlade_pose_lookRD				,
		Great_DualBlade_pose_lookRU				,
		Great_DualBlade_pose_lookU				, 

		Magical_Knight_Atk_Air01				,
		Magical_Knight_Atk_Air02				,
		Magical_Knight_Atk_Energy01				,
		Magical_Knight_Atk_Energy02				,
		Magical_Knight_Atk_Energy03				,
		Magical_Knight_Atk_Energy04				,
		Magical_Knight_Atk_Energy05				,
		Magical_Knight_Atk_Energy06				,
		Magical_Knight_Atk_Energy07				,
		Magical_Knight_Atk_Energy08				,
		Magical_Knight_Atk_Energy09_End			,
		Magical_Knight_Atk_Energy09_Loop		,
		Magical_Knight_Atk_Energy09_Start		,
		Magical_Knight_Atk_Energy10				,
		Magical_Knight_Atk_Energy11				,
		Magical_Knight_Atk_Sword01				,
		Magical_Knight_Atk_Sword02				,
		Magical_Knight_Atk_Sword03				,
		Magical_Knight_Atk_Sword04				,
		Magical_Knight_Atk_Sword05				,
		Magical_Knight_Atk_Sword06				,
		Magical_Knight_Atk_Sword07				,
		Magical_Knight_Atk_Sword08				,
		Magical_Knight_Avoid_Back				,
		Magical_Knight_Avoid_Front				,
		Magical_Knight_Avoid_Left				,
		Magical_Knight_Avoid_Right				,
		Magical_Knight_Buff01					,
		Magical_Knight_Combo01					,
		Magical_Knight_Combo01_1				,
		Magical_Knight_Combo01_2				,
		Magical_Knight_Combo01_3				,
		Magical_Knight_Combo01_4				,
		Magical_Knight_Combo02					,
		Magical_Knight_Combo02_1				,
		Magical_Knight_Combo02_2				,
		Magical_Knight_Combo02_3				,
		Magical_Knight_Dead_01					,
		Magical_Knight_Dead_02					,
		Magical_Knight_Dead_03					,
		Magical_Knight_Dead_04					,
		Magical_Knight_Dead_05					,
		Magical_Knight_Dodge_Back_Atk			,
		Magical_Knight_Down_Bound_Down			,
		Magical_Knight_Down_Bound_Down_High		,
		Magical_Knight_Down_Bound_Up			,
		Magical_Knight_Down_Bound_Up_High		,
		Magical_Knight_Down_Knockdown_Down		,
		Magical_Knight_Down_Knockdown_Up01		,
		Magical_Knight_Down_Knockdown_Up02		,
		Magical_Knight_Down_Knockdown_Up03		,
		Magical_Knight_Down_Liedown_Hit			,
		Magical_Knight_Down_Liedown_Idle_Down	,
		Magical_Knight_Down_Liedown_Idle_Up		,
		Magical_Knight_Down_Wall_Liedown_Down	,
		Magical_Knight_Down_Wall_Liedown_Up		,
		Magical_Knight_Equip					,
		Magical_Knight_Hit_Body_Back			,
		Magical_Knight_Hit_Body_Front			,
		Magical_Knight_Hit_Body_Left			,
		Magical_Knight_Hit_Body_Right			,
		Magical_Knight_Hit_Head_Back			,
		Magical_Knight_Hit_Head_Front			,
		Magical_Knight_Hit_Head_Left			,
		Magical_Knight_Hit_Head_Right			,
		Magical_Knight_Hit_Heavy_Back			,
		Magical_Knight_Hit_Heavy_Front			,
		Magical_Knight_Hit_Heavy_Left			,
		Magical_Knight_Hit_Heavy_Right			,
		Magical_Knight_Idle						,
		Magical_Knight_Jump						,
		Magical_Knight_JumpZ0					,
		Magical_Knight_JumpZ1					,
		Magical_Knight_Jump_Landing				,
		Magical_Knight_Jump_Link				,
		Magical_Knight_Jump_LinkZ0				,
		Magical_Knight_Jump_LinkZ1				,
		Magical_Knight_Jump_Loop				,
		Magical_Knight_Jump_Start				,
		Magical_Knight_Move_Run_01				,
		Magical_Knight_Move_Run_02				,
		Magical_Knight_Move_Step_Back			,
		Magical_Knight_Move_Step_Front			,
		Magical_Knight_Pose_Look_C				,
		Magical_Knight_Pose_Look_D				,
		Magical_Knight_Pose_Look_L				,
		Magical_Knight_Pose_Look_LD				,
		Magical_Knight_Pose_Look_LU				,
		Magical_Knight_Pose_Look_R				,
		Magical_Knight_Pose_Look_RD				,
		Magical_Knight_Pose_Look_RU				,
		Magical_Knight_Pose_Look_U				,
		Magical_Knight_Rise_01					,
		Magical_Knight_Rise_02					,
		Magical_Knight_Rise_03					,
		Magical_Knight_Rise_04					,
		Magical_Knight_Rise_Down				,
		Magical_Knight_Roll_Back				,
		Magical_Knight_Roll_Front				,
		Magical_Knight_Roll_Left				,
		Magical_Knight_Roll_Right				,
		Magical_Knight_Run_Back					,
		Magical_Knight_Run_Back_L45				,
		Magical_Knight_Run_Back_R45				,
		Magical_Knight_Run_Front				,
		Magical_Knight_Run_Front_L45				,
		Magical_Knight_Run_Front_R45				,
		Magical_Knight_Run_Left					,
		Magical_Knight_Run_Right				,
		Magical_Knight_Run_Start_L				,
		Magical_Knight_Run_Start_R				,
		Magical_Knight_Run_Stop_L				,
		Magical_Knight_Run_Stop_R				,
		Magical_Knight_Unequip					,
		Magical_Knight_Walk_Back				,
		Magical_Knight_Walk_Back_L45				,
		Magical_Knight_Walk_Back_R45				,
		Magical_Knight_Walk_Front				,
		Magical_Knight_Walk_Front_L45			,
		Magical_Knight_Walk_Front_R45			,
		Magical_Knight_Walk_Left				,
		Magical_Knight_Walk_Right				,
		Magical_Knight_Walk_Start_L				,
		Magical_Knight_Walk_Start_R				,
		Magical_Knight_Walk_Stop_L				,
		Magical_Knight_Walk_Stop_R				,
		

	};

protected:
	CRaider(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider(const CRaider& rhs);
	virtual ~CRaider() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual void Write_Json(json& Out_Json) override;

protected:
	CShader* m_pShaderCom = { nullptr };

	

protected:
	virtual HRESULT Ready_Components() PURE;
	HRESULT Ready_Components_Origin(LEVEL eLevel);
	HRESULT Bind_ShaderResources();


public:
	virtual void Free() override;
};

END