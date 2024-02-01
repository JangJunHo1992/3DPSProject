#include "Weapon_Client.h"

CParticle_Custom::PARTICLE_DESC CWeapon_Client::Get_Particle_Blood_Desc()
{
	CParticle_Custom::PARTICLE_DESC Desc;

	Desc.ParticleDesc.vRange = _float2(0.5f, 0.5f);
	Desc.ParticleDesc.vSpeed = _float2(0.8999999761581421f, 2.4000000953674316f);
	Desc.ParticleDesc.vCenter.x = _float(1.f);
	Desc.ParticleDesc.vCenter.y = _float(0.f);
	Desc.ParticleDesc.vCenter.z = _float(0.f);
	Desc.ParticleDesc.fAcceleration = -7.699999809265137f;
	Desc.ParticleDesc.vRotationX = _float2(0.f,360.f);
	Desc.ParticleDesc.vRotationY = _float2(0.f, 360.f);
	Desc.ParticleDesc.vRotationZ = _float2(0.f, 360.f);
	Desc.ParticleDesc.vLifeTime = _float2(0.1f, 1.5f);
	Desc.ParticleDesc.vScaleX = _float2(0.10000000149011612f, 0.30000001192092896f);
	Desc.ParticleDesc.vScaleY = _float2(0.10000000149011612f, 0.30000001192092896f);

	return Desc;
}

CParticle_Custom::PARTICLE_DESC CWeapon_Client::Get_Particle_HitEffect_Desc()
{
	CParticle_Custom::PARTICLE_DESC Desc;

	Desc.ParticleDesc.vRange = _float2(0.0f,1.8f);
	Desc.ParticleDesc.vSpeed = _float2(1.4f, 2.4f);
	Desc.ParticleDesc.vCenter.x = _float(2.f);
	Desc.ParticleDesc.vCenter.y = _float(0.f);
	Desc.ParticleDesc.vCenter.z = _float(0.f);
	Desc.ParticleDesc.fAcceleration = -3.f;
	Desc.ParticleDesc.vRotationX = _float2(90.f, 180.f);
	Desc.ParticleDesc.vRotationY = _float2(90.f, 180.f);
	Desc.ParticleDesc.vRotationZ = _float2(270.f, 360.f);
	Desc.ParticleDesc.vLifeTime = _float2(0.1f, 1.5f);
	Desc.ParticleDesc.vScaleX = _float2(0.2f, 0.2f);
	Desc.ParticleDesc.vScaleY = _float2(0.2f, 0.2f);

	return Desc;
}

CParticle_Custom::PARTICLE_DESC CWeapon_Client::Get_Particle_HalfMoon_Desc()
{
	CParticle_Custom::PARTICLE_DESC Desc;

	Desc.ParticleDesc.vRange = _float2(0.6f, 0.6f);
	Desc.ParticleDesc.vSpeed = _float2(5.f, 5.f);
	Desc.ParticleDesc.vCenter.x = _float(0.4f);
	Desc.ParticleDesc.vCenter.y = _float(0.f);
	Desc.ParticleDesc.vCenter.z = _float(0.f);
	Desc.ParticleDesc.fAcceleration = -29.f;
	Desc.ParticleDesc.vRotationX = _float2(270.f, 270.f);
	Desc.ParticleDesc.vRotationY = _float2(180.f, 360.f);
	Desc.ParticleDesc.vRotationZ = _float2(360.f, 360.f);
	Desc.ParticleDesc.vLifeTime = _float2(0.9f, 0.9f);
	Desc.ParticleDesc.vScaleX = _float2(0.2f, 0.2f);
	Desc.ParticleDesc.vScaleY = _float2(0.2f, 0.2f);

	return Desc;
}
