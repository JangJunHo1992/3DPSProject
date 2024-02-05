#include "stdafx.h"
#include "Character_Client.h"

CParticle_Hit::PARTICLE_DESC CCharacter_Client::Get_Particle_Hitblood_Desc()
{
	CParticle_Hit::PARTICLE_DESC Desc;

	Desc.ParticleDesc.vRange = _float2(0.6f, 0.6f);
	Desc.ParticleDesc.vSpeed = _float2(0.9f, 2.4f);
	Desc.ParticleDesc.vCenter.x = _float(0.0f);
	Desc.ParticleDesc.vCenter.y = _float(1.f);
	Desc.ParticleDesc.vCenter.z = _float(0.f);
	Desc.ParticleDesc.fAcceleration = -7.7f;
	Desc.ParticleDesc.vRotationX = _float2(0.f, 360.f);
	Desc.ParticleDesc.vRotationY = _float2(0.f, 360.f);
	Desc.ParticleDesc.vRotationZ = _float2(0.f, 360.f);
	Desc.ParticleDesc.vLifeTime = _float2(0.0f, 1.5f);
	Desc.ParticleDesc.vScaleX = _float2(0.05f, 0.05f);
	Desc.ParticleDesc.vScaleY = _float2(0.05f, 0.05f);

	return Desc;
}
