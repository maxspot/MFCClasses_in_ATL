#include "stdafx.h"
#include "XML_Tag.h"

#include "FileManager_ASCII.h"
#include "UV_string.h"

using namespace std;

CXML_Tag::CXML_Tag()
{
}


CXML_Tag::~CXML_Tag()
{
}

bool CXML_Tag::ReadFromFile(std::string strFileName)
{
	CFileManager_ASCII		AscMan;

	if (AscMan.Read_ASCII(strFileName))
	{
		Figli_FreeMem();
		Convert_Righe_2_Tag( AscMan.m_rows, this);
		MakeString_FileUnCompatible();
		return true;
	}
	return false;
}

void CXML_Tag::Figli_FreeMem(void)		///< Vuoto la lista dei TAG figli.
{
	FreeTags(m_aTagFigli);
}

CXML_Tag *CXML_Tag::Get_Figlio(std::string strName, bool bGoDepth, bool bDepthFirst)
{
	vect_PCXML_Tag::iterator	i;
	CXML_Tag					*pOut = nullptr;

	for (i=m_aTagFigli.begin(); i< m_aTagFigli.end(); i++)
	{
		if (!(*i)->m_strName.compare(strName))			// torno il tag corrente.
			return (*i);
		if (bGoDepth && bDepthFirst)
		{
			pOut = (*i)->Get_Figlio(strName, bGoDepth, bDepthFirst);
			if (pOut)
				return pOut;
		}
	}

	if ( bGoDepth && !bDepthFirst )
		for (i = m_aTagFigli.begin(); i < m_aTagFigli.end(); i++)
		{
			pOut = (*i)->Get_Figlio(strName, bGoDepth, bDepthFirst);
			if (pOut)
				return pOut;
		}

	return nullptr;
}

void CXML_Tag::FreeTags(vect_PCXML_Tag &aTags)
{
	unsigned int			nI;

	for (nI = 0; nI<aTags.size(); nI++)
		delete aTags[nI];
	aTags.clear();
}

