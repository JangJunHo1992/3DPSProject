#pragma once

#include "Magician_Body.h"

BEGIN(Client)

class CMagician_Body_GamePlay final : public CMagician_Body
{
private:
	CMagician_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Body_GamePlay(const CMagician_Body_GamePlay& rhs);
	virtual ~CMagician_Body_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CMagician_Body_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END