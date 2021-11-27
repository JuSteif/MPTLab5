/******************************************************************************/
/*                                                                            */
/*              Ostfalia Hochschule für angewandte Wissenschaften             */
/*                        Fakultät für Fahrzeugtechnik                        */
/*           Institut für Fahrzeuginformatik und Fahrzeugelektronik           */
/*                             Fahrzeuginformatik                             */
/*                                                                            */
/* Paket:        MPT_LAB                                                      */
/*                                                                            */
/* Modul:        MPT_LAB_5                                                    */
/*                                                                            */
/* Beschreibung: Aufgaben 5.MPT-Labor                                         */
/*                                                                            */
/* Funktionen:   A_5_1: Timer0 als Frequenzgenerator                          */
/*                                                                            */
/* Version:      1.0 / 120716 / V. v. Holt                                    */
/*                                                                            */
/******************************************************************************/

//------------------------------------------------------------------------------
//  Headerdateien
//------------------------------------------------------------------------------
// Allgemeine Headerdateien
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Eigene Headerdateien
#include "MPT_LAB_MAIN.h"
#include "MPT_LAB_UTIL.h"
#include "MPT_LAB_5_1.h"


#ifdef ENABLE_A_5
#ifdef ENABLE_A_5_1
//------------------------------------------------------------------------------
//  Makro-/Konstantendefinitionen
//------------------------------------------------------------------------------
#define LED_DDR     DDRC
#define LED_PORT    PORTC
#define TASTER_DDR  DDRB
#define TASTER_PIN  PINB
#define TASTER_UP   PB6
#define TASTER_DOWN PB7
#define FG_DDR      DDRB
#define FG_PORT     PORTB
#define FG_PIN      PB3
#define FG_DELTA    10


//------------------------------------------------------------------------------
//  Private Variablen
//------------------------------------------------------------------------------
	
	
//------------------------------------------------------------------------------
//  Interrupt Service Routinen
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Private Funktionen
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Public Funktionen
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Aufgabe A_5_1: Timer0 als Frequenzgenerator
// A_5_1_1: Timer0 als Frequenzgenerator mit fester Frequenz.
// A_5_1_2: Timer0 als Frequenzgenerator mit fester Frequenz und Terminalausgabe.
// A_5_1_3: Timer0 als Frequenzgenerator mit einstellbarer Frequenz und Terminalausgabe.
//------------------------------------------------------------------------------

//##############################################################################

// A_5_1_1: Timer0 als Frequenzgenerator mit fester Frequenz.
void A_5_1_1(void)
{
  // IHR_CODE_HIER ...
}	

//##############################################################################

// A_5_1_2: Timer0 als Frequenzgenerator mit fester Frequenz und Terminalausgabe.
void A_5_1_2(void)
{
  // IHR_CODE_HIER ...
}	

//##############################################################################

// A_5_1_3: Timer0 als Frequenzgenerator mit einstellbarer Frequenz und Terminalausgabe.
void A_5_1_3(void)
{
  // IHR_CODE_HIER ...
}	

//##############################################################################

#endif /* ENABLE_A_5_1 */
#endif /* ENABLE_A_5 */


/*
 *  EoF
 */
