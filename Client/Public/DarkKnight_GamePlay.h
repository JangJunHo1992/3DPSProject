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
	/* ������ü�� �����Ѵ�. */
	static CDarkKnight_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CDarkKnight_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END