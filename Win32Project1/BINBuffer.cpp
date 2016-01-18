#include "stdafx.h"
#include "BINBuffer.h"

using namespace std;

CBINBuffer::CBINBuffer()
{
}


CBINBuffer::~CBINBuffer()
{
}

bool CBINBuffer::Read_FromFile_BIN(std::string strFileName)
{
	std::fstream		file;
	streampos			pos_fine;

	file.open(strFileName, std::ios::binary | std::ios_base::in);
	if (file.is_open())
	{
		file.seekg(0, ios_base::end);			// Mi posiziono alla fine
		pos_fine = file.tellg();
		size_t file_size = pos_fine;			// Leggo la lunghezza del file

		m_data.resize(file_size);				// Alloco i byte necessari
		file.seekg(0, ios_base::beg);			// Mi posiziono all'inizio
		file.read(m_data.data(), file_size);	// Leggo tutto il file
		file.close();
		return true;
	}
	return false;
}
