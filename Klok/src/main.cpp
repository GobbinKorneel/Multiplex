#include <Arduino.h>

// Uitgang ESP voor multiplex via transistor

#define Tiental 13       //bovenste 7-segment display
#define Eenheid 12       //onderste 7-segment display


// uitgang ESP volgens standaard benaming segmenten

#define a 27    // pin 1 ok
#define b 14    // pin 13 ok
#define c 32    // pin 10 ok
#define d 33    // pin 8 ok
#define e 25    // pin 7 ok
#define f 26    // pin 2 ok
#define g 23    // pin 11 ok
                // pin 3 en 14 = ground


// 7 - segment display
//
//        ____a____
//       |         |
//       f         b
//       |         |
//       |____g____|
//       |         |
//       |         |
//       e         c
//       |____d____| 

int led[10][7] = 
{
  {a,b,c,d,e,f,0},    //0
  {0,b,c,0,0,0,0},    //1
  {a,b,0,d,e,0,g},    //2
  {a,b,c,d,0,0,g},    //3
  {0,b,c,0,0,f,g},    //4
  {a,0,c,d,0,f,g},    //5
  {a,0,c,d,e,f,g},    //6
  {a,b,c,0,0,0,0},    //7
  {a,b,c,d,e,f,g},    //8
  {a,b,c,d,0,f,g}     //9
};

int pin[] = {Tiental, Eenheid,a, b, c, d, e, f, g};    // alle pinnen zodat deze via een lus kunnen als output gezet worden.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// schrijft een getal naar één segment
//
// int getal is het weer te geven getal. Dit moet tussen 0 en 9 zijn.
// int segment is het weer te geven segment, waarbij 0 voor de tientallen staat en 1 voor de eenheden.
//
// return van het type bool: true indien alles ok verliep, false indien er een fout werd gedetecteerd.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool schrijfNaarSegment(int getal, int segment){
  switch(segment)                                 // zal zorgen voor de multiplex tussen de 2 segmenten
  {
    case 0:
      digitalWrite(Tiental, HIGH);
      digitalWrite(Eenheid, LOW);
      break;
    case 1:
      digitalWrite(Eenheid, HIGH);
      digitalWrite(Tiental, LOW);
      break;
    default:
      digitalWrite(Eenheid, HIGH);
      digitalWrite(Tiental, LOW);
      return false;                               // fout! --> komen hier indien een onbestaand segment wordt aangesproken
  }

  if (getal < 0 || getal > 9) return false;       // fout! --> komen hier indien een negatief cijfer of een cijfer groter dan 9 wordt ontvangen
    
  for (int segment = 0; segment < 7; segment++)
  {
    digitalWrite(led[8][segment], LOW);           // zet alle segmenten uit (het cijfer 8 bevat alle segmenten)
  }
  for (int segment = 0; segment < 7 ; segment++)
  {
    if(led[getal][segment] != 0)
    {
      digitalWrite(led[getal][segment], HIGH);        
    }
  }
  return true;                                    // alles ok voor zover we weten
}

//////////////////////////////////////////////////////////
// setup
//////////////////////////////////////////////////////////

void setup() {
  
  int aantalUitgangen = sizeof(pin)/sizeof(int);   // kijken hoeveel elementen er in de array zitten
   
  for(int i = 0; i < aantalUitgangen; i++)
  {
    pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
  }

}


///////////////////////////////////////////////////////////////
// loop
///////////////////////////////////////////////////////////////

int teller = 0;

void loop() {
  for(int i = 0; i < 100; i++)
  {
    if(i % 2 != 0)                          // % = remainder --> rest bij delen door 2 is dit 1 of 0 of nog even en oneven
    {
      schrijfNaarSegment(teller % 10, 1);   // delen door tien, rest x --> geeft de eenheid weer
    }
    else
    {
      schrijfNaarSegment(teller / 10, 0);   // delen door tien is opschuiven naar rechts, dus tiental wordt eenheid.
    }
    delay(10);      
  }

  if (teller >= 99)
  {
     teller = 0;
  }
  else
  {
    teller++;
  }
}