#pragma once

#include "inclusioni.h"

class CUV_string
{
public:
						CUV_string();
						~CUV_string();

	static int			ReplaceAll_(std::string &str, const std::string & from, const std::string & to);
	static void			Convert_CStdString_2_string( CStdString &strSrc, std::wstring &strDst);
};

