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
	//LED inititalisieren
	LED_DDR = 0xff;
	LED_PORT = ~0x01;
	
	//Richtungsregister initialisieren: Port 3 in PINB Ausgang des Wavefrontgenerators
	FG_DDR = 0x08;
	
	//Timer0 auf CTC initalisieren
	OCR0 = 0x80;
	TCCR0 = 0b01001101;
	TCNT0 = 0;
	
	//Nix tun
	while(1){
	}
}

//##############################################################################

// A_5_1_2: Timer0 als Frequenzgenerator mit fester Frequenz und Terminalausgabe.
void A_5_1_2(void)
{
	// IHR_CODE_HIER ...
	//LED inititalisieren
	LED_DDR = 0xff;
	LED_PORT = ~0x01;
	
	//Richtungsregister initialisieren: Port 3 in PINB Ausgang des Wavefrontgenerators
	FG_DDR = 0x08;
	
	//usart initalisieren
	UsartInit(8, 1, 0, 9600);
	
	//Timer0 auf CTC initalisieren
	OCR0 = 0x80;
	TCCR0 = 0b01001101;
	TCNT0 = 0;
	
	//Berechnung der Frequenz
	double Periode = ((uint32_t)(2*1024) * (uint32_t)(OCR0+1))/((uint32_t)F_CPU/(uint32_t)1000000);
	double Frequenz = ((uint32_t)1000000)/Periode;
	char* string[20];
	sprintf(string, "%lf", Frequenz);
	UsartPuts(string);
	
	while(1){

	}
}

//##############################################################################

// A_5_1_3: Timer0 als Frequenzgenerator mit einstellbarer Frequenz und Terminalausgabe.
void A_5_1_3(void)
{
	// IHR_CODE_HIER ...
	//LED inititalisieren
	LED_DDR = 0xff;
	LED_PORT = ~0x01;
	
	//Richtungsregister initialisieren: Port 3 in PINB Ausgang des Wavefrontgenerators
	FG_DDR = 0x08;
	
	//usart initalisieren
	UsartInit(8, 1, 0, 9600);
	
	//Timer0 auf CTC initalisieren
	OCR0 = 0x80;
	TCCR0 = 0b01001101;
	TCNT0 = 0;
	
	//Berechnung der Frequenz
	char* string[20];
	double Periode = ((uint32_t)(2*1024) * (uint32_t)(OCR0+1))/((uint32_t)F_CPU/(uint32_t)1000000);
	double Frequenz = ((uint32_t)1000000)/Periode;
	sprintf(string, "%lf", Frequenz);
	UsartPuts(string);
	
	while(1){
		//Abfrage ob Taster gedrückt wurde
		if(BIT_IS_SET(TASTER_PIN, TASTER_UP) || BIT_IS_SET(TASTER_PIN, TASTER_DOWN)){
			//Abfangen von Overflows und bestimmen des Verhaltens von OCR0
			if(BIT_IS_SET(TASTER_PIN, TASTER_UP) && OCR0 < 255){
				OCR0++;
			}
			else if(OCR0 > 0){
				OCR0--;
			}
			
			//ausgabe der neuen Frequenz an Terminal
			Periode = ((uint32_t)(2*1024) * (uint32_t)(OCR0+1))/((uint32_t)F_CPU/(uint32_t)1000000);
			Frequenz = ((uint32_t)1000000)/Periode;
			sprintf(string, "%lf", Frequenz);
			UsartPuts(string);
			
			//Delay gegen Prellen
			Wait_x_ms(50);
		}
	}
}

//##############################################################################

#endif /* ENABLE_A_5_1 */
#endif /* ENABLE_A_5 */


/*
*  EoF
*/
