#pragma once

//#include "UtilVARIE_Export.h"

//#include "Dlg_Progresso.h"

//#include "Dlg_ProgressoEM2D.h"
//class CDlg_Progresso;

#include "inclusioni_UV.h"

namespace UV
{

	/** Gestore File ASCII, legge letti riga per riga.
	*
	*/
	class /*UTILVARIELIB_API*/ CASCIIManager
	{
		// Metodi.
	public:
								CASCIIManager(void);
								~CASCIIManager(void);

		virtual bool			ReadFile(CStdString strFileName/*, UV_MFC::CDlg_Progresso *pDlg = NULL*/);		///< Leggo da file.
		static bool				ReadFile(CStdString strFileName, CStdStringArray &aRighe/*, UV_MFC::CDlg_Progresso *pDlg = NULL*/);		///< Leggo da file.
		virtual bool			WriteFile(CStdString strFileName/*, UV_MFC::CDlg_Progresso *pDlg = NULL*/);		///< Scrivo il file, con le righe caricate.

		static bool				Convert_BinaryBuffer_2_CStrings(char *pBuf, ULONGLONG nBufLen, CStdStringArray &aRows);	///< Converte la sequenza di caratteri in un vettore di stringhe. Per convertire bene l'ultima stringa c'e' bisogno che ci sia un terminatore (10) oppure uno (0).

	protected:
		//static bool			readFile_using_CStdioFile(CStdString strFileName, CStdStringArray &aRighe/*, UV_MFC::CDlg_Progresso *pDlg = NULL*/);	///< Leggo da file.
		static bool				readFile_using_std_stream(CStdString strFileName, CStdStringArray &aRighe/*, UV_MFC::CDlg_Progresso *pDlg = NULL*/);	///< Leggo da file.
		//static bool			readFile_using_CFile(CStdString strFileName, CStdStringArray &aRighe/*, UV_MFC::CDlg_Progresso *pDlg = NULL*/);		///< Leggo da file.

	public:
		static bool				writeFile_using_std_stream(CStdString strFileName, CStdStringArray &aRighe);		///< Scrivo su file le righe
		//static bool				WriteFile(CStdString strFileName, CStdString strText);										///< Testo del file da scrivere.

	public:
		int						GetUniqueString(CStdString &strText);			///< Torna il testo in una unica stringa. Torna il numero di righe.

		// Dati.
	public:
		CStdString				m_strFileName;	///< Nome del file che ho caricato.
		CStdStringArray			m_aRighe;		///< Vettore di righe lette dal fila ascii.
	};


}
