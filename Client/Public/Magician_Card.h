#pragma once

#include "Magician_Weapon.h"

BEGIN(Client)

class CMagician_Card abstract : public CMagician_Weapon
{
protected:
	CMagician_Card(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Card(const CMagician_Card& rhs);
	virtual ~CMagician_Card() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	_vector m_vPlayerPos = {};
public:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
};

END
