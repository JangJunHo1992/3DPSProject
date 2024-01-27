#pragma once

#include "Magician_Card_Bullet.h"

BEGIN(Client)

class CMagician_Card_Bullet_GamePlay final : public CMagician_Card_Bullet
{
private:
	CMagician_Card_Bullet_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Card_Bullet_GamePlay(const CMagician_Card_Bullet_GamePlay& rhs);
	virtual ~CMagician_Card_Bullet_GamePlay() = default;

private:
	HRESULT Ready_Components();


public:
	/* 원형객체를 생성한다. */
	static CMagician_Card_Bullet_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CMagician_Card_Bullet_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;
};

END