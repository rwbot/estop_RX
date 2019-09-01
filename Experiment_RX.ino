#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup()   
{
  Serial.begin(9600);
  radio.begin();  //Start the nRF24 module
  radio.maskIRQ(1,1,0);               //mask all IRQ triggers except for receive (1 is mask, 0 is no mask)
  radio.setPALevel(RF24_PA_MAX); //Set power level to low, won't work well at higher levels (interfer with receiver)
  radio.openReadingPipe(0,address);      //open pipe o for recieving meassages with pipe address
  radio.startListening();                 // Start listening for messages
  attachInterrupt(1, interruptFunction, FALLING);  //Create interrupt: 0 for pin 2 or 1 for pin 3, the name of the interrupt function or ISR, and condition to trigger interrupt
}

void loop() 
{
  
}
//This is the function called when the interrupt occurs (pin 3 goes LOW)
//this is often referred to as the interrupt service routine or ISR
//This cannot take any input arguments or return anything

void interruptFunction() 
{
 if (radio.available()) 
 {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
