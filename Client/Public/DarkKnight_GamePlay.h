#pragma once

#include "DarkKnight.h"
#include "Actor.h"

BEGIN(Client)

class CDarkKnight_GamePlay final : public CDarkKnight
{
private:
	CDarkKnight_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CDarkKnight_GamePlay(const CDarkKnight_GamePlay& rhs);
	virtual ~CDarkKnight_GamePlay() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual void Set_Hitted() override;

private:
	virtual HRESULT Ready_Components() override;

private:
	CActor<CDarkKnight_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CDarkKnight_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CDarkKnight_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END