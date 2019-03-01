//intializes libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//initializes the transceiver chip
RF24 radio(7,8); //CS,CSN

//********************IMPORTANT*************************************
//the pipe address isn't the address of the transceiver chip, it is the address of the
//connection between two transceiver chips. This means that if the transmitter and
//receiver don't have the same pipe address, they won't communicate. So make sure they
//are the same in both pieces of code.
const byte address[6] = "00002";

void setup() {
  // put your setup code here, to run once:

  //starts up serial monitor
  Serial.begin(9600);

  //starts up the radio using the address from before
  radio.begin();
  radio.openReadingPipe(0, address);

  //set the PA level to minimum to stop it from jamming if too close to other transceivers
  radio.setPALevel(RF24_PA_MIN);

  //makes the chip start to listen for signals
  radio.startListening();

  //sets the pin the LED is in to an output
  pinMode(9, OUTPUT);
}

void loop() {

  //if a signal is found
  if  (radio.available()) {

    //The number of characters in this string is the max amount that a received message can be.
    //So, if your text array is only 3 letters long. It will only save "Hel" from the message "Hello."
    const char text[] = "xxxxxxx";

    //reads the message and stores it in text
    radio.read(&text, sizeof(text));

    //converts the received character array into a string
    String text2 = text;

    //Prints to the serial monitor both the unconverted and converted message for debugging purposes.
    //this line can be freely skipped or removed.
    Serial.println(text);
    Serial.println(text2);

    //checks to see if the message received was "on" and then turns on the LED if it was
    if(text2.indexOf("on")>-1){
      digitalWrite(9,HIGH);
    }

    //checks to see if the message received was "off" and then turns on the LED off it was
    if(text2.indexOf("off")>-1){
      digitalWrite(9,LOW);
    }
  }
}

