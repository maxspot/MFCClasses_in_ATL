#pragma once

#include "inclusioni.h"

#define vect_PCXML_Tag		std::vector<CXML_Tag*>

class CXML_Tag
{
public:
							CXML_Tag();
							~CXML_Tag();

	bool					ReadFromFile(std::string strFileName);

	void					Figli_FreeMem(void);		///< Vuoto la lista dei TAG figli.

	CXML_Tag*				Get_Figlio(std::string strName, bool bGoDepth=true, bool bDepthFirst=false );		// Torna il figlio con il nome specificato. Devo cercare anche tra tutta la progenie?

	static void				FreeTags( vect_PCXML_Tag &aTags);													// Vuoto la lista dei TAG passati.

	void					Attr_Set(std::string strAttrName, std::string strVal);	///< Aggiungo l'attributo di tipo string
	void					Attr_Set(std::string strAttrName, bool bVal);			///< Aggiungo l'attributo di tipo bool
	void					Attr_Set(std::string strAttrName, int nVal);			///< Aggiungo l'attributo di tipo int
	void					Attr_Set(std::string strAttrName, double dVal);			///< Aggiungo l'attributo di tipo double

	bool					Attr_Get(std::string strAttrName, std::string &strVal) const;	///< Leggo l'attributo di tipo string
	bool					Attr_Get(std::string strAttrName, bool &bVal) const;			///< Leggo l'attributo di tipo bool
	bool					Attr_Get(std::string strAttrName, int &nVal) const;				///< Leggo l'attributo di tipo int
	bool					Attr_Get(std::string strAttrName, double &dVal) const;			///< Leggo l'attributo di tipo double

	int						MakeString_FileCompatible(void);						///< Faccio si che tutti i caratteri siano compatibili in scrittura/lettura su file
	int						MakeString_FileUnCompatible(void);						///< Ritorno alle stringe originali
	static int				MakeString_FileCompatible(std::string &strMess);		///< Faccio si che tutti i caratteri siano compatibili in scrittura/lettura su file
	static int				MakeString_FileUnCompatible(std::string &strMess);		///< Ritorno alle stringe originali

	static void				Convert_Righe_2_Tag(const vect_string &vRows, CXML_Tag *pTagPadre);			///< Dalle righe del file teste ottengo i TAG XML.

protected:
	static void				convert_righe_2_tag_step(const vect_string &vRows, CXML_Tag *pTagPadre, int &nCurrRiga, int &nCurrChar);	///< Dalle righe del file teste ottengo i TAG XML.

public:
	std::string				m_strName;					// Nome del tag
	std::string				m_strData;					// Dati del tag.
protected:
	vect_PCXML_Tag			m_aTagFigli;				// Figli di questo tag
	vect_sUV_Attrib			m_aAttr;					// Attributi di questo tag
};

