#pragma once

//#include "EM2D_UtilString.h"
//#include "UtilVARIE_Export.h"
//#include "EliMath2D_Export.h"

#include "inclusioni_UV.h"

#include "UV_UtilString.h"

namespace UV
{
	class CUV_XMLTag;

//#include "Dlg_Progresso.h"


#define vect_PCUV_XMLTag		std::vector<CUV_XMLTag*>	///< vettore di puntatori a TAG.
#define CArrayPMR_XMLTag		vect_PCUV_XMLTag

	/** Tag XML con attributi(nome e valore) e TAG figli.
	*
	*/
	class /*UTILVARIELIB_API*/ CUV_XMLTag
	{
		// Metodi.
	public:
		CUV_XMLTag(void);
		~CUV_XMLTag(void);

		// Lettura/Scrittura su file
		bool				LeggiDaFile(CStdString strFileName /*,UV_MFC::CDlg_Progresso *pDlg=NULL*/);			///< Legge da file
		bool				ScriviSuFile(CStdString strFileName /*, UV_MFC::CDlg_Progresso *pDlg=NULL*/) const;	///< Scrive su file

							// Conversione
		static void			Convert_Righe_2_Tag(const CStdStringArray &aRighe, CUV_XMLTag *pTagPadre /*,UV_MFC::CDlg_Progresso *pDlg=NULL*/);			///< Dalle righe del file teste ottengo i TAG XML.
		static void			Convert_Tag_2_Righe(const CUV_XMLTag *pTagPadre, CStdStringArray &aRighe, int nTab = 0 /*,UV_MFC::CDlg_Progresso *pDlg=NULL*/);	///< Converto il Tag in righe per scrivere sul file
		static INT_PTR		ConvertHexStr2int(CStdString strVal);						///< Converte da stringa esadecimale a short.
		int					MakeString_FileCompatible(void);							///< Faccio si che tutti i caratteri siano compatibili in scrittura/lettura su file
		int					MakeString_FileUnCompatible(void);						///< Ritorno alle stringe originali
		static int			MakeString_FileCompatible(CStdString &strMess);				///< Faccio si che tutti i caratteri siano compatibili in scrittura/lettura su file
		static int			MakeString_FileUnCompatible(CStdString &strMess);			///< Ritorno alle stringe originali

							// Attributi
		void				Attr_Set(CStdString strAttrName, CStdString strVal);			///< Aggiungo l'attributo alla lista.
		void				Attr_Set(CStdString strAttrName, bool bVal);					///< Aggiungo un attributo di tipo bool
		void				Attr_Set(CStdString strAttrName, int nVal, const CStdStringArray *pAVal = NULL);					///< Aggiungo un attributo di tipo int
		void				Attr_Set(CStdString strAttrName, LONG nVal);					///< Aggiungo un attributo di tipo LONG
		void				Attr_Set(CStdString strAttrName, double dVal);				///< Aggiungo un attributo di tipo double
		void				Attr_Set(CStdString strAttrName, const CArrayDouble &aVal);	///< Aggiungo un attributo di tipo array-double
		void				Attr_Set(CStdString strAttrName, const CArrayInt &aVal);		///< Aggiungo un attributo di tipo array-int
		void				Attr_Set(CStdString strAttrName, const CArrayDWORD &aVal);	///< Aggiungo un attributo di tipo array-dword
		void				Attr_Set(CStdString strAttrName, COLORREF colVal);			///< Aggiungo un attributo di tipo colore
		void				Attr_Set(CStdString strAttrName, RECT rect);					///< Aggiungo un attributo di tipo rettangolo
		void				Attr_Set(CStdString strAttrName, double dX, double dY);		///< Aggiungo un attributo di tipo CPoint2D
		void				Attr_Set_DWORD(CStdString strAttrName, DWORD nVal);			///< Aggiungo un attributo di tipo DWORD
		void				Attr_Set_INT_PTR(CStdString strAttrName, INT_PTR nVal);		///< Aggiungo un attributo di tipo INT_PTR
		void				Attr_Set_UINT(CStdString strAttrName, UINT nVal);				///< Aggiungo un attributo di tipo UINT

