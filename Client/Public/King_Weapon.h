#pragma once

#include "Weapon_Client.h"

BEGIN(Client)

class CKing_Weapon abstract : public CWeapon_Client
{
protected:
	CKing_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKing_Weapon(const CKing_Weapon& rhs);
	virtual ~CKing_Weapon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual _bool Collision_Chcek();

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Bind_ShaderResources() override;

public:
	virtual void Free() override;

};

END