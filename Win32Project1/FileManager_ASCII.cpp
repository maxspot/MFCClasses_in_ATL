#include "stdafx.h"
#include "FileManager_ASCII.h"

using namespace std;

CFileManager_ASCII::CFileManager_ASCII()
{
}

CFileManager_ASCII::~CFileManager_ASCII()
{
}

bool CFileManager_ASCII::Read_ASCII(std::string strFileName)			// Leggo il file ASCII specificato
{
	if (Read_BIN(strFileName))											// Leggo il binario
	{
		int			nOffset = 0;
		m_eType = GetASCIIType( m_buf.m_data.data(), m_buf.m_data.size(), &nOffset );											// Tipo di testo
		return Convert_BIN_2_ASCIIRows( m_buf.m_data.data()+ nOffset, m_buf.m_data.size()- nOffset, m_rows, m_wrows, m_eType );	// Conversione
	}
	return false;
}

bool CFileManager_ASCII::Convert_BIN_2_ASCIIRows( const char *pBuf, unsigned int nLen, vect_string &rows, vect_wstring &wrows, eTextFileType eTextType )
{
	unsigned int		nPosCurr = 0;				// Posizione corrente
	unsigned int		nPosStart = 0;				// Posizione di partenza per la prossima stringa
	unsigned int		nLenBreak = 0;				// Lunghezza del break (numero di bye)
	string				strNew;						// Nuova stringa da inserire
	wstring				wstrNew;					// Nuova stringa da inserire
	int					nRes;

	rows.clear();

	for (nPosCurr = 0; nPosCurr < nLen -1; nPosCurr++)
	{
		// 1 - controllo se alla posizione corrente ho un break
		if ((pBuf[nPosCurr] == 10) && (pBuf[nPosCurr + 1] == 13))
			nLenBreak = 2;
		else if ((pBuf[nPosCurr] == 13) && (pBuf[nPosCurr + 1] == 10))
			nLenBreak = 2;
		else if ((pBuf[nPosCurr] == 10) || (pBuf[nPosCurr] == 13))
			nLenBreak = 1;
		else
			nLenBreak = 0;

		// 2 - Se ho un break, vado a spezzare
		if (nLenBreak > 0)
		{
			nRes = Convert_BIN_2_ASCII( pBuf+nPosStart, nPosCurr-nPosStart, &strNew, &wstrNew, eTextType);
			if (nRes==1)
				rows.push_back(strNew);
			else if (nRes == 2)
				wrows.push_back(wstrNew);
			nPosCurr += nLenBreak;
			nPosStart = nPosCurr;
			nPosCurr--;
		}
	}

	if (nPosStart < nPosCurr)
	{
		nRes = Convert_BIN_2_ASCII(pBuf + nPosStart, nPosCurr - nPosStart, &strNew, &wstrNew, eTextType);
		if (nRes == 1)
			rows.push_back(strNew);
		else if (nRes == 2)
			wrows.push_back(wstrNew);
	}
	return true;
}

//#include "stdstring.h"

int CFileManager_ASCII::Convert_BIN_2_ASCII(const char * pBuf, unsigned int nLen, std::string *pStr, std::wstring *pWStr, eTextFileType eTextType)
{
	//CStdString		SS;
	

	int			nRes = 0;
	switch (eTextType)
	{
		case eTextFileType_ANSI:
			if (pStr)
			{
				*pStr = string(pBuf, nLen);
				nRes = 1;
			}
		break;
		case eTextFileType_UNICODE:
		break;
		case eTextFileType_UNICODE_BE:
		break;
		case eTextFileType_UTF_8:
			if (pStr)
			{
				*pWStr = Convert_UTF8_to_string(pBuf, nLen);
				nRes = 2;
			}
		break;
		default:
		break;
	}
	return nRes;
}

eTextFileType CFileManager_ASCII::GetASCIIType(const char *pBuf, unsigned int nLen, int *pNOffset)		// Che tipo è questo file ANSI o UNICODE?
{
	const unsigned char		*pBuf_U = (const unsigned char *)pBuf;

	if (nLen > 3)
		if ((pBuf_U[0] == 0xef) && (pBuf_U[1] == 0xbb) && (pBuf_U[2] == 0xbf))
		{
			if (pNOffset)
				*pNOffset = 3;
			return eTextFileType_UTF_8;
		}
	if (nLen > 2)
	{
		if ((pBuf_U[0] == 0xff) && (pBuf_U[1] == 0xfe))
		{
			if (pNOffset)
				*pNOffset = 2;
			return eTextFileType_UNICODE;
		}
		if ((pBuf_U[0] == 0xfe) && (pBuf_U[1] == 0xff))
		{
			if (pNOffset)
				*pNOffset = 2;
			return eTextFileType_UNICODE_BE;
		}
	}
	return eTextFileType_ANSI;
}

