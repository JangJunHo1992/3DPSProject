#pragma once

#include "Base.h"


BEGIN(Engine)

class ENGINE_DLL CRapidJson
{
public:
	CRapidJson() = default;
	~CRapidJson() = default;

public:
	HRESULT		Save_RapidJson(string _strPath, json& pOut);
	HRESULT		Load_RapidJson(string _strPath, json& pOut);

private:
	string		m_DirectoryPath = "../Bin/RapidJson/";
	Document	m_Doc;

};

END

// json 파일 만들기
// https://csj000714.tistory.com/430