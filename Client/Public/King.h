#pragma once

#include "Client_Defines.h"
#include "Character.h"

BEGIN(Engine)
class CShader;
class CModel;
END

BEGIN(Client)

class CKing abstract : public CCharacter
{
public:
	enum King_State 
	{
		TwoHandedHammerSet_Attack01					,
		TwoHandedHammerSet_Attack02					,
		TwoHandedHammerSet_Attack03					,
		TwoHandedHammerSet_Attack04					,
		TwoHandedHammerSet_Attack05					,
		TwoHandedHammerSet_Attack06					,
		TwoHandedHammerSet_Attack07					,
		TwoHandedHammerSet_Attack_1H_Around			,
		TwoHandedHammerSet_Attack_1H_Around2		,
		TwoHandedHammerSet_Avoid_Back				,
		TwoHandedHammerSet_Avoid_Front				,
		TwoHandedHammerSet_Avoid_Left				,
		TwoHandedHammerSet_Avoid_Right				,
		TwoHandedHammerSet_Buff01					,
		TwoHandedHammerSet_Combo01					,
		TwoHandedHammerSet_Combo02					,
		TwoHandedHammerSet_Combo03					,
		TwoHandedHammerSet_Combo03_1				,
		TwoHandedHammerSet_Combo03_2				,
		TwoHandedHammerSet_Combo03_3				,
		TwoHandedHammerSet_Combo03_4				,
		TwoHandedHammerSet_Combo04					,
		TwoHandedHammerSet_Combo04_1				,
		TwoHandedHammerSet_Combo04_2				,
		TwoHandedHammerSet_Combo04_3				,
		TwoHandedHammerSet_Combo04_4				,
		TwoHandedHammerSet_Dead01					,
		TwoHandedHammerSet_Dead02					,
		TwoHandedHammerSet_Dead03					,
		TwoHandedHammerSet_Defense					,
		TwoHandedHammerSet_Down						,
		TwoHandedHammerSet_Down_Start				,
		TwoHandedHammerSet_Hit_Body_Back			,
		TwoHandedHammerSet_Hit_Body_Front			,
		TwoHandedHammerSet_Hit_Body_Left			,
		TwoHandedHammerSet_Hit_Body_Right			,
		TwoHandedHammerSet_Hit_Down					,
		TwoHandedHammerSet_Hit_Head_Back			,
		TwoHandedHammerSet_Hit_Head_Front			,
		TwoHandedHammerSet_Hit_Head_Left			,
		TwoHandedHammerSet_Hit_Head_Right			,
		TwoHandedHammerSet_Idle						,
		TwoHandedHammerSet_Idle_Long				,
		TwoHandedHammerSet_Jump						,
		TwoHandedHammerSet_JumpZ1					,
		TwoHandedHammerSet_Knockdown01				,
		TwoHandedHammerSet_Knockdown02				,
		TwoHandedHammerSet_Knockdown03				,
		TwoHandedHammerSet_Knockdown04				,
		TwoHandedHammerSet_N_idle					,
		TwoHandedHammerSet_Pose_Look_C				,
		TwoHandedHammerSet_Pose_Look_D				,
		TwoHandedHammerSet_Pose_Look_L				,
		TwoHandedHammerSet_Pose_Look_LD				,
		TwoHandedHammerSet_Pose_Look_LU				,
		TwoHandedHammerSet_Pose_Look_R				,
		TwoHandedHammerSet_Pose_Look_RD				,
		TwoHandedHammerSet_Pose_Look_RU				,
		TwoHandedHammerSet_Pose_Look_U				,
		TwoHandedHammerSet_Rise01					,
		TwoHandedHammerSet_Roll_Front				,
		TwoHandedHammerSet_Run_Back					,
		TwoHandedHammerSet_Run_BackL				,
		TwoHandedHammerSet_Run_BackR				,
		TwoHandedHammerSet_Run_Front				,
		TwoHandedHammerSet_Run_FrontL				,
		TwoHandedHammerSet_Run_FrontR				,
		TwoHandedHammerSet_Run_Left					,
		TwoHandedHammerSet_Run_Right				,
		TwoHandedHammerSet_Turn_L180				,
		TwoHandedHammerSet_Turn_L90					,
		TwoHandedHammerSet_Turn_R180				,
		TwoHandedHammerSet_Turn_R90					,
		TwoHandedHammerSet_Turn_Rotation_Turn_L180	,
		TwoHandedHammerSet_Turn_Rotation_Turn_L90	,
		TwoHandedHammerSet_Turn_Rotation_Turn_R180	,
		TwoHandedHammerSet_Turn_Rotation_Turn_R90	,
		TwoHandedHammerSet_Walk_Back				,
		TwoHandedHammerSet_Walk_BackL				,
		TwoHandedHammerSet_Walk_BackR				,
		TwoHandedHammerSet_Walk_Front				,
		TwoHandedHammerSet_Walk_FrontL				,
		TwoHandedHammerSet_Walk_FrontR				,
		TwoHandedHammerSet_Walk_Left				,
		TwoHandedHammerSet_Walk_Right				,
		TwoHandedHammerSet_Walk_Start				,
		TwoHandedHammerSet_Walk_Stop				,

	};
protected:
	CKing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKing(const CKing& rhs);
	virtual ~CKing() = default;

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