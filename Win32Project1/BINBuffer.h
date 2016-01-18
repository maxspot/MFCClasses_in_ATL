#pragma once

#include "inclusioni.h"

/* Classe per la gestione di BUFFER binari.
*/
class CBINBuffer
{
public:
					CBINBuffer();
					~CBINBuffer();

	bool			Read_FromFile_BIN(std::string strFileName);		// Leggo il file specificato

public:
	vect_char		m_data;								// Dati binari letti dal file
};



