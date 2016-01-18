#include "..\StdAfx.h"
#include "UV_UtilString.h"
#include <math.h>

namespace UV
{

	CUV_UtilString::CUV_UtilString(void)
	{
	}

	CUV_UtilString::~CUV_UtilString(void)
	{
	}

	void CUV_UtilString::SplitStringOnChar(const CStdString *pStrOrig, CStdString strSplitChars, vect_CString &aSpez)	///< Spezza la stringa nella sotto stringa indicata.
	{
		int			nI, nMin, nPos = 0, nC, nStart = 0;		// parto dall'inizio.
		int			*pPos = NULL, nPosOld;
		BOOL		bTrovato;

		aSpez.clear();
		if (!pStrOrig)
		{
			return;
		}

		pPos = new int[strSplitChars.GetLength()];
		for (nC = 0; nC < strSplitChars.GetLength(); nC++)
		{
			pPos[nC] = -1;
		}
		do
		{
			nPosOld = pPos[nPos];			// posizione di partenza.
			bTrovato = FALSE;
			nMin = pStrOrig->GetLength() + 10;
			for (nC = 0; nC < strSplitChars.GetLength(); nC++)
			{
				pPos[nC] = pStrOrig->Find(strSplitChars[nC], nStart);
				if (pPos[nC] >= 0)
				{
					if (pPos[nC] < nMin)
					{
						nPos = nC;
						nMin = pPos[nPos];
					}
					bTrovato = TRUE;
				}
			}
			if (bTrovato)
			{
				// cerco l'indice minore.
				aSpez.push_back(pStrOrig->Mid(nPosOld + 1, pPos[nPos] - nPosOld - 1));
				nStart = pPos[nPos] + 1;
			}
		} while (bTrovato);
		aSpez.push_back(pStrOrig->Mid(nPosOld + 1));

		// rimuovo le stringhe nulle.
		for (nI = 0; nI < aSpez.size(); nI++)
		{
			if (aSpez[nI].IsEmpty() || ((aSpez[nI].GetLength() == 1) && (aSpez[nI].GetAt(0) == 9)))	// tolgo i tab e le vuote.
			{
				aSpez.erase(aSpez.begin() + nI);
				nI--;
			}
		}

		delete[] pPos;
	}

	BOOL CUV_UtilString::GetAttrib(CStdString strAttrName, CStdString &strAttrVal, const vect_sUV_Attrib &aAttr)	///< Torna l'attributo specificato.
	{
		INT_PTR						nI;
		const sUV_Attrib			*pAttr = aAttr.data();

		for (nI = 0; nI < aAttr.size(); nI++)
		{
			if (strAttrName.CompareNoCase(pAttr[nI].strName) == 0)
			{
				strAttrVal = pAttr[nI].strVal;
				return TRUE;
			}
		}
		return FALSE;
	}

	INT_PTR CUV_UtilString::GetListOfDouble(const CStdString *pStrVal, vect_double &aVals)
	{
		vect_CString			aSpez;
		CStdString					strApp;
		INT_PTR					nI;
		int						nMeno;

		ASSERT(pStrVal);
		if (!pStrVal)
		{
			return 0;
		}

		if (pStrVal->IsEmpty())
		{
			aVals.clear();
			return 0;
		}
		strApp = *pStrVal;
		strApp.Remove(' ');
		if (strApp.IsEmpty())
		{
			aVals.clear();
			return 0;
		}

		CUV_UtilString::SplitStringOnChar(pStrVal, _T(", "), aSpez);

		for (nI = 0; nI < aSpez.size(); nI++)
		{
			// spezzo sui segni -
			nMeno = aSpez[nI].Find(_T('-'), 1);		// quello iniziale non devo considerarlo.
			if (nMeno > 0)
			{		// forse devo spezzare.
				if (aSpez[nI].GetAt(nMeno - 1) != 'e')
				{
					strApp = aSpez[nI].Right(aSpez[nI].GetLength() - nMeno);
					aSpez[nI] = aSpez[nI].Left(nMeno);
					//aSpez.InsertAt( nI+1 , strApp );
					aSpez.insert(aSpez.begin() + nI + 1, strApp);

				}
			}
		}

		aVals.resize(aSpez.size());
		for (nI = 0; nI < aSpez.size(); nI++)
		{
			aVals[nI] = GetDouble(aSpez[nI]);
		}
		return aVals.size();
	}

