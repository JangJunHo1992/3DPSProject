#pragma once

#include "DarkKnight.h"

BEGIN(Client)

class CDarkKnight_GamePlay final : public CDarkKnight
{
private:
	CDarkKnight_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CDarkKnight_GamePlay(const CDarkKnight_GamePlay& rhs);
	virtual ~CDarkKnight_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;

	CActor<CDarkKnight_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CDarkKnight_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CDarkKnight_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END