void CXML_Tag::convert_righe_2_tag_step(const vect_string &vRows, CXML_Tag * pTagPadre, int & nCurrRiga, int & nCurrChar)
{
	enum eStatoParser
	{
		STATO_ATTESA_INIZIO_TAG=0,
		STATO_ATTESA_NOME_TAG,
		STATO_ATTESA_NOME_ATTR,
		STATO_ATTESA_VAL_ATTR,
		STATO_ATTESA_FINE_COMMENTO
	};

	char				cCurrChar = 0;
	char				cPrevChar = 0;
	bool				bFineRighe = false;
	bool				bTagSenzaFigli = false;
	char				cSepValore = 0;					// separatore del valore.
	eStatoParser		nStato = STATO_ATTESA_INIZIO_TAG;
	CXML_Tag			*pNewTag = NULL;
	string				strAttrVal = "", strAttrName;
	bool				bCommentScript = false;
	string				*pSrtApp;
	bool				bTermineValoreAttributo;

	CXML_Tag::FreeTags(pTagPadre->m_aTagFigli);
	const string		*pStr = vRows.data();
	pTagPadre->m_strData = "";

	if (!pStr)
		return;

	while (!bFineRighe)
	{
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
					pTagPadre->m_aTagFigli.push_back(pNewTag);
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
				pNewTag = new CXML_Tag;
			}
			else if (cCurrChar == '>')
			{
			}
			else
			{
				pTagPadre->m_strData.push_back( (wchar_t)cCurrChar );
			}
			break;
		case STATO_ATTESA_NOME_TAG:
			if ((cCurrChar == '!') && (pNewTag->m_strName.empty()))
			{	// Inizia un commento.
				nStato = STATO_ATTESA_FINE_COMMENTO;
				bCommentScript = FALSE;
				//if (pTagPadre->m_strName.CompareNoCase(_T("script")) == 0)
				if (pTagPadre->m_strName.compare("script") == 0)
					{			// Script.
					pSrtApp = NULL;
					if (pTagPadre->Attr_Get("type", *pSrtApp))
					{
						//ASSERT(pSrtApp);
						if (pSrtApp->compare("text/ecmascript") == 0)
						{
							bCommentScript = TRUE;
						}
					}
				}
			}
			else if (((cCurrChar == ' ') || (cCurrChar == 9)) && (!pNewTag->m_strName.empty()))
			{					// il nome del tag è finito.
				nStato = STATO_ATTESA_NOME_ATTR;
			}
			else if (cCurrChar == '>')
			{
				if (pNewTag->m_strName[0] == '/')
				{
					string		strApp(pNewTag->m_strName.begin() + 1, pNewTag->m_strName.end());
					//CStdString		strApp = pNewTag->m_strName.Right(pNewTag->m_strName.length() - 1);
					//ASSERT(strApp.CompareNoCase(pTagPadre->m_strName) == 0);
					// Non è un nuovo TAG, devo terminare.
					delete pNewTag;
					pNewTag = NULL;
					return;				// Non posso scorrere, senno' mi perdo qualcosa!!!
				}
				else					// Il tag HA FIGLI, termina subito dopo il nome.
				{
					if ( pNewTag->m_strName.find('?') != string::npos )
					{
						bTagSenzaFigli = TRUE;
					}
					// fine del tag attuale CON o SENZA FIGLI.
					if (!bTagSenzaFigli)
					{
						convert_righe_2_tag_step(vRows, pNewTag, nCurrRiga, nCurrChar);
					}
					pTagPadre->m_aTagFigli.push_back(pNewTag);
					pNewTag = NULL;
					nStato = STATO_ATTESA_INIZIO_TAG;
					bTagSenzaFigli = FALSE;
				}
			}
			else if (!pNewTag->m_strName.empty() && cCurrChar == '/')			// il tag finisce subito.
			{
				pTagPadre->m_aTagFigli.push_back(pNewTag);
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
				if (strAttrName.length())
				{
					nStato = STATO_ATTESA_VAL_ATTR;
				}
			}
			else if (cCurrChar == '=')
			{
				nStato = STATO_ATTESA_VAL_ATTR;
			}
			else if (cCurrChar == '/')
			{
				bTagSenzaFigli = TRUE;
			}
			else if (cCurrChar == '>')
			{
				if (pNewTag->m_strName[0] == '/')		// fine del TAG's.
				{
					string		strApp(pNewTag->m_strName.begin() + 1, pNewTag->m_strName.end());
					//CStdString		strApp = pNewTag->m_strName.Right(pNewTag->m_strName.length() - 1);
					//ASSERT(strApp.compare(pTagPadre->m_strName) == 0);
					// Non è un nuovo TAG, devo terminare.
					delete pNewTag;
					pNewTag = NULL;
					return;				// Non posso scorrere, senno' mi perdo qualcosa!!!
				}

				if (pNewTag->m_strName.find('?') != string::npos )
				{
					bTagSenzaFigli = TRUE;
				}
				// fine del tag attuale CON o SENZA FIGLI.
				if (!bTagSenzaFigli)
				{
					convert_righe_2_tag_step(vRows, pNewTag, nCurrRiga, nCurrChar);
				}
				pTagPadre->m_aTagFigli.push_back(pNewTag);
				pNewTag = NULL;
				nStato = STATO_ATTESA_INIZIO_TAG;
				bTagSenzaFigli = FALSE;
			}
			else
			{
				strAttrName += cCurrChar;
			}
			break;

		case STATO_ATTESA_VAL_ATTR:						// Attesa del valore dell'attributo.
			if (((cCurrChar == '"') || (cCurrChar == '\'')) && cPrevChar != '\\')
			{
				// Decido se il valore dell'attributo e' terminato o meno
				bTermineValoreAttributo = false;
				if (strAttrVal.length())
					bTermineValoreAttributo = true;
				if ((cCurrChar == '"') && strAttrVal.empty() && (cPrevChar == '"'))		// aperte e chiuse virgolette
					bTermineValoreAttributo = true;

				// Se non e' il separatore con il quale ho iniziato ... lo scrivo nel valore e proseguo! (es: FILE = "PIPPO D'APE" )
				if (bTermineValoreAttributo && cSepValore && (cCurrChar != cSepValore))
				{
					strAttrVal += cCurrChar;
					break;
				}

				if (bTermineValoreAttributo)	// FINE!
				{
					nStato = STATO_ATTESA_NOME_ATTR;	// Passo al prossimo attributo.
					pNewTag->Attr_Set(strAttrName, strAttrVal);
					strAttrName = "";
					strAttrVal = "";
					cSepValore = 0;
				}
				else							// INIZIO! (dell'attesa di un valore (mi segno il carattere separatore))
				{
					cSepValore = cCurrChar;
				}
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
		if (nCurrChar<vRows[nCurrRiga].length() - 1)		// posso andare ancora avanti.
		{
			nCurrChar++;
		}
		else if (nCurrChar >= vRows[nCurrRiga].length() - 1)	// sono all'ultimo carattere, passo alla riga successiva.
		{
			if (nCurrRiga<vRows.size() - 1)				// c'è ancora una ruga.
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

void CXML_Tag::Attr_Set(std::string strAttrName, std::string strVal)	///< Aggiungo l'attributo alla lista.
{
	sUV_Attrib		newAttr;

	newAttr.strName = strAttrName;
	newAttr.strVal = strVal;
	m_aAttr.push_back(newAttr);
}

void CXML_Tag::Attr_Set(std::string strAttrName, bool bVal)			///< Aggiungo un attributo di tipo bool
{
	sUV_Attrib		newAttr;

	newAttr.strName = strAttrName;
	if (bVal)
		newAttr.strVal = "Y";
	else
		newAttr.strVal = "N";
	m_aAttr.push_back(newAttr);
}

void CXML_Tag::Attr_Set(std::string strAttrName, int nVal)			///< Aggiungo un attributo di tipo int
{
	Attr_Set(strAttrName, to_string(nVal));
}

void CXML_Tag::Attr_Set(std::string strAttrName, double dVal)
{
	Attr_Set(strAttrName, to_string(dVal));
}

bool CXML_Tag::Attr_Get(std::string strAttrName, std::string &strVal) const		///< Leggo l'attributo di tipo string
{
	int			nI;

	for (nI = 0; nI<m_aAttr.size(); nI++)
	{
		if (m_aAttr[nI].strName.compare(strAttrName) == 0)
		{
			strVal = m_aAttr[nI].strVal;
			return true;
		}
	}
	return false;
}

bool CXML_Tag::Attr_Get(std::string strAttrName, bool &bVal) const				///< Leggo l'attributo di tipo bool
{
	string				strVal;

	if (Attr_Get(strAttrName, strVal))
	{
		if (strVal.compare("Y") == 0)
		{
			bVal = true;
			return true;
		}
		else if (strVal.compare("N") == 0)
		{
			bVal = false;
			return true;
		}
	}
	return false;
}

bool CXML_Tag::Attr_Get(std::string strAttrName, int &nVal) const				///< Leggo l'attributo di tipo int
{
	string				strVal;

	if (Attr_Get(strAttrName, strVal))
	{
		nVal = std::stoi(strVal);
		return true;
	}
	return false;
}

bool CXML_Tag::Attr_Get(std::string strAttrName, double &dVal) const			///< Leggo l'attributo di tipo double
{
	string				strVal;

	if (Attr_Get(strAttrName, strVal))
	{
		dVal = std::stod(strVal);
		return true;
	}
	return false;
}

int CXML_Tag::MakeString_FileCompatible(void)
{
	int				nI, nChange = 0;

	nChange += MakeString_FileCompatible(m_strName);

	// Figli
	for (nI = 0; nI<m_aTagFigli.size(); nI++)
		nChange += m_aTagFigli[nI]->MakeString_FileCompatible();

	// Attributi
	for (nI = 0; nI<m_aAttr.size(); nI++)
	{
		nChange += MakeString_FileCompatible(m_aAttr[nI].strName);
		nChange += MakeString_FileCompatible(m_aAttr[nI].strVal);
	}

	return nChange;
}

int CXML_Tag::MakeString_FileUnCompatible(void)
{
	int				nI, nChange = 0;

	nChange += MakeString_FileUnCompatible(m_strName);

	// Figli
	for (nI = 0; nI<m_aTagFigli.size(); nI++)
		nChange += m_aTagFigli[nI]->MakeString_FileUnCompatible();

	// Attributi
	for (nI = 0; nI<m_aAttr.size(); nI++)
	{
		nChange += MakeString_FileUnCompatible(m_aAttr[nI].strName);
		nChange += MakeString_FileUnCompatible(m_aAttr[nI].strVal);
	}

	return nChange;

}

void CXML_Tag::Convert_Righe_2_Tag(const vect_string & vRows, CXML_Tag * pTagPadre)
{
	int					nCurrRiga = 0;
	int					nCurrChar = 0;

	convert_righe_2_tag_step(vRows, pTagPadre, nCurrRiga, nCurrChar);
}

int CXML_Tag::MakeString_FileUnCompatible( string &strMess)			///< Ritorno alle stringe originali
{
	int				nChange = 0;

	nChange += CUV_string::ReplaceAll(strMess, std::string("\\\""), std::string("\""));				// sostituisco _\"_ -> _"_
	nChange += CUV_string::ReplaceAll(strMess, std::string("\\'"), std::string("'"));				// sostituisco _\'_ -> _'_
	return nChange;
}

int CXML_Tag::MakeString_FileCompatible( string &strMess)			///< Faccio si che tutti i caratteri siano compatibili in scrittura/lettura su file
{
	int				nChange = 0;

	nChange += CUV_string::ReplaceAll(strMess, std::string("\""), std::string("\\\"") );			// sostituisco _"_ -> _\"_
	nChange += CUV_string::ReplaceAll(strMess, std::string("'"), std::string("\\'"));				// sostituisco _'_ -> _\'_
	return nChange;
}
