#include "stdafx.h"
#include "FileManager_BIN.h"

using namespace std;

CFileManager_BIN::CFileManager_BIN()
{
	m_bFileLoaded = false;
}


CFileManager_BIN::~CFileManager_BIN()
{
}

bool CFileManager_BIN::Read_BIN(std::string strFileName)
{
	m_strFile = strFileName;
	m_bFileLoaded = m_buf.Read_FromFile_BIN(strFileName);
	return m_bFileLoaded;
}
