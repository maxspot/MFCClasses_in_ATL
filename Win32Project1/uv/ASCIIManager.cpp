#include "..\stdafx.h"
#include "ASCIIManager.h"

//#include "MiraCounter.h"
//#include "UV_Util.h"
#include "UV_UtilString.h"
#include "..\UV_string.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "MiraCounter.h"

using namespace std;

namespace UV
{

	CASCIIManager::CASCIIManager(void)
	{
	}

	CASCIIManager::~CASCIIManager(void)
	{
	}

	bool CASCIIManager::ReadFile(CStdString strFileName, CStdStringArray &aRighe /*, UV_MFC::CDlg_Progresso *pDlg*/)		///< Leggo da file.
	{
		CMiraCounter		HPC;
		double				dSec;
		bool				bRes = false;

		HPC.StartHPCrono();
		bRes = readFile_using_std_stream(strFileName, aRighe/*, pDlg*/);
		dSec = HPC.ReadHPCrono();

		return bRes;
	}

	bool CASCIIManager::ReadFile(CStdString strFileName /*, UV_MFC::CDlg_Progresso *pDlg*/)
	{
		bool			bRes;

		bRes = ReadFile(strFileName, m_aRighe/*, pDlg*/);
		if (bRes)
			m_strFileName = strFileName;
		return bRes;
	}

	bool CASCIIManager::writeFile_using_std_stream(CStdString strFileName, CStdStringArray &aRighe)		///< Scrivo su file le righe
	{
		wofstream		myfile;
		wstring			strApp;
		int				nR;

		CUV_string::Convert_CStdString_2_string(strFileName, strApp);

		myfile.open(strApp);

		if (myfile.is_open())
		{

			for (nR = 0; nR < aRighe.size(); nR++)
			{
				CUV_string::Convert_CStdString_2_string(aRighe[nR], strApp);
				myfile << strApp;
				myfile << "\n";
			}
			myfile.close();
		}
		return 0;
	}

	bool CASCIIManager::readFile_using_std_stream(CStdString strFileName, CStdStringArray &aRighe /*, UV_MFC::CDlg_Progresso *pDlg*/)		///< Leggo da file.
	{
		std::wifstream			myfile(strFileName);
		std::streampos			pos_begin = std::ios::beg;
		std::streampos			pos_curr;
		std::wstring			line;
		CStdString				strLine;
		int						fileLen = 0;
		int						nI = 0, nCont = 3500;
		ULONGLONG				nPosition;
		double					dPerc, dPerc1;
		CStdString				strFase;

		if (myfile.is_open())
		{
			// get length of file:
			myfile.seekg(0, myfile.end);
			fileLen = (int)myfile.tellg();
			myfile.seekg(0, myfile.beg);

			pos_curr = myfile.tellg();
			aRighe.clear();
			while (getline(myfile, line))
			{
				pos_curr = myfile.tellg();

				// std::cout << line << '\n';
				strLine.Format(_T("%s"), line.c_str());
				aRighe.push_back(strLine);
				nI++;

				//if (pDlg && nI > nCont)
				//{
				//	nPosition = pos_curr.seekpos();
				//	dPerc = nPosition / (double)fileLen;
				//	dPerc = max(0, min(1, dPerc));
				//	dPerc1 = pDlg->m_dPercMin + dPerc*(pDlg->m_dPercMax - pDlg->m_dPercMin);

				//	pDlg->SetPos(dPerc1);
				//	strFase.Format(_T("[%d/%d] Reading rows (%.1lf%%)"), pDlg->m_nFaseCurr, pDlg->m_nFaseTot, 100.0*dPerc);
				//	pDlg->SetFase(strFase);
				//	nI = 0;
				//	if (!pDlg->m_bContinua)
				//	{
				//		myfile.close();
				//		return false;
				//	}
				//}
			}
			myfile.close();
		}
		return true;
	}

	//bool CASCIIManager::readFile_using_CFile(CStdString strFileName, CStdStringArray &aRighe /*, UV_MFC::CDlg_Progresso * pDlg*/)		///< Leggo da file.
	//{
	//	return false;

	//	CFile					fIn;
	//	UINT					nFileLen = 0;
	//	char					*pBuf = NULL;
	//	UINT					nByteReaded = 0;
	//	bool					bReadOk = false;

	//	if (fIn.Open(strFileName, CFile::modeRead))
	//	{
	//		nFileLen = (UINT)fIn.GetLength();
	//		pBuf = new char[nFileLen + 1];
	//		nByteReaded = fIn.Read(pBuf, nFileLen);
	//		pBuf[nFileLen] = 10;
	//		fIn.Close();
	//		bReadOk = (nByteReaded == nFileLen);
	//		if (bReadOk)
	//			bReadOk = Convert_BinaryBuffer_2_CStrings(pBuf, nFileLen + 1, aRighe);
	//	}
	//	return bReadOk;
	//}


	//bool CASCIIManager::readFile_using_CStdioFile(CStdString strFileName, CStdStringArray &aRighe /*, UV_MFC::CDlg_Progresso *pDlg*/)
	//{
	//	CStdioFile		fIn;
	//	CStdString			strMess;
	//	int				nI, nCont = 3500;
	//	double			dPerc, dPerc1;
	//	ULONGLONG		nFileLen = 0;			// lunghezza del file.
	//	ULONGLONG		nPosition = 0;		// posizione corrente.
	//	CStdString			strFase;

	//	if (fIn.Open(strFileName, CFile::modeRead))			// Ho aperto il file in Lettura?
	//	{
	//		aRighe.RemoveAll();
	//		aRighe.SetSize(0, 1000);
	//		nFileLen = fIn.GetLength();
	//		nPosition = fIn.GetPosition();
	//		nI = 0;

