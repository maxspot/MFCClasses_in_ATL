#include "stdafx.h"
#include "UV_string.h"

#include <sstream>

CUV_string::CUV_string()
{
}


CUV_string::~CUV_string()
{
}

int CUV_string::ReplaceAll_(std::string &str, const std::string& from, const std::string& to)
{
	size_t			start_pos = 0;
	int				nChanges = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		nChanges++;
	}
	return nChanges;
}

void CUV_string::Convert_CStdString_2_string( CStdString & strSrc, std::wstring & strDst)
{
	//int					nLen = strSrc.GetLength();
	//wchar_t				*pBuffDst = new wchar_t[nLen+1];
	//const wchar_t		*pBuffSrc = strSrc.Buffer();

	//_sntprintf_s(pBuffDst, nLen, nLen, pBuffSrc);
	strDst = std::wstring(strSrc.Buffer() /*pBuffDst*/ );
}
