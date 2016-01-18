#include "stdafx.h"
#include "MyString.h"


CMyString::CMyString()
{
}

CMyString::CMyString( const wchar_t * pStr)
{
	Set(pStr);
}


CMyString::~CMyString()
{
}

void CMyString::Set(const wchar_t * pStr)
{
	m_strData = std::wstring(pStr);
}

void CMyString::fmt(wchar_t* szFmt, ...)
{
	va_list argList;
	va_start(argList, szFmt);
	formatV(szFmt, argList);
	va_end(argList);
}

void CMyString::formatV(wchar_t* szFormat, va_list argList)
{
#ifdef SS_ANSI
	MYTYPE str;
	int nLen = sslen(szFormat) + STD_BUF_SIZE;
	ssvsprintf(str.GetBuffer(nLen), nLen - 1, szFormat, argList);
	str.ReleaseBuffer();
	*this = str;

#else

	wchar_t* pBuf = NULL;
	int nChars = 1;
	int nUsed = 0;
	int nActual = 0;
	int nTry = 0;

	do
	{
		// Grow more than linearly (e.g. 512, 1536, 3072, etc)

		nChars += ((nTry + 1) * FMT_BLOCK_SIZE);
		pBuf = reinterpret_cast<wchar_t*>(_alloca(sizeof(wchar_t)*nChars));
		nUsed = ssvsprintf(pBuf, nChars - 1, szFormat, argList);

		// Ensure proper NULL termination.

		nActual = nUsed == -1 ? nChars - 1 : SSMIN(nUsed, nChars - 1);
		pBuf[nActual] = '\0';


	} while (nUsed < 0 && nTry++ < MAX_FMT_TRIES);

	// assign whatever we managed to format
	m_strData.assign(pBuf, nActual);
	//this->assign(pBuf, nActual);

#endif
}

void CMyString::Append(CMyString strApp)
{
	m_strData.append(strApp.m_strData);
}

int CMyString::GetLength() const
{
	return m_strData.length();
}

bool CMyString::IsEmpty() const
{
	return m_strData.empty();
}

void CMyString::Empty()
{
	m_strData.clear();
}

wchar_t CMyString::GetAt(int nIndex) const
{
	return m_strData[nIndex];
}

void CMyString::SetAt(int nIndex, wchar_t ch)
{
	m_strData[nIndex] = ch;
}

int CMyString::Compare(CMyString strVal) const
{
	return m_strData.compare(strVal.m_strData.data());
}

int CMyString::Compare(wchar_t * pStr) const
{
	return m_strData.compare(pStr);
}

CMyString CMyString::MakeUpper(void)
{
	for ( int nI=0; nI<m_strData.length(); nI++)
		m_strData[nI] = toupper(m_strData[nI]);
	return(*this);
}

CMyString CMyString::MakeLower(void)
{
	for (int nI = 0; nI<m_strData.length(); nI++)
		m_strData[nI] = tolower(m_strData[nI]);
	return(*this);
}

CMyString CMyString::MakeReverse(void)
{
	for (int nI = 0; nI < m_strData.length(); nI++)
	{
		if (isupper(m_strData[nI]))
			m_strData[nI] = tolower(m_strData[nI]);
		else
			m_strData[nI] = toupper(m_strData[nI]);
	}
	return(*this);
}

int CMyString::CompareNoCase(CMyString strVal_UP) const	// Compare respect to "strVal", case insensitive
{
	CMyString			strThis_UP = *this;

	strThis_UP.MakeUpper();
	strVal_UP.MakeUpper();

	return strThis_UP.Compare(strVal_UP);
}
int CMyString::CompareNoCase(const wchar_t *pStr) const		// Compare respect to "pStr", case insensitive
{
	CMyString			strThis_UP = *this;
	CMyString			strVal_UP(pStr);

	strThis_UP.MakeUpper();
	strVal_UP.MakeUpper();

	return strThis_UP.Compare(strVal_UP);
}

int CMyString::Find(wchar_t ch) const
{
	size_t		nRes = m_strData.find(ch);
	if (nRes != std::string::npos)
		return nRes;
	return -1;
}

int CMyString::Find(wchar_t ch, int nStart) const
{
	size_t		nRes = m_strData.find(ch,nStart);
	if (nRes != std::string::npos)
		return nRes;
	return -1;
}

int CMyString::Find(const wchar_t * pStrToFind) const
{
	size_t		nRes = m_strData.find(pStrToFind);
	if (nRes != std::string::npos)
		return nRes;
	return -1;
}

int CMyString::Find(const wchar_t * pStrToFind, int nStart) const
{
	size_t		nRes = m_strData.find(pStrToFind, nStart);
	if (nRes != std::string::npos)
		return nRes;
	return -1;
}

int CMyString::Replace(wchar_t chOld, wchar_t chNew)
{
	replace_all()
	size_t			start_pos = 0;
	int				nChanges = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		m_strData.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		nChanges++;
	}
	return nChanges;
	return 0;
}

int CMyString::Replace(const wchar_t * lpszOld, const wchar_t * lpszNew)
{
	CMyString			strOld(lpszOld);
	CMyString			strNew(lpszNew);

	replace_all( *this, )
	return 0;
}

int CMyString::replace_all( CMyString &str, CMyString from, CMyString to)
{
	size_t			start_pos = 0;
	int				nChanges = 0;
	while ((start_pos = str.m_strData.find(from.m_strData, start_pos)) != std::string::npos)
	{
		str.m_strData.replace(start_pos, from.m_strData.length(), to.m_strData);
		start_pos += to.m_strData.length(); // Handles case where 'to' is a substring of 'from'
		nChanges++;
	}
	return nChanges;
}
