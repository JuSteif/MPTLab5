/*
 * MPT.c
 *
 * Created: 25.05.2012 18:12:01
 *  Author: holtv
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "MPT_LAB_MAIN.h"
#include "MPT_LAB_UTIL.h"

#include "Labor_5/MPT_LAB_5_1.h"
#include "Labor_5/MPT_LAB_5_2.h"

int main(void)
{
	//##############################################################################
	//
	// Aufgabe A_5
	//
	//##############################################################################
  //------------------------------------------------------------------------------
  // Aufgabe A_5_1: Timer0 als Frequenzgenerator
  // A_5_1_1: Timer0 als Frequenzgenerator mit fester Frequenz.
  // A_5_1_2: Timer0 als Frequenzgenerator mit fester Frequenz und Terminalausgabe.
  // A_5_1_3: Timer0 als Frequenzgenerator mit einstellbarer Frequenz und Terminalausgabe.
  //------------------------------------------------------------------------------
  A_5_1_1();
  //A_5_1_2();
  //A_5_1_3();


  //------------------------------------------------------------------------------
  // Aufgabe A_5_2: Motorsteuerung über PWM mit Timer0
  // A_5_2_1: Motorsteuerung mit fester Drehzahl und Terminalausgabe.
  // A_5_2_2: Motorsteuerung mit einstellbarer Drehzahl und Terminalausgabe.
  // A_5_2_3: Motorsteuerung mit einstellbarer Drehzahl, Stopfunktion und Terminalausgabe.
  //------------------------------------------------------------------------------
  //A_5_2_1();
  //A_5_2_2();
  //A_5_2_3();
	
	
  while(1)
  {
      //TODO:: Please write your application code 
  }
}