	DOUBLE CUV_UtilString::GetDouble(const CStdString &strVal)
	{
		int				nPosE = -1;
		DOUBLE			dVal = 0.0;

		// Notazione scientifica.
		nPosE = strVal.Find(_T('e'));
		if (nPosE == -1)
		{
			nPosE = strVal.Find(_T('E'));
		}
		if (nPosE > 0)
		{
			CStdString			strMantissa, strEsponente;
			DOUBLE			dMantissa, dEsponente;

			strMantissa = strVal.Mid(0, nPosE);			// mantissa.
			strEsponente = strVal.Mid(nPosE + 1);			// esponente.
			dMantissa = GetDouble(strMantissa);
			dEsponente = GetDouble(strEsponente);
			dVal = dMantissa * pow(10.0, dEsponente);
		}
		else
		{
			dVal = std::stod(strVal);
		}
		return dVal;
	}

	BOOL CUV_UtilString::IsCharSeparator(TCHAR cIn, TCHAR *pChar, INT_PTR nChar)		///< Il carattere e' uno dei separatori?
	{
		BOOL			bMemPropria = FALSE;
		BOOL			bIsSeparatore = FALSE;
		INT_PTR			nI;

		if (!pChar)
		{
			nChar = 2;
			pChar = new TCHAR[nChar];
			pChar[1] = _T(' ');			// spazio.
			pChar[2] = _T('	');			// tab.
			bMemPropria = TRUE;
		}
		for (nI = 0; nI < nChar; nI++)
		{
			if (cIn == pChar[nI])
			{
				bIsSeparatore = TRUE;
				break;
			}
		}
		if (bMemPropria)
		{
			delete pChar;
		}
		return bIsSeparatore;
	}

	//CStdString CUV_UtilString::BrowseForFile( CWnd *pWin , CStdString strOldFileName , CStdString strFilter , BOOL bOpen )
	//{
	//	CStdString			strOut;
	//	CStdString			strFile, strGridName;
	//	CStdString			strTitle;
	//
	//	if ( strFilter.IsEmpty() )
	//	{
	//		strFilter = _T("Tutti i files (*.*)|*.*||");
	//	}
	//	strTitle = _T("Seleziona eseguibile Domino" );
	//	CFileDialog		dlg( bOpen , _T("*.exe"), NULL , OFN_FILEMUSTEXIST | OFN_ENABLESIZING | OFN_NOCHANGEDIR, strFilter, pWin );		// Apro la finestra per il caricamento exe domino (file .exe).
	//	dlg.m_pOFN->lpstrTitle = strTitle;
	//	dlg.m_ofn.lpstrInitialDir = strOldFileName;
	//
	//	if( dlg.DoModal() == IDOK )
	//	{
	//		strOut = dlg.GetPathName();
	//	}
	//	return strOut;
	//}
	//
	//CStdString CUV_UtilString::BrowseForDir( CWnd * /*pWin*/ , CStdString /*strOldDirPath*/ , BOOL /*bOpen*/ )
	//{
	//	CStdString			strOut;
	//
	//	return strOut;
	//}

	void CUV_UtilString::RandomInit(void)
	{
		/*
		CFileTime				ftIniz = CFileTime::GetCurrentTime();
		unsigned int			nVal;

		nVal = ftIniz.dwLowDateTime;				// Seme basato sull'ora attuale.
		srand( nVal );
		*/
	}

	CStdString CUV_UtilString::GetRandomString(int nLenMin, int nLenMax)							///< Torna una stringa casuale
	{
		unsigned int			nVal;
		nVal = rand() % (nLenMax - nLenMin + 1);
		return GetRandomString_Len(nLenMin + nVal);
	}

