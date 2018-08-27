#pragma once

/* FRAMEWORK, Modified by: Kendrick */

#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>

class CStopWatch
{
private:
    // class variables declaration
    LARGE_INTEGER   m_liFrequency;
    LARGE_INTEGER   m_liPrevTime, m_liCurrTime, m_liStartTime;
    UINT            m_uTimerRes;
    
    // function declarations
    double          LiToSecs( LARGE_INTEGER & liInput ) ;

public:
    
    // constructor
    CStopWatch( void ) ;
    // destructor
    ~CStopWatch( void );

    // function declarations
    // Note: Use Get and Set functions if you need to access class variables
    // Do not declare public variables 
    void    startTimer        ( void );                // start the timer by getting current time and store it
    double  getElapsedTime    ( void ); /* Modified by: Kendrick */ // get time in seconds since the last call to this function
    void    waitUntil         ( double llTime); /* Modified by: Kendrick */  // wait until this time in milliseconds has passed
	double accurateTotalTime(); /* Made by: Kendrick */
};

#endif // _TIMER_H