	//		while (fIn.ReadString(strMess))
	//		{
	//			nPosition = fIn.GetPosition();
	//			aRighe.Add(strMess);
	//			nI++;
	//			if (pDlg && nI > nCont)
	//			{
	//				dPerc = nPosition / (double)nFileLen;
	//				dPerc1 = pDlg->m_dPercMin + dPerc*(pDlg->m_dPercMax - pDlg->m_dPercMin);

	//				pDlg->SetPos(dPerc1);
	//				strFase.Format(_T("[%d/%d] Reading rows (%.1lf%%)"), pDlg->m_nFaseCurr, pDlg->m_nFaseTot, 100.0*dPerc);
	//				pDlg->SetFase(strFase);
	//				nI = 0;
	//				if (!pDlg->m_bContinua)
	//				{
	//					fIn.Close();
	//					return false;
	//				}
	//			}
	//		}
	//		fIn.Close();
	//		return true;
	//	}
	//	return false;
	//}

	//bool CASCIIManager::WriteFile(CStdString strFileName, CStdString strText)		///< Testo del file da scrivere.
	//{
	//	/*
	//	CStdioFile			fOut;
	//	if (fOut.Open(strFileName, CFile::modeWrite | CFile::modeCreate))
	//	{
	//		fOut.WriteString(strText);
	//		fOut.Close();
	//		return true;
	//	}
	//	*/
	//	return false;
	//}

	bool CASCIIManager::WriteFile(CStdString strFileName /*, UV_MFC::CDlg_Progresso *pDlg*/)	///< Scrivo il file, con le righe caricate.
	{
		return writeFile_using_std_stream(strFileName, m_aRighe);

		/*
		CStdioFile			fOut;
		int					nI = 0, nCont = 1000;
		double				dPerc;

		if (fOut.Open(strFileName, CFile::modeWrite | CFile::modeCreate))
		{
			for (INT_PTR nR = 0; nR < m_aRighe.size(); nR++)
			{
				fOut.WriteString(m_aRighe[nR]);
				fOut.WriteString(_T("\n"));

				nI++;
				if (pDlg && nI > nCont)
				{
					dPerc = nR / (double)m_aRighe.size();
					pDlg->SetPos(pDlg->m_dPercMin + dPerc*(pDlg->m_dPercMax - pDlg->m_dPercMin));
					nI = 0;
				}
			}
			fOut.Close();
			return true;
		}
		*/
		return false;
	}

	int CASCIIManager::GetUniqueString(CStdString &strText)			///< Torna il testo in una unica stringa. Torna il numero di righe.
	{
		int					nI, nRighe = (int)m_aRighe.size();

		strText = _T("");
		for (nI = 0; nI < nRighe; nI++)
		{
			strText += m_aRighe[nI];
			strText += "\n";
		}
		return nRighe;
	}

	bool CASCIIManager::Convert_BinaryBuffer_2_CStrings(char *pBuf, ULONGLONG nBufLen, CStdStringArray &aRows)
	{
		int							nI, nLen = 0, nCurr = 0;
		int							nBreakType = 0;
		struct						sIndType { UINT nPos; int nType; };
		std::vector<sIndType>		aBreaks;
		int							nBreaksAllocated = 0, nBreakCurr = 0;
		sIndType					*pBreaks = NULL;
		CStdString						strMess;

		// 1 - Individuo i caratteri che spezzano le righe (e ci metto al loro posto NULL)
		for (nI = 0; nI < nBufLen; nI++)
		{
			if ((nI < nBufLen - 1) && (pBuf[nI] == 13) && (pBuf[nI + 1] == 10))	// E' un return ? CR+LF (tipo Windows)
			{
				nBreakType = 1;
				pBuf[nI] = 0;
				pBuf[nI + 1] = 0;
			}
			else if (pBuf[nI + 1] == 10)								// E' un return ? LF (tipo Unix)
			{
				nBreakType = 2;
				pBuf[nI] = 0;
			}
			else if (pBuf[nI] == 13)									// E' un return ? CR (tipo Macintosh)
			{
				nBreakType = 3;
				pBuf[nI] = 0;
			}

			if (nBreakType)									// Aggiungo il break
			{
				if (nBreakCurr >= nBreaksAllocated)
				{
					aBreaks.resize(nBreaksAllocated + 10000);
					pBreaks = aBreaks.data();
					nBreaksAllocated = (int)aBreaks.size();
					ASSERT(nBreakCurr < nBreaksAllocated);
				}
				pBreaks[nBreakCurr].nPos = nI;
				pBreaks[nBreakCurr].nType = nBreakType;
				nBreakType = 0;
				nBreakCurr++;
			}
		}

		// 2 - Spezzo le varie stringhe 
		nCurr = 0;
		aRows.resize(nBreakCurr);
		for (nI = 0; nI < nBreakCurr; nI++)
		{
			nLen = pBreaks[nI].nPos - nCurr;			// Lunghezza della stringa
			if ((pBuf + nCurr + nLen)[0] == 0)			// So dove deve stare il terminatore
			{
				CUV_UtilString::Convert_charVet2CString(pBuf + nCurr, strMess, nLen + 2);
				aRows[nI] = strMess;

				// Incremento per passare al prossimo pezzo
				nCurr = pBreaks[nI].nPos;
				if (pBreaks[nI].nType == 1)
					nCurr += 2;
				else if ((pBreaks[nI].nType == 2) || (pBreaks[nI].nType == 3))
					nCurr += 1;
				else
					ASSERT(FALSE);
			}
			else
			{
				aRows.resize(nI);
				ASSERT(FALSE);
				return false;
			}
		}

		return true;
	}



}
