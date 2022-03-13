#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ESP8266WiFi.h>
//#include <WiFi.h>
#include <WiFiUdp.h>
struct Package {
  int iD = 2;
  int rFID = 3;
  int batLevel;
  int sttCar;
};

struct Send_Message {
  int iD = 1;
  int action = 2;
  int nextStation;
  int targetStation;
};

/* WiFi network name and password */
// Your wirelless router ssid and password
const char* ssid = "Family";         // Tên của mạng WiFi mà bạn muốn kết nối đến
const char* password = "happy1818";   // Mật khẩu của mạng WiFi

// IP address to send UDP data to.
// it can be ip address of the server or
// a network broadcast address
// here is broadcast address
const char * udpAddress = "192.168.31.19"; // your pc ip
const int udpPort = 8080; //port server

//create UDP instance
WiFiUDP udp;

void setup() {
  Serial.begin(115200); // to monitor activity

  //Connect to the WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //This initializes udp and transfer buffer
  udp.begin(udpPort);
}

void loop() {

  //data will be sent to server
  uint8_t buffer[50] = "";

  struct Package senddata;
  senddata.iD = 3;
  senddata.rFID = 4;
  senddata.batLevel = 5;
  senddata.sttCar = 6;

  //send hello world to server
  udp.beginPacket(udpAddress, udpPort);
  udp.write((byte*) &senddata, sizeof(Package));
  udp.endPacket();
  memset(buffer, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();
  //receive response from server, it will be HELLO WORLD
  if (udp.read(buffer, sizeof(Send_Message)) > 0) {

    Send_Message* recMess;
    recMess = (Send_Message*)buffer;

    Serial.print("Server to client: ");
    Serial.println(recMess->iD);
    Serial.println(recMess->action);
    Serial.println(recMess->nextStation);
    Serial.println(recMess->targetStation);
  }
  //Wait for 1 second
  delay(1000);
}
