#pragma once

#include "Client_Defines.h"
#include "Character.h"

BEGIN(Engine)
class CShader;
class CModel;
END

BEGIN(Client)

class CDarkKnight abstract : public CCharacter
{
public:
	enum DarkKnight_State
	{
		Massive_Greate_Sword_Attack01					,
		Massive_Greate_Sword_Attack02					,
		Massive_Greate_Sword_Attack03					,
		Massive_Greate_Sword_Attack04					,
		Massive_Greate_Sword_Attack_Dash01				,
		Massive_Greate_Sword_Attack_Dash02				,
		Massive_Greate_Sword_Attack_Ground01			,
		Massive_Greate_Sword_Attack_Ground02			,
		Massive_Greate_Sword_Attack_Jump01				,
		Massive_Greate_Sword_Attack_Jump02				,
		Massive_Greate_Sword_Attack_Sting				,
		Massive_Greate_Sword_Attack_Upper01				,
		Massive_Greate_Sword_Attack_Upper02				,
		Massive_Greate_Sword_Avoid_Back					,
		Massive_Greate_Sword_Avoid_Front				,
		Massive_Greate_Sword_Avoid_Left					,
		Massive_Greate_Sword_Avoid_Right				,
		Massive_Greate_Sword_Buff						,
		Massive_Greate_Sword_Combo01					,
		Massive_Greate_Sword_Combo01_1					,
		Massive_Greate_Sword_Combo01_2					,
		Massive_Greate_Sword_Combo01_3					,
		Massive_Greate_Sword_Combo02					,
		Massive_Greate_Sword_Combo02_1					,
		Massive_Greate_Sword_Combo02_2					,
		Massive_Greate_Sword_Combo02_3					,
		Massive_Greate_Sword_Combo03					,
		Massive_Greate_Sword_Combo03_1					,
		Massive_Greate_Sword_Combo03_2					,
		Massive_Greate_Sword_Combo03_3					,
		Massive_Greate_Sword_Combo03_4					,
		Massive_Greate_Sword_Dead01						,
		Massive_Greate_Sword_Defense01					,
		Massive_Greate_Sword_Defense01_CounterAttack	,
		Massive_Greate_Sword_Defense01_End				,
		Massive_Greate_Sword_Defense01_Loop				,
		Massive_Greate_Sword_Defense01_Start			,
		Massive_Greate_Sword_Down01						,
		Massive_Greate_Sword_Down02						,
		Massive_Greate_Sword_Hit_Back					,
		Massive_Greate_Sword_Hit_Front					,
		Massive_Greate_Sword_Hit_Left					,
		Massive_Greate_Sword_Hit_Right					,
		Massive_Greate_Sword_Idle01						,
		Massive_Greate_Sword_Jump						,
		Massive_Greate_Sword_JumpZ0						,
		Massive_Greate_Sword_JumpZ1						,
		Massive_Greate_Sword_Jump_Falling_Loop			,
		Massive_Greate_Sword_Jump_Landing				,
		Massive_Greate_Sword_Jump_Start					,
		Massive_Greate_Sword_Move_Run_Back				,
		Massive_Greate_Sword_Move_Run_Back_L45			,
		Massive_Greate_Sword_Move_Run_Back_R45			,
		Massive_Greate_Sword_Move_Run_Front				,
		Massive_Greate_Sword_Move_Run_Front_L45			,
		Massive_Greate_Sword_Move_Run_Front_R45			,
		Massive_Greate_Sword_Move_Run_Left				,
		Massive_Greate_Sword_Move_Run_Right				,
		Massive_Greate_Sword_Move_Walk_Back				,
		Massive_Greate_Sword_Move_Walk_Back_L45			,
		Massive_Greate_Sword_Move_Walk_Back_R45			,
		Massive_Greate_Sword_Move_Walk_Front			,
		Massive_Greate_Sword_Move_Walk_Front_L45		,
		Massive_Greate_Sword_Move_Walk_Front_R45		,
		Massive_Greate_Sword_Move_Walk_Left				,
		Massive_Greate_Sword_Move_Walk_Right			,
		Massive_Greate_Sword_Pose_Look_C				,
		Massive_Greate_Sword_Pose_Look_D				,
		Massive_Greate_Sword_Pose_Look_L				,
		Massive_Greate_Sword_Pose_Look_LD				,
		Massive_Greate_Sword_Pose_Look_LU				,
		Massive_Greate_Sword_Pose_Look_R				,
		Massive_Greate_Sword_Pose_Look_RD				,
		Massive_Greate_Sword_Pose_Look_RU				,
		Massive_Greate_Sword_Pose_Look_U				,
		Massive_Greate_Sword_Rise01						,
		Massive_Greate_Sword_Roll_Back					,
		Massive_Greate_Sword_Roll_Front					,
		Massive_Greate_Sword_Roll_Left					,
		Massive_Greate_Sword_Roll_Right					,
		Massive_Greate_Sword_Setmotion01_ATK			,
		Massive_Greate_Sword_Setmotion01_HIT			,
		Massive_Greate_Sword_Setmotion02_ATK			,
		Massive_Greate_Sword_Setmotion02_HIT			,
		Massive_Greate_Sword_Taunt						,
		Massive_Greate_Sword_TurnL180					,
		Massive_Greate_Sword_TurnL90					,
		Massive_Greate_Sword_TurnR180					,
		Massive_Greate_Sword_TurnR90					,
		Massive_Greate_Sword_WP_Equip					,
		Massive_Greate_Sword_WP_Unequip					,


	};
protected:
	CDarkKnight(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CDarkKnight(const CDarkKnight& rhs);
	virtual ~CDarkKnight() = default;

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