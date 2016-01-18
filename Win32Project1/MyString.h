#pragma once

#include "inclusioni.h"

class CMyString
{
	// Metodi
	public:
						CMyString();
						CMyString( const CMyString &strSrc );		// Create from "CMyString"
						CMyString( const wchar_t *pStr );			// Create string from buffer "pStr"
						CMyString( const wchar_t chOld );			// Create a string from char
						~CMyString();

	// Assignment / Concatenation
	void				operator = (const CMyString &strSrc);		// operator =
	void				operator = (const wchar_t *pStr);			// operator =
	void				operator = (wchar_t ch);					// operator =
	CMyString			operator + (const CMyString &strPlus);		// operator +
	const CMyString&	operator +=(const CMyString& string);		// operator +=

	// Comparison
	int					Compare(CMyString strVal) const;			// Compare respect to "strVal", case sensitive
	int					Compare(wchar_t *pStr) const;				// Compare respect to "pStr", case sensitive
	int					CompareNoCase(CMyString strVal) const;		// Compare respect to "strVal", case insensitive
	int					CompareNoCase(const wchar_t *pStr) const;	// Compare respect to "pStr", case insensitive

// Metodi per la compatibilità di chiamata con CString
	void				Append(CMyString strApp);					// Appends "strApp" at the end of the current string
	int					GetLength() const;							// Returns the length of the string
	bool				IsEmpty() const;							// Is the string empty?
	void				Empty();									// Clears the string
	wchar_t				GetAt(int nIndex) const;					// Returns char at index "nIndex"
	void				SetAt(int nIndex, wchar_t ch);				// Set the character at position "nIndex"
	CMyString			MakeUpper(void);							// Convert all the string in upper case char
	CMyString			MakeLower(void);							// Convert all the string in lower case char
	CMyString			MakeReverse(void);							// Convert all the string in reverse case char
	int					Find(wchar_t ch) const;						// Find the first occourrency of "ch" in the string
	int					Find(wchar_t ch, int nStart) const;			// Find the first occourrency of "ch" in the string, starting from nStart
	int					Find(const wchar_t *pStrToFind) const;						// Find the first occourrency of "pStrToFind" in the string
	int					Find(const wchar_t *pStrToFind, int nStart) const;			// Find the first occourrency of "pStrToFind" in the string, starting from nStart
	int					Replace(wchar_t chOld, wchar_t chNew);						// Replace all the char in the string
	int					Replace(const wchar_t * lpszOld, const wchar_t * lpszNew);	// Replace all the char in the string

	// Extraction
	CMyString			Left(int nCount) const;						// Extracts the left part of a string(like the Basic LEFT$ function).

	void				Set( const CMyString &strSrc );				// Set the string as "strSrc"
	void				Set( const wchar_t *pStr );					// Set the string as "pStr"
	void				Set( wchar_t ch );							// Set the string as "ch"

	template<class A1>
	void				Format( wchar_t* szFmt, const A1& v)
	{
		fmt(szFmt, FmtArg<A1>(v)());
	}
	template<class A1>
	void				AppendFormat(wchar_t* szFmt, const A1& v)
	{
		CMyString		strApp;
		strApp.Format(szFmt, v);
		Append(strApp);
	}

	template<class A1, class A2>
	void				Format(wchar_t* szFmt, const A1& v1, const A2& v2)
	{fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)());}



	template<class A1, class A2>
	void				AppendFormat(wchar_t* szFmt, const A1& v1, const A2& v2)
	{
		CMyString		strApp;
		strApp.Format(szFmt, v1, v2);
		*this += strApp;
	}

protected:
	void				fmt(wchar_t* szFmt, ...);
	void				formatV( wchar_t *szFormat, va_list argList );
	int					replace_all( CMyString & str, CMyString from, CMyString to);

	// Membri
private:
#ifdef UNICODE
	std::wstring		m_strData;					// Stringa
#else
	std::string			m_strData;					// Stringa
#endif

};

