#include "..\Public\RapidJson.h"
#include "GameInstance.h"


HRESULT CRapidJson::Load_RapidJson(string _strPath, json& pOut)
{
	json loadedJson;
	CGameInstance::GetInstance()->Load_Json(_strPath, loadedJson);
	string loadedJsonString = loadedJson.dump(2);

	m_Doc.Parse(loadedJsonString.c_str());



	return S_OK;
}

HRESULT CRapidJson::Save_RapidJson(string _strPath, json& pOut)
{
	string filePath = m_DirectoryPath + _strPath;

	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);

	ofstream ofs(filePath);

	ofs << buffer.GetString();

	ofs << endl;

	return S_OK;
}


//void CRapidJson::Write(string fileName)
//{
//
//	_int test = 0;
//	{
//
//		_char json[] = R"(
//	{
//		"hello" : "world",
//		"t" : true,
//		"f" : false,
//		"n" : null,
//		"i" : 123,
//		"pi" : 3.1416,
//		"a" : [1, 2, 3, 4]
//	})";
//
//		Document d;
//		d.Parse(json);
//
//		Value& s = d["i"];
//		s.SetInt(s.GetInt() + 1);
//
//		StringBuffer buffer;
//		Writer<StringBuffer> writer(buffer);
//		d.Accept(writer);
//		
//		string filePath = m_DirectoryPath + fileName;
//		const char* result = filePath.c_str();
//
//		ofstream ofs(result);
//
//		ofs << buffer.GetString();
//
//		ofs << endl;
//	}
//
//
//
//	{
//		try
//		{
//			string filePath = m_DirectoryPath + "new_example.json";
//			const char* result = filePath.c_str();
//
//			//ifstream ifs("../Bin/RapidJson/new_example.json");
//			ifstream ifs(result);
//			if (!ifs.is_open()) {
//				throw runtime_error("failed to open the file");
//			}
//
//			// 파일 내용을 문자열로 읽기
//			string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
//
//			// JSON 문자열 파싱
//			Document doc;
//			doc.Parse(json.c_str());
//
//			Value& hello = doc["hello"];
//			hello.SetString("World!");
//
//			Value& i = doc["i"];
//			test = i.GetInt();
//
//			StringBuffer buffer;
//			PrettyWriter<StringBuffer> writer(buffer);
//			doc.Accept(writer);
//
//			//ofstream ofs(MakePath("new_example2.json"));
//			ofstream ofs("../Bin/RapidJson/new_example2.json");
//
//			ofs << buffer.GetString();
//
//			ofs << endl;
//
//		}
//		catch (std::exception& e) {
//
//		}
//	}





//string projectName = "rapidjson";
//_int value = 100;
//
//json jsonData =
//{
//	{"project", projectName},
//	{"stars", value}
//};
//
////CRapidJson rapidJson;
//m_pGameInstance->Save_Json("json1.json", jsonData);
//
//json json2;
//m_pGameInstance->Load_Json("json1.json", json2);
//
//string test1 = json2["project"];
//_int test2 = json2["stars"];
//
//string result = json2.dump(2);
//_bool stop = true;



