
//initialize required libraries
#include <SPI.h>
#include <Ethernet.h>

//configuring the arduino shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x04
};

//giving the arduino a fallback ip address
//the ip address should be randomly generated, 
//but if it fails it will attempt
//to use this address
IPAddress ip(10, 33, 50, 66);
IPAddress myDns(192,168,1, 1);
IPAddress gateway(10, 33, 50, 1);
IPAddress subnet(255, 255, 255, 0);

// telnet is ran out of port 23
EthernetServer server(23);

//stores the most recent command
String command;
boolean alreadyConnected = false;
char Char;

void setup() {

  //starts up the ethernet shield
  Ethernet.begin(mac,ip,gateway,subnet);
  server.begin();

  //starts up the serial monitor
  Serial.begin(9600);

  //prints out the ip address assigned to the arduino
  Serial.println("Main Control Server IP Address");
  Serial.println(Ethernet.localIP());

  //sets up the output to tell the transmiter arduino when to send the command to the receiver
  pinMode(8, OUTPUT);
}

void loop() { 

  //activates the server
  EthernetClient client = server.available();

  //if a user has joined the chat
  if(client){
    //sends the user an opening message when they 
    //first connect detailing what commands they can give
    if(!alreadyConnected) {
      client.flush();
      command="";

      server.print("Welcome User!");
      //ensures the opening message is only displayed once
      alreadyConnected = true;
    }
  }

//while a user is connected obtain user input
  while(client.available()) {
    Char = client.read();
  
//0x0D = enter key
//if the user hits the enter key, attempt to run the current command string
//if the last keypress was not enter, add it to the command string
  if(Char == 0x0D){
    server.print("Command Recieved");
    server.println(command);
    processCommand(command);
  }else{
    Serial.println(Char);
    command += Char;
  }
  }
}

//determines whether a valid command has been entered
void processCommand(String command2){

    //sends a high signal to the transmitter arduino if the command "on" is found
    if(command.indexOf("on") > -1){
        digitalWrite(8, HIGH);
    }
    //sends a low signal to the transmitter if the command "off" is found
    else if(command.indexOf("off")> -1){
        digitalWrite(8, LOW);
    }
    //if no valid command is found, displays a list of valid commands in the chat room
    else{
        server.println("List of Valid Commands:");
        server.println("on");
        server.println("off");
    }

    //clears the command string to start building the next command string
    command = "";
}

