#ifndef WIFI_UDP // include guard
#define WIFI_UDP

#include<stdio.h>
#include <iostream>
#include <string>
#include<winsock2.h>
#include<ip2string.h>
#include<ws2tcpip.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib") //Winsock Library

const int port = 8080;	//The port on which to listen for incoming data

struct Shuttle_Message { // The message from shuttele
    int iD = 2;
    int rFID = 3;
    int batLevel;
    int sttCar;
};

struct PC_Message { // This message will be sent to shuttle
    int iD = 1;
    int action = 2;
    int nextStation;
    int targetStation;
};

struct Recived_Message {
    char ip[INET_ADDRSTRLEN];
    Shuttle_Message shuttleMessage;
};

struct Send_Message {
    char ip[INET_ADDRSTRLEN];
    PC_Message pcMessage;
};

SOCKET WifiInit();

void WifiDestroy(SOCKET s);

USHORT WifiRecive(SOCKET s, Recived_Message& message);

void WifiSend(SOCKET s, Send_Message message);


#endif /* WIFI_UDP */
