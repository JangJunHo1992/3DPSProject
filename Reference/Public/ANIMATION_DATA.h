#pragma once

#include "Base.h"
#include "CHANNEL_DATA.h"

BEGIN(Engine)
struct ENGINE_DLL ANIMATION_DATA
{
	vector<CHANNEL_DATA*> Channel_Datas;

	string szName;
	_uint  iNumChannels = 0;
	_float fDuration = 0.f;
	_float fTickPerSecond = 0.f;

	HRESULT Make_AnimationData(aiAnimation* In_pAiAnimation, _float In_fSpeed = 1.f);

public:
	void Bake_Binary(ofstream& os);
	void Load_FromBinary(ifstream& is);
	void Bake_ReverseAnimation(ANIMATION_DATA* Out_AnimationData);
};
END