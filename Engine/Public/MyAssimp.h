#pragma once
#include "Base.h"
#include "MyAIScene.h"

BEGIN(Engine)


class ENGINE_DLL CMyAssimp
{
private:
	_bool					m_bIsBinary = { false };
	Assimp::Importer		m_Importer;

public:
	CMyAIScene ReadFile(const string& strModelFilePath, _uint iFlag, _bool _bIsBinary);
	CMyAIScene ReadFile(const string& strModelFilePath, _uint iFlag);
	void FreeScene();



};

END