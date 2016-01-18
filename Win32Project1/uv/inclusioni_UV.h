#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "stdstring.h"

struct sUV_Attrib
{
	CStdString		strName;	///< Nome dell'attributo.
	CStdString		strVal;		///< Valore dell'attributo.
};

#define vect_char			std::vector<char>
#define vect_int			std::vector<int>
#define vect_double			std::vector<double>
#define vect_DWORD			std::vector<DWORD>

#define vect_string			std::vector<std::string>
#define vect_wstring		std::vector<std::wstring>
#define vect_CString		std::vector<CStdString>
#define vect_sUV_Attrib		std::vector<sUV_Attrib>

#define CStdStringArray		vect_CString
#define CStringArray		vect_CString
#define CArrayInt			vect_int
#define CArrayDouble		vect_double
#define CArrayDWORD			vect_DWORD
#define CArraysUV_Attrib	vect_sUV_Attrib