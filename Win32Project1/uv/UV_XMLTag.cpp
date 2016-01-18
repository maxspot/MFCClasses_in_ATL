#include "..\StdAfx.h"

#include "UV_XMLTag.h"
#include "ASCIIManager.h"
//#include "Dlg_ProgressoEM2D.h"

namespace UV
{


	CUV_XMLTag::CUV_XMLTag(void)
	{
	}

	CUV_XMLTag::~CUV_XMLTag(void)
	{
		Figli_FreeMem();
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, CStdString strVal)		///< Aggiungo l'attributo alla lista.
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal = strVal;
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, bool bVal)			///< Aggiungo un attributo di tipo bool
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal = (bVal ? _T("Y") : _T("N"));
		m_aAttr.push_back(newAttr);
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, double &dX, double &dY) const	///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdStringArray		aPez;
		CStdString				strVal;

		if (Attr_Get(strAttrName, strVal))
		{
			CUV_UtilString::SplitStringOnChar(&strVal, _T(","), aPez);

			if (aPez.size() >= 1)
				dX = std::stod(aPez[0]);
			if (aPez.size() >= 2)
				dY = std::stod(aPez[1]);
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, RECT &rect) const			///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdStringArray		aPez;
		CStdString				strVal;
		int					vVal[4] = { 0,0,0,0 };

		if (Attr_Get(strAttrName, strVal))
		{
			CUV_UtilString::SplitStringOnChar(&strVal, _T(","), aPez);

			if (aPez.size() >= 1)
				vVal[0] = std::stoi(aPez[0]);
			if (aPez.size() >= 2)
				vVal[1] = std::stoi(aPez[1]);
			if (aPez.size() >= 3)
				vVal[2] = std::stoi(aPez[2]);
			if (aPez.size() >= 4)
				vVal[3] = std::stoi(aPez[3]);

			rect.left = vVal[0];
			rect.top = vVal[1];
			rect.right = vVal[2];
			rect.bottom = vVal[3];
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, COLORREF &colVal) const	///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdStringArray		aPez;
		CStdString				strVal;
		int					vVal[3] = { 0,0,0 };

		if (Attr_Get(strAttrName, strVal))
		{
			CUV_UtilString::SplitStringOnChar(&strVal, _T(","), aPez);

			if (aPez.size() >= 1)
				vVal[0] = std::stoi(aPez[0]);
			if (aPez.size() >= 2)
				vVal[1] = std::stoi(aPez[1]);
			if (aPez.size() >= 3)
				vVal[2] = std::stoi(aPez[2]);

			colVal = RGB(vVal[0], vVal[1], vVal[2]);
			return true;
		}
		return false;
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, double dX, double dY)	///< Aggiungo un attributo di tipo CPoint2D
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal.Format(_T("%lf,%lf"), dX, dY);
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, RECT rect)		///< Aggiungo un attributo di tipo rettangolo
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal.Format(_T("%d,%d,%d,%d"), rect.left, rect.top, rect.right, rect.bottom);
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, COLORREF colVal)	///< Aggiungo un attributo di tipo colore
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal.Format(_T("%d,%d,%d"), GetRValue(colVal), GetGValue(colVal), GetBValue(colVal));
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, const CArrayDWORD &aVal)			///< Aggiungo un attributo di tipo array-dword
	{
		sUV_Attrib		newAttr;
		int				nI;
		CStdString		strApp;

		newAttr.strName = strAttrName;
		newAttr.strVal = _T("");
		for (nI = 0; nI < aVal.size(); nI++)
		{
			strApp.Format(_T("%d "), aVal[nI]);
			newAttr.strVal += strApp;
		}
		if (!newAttr.strVal.IsEmpty())
			newAttr.strVal.TrimRight(_T(" "));

		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, const CArrayInt &aVal)			///< Aggiungo un attributo di tipo array-int
	{
		sUV_Attrib		newAttr;
		int				nI;
		CStdString		strApp;

		newAttr.strName = strAttrName;
		newAttr.strVal = _T("");
		for (nI = 0; nI < aVal.size(); nI++)
		{
			strApp.Format(_T("%d "), aVal[nI]);
			newAttr.strVal += strApp;
		}
		if (!newAttr.strVal.IsEmpty())
			newAttr.strVal.TrimRight(_T(" "));

		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, const CArrayDouble &aVal)		///< Aggiungo un attributo di tipo array-double
	{
		sUV_Attrib		newAttr;
		int				nI;
		CStdString		strApp;

		newAttr.strName = strAttrName;
		newAttr.strVal = _T("");
		for (nI = 0; nI < aVal.size(); nI++)
		{
			strApp.Format(_T("%lf "), aVal[nI]);
			newAttr.strVal += strApp;
		}
		if (!newAttr.strVal.IsEmpty())
			newAttr.strVal.TrimRight(_T(" "));

		m_aAttr.push_back(newAttr);
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, CArrayDWORD &aVal) const	///< Torna il valore di tipo array-dword
	{
		CStdStringArray		aPez;
		CStdString				strVal;
		int					nI;

		if (Attr_Get(strAttrName, strVal))
		{
			CUV_UtilString::SplitStringOnChar(&strVal, _T(" "), aPez);

			aVal.clear();
			for (nI = 0; nI < aPez.size(); nI++)
				aVal.push_back(std::stoi(aPez[nI]));
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, CArrayInt &aVal) const		///< Torna il valore di tipo array-int
	{
		CStdStringArray		aPez;
		CStdString				strVal;
		int					nI;

		if (Attr_Get(strAttrName, strVal))
		{
			CUV_UtilString::SplitStringOnChar(&strVal, _T(" "), aPez);

			aVal.clear();
			for (nI = 0; nI < aPez.size(); nI++)
				aVal.push_back(std::stoi(aPez[nI]));
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, CArrayDouble &aVal) const		///< Aggiungo un attributo di tipo array-double
	{
		CStdStringArray		aPez;
		CStdString				strVal;
		int					nI;

		if (Attr_Get(strAttrName, strVal))
		{
			CUV_UtilString::SplitStringOnChar(&strVal, _T(" "), aPez);

			aVal.clear();
			for (nI = 0; nI < aPez.size(); nI++)
				aVal.push_back(std::stod(aPez[nI]));
			return true;
		}
		return false;
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, double dVal)		///< Aggiungo un attributo di tipo double
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal.Format(_T("%lf"), dVal);
		CUV_UtilString::CancellaZeriAllaDxDelPunto(newAttr.strVal);
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set_DWORD(CStdString strAttrName, DWORD nVal)		///< Aggiungo un attributo di tipo DWORD
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal.Format(_T("%d"), nVal);
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set_INT_PTR(CStdString strAttrName, INT_PTR nVal)		///< Aggiungo un attributo di tipo INT_PTR
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal.Format(_T("%d"), nVal);
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set_UINT(CStdString strAttrName, UINT nVal)					///< Aggiungo un attributo di tipo UINT
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal.Format(_T("%d"), nVal);
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, int nVal, const CStdStringArray *pAVal)			///< Aggiungo un attributo di tipo int
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		if (pAVal && (0 <= nVal) && (nVal < pAVal->size()))
			newAttr.strVal = pAVal->at(nVal);
		else
			newAttr.strVal.Format(_T("%d"), nVal);
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Attr_Set(CStdString strAttrName, LONG nVal)			///< Aggiungo un attributo di tipo int
	{
		sUV_Attrib		newAttr;

		newAttr.strName = strAttrName;
		newAttr.strVal.Format(_T("%d"), nVal);
		m_aAttr.push_back(newAttr);
	}

	void CUV_XMLTag::Figli_FreeMem(void)		///< Vuoto la lista dei TAG figli.
	{
		FreeTags(m_aPTagFigli);
	}

	void CUV_XMLTag::FreeTags(CArrayPMR_XMLTag &aTags)		///< Vuoto la lista dei TAG passati.
	{
		INT_PTR			nI;

		for (nI = 0; nI < aTags.size(); nI++)
		{
			delete aTags[nI];
		}
		aTags.clear();
	}

	void CUV_XMLTag::ShowTagsOnTree(CUV_XMLTag *pTag /*, CTreeCtrl *pAlb , HTREEITEM ramoPadre , BOOL bExpand*/)	///< Mostro i tag sull'albero passato.
	{
		/*
		CStdString			strMess;
		HTREEITEM		itemInserito;
		INT_PTR			nI;

		if (!ramoPadre)
		{
			ramoPadre = pAlb->GetRootItem();
		}
		SetTreeStyle( pAlb );
		//ASSERT( pTag->m_aAttrName.size()==pTag->m_aAttrVal.size() );
		strMess.Format(_T("NOME: <%s> DATA: <%s> ATTRIB:%d FIGLI: %d") , pTag->m_strName , pTag->m_strData , pTag->m_aAttr.size() , pTag->m_aPTagFigli.size() );
		itemInserito = pAlb->InsertItem( strMess , ramoPadre );

		// attributi.
		for (nI=0;nI<pTag->m_aAttr.size();nI++)
		{
			strMess.Format( _T("ATTR: <%s> VAL: <%s>") , pTag->m_aAttr[nI].strName , pTag->m_aAttr[nI].strVal );
			pAlb->InsertItem( strMess , itemInserito );
		}

		// figli.
		for (nI=0;nI<pTag->m_aPTagFigli.size();nI++)
		{
			ShowTagsOnTree( pTag->m_aPTagFigli[nI] , pAlb , itemInserito );
		}
		pAlb->Expand( itemInserito , (bExpand?TVE_EXPAND:TVE_COLLAPSE) );
		*/
	}

	void CUV_XMLTag::SetTreeNewStyle( /*CTreeCtrl *pAlb , long lStyleMask, BOOL bSetBits*/)
	{
		/*
		long        lStyleOld;

		lStyleOld = GetWindowLong( pAlb->m_hWnd, GWL_STYLE);
		lStyleOld &= ~lStyleMask;
		if (bSetBits)
			lStyleOld |= lStyleMask;

		SetWindowLong(pAlb->m_hWnd, GWL_STYLE, lStyleOld);
		pAlb->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		*/
	}

	void CUV_XMLTag::SetTreeStyle( /*CTreeCtrl *pAlb*/)
	{
		/*
		// setTreeNewStyle( pAlb , TVS_CHECKBOXES, TRUE );
		SetTreeNewStyle( pAlb , TVS_HASLINES, TRUE );
		SetTreeNewStyle( pAlb , TVS_DISABLEDRAGDROP , FALSE );
		SetTreeNewStyle( pAlb , TVS_HASBUTTONS , TRUE );
		*/
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, double &dVal) const		///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdString				strVal;

		if (Attr_Get(strAttrName, strVal))
		{
			dVal = std::stod(strVal);
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get_INT_PTR(CStdString strAttrName, INT_PTR &nVal) const		///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdString				strVal;

		if (Attr_Get(strAttrName, strVal))
		{
			nVal = std::stoi(strVal);
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get_DWORD(CStdString strAttrName, DWORD &nVal) const			///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdString				strVal;

		if (Attr_Get(strAttrName, strVal))
		{
			nVal = std::stoi(strVal);
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, LONG &nVal) const			///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdString				strVal;

		if (Attr_Get(strAttrName, strVal))
		{
			nVal = std::stoi(strVal);
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get_UINT(CStdString strAttrName, UINT &nVal) const		///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdString				strVal;

		if (Attr_Get(strAttrName, strVal))
		{
			nVal = std::stoi(strVal);
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, int &nVal, const CStdStringArray *pAVal) const			///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdString				strVal;

		if (Attr_Get(strAttrName, strVal))
		{
			// Provo a leggere dalle stringhe
			if (pAVal)
			{
				for (int nI = 0; nI < (int)pAVal->size(); nI++)
				{
					if (!strVal.CompareNoCase(pAVal->at(nI)))
					{
						nVal = nI;
						return true;
					}
				}
			}

			nVal = std::stoi(strVal);
			return true;
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, bool &bVal) const		///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
	{
		CStdString				strVal;

		if (Attr_Get(strAttrName, strVal))
		{
			if (strVal.CompareNoCase(_T("Y")) == 0)
			{
				bVal = true;
				return true;
			}
			else if (strVal.CompareNoCase(_T("N")) == 0)
			{
				bVal = false;
				return true;
			}
		}
		return false;
	}

	bool CUV_XMLTag::Attr_Get(CStdString strAttrName, CStdString &strVal) const		///< Torna il valore dell'attributo.
	{
		INT_PTR			nI;

		for (nI = 0; nI < m_aAttr.size(); nI++)
		{
			if (m_aAttr[nI].strName.CompareNoCase(strAttrName) == 0)
			{
				strVal = m_aAttr[nI].strVal;
				return true;
			}
		}

		return false;
	}

	BOOL CUV_XMLTag::StyleString_Get(CStdString *pStr, CStdString strAttrName, CStdString &strAttrVal)
	{
		CArraysUV_Attrib		aAttr;
		StyleString_Split(pStr, aAttr, _T("("), _T(")"));
		return CUV_UtilString::GetAttrib(strAttrName, strAttrVal, aAttr);
	}

	int CUV_XMLTag::StyleString_Split(CStdString *pStr, CArraysUV_Attrib &aAttrib, CStdString strOpen, CStdString strClose)		///< Lista degli attributi specificando stringa di apertura e chiusura.
	{
		CStdStringArray			aSpez;
		int						nAttrib = 0;
		sUV_Attrib			newAttr;

		aAttrib.clear();
		if (pStr)
		{
			CUV_UtilString::SplitStringOnChar_OC(*pStr, aSpez, _T(": ;"), strOpen, strClose);
			while (aSpez.size() >= 2)
			{
				newAttr.strName = aSpez[0];
				newAttr.strVal = aSpez[1];
				aAttrib.push_back(newAttr);

				aSpez.erase(aSpez.begin(), aSpez.begin() + 2);
				//aSpez.RemoveAt( 0 , 2 );

				nAttrib++;
			}
		}
		return nAttrib;
	}

	int CUV_XMLTag::StyleString_Split(CStdString *pStr, CArraysUV_Attrib &aAttrib)	///< Lista di attributi.
	{
		CStdStringArray		aSpez;
		int					nAttrib = 0;
		sUV_Attrib			newAttr;

		aAttrib.clear();
		if (pStr)
		{
			CUV_UtilString::SplitStringOnChar(pStr, _T(": ;"), aSpez);
			while (aSpez.size() >= 2)
			{
				newAttr.strName = aSpez[0];
				newAttr.strVal = aSpez[1];
				aAttrib.push_back(newAttr);

				aSpez.erase(aSpez.begin(), aSpez.begin() + 2);
				//aSpez.RemoveAt( 0 , 2 );

				nAttrib++;
			}
		}
		return nAttrib;
	}

	BOOL CUV_XMLTag::GetPercentageVal(CStdString *pStr, DOUBLE &dVal)	///< Se è una percentuale la leggo.
	{
		BOOL			bRes = FALSE;
		CStdString			strVal;
		int				nFind;

		if (pStr)
		{
			nFind = pStr->Find(_T('%'));
			if (nFind >= 0)
			{
				strVal = *pStr;
				strVal.Remove(_T('%'));
				dVal = std::stod(strVal);
				bRes = TRUE;
			}
		}
		return bRes;
	}

	int CUV_XMLTag::MakeString_FileUnCompatible(CStdString &strMess)			///< Ritorno alle stringe originali
	{
		int				nChange = 0;

		nChange += strMess.Replace(_T("\\\""), _T("\""));					// sostituisco _\"_ -> _"_
		nChange += strMess.Replace(_T("\\'"), _T("'"));					// sostituisco _\'_ -> _'_

		return nChange;
	}

	int CUV_XMLTag::MakeString_FileCompatible(CStdString &strMess)			///< Faccio si che tutti i caratteri siano compatibili in scrittura/lettura su file
	{
		int				nChange = 0;

		nChange += strMess.Replace(_T("\""), _T("\\\""));					// sostituisco _"_ -> _\"_
		nChange += strMess.Replace(_T("'"), _T("\\'"));					// sostituisco _'_ -> _\'_

		return nChange;
	}

	int CUV_XMLTag::MakeString_FileUnCompatible(void)					///< Ritorno alle stringe originali
	{
		int				nI, nChange = 0;

		nChange += MakeString_FileUnCompatible(m_strName);

		// Figli
		for (nI = 0; nI < m_aPTagFigli.size(); nI++)
			nChange += m_aPTagFigli[nI]->MakeString_FileUnCompatible();

		// Attributi
		for (nI = 0; nI < m_aAttr.size(); nI++)
		{
			nChange += MakeString_FileUnCompatible(m_aAttr[nI].strName);
			nChange += MakeString_FileUnCompatible(m_aAttr[nI].strVal);
		}

		return nChange;
	}

	int CUV_XMLTag::MakeString_FileCompatible(void)				///< Faccio si che tutti i caratteri siano compatibili in scrittura/lettura su file
	{
		int				nI, nChange = 0;

		nChange += MakeString_FileCompatible(m_strName);

		// Figli
		for (nI = 0; nI < m_aPTagFigli.size(); nI++)
			nChange += m_aPTagFigli[nI]->MakeString_FileCompatible();

		// Attributi
		for (nI = 0; nI < m_aAttr.size(); nI++)
		{
			nChange += MakeString_FileCompatible(m_aAttr[nI].strName);
			nChange += MakeString_FileCompatible(m_aAttr[nI].strVal);
		}

		return nChange;
	}

	bool CUV_XMLTag::LeggiDaFile(CStdString strFileName /*,UV_MFC::CDlg_Progresso *pDlg*/)			///< Legge da file
	{
		CASCIIManager			AscMan;
		double					dPerc0=0;
		double					dPerc1=0;
		double					dPerc2=0;

		//if (pDlg)
		//{
		//	dPerc0 = pDlg->m_dPercMin;
		//	dPerc1 = pDlg->m_dPercMin + 0.3*(pDlg->m_dPercMax-pDlg->m_dPercMin);
		//	dPerc2 = pDlg->m_dPercMax;
		//	pDlg->m_dPercMin = dPerc0;
		//	pDlg->m_dPercMax = dPerc1;
		//}

		if (AscMan.ReadFile(strFileName /*,pDlg*/))
		{
			//if (pDlg)
			//{
			//	pDlg->m_nFaseCurr++;
			//	pDlg->m_dPercMin = dPerc1;
			//	pDlg->m_dPercMax = dPerc2;
			//}
			Figli_FreeMem();
			Convert_Righe_2_Tag( AscMan.m_aRighe, this/*, pDlg*/ );
			MakeString_FileUnCompatible();
			//if (pDlg)
			//{
			//	pDlg->m_dPercMin = dPerc0;
			//	pDlg->m_dPercMax = dPerc2;
			//}
			return true;
		}
		//if (pDlg)
		//{
		//	pDlg->m_dPercMin = dPerc0;
		//	pDlg->m_dPercMax = dPerc2;
		//}
		return false;
	}

	bool CUV_XMLTag::ScriviSuFile(CStdString strFileName /*,UV_MFC::CDlg_Progresso *pDlg*/) const	///< Scrive su file
	{
		CASCIIManager			AscMan;
		double					dPerc0 = 0;
		double					dPerc1 = 0;
		double					dPerc2 = 0;
		bool					bRes=false;

		//if (pDlg)
		//{
		//	dPerc0 = pDlg->m_dPercMin;
		//	dPerc1 = pDlg->m_dPercMin + 0.5*(pDlg->m_dPercMax-pDlg->m_dPercMin);
		//	dPerc2 = pDlg->m_dPercMax;
		//	pDlg->m_dPercMin = dPerc0;
		//	pDlg->m_dPercMax = dPerc1;
		//}

		Convert_Tag_2_Righe( this, AscMan.m_aRighe );

		//if (pDlg)
		//{
		//	pDlg->m_dPercMin = dPerc1;
		//	pDlg->m_dPercMax = dPerc2;
		//}
		if (AscMan.WriteFile(strFileName))
			bRes = true;

		//if (pDlg)
		//{
		//	pDlg->m_dPercMin = dPerc0;
		//	pDlg->m_dPercMax = dPerc2;
		//}
		return bRes;
	}

	void CUV_XMLTag::Convert_Righe_2_Tag(const CStdStringArray &aRighe, CUV_XMLTag *pTagPadre /*,UV_MFC::CDlg_Progresso *pDlg*/)		///< Dalle righe del file teste ottengo i TAG XML.
	{
		int					nCurrRiga = 0;
		int					nCurrChar = 0;
		int					nI = 0;

		convert_righe_2_tag_step(aRighe, pTagPadre, nCurrRiga, nCurrChar, /*pDlg,*/ nI);
	}

	void CUV_XMLTag::convert_righe_2_tag_step(const CStdStringArray &aRighe, CUV_XMLTag *pTagPadre, int &nCurrRiga, int &nCurrChar /*,UV_MFC::CDlg_Progresso *pDlg*/, int &nI)
	{
#define STATO_ATTESA_INIZIO_TAG		0		// aspetto il prossimo tag.
#define STATO_ATTESA_NOME_TAG		1		// sto scorrendo il nome del tag.
#define STATO_ATTESA_NOME_ATTR		2		// sto scorrendo il nome dell'attributo.
#define STATO_ATTESA_VAL_ATTR		3		// sto scorrendo il valore del tag.
#define STATO_ATTESA_FINE_COMMENTO	4		// sto scorrendo un commento.

		TCHAR				cCurrChar = 0;
		TCHAR				cPrevChar = 0;
		BOOL				bFineRighe = FALSE;
		BOOL				bTagSenzaFigli = FALSE;
		BOOL				bInizioAttesaValoreAttr;
		TCHAR				cSepValore = 0;					// separatore del valore. __"__ oppure __'__
		int					nStato = STATO_ATTESA_INIZIO_TAG;
		CUV_XMLTag			*pNewTag = NULL;
		CStdString			strAttrVal = _T(""), strAttrName;
		BOOL				bCommentScript = FALSE;
		CStdString			*pSrtApp;
		double				dPerc1, dPerc2;
		CStdString			strApp;

		CUV_XMLTag::FreeTags(pTagPadre->m_aPTagFigli);
		const CStdString		*pStr = aRighe.data();
		pTagPadre->m_strData = _T("");

		if (!pStr)
		{
			return;
		}
		while (!bFineRighe)
		{
			nI++;
			//if ( pDlg && nI>10000 )
			//{
			//	dPerc1 = nCurrRiga/(double)aRighe.size();
			//	dPerc2 = pDlg->m_dPercMin + dPerc1*(pDlg->m_dPercMax-pDlg->m_dPercMin);
			//	pDlg->SetPos( dPerc2 );
			//	strApp.Format(_T("[%d/%d] Interpreting XML objects (%.1lf%%)"), pDlg->m_nFaseCurr, pDlg->m_nFaseTot, dPerc1*100 );
			//	pDlg->SetFase( strApp );
			//	nI=0;
			//	//if (!pDlg->m_bContinua)
			//	//	return;
			//}
			cPrevChar = cCurrChar;
			cCurrChar = pStr[nCurrRiga][nCurrChar];

			switch (nStato)
			{
			case STATO_ATTESA_FINE_COMMENTO:
				if (cCurrChar == '>')
				{
					if ((!bCommentScript) ||
						((bCommentScript) && (cPrevChar == ']')))
					{
						pTagPadre->m_aPTagFigli.push_back(pNewTag);
						pNewTag = NULL;
						nStato = STATO_ATTESA_INIZIO_TAG;
						bTagSenzaFigli = FALSE;
					}
				}
				else
				{
					pNewTag->m_strName += cCurrChar;
				}
				break;
			case STATO_ATTESA_INIZIO_TAG:
				if (cCurrChar == '<')
				{						// Inizia un nuovo tag.
					nStato = STATO_ATTESA_NOME_TAG;
					pNewTag = new CUV_XMLTag;
				}
				else if (cCurrChar == '>')
				{
				}
				else
				{
					//pTagPadre->m_strData.AppendChar( cCurrChar );
					pTagPadre->m_strData += cCurrChar;
				}
				break;
			case STATO_ATTESA_NOME_TAG:
				if ((cCurrChar == '!') && (pNewTag->m_strName.IsEmpty()))
				{	// Inizia un commento.
					nStato = STATO_ATTESA_FINE_COMMENTO;
					bCommentScript = FALSE;
					if (pTagPadre->m_strName.CompareNoCase(_T("script")) == 0)
					{			// Script.
						pSrtApp = NULL;
						if (pTagPadre->Attr_Get(_T("type"), *pSrtApp))
						{
							ASSERT(pSrtApp);
							if (pSrtApp->CompareNoCase(_T("text/ecmascript")) == 0)
							{
								bCommentScript = TRUE;
							}
						}
					}
				}
				else if (((cCurrChar == ' ') || (cCurrChar == 9)) && (!pNewTag->m_strName.IsEmpty()))
				{					// il nome del tag è finito.
					nStato = STATO_ATTESA_NOME_ATTR;
				}
				else if (cCurrChar == '>')
				{
					if (pNewTag->m_strName[0] == '/')
					{
						CStdString		strApp = pNewTag->m_strName.Right(pNewTag->m_strName.GetLength() - 1);
						ASSERT(strApp.CompareNoCase(pTagPadre->m_strName) == 0);
						// Non è un nuovo TAG, devo terminare.
						delete pNewTag;
						pNewTag = NULL;
						return;		// Non posso scorrere, senno' mi perdo qualcosa!!!
					}
					else					// Il tag HA FIGLI, termina subito dopo il nome.
					{
						if (pNewTag->m_strName.Find('?') >= 0)
						{
							bTagSenzaFigli = TRUE;
						}
						// fine del tag attuale CON o SENZA FIGLI.
						if (!bTagSenzaFigli)
						{
							convert_righe_2_tag_step(aRighe, pNewTag, nCurrRiga, nCurrChar, /*pDlg,*/ nI);
						}
						pTagPadre->m_aPTagFigli.push_back(pNewTag);
						pNewTag = NULL;
						nStato = STATO_ATTESA_INIZIO_TAG;
						bTagSenzaFigli = FALSE;
					}
				}
				else if (!pNewTag->m_strName.IsEmpty() && cCurrChar == '/')			// il tag finisce subito.
				{
					pTagPadre->m_aPTagFigli.push_back(pNewTag);
					pNewTag = NULL;
					nStato = STATO_ATTESA_INIZIO_TAG;
					bTagSenzaFigli = FALSE;
				}
				else
				{		// il nome del tag continua.
					pNewTag->m_strName += cCurrChar;
				}
				break;
			case STATO_ATTESA_NOME_ATTR:
				if (cCurrChar == '?')
				{
				}
				else if ((cCurrChar == ' ') || (cCurrChar == 9) || (cCurrChar == 0))
				{
					if (!strAttrName.IsEmpty())
					{
						nStato = STATO_ATTESA_VAL_ATTR;
					}
				}
				else if (cCurrChar == '=')
				{
					nStato = STATO_ATTESA_VAL_ATTR;
					bInizioAttesaValoreAttr = TRUE;		// mi posso aspettare __(nulla), _'_ oppure _"_
				}
				else if (cCurrChar == '/')
				{
					bTagSenzaFigli = TRUE;
				}
				else if (cCurrChar == '>')
				{
					if (pNewTag->m_strName[0] == '/')		// fine del TAG's.
					{
						CStdString		strApp = pNewTag->m_strName.Right(pNewTag->m_strName.GetLength() - 1);
						ASSERT(strApp.CompareNoCase(pTagPadre->m_strName) == 0);
						// Non è un nuovo TAG, devo terminare.
						delete pNewTag;
						pNewTag = NULL;
						return;				// Non posso scorrere, senno' mi perdo qualcosa!!!
					}

					if (pNewTag->m_strName.Find('?') >= 0)
					{
						bTagSenzaFigli = TRUE;
					}
					// fine del tag attuale CON o SENZA FIGLI.
					if (!bTagSenzaFigli)
					{
						convert_righe_2_tag_step(aRighe, pNewTag, nCurrRiga, nCurrChar, /*pDlg,*/ nI);
					}
					pTagPadre->m_aPTagFigli.push_back(pNewTag);
					pNewTag = NULL;
					nStato = STATO_ATTESA_INIZIO_TAG;
					bTagSenzaFigli = FALSE;
				}
				else
				{
					strAttrName += cCurrChar;
				}
				break;
			case STATO_ATTESA_VAL_ATTR:
				if (((cCurrChar == '"') || (cCurrChar == '\'')) && cPrevChar != '\\')
				{
					if (!strAttrVal.IsEmpty() || ((cCurrChar == '"') && strAttrVal.IsEmpty() && (cPrevChar == '"')))
					{
						if (cSepValore && cCurrChar != cSepValore)	// inserisco il carattere e passo oltre, per evitare errori tipo "ciao 'cane' pippo".
						{
							strAttrVal += cCurrChar;
							break;
						}
						nStato = STATO_ATTESA_NOME_ATTR;			// passo al prossimo attributo.
						pNewTag->Attr_Set(strAttrName, strAttrVal);
						strAttrName = _T("");
						strAttrVal = _T("");
					}
					if (!cSepValore)
						cSepValore = cCurrChar;
				}
				else
				{
					strAttrVal += cCurrChar;
				}
				break;
			}




			////////////////////////////////////////////////////////////////////////////////////////
			// Prossimo carattere.
			////////////////////////////////////////////////////////////////////////////////////////
			if (nCurrChar < aRighe[nCurrRiga].length() - 1)		// posso andare ancora avanti.
			{
				nCurrChar++;
			}
			else if (nCurrChar >= aRighe[nCurrRiga].length() - 1)	// sono all'ultimo carattere, passo alla riga successiva.
			{
				if (nCurrRiga < aRighe.size() - 1)				// c'è ancora una ruga.
				{
					nCurrRiga++;
					nCurrChar = 0;
				}
				else
				{
					bFineRighe = TRUE;
				}
			}
		}
	}

	INT_PTR CUV_XMLTag::ConvertHexStr2int(CStdString strVal)	///< Converte da stringa esadecimale a short.
	{
		INT_PTR			nValLoc, nVal = 0;
		INT_PTR			nMolt = 1;
		int				nI;
		TCHAR			cBuf;

		strVal.MakeUpper();
		for (nI = strVal.GetLength() - 1; nI >= 0; nI--)
		{
			cBuf = strVal[nI];
			nValLoc = 0;
			if ((cBuf >= '0') && (cBuf <= '9'))
			{
				nValLoc = cBuf - '0';
				nVal += nValLoc * nMolt;
				nMolt *= 16;
			}
			else if ((cBuf >= 'A') && (cBuf <= 'F'))
			{
				nValLoc = 10 + cBuf - 'A';
				nVal += nValLoc * nMolt;
				nMolt *= 16;
			}
		}
		return nVal;
	}

	void CUV_XMLTag::Convert_Tag_2_Righe(const CUV_XMLTag *pTagPadre, CStdStringArray &aRighe, int nTab /*,UV_MFC::CDlg_Progresso *pDlg*/)		///< Converto il Tag in righe per scrivere sul file
	{
		const sUV_Attrib			*pAttr = NULL;
		CStdString					NewRiga;
		CStdString					strAppComp1, strAppComp2;
		int							nI;
		CStdString					strApp;

		// Inizio (e attributi)
		NewRiga = _T("");
		for (nI = 0; nI < nTab; nI++)
			NewRiga += _T("\t");
		strAppComp1 = pTagPadre->m_strName;
		ASSERT(!pTagPadre->m_strName.IsEmpty());				// Devo avere un nome per il tag!!!
		CUV_XMLTag::MakeString_FileCompatible(strAppComp1);
		strApp.Format(_T("<%s"), strAppComp1);
		NewRiga += strApp;			// Inizio

		for (nI = 0; nI < pTagPadre->m_aAttr.size(); nI++)
		{
			pAttr = &(pTagPadre->m_aAttr[nI]);
			strAppComp1 = pAttr->strName;
			strAppComp2 = pAttr->strVal;
			CUV_XMLTag::MakeString_FileCompatible(strAppComp1);
			CUV_XMLTag::MakeString_FileCompatible(strAppComp2);
			strApp.Format(_T(" %s=\"%s\""), strAppComp1, strAppComp2);
			NewRiga += strApp;
		}
		if (pTagPadre->m_aPTagFigli.size())						// Passo alla nuova riga solo se ho dei figli
		{
			NewRiga += _T(">");
			aRighe.push_back(NewRiga);
		}
		else
		{
			NewRiga += _T("/>");
			aRighe.push_back(NewRiga);
			return;								// finisco la riga cosi'
		}

		// Figli
		for (nI = 0; nI < pTagPadre->m_aPTagFigli.size(); nI++)
			Convert_Tag_2_Righe(pTagPadre->m_aPTagFigli[nI], aRighe, nTab + 1);

		// Fine
		NewRiga = _T("");
		for (nI = 0; nI < nTab; nI++)
			NewRiga += _T("\t");
		strAppComp1 = pTagPadre->m_strName;
		CUV_XMLTag::MakeString_FileCompatible(strAppComp1);
		strApp.Format(_T("</%s>"), strAppComp1);
		NewRiga += strApp;		// Fine
		aRighe.push_back(NewRiga);
	}

	CUV_XMLTag *CUV_XMLTag::Figli_Get(CStdString strName, bool bSearchDepth, bool bCaseSensitive) const		///< Torna il puntatore al tag figlio con il nome indicato. Cerco in profondita'?. NULL se non si trova.
	{
		int						nI;
		CUV_XMLTag				*pFind = NULL;

		for (nI = 0; nI < m_aPTagFigli.size(); nI++)
		{
			// vedo il figlio
			if (bCaseSensitive)
			{
				if (m_aPTagFigli[nI]->m_strName.Compare(strName) == 0)
					return m_aPTagFigli[nI];
			}
			else
			{
				if (m_aPTagFigli[nI]->m_strName.CompareNoCase(strName) == 0)
					return m_aPTagFigli[nI];
			}

			// scorro i nipoti? (se lo trovo esco, sennò continuo)
			if (bSearchDepth)
			{
				pFind = m_aPTagFigli[nI]->Figli_Get(strName, bSearchDepth, bCaseSensitive);
				if (pFind)
					return pFind;
			}
		}
		return NULL;
	}

	CStdString *CUV_XMLTag::Attr_Get(CStdString strAttrName)		///< Torna il valore dell'attributo.
	{
		INT_PTR				nI;

		//ASSERT( m_aAttrName.size()==m_aAttrVal.size() );
		for (nI = 0; nI < m_aAttr.size(); nI++)
		{
			if (m_aAttr[nI].strName.CompareNoCase(strAttrName) == 0)
			{
				return &m_aAttr[nI].strVal;
			}
		}
		return NULL;
	}

	void CUV_XMLTag::Figli_SetNameAndValue(CStdString strNomeFiglio, CStdString strValue)						///< Aggiungo un figlio specificando: "strNomeFiglio", l'attributo "VALUE" settato a "strValue".
	{
		CUV_XMLTag		*pNewTag = new CUV_XMLTag;

		pNewTag->m_strName = strNomeFiglio;
		pNewTag->Attr_Set(_T("VALUE"), strValue);
		m_aPTagFigli.push_back(pNewTag);
	}

	bool CUV_XMLTag::Figli_GetNameAndValue(CStdString strNomeFiglio, CStdString &strValue) const				///< Aggiungo un figlio specificando: "strNomeFiglio", l'attributo "VALUE" settato a "strValue".
	{
		CUV_XMLTag		*pTagFig = Figli_Get(strNomeFiglio);

		if (pTagFig)
			return pTagFig->Attr_Get(_T("VALUE"), strValue);
		return false;
	}



}