std::wstring CFileManager_ASCII::Convert_UTF8_to_string(const char *pBuf, unsigned int nLen)
{
	INT_PTR			n, nMax = nLen;
	wstring			sFinal, sTemp;
	BYTE			z, y, x, w, v, u;

	//wstring			sFF;
	//sFF = _T("(漢)");

	for (n = 0; n < nMax; ++n)
	{
		z = pBuf[n];

		/////////////////////////////////
		// newline + c.r.
		if (z == 13)
		{
			if (n + 1 >= nMax) break;			// errore-.
			y = pBuf[n + 1];
			if (y == 10)
			{
				sFinal += _T('\n');
				n += 1;
			}
		}
		/////////////////////////////////
		// carattere normale.(1 byte)
		else if (z < 127)
		{
			sFinal += (TCHAR)z;					// lo prendo così com'è.
		}
		/////////////////////////////////
		// carattere di 2 byte.
		else if (z <= 223)
		{
			if (n + 1 >= nMax) break;			// errore-.
			y = pBuf[n + 1];
			sFinal += (TCHAR)((z - 192) * 64 + (y - 128));
			n += 1;
		}
		/////////////////////////////////
		// carattere di 3 byte.
		else if (z <= 239)
		{
			if (n + 2 >= nMax) break;			// errore-.
			y = pBuf[n + 1];
			x = pBuf[n + 2];
			sFinal += (TCHAR)((z - 224) * 4096 + (y - 128) * 64 + (x - 128));
			n += 2;
		}
		/////////////////////////////////
		// carattere di 4 byte.
		else if (z <= 247)			// character is four bytes
		{
			if (n + 3 >= nMax) break;			// errore-.
			y = pBuf[n + 1];
			x = pBuf[n + 2];
			w = pBuf[n + 3];
			sFinal += (TCHAR)((z - 240) * 262144 + (y - 128) * 4096 + (x - 128) * 64 + (w - 128));
			n += 3;
		}
		/////////////////////////////////
		// carattere di 5 byte.
		else if (z <= 251)
		{
			// character is four bytes
			if (n + 4 >= nMax) break;			// errore-.
			y = pBuf[n + 1];
			x = pBuf[n + 2];
			w = pBuf[n + 3];
			v = pBuf[n + 4];
			sFinal += (TCHAR)((z - 248) * 16777216 + (y - 128) * 262144 + (x - 128) * 4096 + (w - 128) * 64 + (v - 128));
			n += 4;
		}
		/////////////////////////////////
		// carattere di 6 byte.
		else if (z <= 253)
		{
			if (n + 5 >= nMax) break;			// errore-.
			y = pBuf[n + 1];
			x = pBuf[n + 2];
			w = pBuf[n + 3];
			v = pBuf[n + 4];
			u = pBuf[n + 5];
			sFinal += (TCHAR)((z - 252) * 1073741824 + (y - 128) * 16777216 + (x - 128) * 262144 + (w - 128) * 4096 + (v - 128) * 64 + (u - 128));
			n += 5;
		}
	}
	return sFinal;
}

void CFileManager_ASCII::Convert_string_to_UTF8( const std::string & str, vect_char &data, bool bAppend )
{
	int			nI, nCont = str.length();

	if (!bAppend)
		data.clear();

	for (nI = 0; nI<nCont; nI++)
		Convert_wchar_t_to_UTF8(str[nI], data, true);
}

void CFileManager_ASCII::Convert_wchar_t_to_UTF8( wchar_t cha, vect_char & data, bool bAppend )
{
	WORD		ch;

	if (!bAppend)
	{
		data.clear();
	}
	ch = (WORD)cha;
	if (ch == _T('\n'))					// return.
	{
		data.push_back((BYTE)0x0D);
		data.push_back((BYTE)0x0A);
	}
	else if (ch < 128)					// 1 byte.
	{
		data.push_back((BYTE)ch);
	}
	else if (ch <= 2047)				// 2 byte.
	{
		data.push_back((BYTE)(192 + (ch / 64)));
		data.push_back((BYTE)(128 + (ch % 64)));
	}
	else if (ch <= 65535)				// 3 byte.
	{
		data.push_back((BYTE)(224 + (ch / 4096)));
		data.push_back((BYTE)(128 + ((ch / 64) % 64)));
		data.push_back((BYTE)(128 + (ch % 64)));
	}
	else if (ch <= 2097151)				// 4 byte.
	{
		data.push_back((BYTE)(240 + (ch / 262144)));
		data.push_back((BYTE)(128 + ((ch / 4096) % 64)));
		data.push_back((BYTE)(128 + ((ch / 64) % 64)));
		data.push_back((BYTE)(128 + (ch % 64)));
	}
	else if (ch <= 67108863)				// 5 byte.
	{
		data.push_back((BYTE)(248 + (ch / 16777216)));
		data.push_back((BYTE)(128 + ((ch / 262144) % 64)));
		data.push_back((BYTE)(128 + ((ch / 4096) % 64)));
		data.push_back((BYTE)(128 + ((ch / 64) % 64)));
		data.push_back((BYTE)(128 + (ch % 64)));
	}
	else if (ch <= 2147483647)			// 6 byte.
	{
		data.push_back((BYTE)(252 + (ch / 1073741824)));
		data.push_back((BYTE)(128 + ((ch / 16777216) % 64)));
		data.push_back((BYTE)(128 + ((ch / 262144) % 64)));
		data.push_back((BYTE)(128 + ((ch / 4096) % 64)));
		data.push_back((BYTE)(128 + ((ch / 64) % 64)));
		data.push_back((BYTE)(128 + (ch % 64)));
	}
}

