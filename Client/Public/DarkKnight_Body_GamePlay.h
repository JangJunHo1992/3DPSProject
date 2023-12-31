#pragma once

#include "DarkKnight_Body.h"

BEGIN(Client)

class CDarkKnight_Body_GamePlay final : public CDarkKnight_Body
{
private:
	CDarkKnight_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CDarkKnight_Body_GamePlay(const CDarkKnight_Body_GamePlay& rhs);
	virtual ~CDarkKnight_Body_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CDarkKnight_Body_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END