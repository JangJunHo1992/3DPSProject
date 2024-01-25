#pragma once

#include "Client_Defines.h"
#include "Magician_Card.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CVIBuffer_Rect;
END
BEGIN(Client)

class CMagician_Card_GamePlay : public CMagician_Card
{
protected:
	CMagician_Card_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Card_GamePlay(const CMagician_Card_GamePlay& rhs);
	virtual ~CMagician_Card_GamePlay() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual _bool Collision_Chcek() override;

	void Start_Ranged_Attack();

	void Update_Ranged_Attack(_float fTimeDelta);

protected:
	virtual HRESULT Ready_Components() override;

public:
	CCharacter* m_pPlayer = { nullptr };
	CCharacter* m_pMonster = { nullptr };
	CVIBuffer_Rect* m_pVIBufferCom = { nullptr };
	_vector vPos = {};
	_vector m_vAttackDirection = {};
	_float  m_fAttackSpeed = 0.f;
	_vector vmonPos = {};
public:
	/* 원형객체를 생성한다. */
	static CMagician_Card_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END