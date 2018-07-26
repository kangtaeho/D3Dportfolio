#include "stdafx.h"
#include "cXManager.h"


cXManager::cXManager()
{
	FILE* fp;
	fopen_s(&fp, "character/file_list.txt", "r");

	while (!feof(fp))
	{
		char szTemp[1024];
		fgets(szTemp, 1024, fp);
		if (szTemp[strlen(szTemp) - 1] == '\n')
			szTemp[strlen(szTemp) - 1] = '\0';
		m_vecAllFolderName.push_back(szTemp);
		fgets(szTemp, 1024, fp);
		if (szTemp[strlen(szTemp) - 1] == '\n')
			szTemp[strlen(szTemp) - 1] = '\0';
		m_vecAllFileName.push_back(szTemp);
	}

	fclose(fp);
	FileIndex = 0;

	for (int i = 0; i < m_vecAllFileName.size(); ++i)
	{
		std::string allFath = m_vecAllFolderName[i];
		allFath += "/";
		allFath += m_vecAllFileName[i];
		allFath += ".x";
		FILE* fp;
		fopen_s(&fp, allFath.c_str(), "r");
		fseek(fp, 0, SEEK_END);
		int temp = ftell(fp);
		AllFileSize.push_back(temp);
		fclose(fp);
	}
	LoadFileSize.resize(AllFileSize.size());
}


cXManager::~cXManager()
{
}

bool cXManager::Setup(int & allfilesize, int & loadfilesize)
{
	if (FileIndex == m_vecAllFileName.size())return true;

	allfilesize = loadfilesize = 0;

	AddXfile(m_vecAllFileName[FileIndex].c_str(), m_vecAllFolderName[FileIndex].c_str(), (m_vecAllFileName[FileIndex] + ".x").c_str());
	FileIndex++;
	LoadFileSize[FileIndex] = AllFileSize[FileIndex];

	for (int i = 0; i < AllFileSize.size(); ++i)
	{
		allfilesize += AllFileSize[i];
		loadfilesize += LoadFileSize[i];
	}

	return false;
}

void cXManager::Release()
{
	for (auto p : m_mapXfile)
	{
		SAFE_DELETE(p.second);
	}
}

LPCSKINNEDMESH cXManager::AddXfile(const char* name, const char* szFolder, const char* szFile)
{
	cSkinnedMesh* temp = FindXfile(name);
	if(temp) return temp;
	temp = new cSkinnedMesh;
	temp->Setup(szFolder, szFile);
	m_mapXfile.insert(std::make_pair(name, temp));
	return temp;
}

LPCSKINNEDMESH cXManager::FindXfile(const char* name)
{
	miXfile p = m_mapXfile.find(name);
	if (p != m_mapXfile.end())
	{
		return p->second;
	}
	return NULL;
}
