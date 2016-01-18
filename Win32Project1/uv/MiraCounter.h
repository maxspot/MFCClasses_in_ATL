#pragma once

//#include "UtilVARIE_Export.h"

class /*UTILVARIELIB_API*/ CMiraCounter  
{
public:
					CMiraCounter();
	virtual			~CMiraCounter();

	void			SetHPTimeOut(long mmsec);		//imposta il timeout in millisecondi
	BOOL			IsHPTimeOut(void);				//controlla se e' trascorso il timeout
	void			SetHPTimeOut(double sec);		//imposta il timeout in secondi

	void			StartHPCrono(void);				//inizializza il cronometro(a partire dall'accensione del computer)
	double			ReadHPCrono(void);				//legge il tempo trascorso da StartHPCrono
	
	double			GetHPCounter(void);				//restituisce il valore corrente del timer
	BOOL			IsHPCounterOk(void);			//controlla se MiraCounter e' disponibile


	LARGE_INTEGER	m_Freq;				//frequenza dell'HIGH PERFORMANCE COUNTER
	LARGE_INTEGER	m_tCrono;			//time iniziale per cronometro, quando ho iniziato il conteggio con "StartHPCrono", potrò leggere con "ReadHPCrono"
	LARGE_INTEGER	m_timeOut;			//timeOut memorizzato(tempo di attesa)
	double			m_dInvFreq;			//inverso della frequenza(o inverso del counter)
	BOOL			m_bCounterOk;		//contatore

	double			m_dSec;				// Variabile per appoggiare i secondi letti.

	BOOL			GetIsRunning() const { return m_bIsRunning; }
	BOOL			SetIsRunning( BOOL const & __newValue ) { m_bIsRunning = __newValue; return TRUE; }

private:
	BOOL			m_bIsRunning;
};
