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
/* Funktionen:   A_5_2: Motorsteuerung über PWM mit Timer0                    */
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
#include "MPT_LAB_5_2.h"


#ifdef ENABLE_A_5
#ifdef ENABLE_A_5_2
//------------------------------------------------------------------------------
//  Makro-/Konstantendefinitionen
//------------------------------------------------------------------------------
#define LED_DDR     DDRC
#define LED_PORT    PORTC
#define FG_DDR      DDRB
#define FG_PORT     PORTB
#define FG_PIN      PB3
#define FG_DELTA    10
#define LED_DELAY   50
#define TASTER_DDR  DDRB
#define TASTER_PIN  PINB
#define TASTER_STOP PB5
#define TASTER_SET  PB5
#define TASTER_UP   PB6
#define TASTER_DOWN PB7

#define	MOTOR_DIR_DDR DDRB
#define	MOTOR_PWM_DDR DDRB

#define	MOTOR_DIR_PORT PORTB

#define MOTOR_DIR0_PIN PB0
#define MOTOR_DIR1_PIN PB1
#define MOTOR_PWM_PIN  PB3 /* OC0 */


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
// Aufgabe A_5_2: Motorsteuerung über PWM mit Timer0
// A_5_2_1: Motorsteuerung mit fester Drehzahl und Terminalausgabe.
// A_5_2_2: Motorsteuerung mit einstellbarer Drehzahl und Terminalausgabe.
// A_5_2_3: Motorsteuerung mit einstellbarer Drehzahl, Stopfunktion und Terminalausgabe.
//------------------------------------------------------------------------------

//##############################################################################

// A_5_2_1: Motorsteuerung mit fester Drehzahl und Terminalausgabe.
void A_5_2_1(void)
{
	// IHR_CODE_HIER ...
	//LED inititalisieren
	LED_DDR = 0xff;
	LED_PORT = ~0x01;
	
	//Richtungsregister initialisieren: Port 3 in PINB Ausgang des Wavefrontgenerators Pin 0 & 1 für Richtungssteuerung des Motors
	MOTOR_PWM_DDR = 0x0b;
	MOTOR_DIR_PORT = 0x02;
	
	//usart initalisieren
	UsartInit(8, 1, 0, 9600);
	
	//Timer0 auf phasenkorektes nicht invertierendes PWM-Signal initalisieren
	TCCR0 = 0b00110100;
	OCR0 = 0x30;
	TCNT0 = 0;
	
	//Ausgabe der Drehzahlstufe
	UsartPuts("Drehzahlstufe 0x30");
	
	while(1){
		
	}
}

//##############################################################################

// A_5_2_2: Motorsteuerung mit einstellbarer Drehzahl und Terminalausgabe.
void A_5_2_2(void)
{
	// IHR_CODE_HIER ...
	//String für Terminal Ausgabe
	char string[20]
	
	//LED inititalisieren
	LED_DDR = 0xff;
	LED_PORT = 0x01;
	
	//Richtungsregister initialisieren: Port 3 in PINB Ausgang des Wavefrontgenerators Pin 0 & 1 für Richtungssteuerung des Motors
	MOTOR_PWM_DDR = 0x0b;
	MOTOR_DIR_PORT = 0x02;
	
	//usart initalisieren
	UsartInit(8, 1, 0, 9600);
	
	//Timer0 auf phasenkorektes nicht invertierendes PWM-Signal initalisieren
	TCCR0 = 0b00110100;
	OCR0 = 0x30;
	TCNT0 = 0;
	
	//Berechnung der Frequenz und Ausgabe auf dem Terminal
	double Periode = ((uint32_t)(2*1024) * (uint32_t)(OCR0+1))/((uint32_t)F_CPU/(uint32_t)1000000);
	double Frequenz = ((uint32_t)1000000)/Periode;
	sprintf(string, "'%lf\n'", Frequenz);
	UsartPuts(string);
	
	//Ausgabe der Drehzahlstufe
	UsartPuts("Drehzahlstufe 0x30");
	
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
			sprintf(string, "'%lf\n'", Frequenz);
			UsartPuts(string);
			
			//Delay gegen Prellen
			Wait_x_ms(50);
			
			//Ausgabe der Drehzahlstufe
			sprintf(string, "Drehzahlstufe 0x%x", OCR0);
			UsartPuts(string);
		}
	}
}

//##############################################################################

// A_5_2_3: Motorsteuerung mit einstellbarer Drehzahl, Stopfunktion und Terminalausgabe.
void A_5_2_3(void)
{
	// IHR_CODE_HIER ...
	//String für Terminal Ausgabe
	char string[20]
	
	//LED inititalisieren
	LED_DDR = 0xff;
	LED_PORT = 0x01;
	
	//Richtungsregister initialisieren: Port 3 in PINB Ausgang des Wavefrontgenerators Pin 0 & 1 für Richtungssteuerung des Motors
	MOTOR_PWM_DDR = 0x0b;
	MOTOR_DIR_PORT = 0x02;
	
	//usart initalisieren
	UsartInit(8, 1, 0, 9600);
	
	//Timer0 auf phasenkorektes nicht invertierendes PWM-Signal initalisieren
	TCCR0 = 0b00110100;
	OCR0 = 0x30;
	TCNT0 = 0;
	
	//Berechnung der Frequenz und Ausgabe auf dem Terminal
	double Periode = ((uint32_t)(2*1024) * (uint32_t)(OCR0+1))/((uint32_t)F_CPU/(uint32_t)1000000);
	double Frequenz = ((uint32_t)1000000)/Periode;
	sprintf(string, "'%lf\n'", Frequenz);
	UsartPuts(string);
	
	//Ausgabe der Drehzahlstufe
	UsartPuts("Drehzahlstufe 0x30");
	
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
			sprintf(string, "'%lf\n'", Frequenz);
			UsartPuts(string);
			
			//Ausgabe der Drehzahlstufe
			sprintf(string, "Drehzahlstufe 0x%x", OCR0);
			UsartPuts(string);
			
			//Delay gegen Prellen
			Wait_x_ms(50);
		}
		//Abfrage ob Taster-Stopp gedrückt wurde
		if(BIT_IS_SET(TASTER_PIN, TASTER_STOP)){
			OCR0 = 0;
			//MOTOR_DIR_PORT |= 3;
			
			//ausgabe der neuen Frequenz an Terminal
			Periode = ((uint32_t)(2*1024) * (uint32_t)(OCR0+1))/((uint32_t)F_CPU/(uint32_t)1000000);
			Frequenz = ((uint32_t)1000000)/Periode;
			sprintf(string, "'%lf\n'", Frequenz);
			UsartPuts(string);
			
			//Ausgabe der Drehzahlstufe
			sprintf(string, "Drehzahlstufe 0x%x", OCR0);
			UsartPuts(string);
			
			//Delay gegen Prellen
			Wait_x_ms(50);
			
			//Motor nach bremsen wieder freischalten
			BIT_IS_CLR(MOTOR_DIR_PORT, 0);
		}
	}
}

//##############################################################################

#endif /* ENABLE_A_5_2 */
#endif /* ENABLE_A_5 */


/*
*  EoF
*/
