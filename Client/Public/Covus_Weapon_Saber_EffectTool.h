#pragma once

#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CModel;
END

BEGIN(Client)

class CCovus_Weapon_Saber_EffectTool : public CGameObject
{
private:
	CCovus_Weapon_Saber_EffectTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus_Weapon_Saber_EffectTool(const CCovus_Weapon_Saber_EffectTool& rhs);
	virtual ~CCovus_Weapon_Saber_EffectTool() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();

private:
	CShader* m_pShaderCom = { nullptr };
	CModel* m_pModelCom = { nullptr };


public:
	/* 원형객체를 생성한다. */
	static CCovus_Weapon_Saber_EffectTool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END