	CStdString CUV_UtilString::GetRandomString_Len(int nLen)										///< Torna una stringa casuale
	{
		unsigned int			nVal;
		int						nI;
		int						nCharFirst = 33;	// !
		int						nCharLast = 126;	// ~
		int						nCharNum = nCharLast - nCharFirst + 1;
		TCHAR					*pbuf = NULL;
		CStdString					strOut;

		pbuf = new TCHAR[nLen + 1];

		for (nI = 0; nI < nLen; nI++)
		{
			nVal = rand();
			nVal = nVal%nCharNum;
			pbuf[nI] = (TCHAR)(nCharFirst + nVal);
		}
		pbuf[nLen] = 0;
		strOut.Format(_T("%s"), pbuf);
		delete[] pbuf;
		return strOut;
	}

	INT_PTR CUV_UtilString::SplitStringOnChar_OC(const CStdString strIn, vect_CString &aElem, const CStdString strSplitChar, const CStdString &strOpen, const CStdString &strClose)		///< Spezza la stringa passata secondo dove si trovano gli "splitchar" stando attento che non ci siano parentesi aperte.
	{
		int						nI, nJ;
		int						nStart = 0, nStop = 0;
		TCHAR					cCurr, cSplit;
		CStdString				strElem;
		vect_int				aApert;							///< Numero di aperture per ogni parentesi
		BOOL					bParentesiAperta = FALSE;
		bool					bSameOpenClose;					///< Aperto o chiuso e' la stessa stringa

		bSameOpenClose = (strOpen.Compare(strClose) == 0);
		// Predispongo per contare il numero di aperture e chiusure per ogni parentesi (o simili)
		if ((strOpen.GetLength() == strClose.GetLength()) && (strClose.GetLength() > 0))
		{
			aApert.resize(strOpen.GetLength());
		}

		aElem.clear();
		for (nI = 0; nI < strIn.GetLength(); nI++)
		{
			cCurr = strIn[nI];
			nStop = nI;

			///////////////////////////////////////////////////////////
			// aperture e chiusure
			if (!aApert.empty())
			{
				bParentesiAperta = FALSE;
				if (bSameOpenClose)
				{
					for (nJ = 0; nJ < aApert.size(); nJ++)
					{
						if (cCurr == strOpen.GetAt(nJ))
							aApert[nJ] = 1 - aApert[nJ];
					}
				}
				else
				{
					for (nJ = 0; nJ < aApert.size(); nJ++)
					{
						if (cCurr == strOpen.GetAt(nJ))
							aApert[nJ]++;
						else if (cCurr == strClose.GetAt(nJ))
							aApert[nJ]--;
					}
				}

				// conto il numero di parentesi aperte.
				for (nJ = 0; nJ < aApert.size(); nJ++)
				{
					if (aApert[nJ] != 0)
					{
						bParentesiAperta = TRUE;		// passoal prossimo carattere
						break;
					}
				}
			}

			if (!bParentesiAperta)
			{
				for (nJ = 0; nJ < strSplitChar.GetLength(); nJ++)
				{
					cSplit = strSplitChar[nJ];
					if (cCurr == cSplit)
					{
						if (nStart < nStop)
						{
							strElem = strIn.Mid(nStart, nStop - nStart);
						}
						else
						{
							strElem = _T("");
						}
						if (strElem.GetLength())
							aElem.push_back(strElem);
						nStart = nI + 1;
					}
				}
			}
		}

		if (nStart < strIn.GetLength())
		{
			strElem = strIn.Mid(nStart);
			if (strElem.GetLength())
				aElem.push_back(strElem);
		}

		for (nI = 0; nI < aElem.size(); nI++)
		{
			aElem[nI].TrimLeft(_T("\""));
			aElem[nI].TrimRight(_T("\""));
		}

		return aElem.size();
	}

	void CUV_UtilString::Convert_uint2CStringBin(unsigned int nVal, CStdString &strBin)		// converte l'intero senza segno passato in una stringa che contiene il binario.
	{
		int				nBit, nV;
		CStdString		strApp;

		strBin = _T("");
		for (nBit = 15; nBit >= 0; nBit--)
		{
			nV = (nVal >> nBit) & 0x01;
			strApp.Format(_T("%d"), nV);
			strBin += strApp;
		}
	}

