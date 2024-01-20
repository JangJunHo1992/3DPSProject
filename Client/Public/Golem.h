#pragma once

#include "Client_Defines.h"
#include "Character.h"

BEGIN(Engine)
class CShader;
class CModel;
END

BEGIN(Client)

class CGolem abstract : public CCharacter
{
public:
	enum Golem_State 
	{
		ThirdPerson_Jump,
		ThirdPerson_Idle,
		ThirdPerson_Jump_Loop,
		ThirdPerson_Jump_Start,
		ThirdPerson_Run,
		ThirdPerson_Walk,


		Giant_Golem_Atk_Back01			,
		Giant_Golem_Atk_Dash			,
		Giant_Golem_Atk_Front01			,
		Giant_Golem_Atk_Front02			,
		Giant_Golem_Atk_Front03			,
		Giant_Golem_Atk_Ground			,
		Giant_Golem_Atk_Ground02		,
		Giant_Golem_Atk_Jump			,
		Giant_Golem_Atk_JumpZ1			,
		Giant_Golem_Atk_L_foot			,
		Giant_Golem_Atk_R_foot			,
		Giant_Golem_Atk_Throwstone		,
		Giant_Golem_Atk_Whirlwind		,
		Giant_Golem_Dead01				,
		Giant_Golem_Dead02				,
		Giant_Golem_Defence01			,
		Giant_Golem_Defence02			,
		Giant_Golem_Defence03			,
		Giant_Golem_Down				,
		Giant_Golem_Hit_Left_Shoulder	,
		Giant_Golem_Hit_Light_Back		,
		Giant_Golem_Hit_Light_Front		,
		Giant_Golem_Hit_Light_Left		,
		Giant_Golem_Hit_Light_Right		,
		Giant_Golem_Hit_Right_Shoulder	,
		Giant_Golem_Idle				,
		Giant_Golem_Rise				,
		Giant_Golem_Stun_End			,
		Giant_Golem_Stun_Loop			,
		Giant_Golem_Stun_Start			,
		Giant_Golem_Walk_Front			,
		Giant_Golem_Walk_Left			,
		Giant_Golem_Walk_Right			,

	};
protected:
	CGolem(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGolem(const CGolem& rhs);
	virtual ~CGolem() = default;

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