// send_recive_udp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WifiUDP.h"

SOCKET s = WifiInit();

int main()
{
    while (1)
    {
        Recived_Message message;

        int rlen = WifiRecive(s, message);

        if (rlen > 0)
        {
            printf("IP: %s\n", message.ip);
            
            Shuttle_Message *mess = &message.shuttleMessage;

            printf("Data convert: %d, %d, %d, %d\n", mess->batLevel, mess->iD, mess->rFID, mess->sttCar);
        }


        int input;
        printf("send to client a message: press 0\n");
        std::cin >> input;

        if (input == 0) {

            Send_Message sendMess;
            std::string ip = "192.168.31.51"; // Send to this IP

            strcpy_s(sendMess.ip, INET_ADDRSTRLEN, ip.c_str());

            sendMess.pcMessage.action = 111;
            sendMess.pcMessage.iD = 112;
            sendMess.pcMessage.nextStation = 113;
            sendMess.pcMessage.targetStation = 114;

            WifiSend(s, sendMess);

            printf("sent\n\n\n\n\n");
        }

        fflush(stdout);
    }

    WifiDestroy(s);
}



