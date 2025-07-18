#pragma once

#include "Character_Client.h"

BEGIN(Client)

class CCovus abstract : public CCharacter_Client
{
public:
	enum PlayerState
	{
		Approach,
		Healing2_Blend,
		Healing2_InPlace,
		Healing_Big,
		Healing_Little,
		Lobby_FirstWakeUp,
		Lobby_idle1,
		Lobby_idle1_end,
		Lobby_idle2,
		Lobby_idle2_end,
		QuicklyRecoverUp_B,
		QuicklyRecoverUp_F,
		QuicklyRecoverUp_L,
		QuicklyRecoverUp_R,
		Raven_ClawShortv2_fast01,
		fall_attack,
		ParryL,
		ParryR,
		Sprint,
		Sprint_start,
		AvoidAttack_D,
		AvoidAttack_E2,
		AvoidAttack_E3,
		AvoidF,
		AvoidLongB,
		AvoidLongF,
		AvoidLongL,
		AvoidLongR,
		AvoidshortB,
		AvoidshortF,
		AvoidshortL,
		AvoidshortR,
		AvoidshortMagB,
		AvoidshortMagF,
		AvoidshortMagL,
		AvoidshortMagR,
		Bounce,
		Dead_1,
		Defense_Hurt,
		Defense_Hurt_Lage,
		Defense_Loop,
		Fall_End,
		Fall_Loop,
		Fall_Start,
		GetUp,
		Headache1_End,
		Headache1_Loop,
		Headache1_Start,
		Headache2_Loop,
		Headache2_Start,
		HurtBlown,
		HurtFallDown,
		HurtFallDown_End,
		HurtKnockDown,
		HurtLF,
		HurtMFL,
		HurtMFR,
		HurtSF,
		HurtSL,
		HurtSR,
		HurtXLF,
		HurtXXLF,
		Idle,
		KnockBackF,
		Ladder_Climb_L_Down,
		Ladder_Climb_L_Down_end,
		Ladder_Climb_L_UP,
		Ladder_Climb_L_UP_End,
		Ladder_Climb_R_Down,
		Ladder_Climb_R_Down_End,
		Ladder_Climb_R_UP,
		Ladder_Climb_R_UP_ENd,
		Ladder_Climb_Start,
		Ladder_L_idle,
		Ladder_R_idle,
		LAttatck1,
		LAttatck1_slow,
		LAttatck2,
		LAttatck3,
		LAttatck3_slow,
		LAttatck4,
		LAttatck5,
		ParryDefance,
		parryDeflect_L,
		parryDeflect_Large,
		parryDeflect_LUp,
		parryDeflect_LUp_AI,
		parryDeflect_R,
		parryDeflect_RUp,
		parryDeflect_RUp_AI,
		Rebound_L,
		Rebound_R,
		RootfixJokerRunAttack1,
		RunB,
		RunBL,
		RunBR,
		RunF,
		RunFL,
		RunFR,
		RunL,
		RunR,
		sprintAttack1,
		TD2Thorw2_slow,
		walk_Posion_pose,
		WeakGetup_F,
		BossFightStart_sit,
		BossFightStart_stand,
		GameEnd,
		GameEnd_Idle,
		GameEnd_sp,
		GameEnd_sp_Walk,
		stunExecute_startL_L,
		stunExecute_startL_R,
		stunExecute_startR_L,
		stunExecute_startR_R,
		stunExecute_startRDown_L,
		stunExecute_startRDown_R,
		Suicide,
		VS_MagicianLv1_seq_BossFight,
		WalkN,
		Pw_Axe,
		Pw_Axe_B,
		Pw_Bat_Roar_A,
		Pw_Bat_Roar_B,
		PW_BigHand_B_End,
		PW_BigHand_B_Loop,
		PW_BigHand_B_start,
		PW_BigHand_End,
		PW_BigHand_Start,
		Pw_Bloodwhip,
		Pw_Bloodwhip_end,
		Pw_Bloodwhip_jump,
		Pw_Bloodwhip_Loop,
		Pw_BloodwhipPull,
		Pw_Bow_B,
		Pw_Bow_end,
		Pw_Bow_start,
		Pw_CaneSword_Fast,
		Pw_CaneSword_Sp01,
		Pw_CaneSword_Sp02,
		Pw_Darts_A_B_V1,
		Pw_Darts_A_F_V1,
		Pw_Darts_A_L_V1,
		Pw_Darts_A_R_V1,
		Pw_Darts_A_V1,
		Pw_Darts_B_01,
		Pw_Darts_B_02,
		Pw_Darts_B_03,
		Pw_Darts_B_04,
		Pw_Darts_B_start,
		Pw_DualKnife,
		Pw_DualKnife_B,
		Pw_DualKnife_B_Suc,
		Pw_GianMaggot_A_V1,
		Pw_GreatSword,
		Pw_GreatSword_B,
		Pw_GreatSwordStep,
		Pw_Halberds,
		Pw_Halberds_B,
		Pw_Hammer_A,
		Pw_Hammer_A_AI,
		Pw_Hammer_B_ver2,
		Pw_Hammer_B_ver2_AI,
		Pw_Knife_A,
		Pw_Magician_A,
		Pw_MagicianLv2,
		Pw_Puppet_V1_A,
		Pw_Puppet_V1_A_End,
		Pw_Puppet_V1_B,
		Pw_Puppet_V1_start,
		Pw_Researcher,
		Pw_Researcher_B,
		Pw_Scythe,
		Pw_Scythe_B,
		Pw_Shield,
		Pw_Shield_B,
		Pw_Shield_B_suc,
		Pw_ShieldBlock,
		Pw_Slide_B,
		Pw_Slide_L,
		Pw_Slide_R,
		Pw_TwinSwords_1,
		Pw_TwinSwords_2,
		Pw_TwinSwords_3,
		Pw_TwinSwords_4,
		Pw_TwinSwords_B,
		Pw_urdSword01,
		Pw_urdSword_B_end,
		Pw_urdSword_B_Loop,
		Pw_urdSword_B_Start,
		Pw_VargSword_A,
		Pw_VargSword_B,
		Pw_VargSword_Start,
		ArchiveGetup,
		ArchiveLight_Up,
		ArchivesitLoop,
		ArchiveStart,
		LobbyIdle03,
		LobbyIdle03_end,
		Raven_ClawCommon_ChargeL,
		Raven_ClawCommon_ChargeS,
		Raven_ClawCommonV2_ChargeL,
		Raven_ClawLong_ChargeFull,
		Raven_ClawLong_L01,
		Raven_ClawLong_L02,
		Raven_ClawLong_PlunderAttack1,
		Raven_ClawLong_PlunderAttack2,
		Raven_ClawNear,
		Raven_ClawParry_end,
		Raven_ClawShort_chargeFull,
		Raven_ClawShort_PlunderAttack1,
		Raven_ClawShort_PlunderAttack2,
		Raven_ClawShortV2_Fast01,
		Raven_ClawShortV2_Fast02,
		Raven_ClawShortV2_Fast03,
		Raven_ClawShortV2_Fast031,
		Raven_FeatherRoundAttck,
		Raven_FeatherRoundJump,
		Raven_FeatherRoundRush,
		Raven_FeatherRoundRushAI,
		Raven_Idle,
		Raven_WingsParry,
		RavenAttack_End,
		RavenAttack_Loop,
		RavenAttack_Near,
		RavenAttack_Start,
		RavenJumpBack,
		RavenJumpBack_Start,
		RootFix_BMedium,
		RootFix_BSmall,
		SD2Raven,
		SD_M01_SneakAttck_End,
		SD_M01_SneakAttck_Suc,
		SD_TD2Thorw2,
		SD_VSvarg_Execution,
		SD_VSvarg_Execution_Blendin,
		SD_WalkB,
		SD_WalkB_LEnd,
		SD_WalkB_REnd,
		SD_WalkB_Start,
		SD_WalkBL,
		SD_WalkBR,
		SD_WalkF,
		SD_WalkF_LEnd,
		SD_WalkF_REnd,
		SD_WalkF_Start,
		SD_WalkFL,
		SD_WalkFR,
		SD_WalkIdle,
		SD_WalkL,
		SD_WalkL_LEnd,
		SD_WalkL_REnd,
		SD_WalkL_Start,
		SD_WalkR,
		SD_WalkR_LEnd,
		SD_WalkR_REnd,
		SD_WalkR_Start,
		Stunnedend,
		StunnedLoop,
		StunnedStart,
		Armor_Execution01,
		Armor_Execution02,
		Blood_Execution01,
		Blood_RaidAttck1Hurt,
		VS_GianMaggotExecution_Att01,
		VS_GianMaggotExecution_Att02,
		VS_GianMaggotExecution_End,
		VS_GianMaggotExecutionL,
		VS_GianMaggotExecutionR,
		VS_LAromorLV2Execution,
		VS_LightEXecute01L,
		VS_LightEXecute01R,
		VS_MagicianLv2_Execution_V1,
		VS_MagicianLv2_SPAttack1_Hurt,
		VS_Puppet_Execution_Attack,
		VS_Puppet_Execution_End,
		VS_Puppet_Execution_Start,
		VS_Researcher01_Execution,
		VS_Researcher01_Execution_M,
		VS_Researcher01_SP01hurt,
		VS_BossBat_Execution01,
		VSGiantMaggot_Sp_Hurt,
		VSGrace_Execution,
		VSHArmorLv1_Execution,
		VSHArmorLv1_Execution_NCar,
		VSJoker_Execution,
		VSLV1Villager_M_Execution,
		VSLV2Villager_M_Execution,
		VSMagician_Excution,
		VSMagician_SP1Hurt,
		VSMagician_SP2Hurt,
		VSSelf_ExecuteL,
		VSSelf_ExecuteS,
		VSSelf_TakeExecuteL,
		VSSelf_TakeExecuteS,
		VSUrd_Execution,
		VSVarg_TakeSPAttack,
		VSVarg_TakeSPAttackSeq1,
		O_Corvus_SD1_SprintF,
		O_Corvus_SD1_SprintF1
	};

protected:
	CCovus(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus(const CCovus& rhs);
	virtual ~CCovus() = default;

public:
		virtual HRESULT Initialize_Prototype() override;
		virtual HRESULT Initialize(void* pArg) override;
		virtual void Priority_Tick(_float fTimeDelta) override;
		virtual void Tick(_float fTimeDelta) override;
		virtual void Late_Tick(_float fTimeDelta) override;
		virtual HRESULT Render() override;

public:
	virtual void Set_Hitted() override;

public:
	virtual void Write_Json(json& Out_Json) override;
public:
	_bool	Get_CheckRotatePlayer() { return m_bRotatePlayer; }
	void	Set_CheckRotatePlayer(_bool _bRotatePlayer) { m_bRotatePlayer = _bRotatePlayer; }
protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Ready_PartObjects() override;
	//HRESULT Bind_ShaderResources();
protected:
	_bool	m_bRotatePlayer = false;
	

public:
	virtual void Free() override;

};

END