#include <Arduino.h>

// Uitgang ESP voor multiplex via transistor

#define Tiental 13       //bovenste 7-segment display
#define Eenheid 12       //onderste 7-segment display


// uitgang ESP volgens standaard benaming segmenten

#define a 27    // pin 1 
#define b 35    // pin 13
#define c 23    // pin 10
#define d 21    // pin 8
#define e 5     // pin 7
#define f 26    // pin 2
#define g 34    // pin 11
                // pin 3 en 14 = ground

int led[10][7] = 
{
  {a,b,c,d,e,f,0},    //0
  {b,c,0,0,0,0,0},    //1
  {a,b,g,e,d,0,0},    //2
  {a,b,g,c,d,0,0},    //3
  {a,f,b,g,c,0,0},    //4
  {a,f,g,c,d,0,0},    //5
  {a,b,c,d,e,g,0},    //6
  {a,b,c,0,0,0,0},    //7
  {a,b,c,d,e,f,g},    //8
  {f,a,b,g,c,d,0}     //9
};

int pinnen[] = {Tiental, Eenheid,a, b, c, d, e, f, g};

void setup() {
  // put your setup code here, to run once:
  
  int aantalUitgangen = sizeof(pinnen)/sizeof(int);
  Serial.begin(115200);
  Serial.println(aantalUitgangen);
  
  for(int i = 0; i < aantalUitgangen; i++)
  {
    pinMode(pinnen[i], OUTPUT);
    digitalWrite(pinnen[i], LOW);
  }

}

int teller = 0;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Eenheid, HIGH);
  digitalWrite(Tiental, HIGH);
  for (int segment = 0; segment < 7; segment++)
  {
    digitalWrite(led[8][segment], LOW);   //zet alle segmenten uit (het cijfer 8 bevat alle segmenten)
  }
  for (int segment = 0; segment < 7 ; segment++)
  {
    if(led[teller][segment] != 0)
    {
      digitalWrite(led[teller][segment], HIGH);   
      Serial.print(led[teller][segment]);
    }
  }
  Serial.println();
  delay(1500);
  teller++;
  if (teller >= 10)
  {
     teller = 0;
  }
}