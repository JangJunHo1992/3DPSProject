#pragma once

#include "Covus.h"
#include "Actor.h"

BEGIN(Client)

class CCovus_GamePlay final : public CCovus
{
private:
	CCovus_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus_GamePlay(const CCovus_GamePlay& rhs);
	virtual ~CCovus_GamePlay() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;


private:
	virtual HRESULT Ready_Components() override;

private:
	CActor<CCovus_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CCovus_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CCovus_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END