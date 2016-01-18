#pragma once

#include "BINBuffer.h"

/* Manager di file BINARI
*/
class CFileManager_BIN
{
public:
					CFileManager_BIN();
					~CFileManager_BIN();

public:
	bool			Read_BIN(std::string strFileName);		// Leggo il file BINARIO specificato

protected:
	CBINBuffer		m_buf;								// buffer binario letto
protected:
	std::string		m_strFile;							// File attualmente aperto
	bool			m_bFileLoaded;						// File caricato con successo?
};

