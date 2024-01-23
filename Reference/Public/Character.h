#pragma once
#include "GameObject.h"
#include "Model.h"

#include "Body.h"
#include "Weapon.h"

BEGIN(Engine)

class CNavigation;
class CCollider;

//class CBody;
//class CWeapon;

class ENGINE_DLL CCharacter abstract : public CGameObject
{
protected:
	typedef struct CCharacterStatus
	{
		_int m_iHP;
		_int m_iAttack;

	}CharStat;

protected:
	CCharacter(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CCharacter(const CCharacter& rhs);
	virtual ~CCharacter() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	CGameObject* Find_PartObject(const wstring & strPartTag);
	CBody* Get_Body();
	CWeapon* Get_Weapon(const wstring & strWeaponTag = TEXT("Part_Weapon"));
	CCollider* Get_Collider();
	CNavigation* Get_Navigation();

	virtual void Set_Hitted() PURE;
	virtual void Set_Dead() PURE;
	void Set_IsAttack(_bool _bIsAttack) 
	{
		for (CWeapon* pWeapon : m_Weapons)
			pWeapon->Set_IsAttack(_bIsAttack);
	};

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Ready_PartObjects() PURE;

	HRESULT Add_PartObject(const wstring & strPrototypeTag, const wstring & strPartTag, void* pArg);
	HRESULT Add_Body(const wstring & strPrototypeTag, CBody::BODY_DESC pArg);
	HRESULT Add_Weapon(const wstring & strPrototypeTag, string strBoneName, CWeapon::WEAPON_DESC pArg, const wstring& strWeaponTag = TEXT("Part_Weapon"));

public:
	void	Set_Animation(
		_uint _iNextAnimation
		, CModel::ANIM_STATE _eAnimState = CModel::ANIM_STATE::ANIM_STATE_NORMAL
		, _bool _bIsTransition = true
		, _bool _bUseAnimationPos = true
		, _uint iTargetKeyFrameIndex = 0);


	_bool	Is_Animation_End();
	_bool	Is_Inputable_Front(_uint _iIndexFront);
	_bool	Is_Inputable_Back(_uint _iIndexBack);

	void Go_Straight(_float fTimeDelta		);
	void Go_Straight_L45(_float fTimeDelta );
	void Go_Straight_R45(_float fTimeDelta );
	void Go_Backward(_float fTimeDelta		);
	void Go_Backward_L45(_float fTimeDelta );
	void Go_Backward_R45(_float fTimeDelta );
	void Go_Left(_float fTimeDelta			);
	void Go_Right(_float fTimeDelta		);


	void Knockback(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Pushed(_float3 vPos);
	//RigidBody
public:
	void	Set_Force(_float3 _vForce) { m_vNetPower = _vForce; }
	void	Add_Force(_float3 _vForce) { m_vNetPower += _vForce; }
	_float3* Get_Force() { return &m_vNetPower; };
	_float	Calc_Force_Sum() { return abs(m_vNetPower.x) + abs(m_vNetPower.y) + abs(m_vNetPower.z); };
	void	Update_RigidBody(_float fTimeDelta);
public:
	void	Search_Target();
	_float	Calc_Distance(CCharacter* pTarget);
	_float	Calc_Distance();
	void Look_At_Target();
	_float3 Get_Pos();
	_float4 Get_Pos4();
protected:
	CNavigation* m_pNavigationCom = { nullptr };
	CCollider* m_pColliderCom = { nullptr };

	CBody* m_pBody = { nullptr };
	vector<CWeapon*> m_Weapons;

	CCharacter* m_pTargetPlayer = { nullptr };
	CCharacter* m_pTargetMonster = { nullptr };

	_uint		m_iCurrentLevelIn;
	//RigidBody
	_bool m_bIsPowered = { false };
	_float3	m_vNetPower = { 0.f, 0.f, 0.f };
	_bool	m_bIsJump = { false };
protected:
	map<const wstring, CGameObject*>		m_PartObjects;
	


protected:
	virtual CGameObject* Clone(void* pArg) PURE;

	virtual void Free() override;
};

END