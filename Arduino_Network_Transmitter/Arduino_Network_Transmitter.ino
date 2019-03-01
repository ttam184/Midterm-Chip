//initializes libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//intializes the transceiver chip
RF24 radio(7,8); //CE, CSN

//***************************************IMPORTANT*********************************
//the pipe address isn't the address of the trasceiver chip, it is the address of the
//connection between two transceiver chips. This means that if the transmitter and
//receiver don't have the same pipe address, they won't communicate. So make sure they
//are the same in both sections of code.
const byte address[6] = "00002";

void setup() {

  //starts up the serial monitor
  Serial.begin(9600);

  //starts up the transceiver chip
  radio.begin();
  radio.openWritingPipe(address);

  //puts PA level to minimum to help stop the transceiver chip from jamming
  radio.setPALevel(RF24_PA_MIN);

  //stops the chip from spending processing power listening for commands since it is the sender
  radio.stopListening();

  //sets pin 5 to input, the input it is receiving is based on the command the server arduino received
  pinMode(5, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //if the input from the server arduino was high it will create and send a character array and then print confirmation of the sent message to the monitor
  //Important note, this doesn't work with a string, it only works with character arrays. You can reconvert it to a string in the receiver code by 
  //creating a new string variable and setting it equal to the sent character array.
  if(digitalRead(5) == HIGH){
    const char text[] = "on";
    radio.write(&text, sizeof(text));
    Serial.println(text);
  }

  //if the input from the server arduino was low it will create and send a character array and then print confirmation of the sent message to the monitor
  //Important note, this doesn't work with a string, it only works with character arrays. You can reconvert it to a string in the receiver code by 
  //creating a new string variable and setting it equal to the sent character array.
  if(digitalRead(5) == LOW){
    const char text[] = "off";
    radio.write(&text, sizeof(text));
    Serial.println(text);
  }
}
