#include "..\stdafx.h"
#include ".\MiraCounter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMiraCounter::CMiraCounter()
{
   
   m_bCounterOk = QueryPerformanceFrequency(&m_Freq);    //ritorna la frequenza dell'
                                              //HIGH PERFORMANCE COUNTER, se esiste;cioe' mi da' 
                                              //il numero di impulsi per secondo mandati dal calcolatore 
   if( m_bCounterOk )
      m_dInvFreq = 1.0/ (double)m_Freq.QuadPart;         //calcola l'inverso del counter
   
   m_tCrono.QuadPart = 0;
   m_timeOut.QuadPart = 0;
   m_bIsRunning = FALSE;

   return;
}

CMiraCounter::~CMiraCounter()
{
   m_bIsRunning = FALSE;
}

BOOL CMiraCounter::IsHPCounterOk()
/*
      Ritorna true se il counter e' disponibile, false altrimenti.
*/
{
   return m_bCounterOk;
}

double CMiraCounter::GetHPCounter()
/*
   Calcola il counter in secondi e lo restituisce
*/
{
   LARGE_INTEGER        t;
   
   QueryPerformanceCounter(&t);     //in &t restituisce il valore corrente dell'HIGH RESOLUTION PERMORMANCE COUNTER,
                                    //se esiste;
   
   return (double)t.QuadPart*m_dInvFreq;        //lo trasforma in secondi
}

void CMiraCounter::StartHPCrono()
/*
   Inizializza il cronometro.
*/
{
   QueryPerformanceCounter(&m_tCrono);       //memorizza l'istante corrente(in counts)
                                             //a partire dall'accensione del computer.
   m_bIsRunning = TRUE;
   
   return;
}

double CMiraCounter::ReadHPCrono()
/*
  Legge il cronometro. Il risultato e' sempre in secondi.
*/

{
	LARGE_INTEGER     t;
	LARGE_INTEGER     diff;

	QueryPerformanceCounter(&t);
	diff.QuadPart = t.QuadPart - m_tCrono.QuadPart;		// Differenza fra istante corrente calcolato 
														// Dall'H.R.P e quello memorizzato.
														// La differenza e' calcolata in count.
	m_dSec = (double)(diff.QuadPart*m_dInvFreq);		// Lo trasforma in secondi
	return m_dSec;
}

void CMiraCounter::SetHPTimeOut(double sec)
/*
   Imposta il timeout in secondi.
*/
{
   LARGE_INTEGER     t,d;

   d.QuadPart = (LONGLONG)(sec*(double)m_Freq.QuadPart); //delta
   QueryPerformanceCounter(&t);                       //istante corrente
   m_timeOut.QuadPart = t.QuadPart+d.QuadPart;        //attimo del timeout

   return;
}

BOOL CMiraCounter::IsHPTimeOut()
/*
   Controlla se siamo in timeout.
   Ritorna true se e' stato superato il timeout; false altrimenti.
*/
{ 
   LARGE_INTEGER        t;
   QueryPerformanceCounter(&t);           //istante corrente

   return (t.QuadPart>m_timeOut.QuadPart)? true:false;


}

void CMiraCounter::SetHPTimeOut(long mmsec)
/*
   Imposta il timeout in millisecondi
*/
{
   SetHPTimeOut((double)mmsec/1000.0);

   return;
}