		CStdString			*Attr_Get(CStdString strAttrName);							///< Torna il valore dell'attributo.
		bool				Attr_Get(CStdString strAttrName, CStdString &strVal) const;		///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get(CStdString strAttrName, bool &bVal) const;			///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get(CStdString strAttrName, int &nVal, const CStdStringArray *pAVal = NULL) const;			///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get(CStdString strAttrName, LONG &nVal) const;			///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get(CStdString strAttrName, double &dVal) const;		///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get(CStdString strAttrName, CArrayDouble &aVal) const;	///< Torna il valore di tipo array-double
		bool				Attr_Get(CStdString strAttrName, CArrayInt &aVal) const;		///< Torna il valore di tipo array-int
		bool				Attr_Get(CStdString strAttrName, CArrayDWORD &aVal) const;	///< Torna il valore di tipo array-dword
		bool				Attr_Get(CStdString strAttrName, COLORREF &colVal) const;	///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get(CStdString strAttrName, RECT &rect) const;			///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get(CStdString strAttrName, double &dX, double &dY) const;	///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get_DWORD(CStdString strAttrName, DWORD &nVal) const;	///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get_INT_PTR(CStdString strAttrName, INT_PTR &nVal) const;///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!
		bool				Attr_Get_UINT(CStdString strAttrName, UINT &nVal) const;		///< Torna il valore dell'attributo.torna true se ha trovato l'attributo!

							// Figli
		void				Figli_FreeMem(void);																	///< Vuoto la lista dei TAG figli.
		CUV_XMLTag			*Figli_Get(CStdString strName, bool bSearchDepth = true, bool bCaseSensitive = true) const;	///< Torna il puntatore al tag figlio con il nome indicato. Cerco in profondita'?. NULL se non si trova.

		void				Figli_SetNameAndValue(CStdString strNomeFiglio, CStdString strValue);						///< Aggiungo un figlio specificando: "strNomeFiglio", l'attributo "VALUE" settato a "strValue".
		bool				Figli_GetNameAndValue(CStdString strNomeFiglio, CStdString &strValue) const;				///< Aggiungo un figlio specificando: "strNomeFiglio", l'attributo "VALUE" settato a "strValue".

		static void			ShowTagsOnTree(CUV_XMLTag *pTag /*, CTreeCtrl *pAlb , HTREEITEM ramoPadre=NULL , BOOL bExpand=TRUE*/);		///< Mostro i ag sull'albero passato.
		static void			FreeTags(CArrayPMR_XMLTag &aTags);													///< Vuoto la lista dei TAG passati.

		static int			StyleString_Split(CStdString *pStr, CArraysUV_Attrib &aAttrib);							///< Lista di attributi.
		static int			StyleString_Split(CStdString *pStr, CArraysUV_Attrib &aAttrib, CStdString strOpen, CStdString strClose);			///< Lista degli attributi specificando stringa di apertura e chiusura.

		static BOOL			StyleString_Get(CStdString *pStr, CStdString strAttrName, CStdString &strAttrVal);			///< Leggo il valore dell'attributo.
		static BOOL			GetPercentageVal(CStdString *pStr, DOUBLE &dVal);										///< Se e' una percentuale la leggo.
		static void			SetTreeNewStyle( /*CTreeCtrl *pAlb , long lStyleMask, BOOL bSetBits*/);						///< Setto lo stile predefinito per l'albero passato.
		static void			SetTreeStyle( /*CTreeCtrl *pAlb*/);														///< Setto lo stile predefinito per l'albero passato.

	protected:
		static void			convert_righe_2_tag_step(const CStdStringArray &aRighe, CUV_XMLTag *pTagPadre, int &nCurrRiga, int &nCurrChar, /*UV_MFC::CDlg_Progresso *pDlg,*/ int &nI);	///< Dalle righe del file teste ottengo i TAG XML.

		// Dati.
	public:
		CStdString			m_strName;			///< Nome del tag.
		CStdString			m_strData;			///< Dati vari del tag.
		CArraysUV_Attrib	m_aAttr;			///< Attributi. (NOME + VALORE)
		CArrayPMR_XMLTag	m_aPTagFigli;		///< Lista di puntatori a TAG figli.
	};




}