	void CUV_UtilString::Convert_CString2wchar_t(const CStdString &strMess, wchar_t *pBuf, INT_PTR nCar)		///< Converto la stringa passata in un vettore di wchar_t.
	{
#ifdef UNICODE
		_tcscpy_s(pBuf, nCar, strMess);
#else
		char	*pBufChar = new char[nCar];
		Convert_CString2charVet(strMess, pBufChar, nCar);
		Convert_charVet2WCHAR(pBufChar, pBuf, nCar);
		delete[] pBufChar;
#endif
	}

	void CUV_UtilString::Convert_CString2TCHATVet(const CStdString &strMess, TCHAR *pBuf, INT_PTR nCar)
	{
		if (nCar >= strMess.GetLength() + 1)
		{
			_stprintf_s(pBuf, nCar, strMess);
		}
		else
		{
			_stprintf_s(pBuf, nCar, strMess.Left((int)nCar - 1));
		}
	}

	void CUV_UtilString::Convert_CString2charVet(const CStdString &strMess, char *pBuf, INT_PTR nCar)
	{
#ifdef UNICODE
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strMess, -1, pBuf, (int)nCar, NULL, NULL);
#else
		_stprintf_s(pBuf, nCar, _T("%s"), strMess);
#endif
	}

	void CUV_UtilString::Convert_charVet2WCHAR(const char *pBufScr, wchar_t *pBufDes, INT_PTR nCar)				///< Converto da caratere 1byte a carattere 2byte.
	{
		MultiByteToWideChar(CP_ACP, 0, pBufScr, -1, pBufDes, (int)nCar);
	}

	bool CUV_UtilString::Convert_charVet2CString(const char *pBuf, CStdString &strMess)								///< Converto il vettore di char in una stringa, la lunghezza e' determinata dalla funzione.
	{
#ifdef _UNICODE
		int				nRes = 0;
		TCHAR			*bb = NULL;

		nRes = MultiByteToWideChar(CP_ACP, 0, pBuf, -1, bb, (int)0);		// Mi calcolo il numero di caratteri necessari
		if (nRes > 0)
		{
			TCHAR		*bb = new TCHAR[nRes];								// Alloco lo spazio necessario
			nRes = MultiByteToWideChar(CP_ACP, 0, pBuf, -1, bb, nRes);	// Chiamo la conversione
			if (nRes > 0)														// Se ha avuto successo...
				strMess.Format(_T("%s"), bb);							// Butto dentro la stringa
			delete bb;
			return (nRes > 0);
		}
#else
		strMess.Format(_T("%s"), pBuf);
#endif
		return true;
	}

	void CUV_UtilString::Convert_charVet2CString(const char *pBuf, CStdString &strMess, INT_PTR nCar)
	{
#ifdef _UNICODE
		TCHAR		*bb = new TCHAR[nCar];
		MultiByteToWideChar(CP_ACP, 0, pBuf, -1, bb, (int)nCar);
		strMess.Format(_T("%s"), bb);
		delete bb;
#else
		strMess.Format(_T("%s"), pBuf);
#endif
	}

	INT_PTR CUV_UtilString::FindStringIndex(const vect_CString &aStr, const CStdString &str, BOOL bCaseSensitive)
	{
		INT_PTR			nI;

		for (nI = 0; nI < aStr.size(); nI++)
		{
			if (bCaseSensitive)
			{
				if (aStr[nI].Compare(str) == 0)
					return nI;
			}
			else
			{
				if (aStr[nI].CompareNoCase(str) == 0)
					return nI;
			}
		}
		return -1;
	}

	int CUV_UtilString::CancellaZeriAllaDxDelPunto(CStdString &strValueToReduce)		///< Cancella gli zeri alla destra del punto
	{
		int				nIndex = strValueToReduce.Find(_T("."));
		int				nDeletedZero = 0;

		if (nIndex >= 0)
		{
			// tolgo gli zeri
			while (strValueToReduce.GetLength() && (strValueToReduce.GetAt(strValueToReduce.GetLength() - 1) == _T('0')))
			{
				strValueToReduce.Delete(strValueToReduce.GetLength() - 1);
				nDeletedZero++;
			}

			if (strValueToReduce.GetLength() && (strValueToReduce.GetAt(strValueToReduce.GetLength() - 1) == _T('.')))
			{
				strValueToReduce.Delete(strValueToReduce.GetLength() - 1);
			}
		}
		return nDeletedZero;
	}


}
