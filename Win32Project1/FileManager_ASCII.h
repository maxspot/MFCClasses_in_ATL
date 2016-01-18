#pragma once

#include "FileManager_BIN.h"

enum eTextFileType
{
	eTextFileType_ANSI=0,
	eTextFileType_UNICODE,
	eTextFileType_UNICODE_BE,
	eTextFileType_UTF_8
};

class CFileManager_ASCII : public CFileManager_BIN
{
public:
							CFileManager_ASCII();
							~CFileManager_ASCII();

public:
	bool					Read_ASCII(std::string strFileName);			// Leggo il file ASCII specificato

protected:
	static bool				Convert_BIN_2_ASCIIRows(const char *pBuf, unsigned int nLen, vect_string &rows, vect_wstring &wrows, eTextFileType eTextType= eTextFileType_ANSI);	// Converte da BINARIO a vettore di stringhe. Spezzando dove serve.
	static int				Convert_BIN_2_ASCII(const char *pBuf, unsigned int nLen, std::string *pStr, std::wstring *pWStr, eTextFileType eTextType = eTextFileType_ANSI);		// Converte BIN in string. 0=error, 1=string, 2=wstring.

	static eTextFileType	GetASCIIType( const char *pBuf, unsigned int nLen, int *pNOffset=NULL );					// Che tipo è questo file ASCII?
	static std::wstring		Convert_UTF8_to_string(const char *pBuf, unsigned int nLen);								// Converto da UTF8 a string
	static void				Convert_string_to_UTF8( const std::string &str, vect_char &data, bool bAppend=false);		// Converto da string a UTF8
	static void				Convert_wchar_t_to_UTF8( wchar_t cha, vect_char &data, bool bAppend = false);				// Converto da wchar_t a UTF8

public:
	eTextFileType			m_eType;										// Tipo di codifica ASCII
	vect_string				m_rows;											// Righe del file ascii. lista delle stringhe.
	vect_wstring			m_wrows;										// Righe del file ascii. lista delle stringhe.
};

