/*
Reaktionsspiel
Taster drücken wenn die grüne LED leuchtet

LED grün = 11
LEDs farbig = 6,7, 8, 9, 10
Lautsprecher = 12
Taster (push) = 2
*/

#include <Tone.h>

int push   =  2; //Taster auf Pin 2
int leds[] = { 6, 7, 8, 9, 10, 11 }; //LEDs in einem array = Eingaben zusammen nehmen
int index = 0; //
boolean runningUp = true; //Taster im richtigen Moment drücken
int startSpeed = 600; //Start Spielgeschwindigkeit
int faster = 70; //maximale Spielgeschwindigkeit
boolean pressed = false; //Taster im falschen Moment drücken
int speed = startSpeed;

Tone speaker;

void setup() {
  
  Serial.begin(9600);
  Serial.println("setup");

  speaker.begin(12);
  
  pinMode( push, INPUT ); //Taster als Input definieren
  digitalWrite( push, HIGH ); //Wenn Taster gedrückt, passiert etwas
  attachInterrupt( 0, onPush, FALLING ); //Fehler beim falsch Drücken

  speaker.play( NOTE_G5, 100 );  
  delay (250); 
  speaker.play( NOTE_C6, 100 );  
  delay (250);
  speaker.play( NOTE_E6, 100 );  
  delay (300); 
  speaker.play( NOTE_DS6, 100 );  
  delay (150); 
  speaker.play( NOTE_DS6, 100 );  
  delay (220); 
  speaker.play( NOTE_DS6, 100 );  
  delay (250);
  speaker.play( NOTE_G5, 100 );  
  delay (100); 
  speaker.play( NOTE_GS5, 100 );  
  delay (450);
  speaker.play( NOTE_GS6, 100 );  
  delay (1000);

}

void loop() {

  litLed( index ); //LEDs nacheinander leuchten lassen
  delay( speed ); //Zeit zwischen den LEDs
  
  if( pressed ) { //Taster gedrückt
   
     if( index == 5 ) { //Richtig: Spiel geht schneller. Taster gedrückt wenn die 5. LED leuchtet = richtig. LEDs werden schneller
        speed -= faster;
     } else { //Falsch: Alle LEDs blinken (Ton) und Spiel beginnt von vorn. Taster im falschen Moment drücken, blinken die LEDs dreimal hintereinander kurz auf
        litAllLeds( HIGH );
        delay( 50 );
        litAllLeds( LOW );
        delay( 50 );
        litAllLeds( HIGH );
        delay( 50 );
        litAllLeds( LOW );
        speed = startSpeed;
     }
     
     pressed = false;
  }

  marchIndex();
}



void litAllLeds( int value ) {
  // loop over all leds
  for( int k = 0; k < 6; k = k + 1 )
  {
    pinMode( leds[k], OUTPUT );
    digitalWrite( leds[k], value );
  }
}




//LEDs leuchten nacheinander in der Reihnefolge des index auf

void litLed( int i )
{
  // loop over all leds
  for( int k = 0; k < 6; k = k + 1 )
  {
    pinMode( leds[k], OUTPUT );
    
    if( i == k )
    {
      digitalWrite( leds[k], HIGH );
    }
    else
    {
      digitalWrite( leds[k], LOW );
    }
  }
}



//Marschiert mit dem index rauf und runter

void marchIndex()
{
  if( runningUp ) {
    index++;
    if( index == 5 ) runningUp = false;
  } else {
     index--;
    if( index == 0 ) runningUp = true; 
  }
}


//Wird aufgerufen sobald taste gedrückt wird

void onPush() {
  pressed = true;
}


