#pragma once

//#include "UtilVARIE_Export.h"
//#include "Definizioni_Varie.h"

#include "inclusioni_UV.h"

namespace UV
{

	/** Classe di utilita' varia per le stringhe. Classe di utilita' varia per le stringhe
	*
	*/
	class /*UTILVARIELIB_API*/ CUV_UtilString
	{
		// Metodi.
	public:
		CUV_UtilString(void);
		~CUV_UtilString(void);

		// 1 - Conversione Stringhe-char-TCHAR-wchar_t
		static void				Convert_CString2TCHATVet(const CStdString &strMess, TCHAR *pBuf, INT_PTR nCar);		///< Converto la stringa passata in un vettore di TCHAR.
		static void				Convert_CString2wchar_t(const CStdString &strMess, wchar_t *pBuf, INT_PTR nCar);		///< Converto la stringa passata in un vettore di wchar_t.
		static void				Convert_CString2charVet(const CStdString &strMess, char *pBuf, INT_PTR nCar);			///< Converto la stringa passata in un vettore di char.
		static void				Convert_charVet2CString(const char *pBuf, CStdString &strMess, INT_PTR nCar);			///< Converto il vettore di char in una stringa.
		static bool				Convert_charVet2CString(const char *pBuf, CStdString &strMess);							///< Converto il vettore di char in una stringa, la lunghezza e' determinata dalla funzione.
		static void				Convert_charVet2WCHAR(const char *pBufScr, wchar_t *pBufDes, INT_PTR nCar);			///< Converto da caratere 1byte a carattere 2byte.
		// 2 - Conversione varie -> stringa
		static void				Convert_uint2CStringBin(unsigned int nVal, CStdString &strBin);										///< Converte l'intero senza segno passato in una stringa che contiene il binario.
		static CStdString		Convert_sec2CString(double dTotSec, BOOL bMinutes = TRUE, BOOL bHours = TRUE, BOOL bDays = TRUE);	///< Converte il valore in secondi (con la virgola) in una stringa formattata come si vuole
		static CStdString		Convert_sec2CString(ULONGLONG nTotSec, BOOL bMinutes = TRUE, BOOL bHours = TRUE);					///< Converte il valore in secondi (numero intero) in una stringa formattata come si vuole
		static CStdString		Convert_double2Taglia(DOUBLE dTaglia, BOOL bSX);													///< Converte dal double alla taglia in formato stringa.
		static CStdString		Convert_filesize2String(DWORD nFileSizeHigh, DWORD nFileSizeLow);									///< Lunghezza del file.

		static void				SplitStringOnChar(const CStdString *pStrOrig, CStdString strSplitChars, vect_CString &aSpez);					///< Spezza la stringa nella sotto stringa indicata.
		static INT_PTR			SplitStringOnChar_OC(const CStdString strIn, vect_CString &aElem, const CStdString strSplitChar, const CStdString &strOpen, const CStdString &strClose);		///< Spezza la stringa passata secondo dove si trovano gli "splitchar" stando attento che non ci siano parentesi aperte.

		static BOOL				GetAttrib(CStdString strAttrName, CStdString &strAttrVal, const vect_sUV_Attrib &aAttr);							///< Torna l'attributo.
		static INT_PTR			GetListOfDouble(const CStdString *pStrVal, vect_double &aVals);											///< Legge la lista di VAL nella stringa passata.
		static DOUBLE			GetDouble(const CStdString &strVal);																			///< converto da stringa in valore.
		static BOOL				IsCharSeparator(TCHAR cIn, TCHAR *pChar = NULL, INT_PTR nChar = 0);											///< Il carattere e' uno dei separatori? (li posso indicare oppure per default: spazio + tab + return )

		static CStdString		GetRandomString(int nLenMin = 2, int nLenMax = 20);															///< Torna una stringa casuale
		static CStdString		GetRandomString_Len(int nLen);																			///< Torna una stringa casuale
		static void				RandomInit(void);

		static INT_PTR			FindStringIndex(const vect_CString &aStr, const CStdString &str, BOOL bCaseSensitive);	///< trova la stringa nel vettore, -1 se non lo trovo
		static int				CancellaZeriAllaDxDelPunto(CStdString &strValueToReduce);				///< Cancella gli zeri alla destra del punto
	};



}
