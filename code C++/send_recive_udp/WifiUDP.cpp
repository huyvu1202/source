#include"WifiUDP.h"


SOCKET WifiInit()
{
    SOCKET s;
    struct sockaddr_in server;
    WSADATA wsa;

    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
    }
    printf("Initialised.\n");

    //Create a socket
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    //Bind
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }
    puts("Bind done");
    return s;
}

USHORT WifiRecive(SOCKET s, Recived_Message& message)
{
    USHORT rlen = 0;
    struct sockaddr_in si_other;
    int slen = sizeof(sockaddr_in);

    if ((rlen = recvfrom(s, (char *)&message.shuttleMessage, sizeof(Shuttle_Message), 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
    {
        printf("recvfrom() failed with error code : %d", WSAGetLastError());
    }
    inet_ntop(AF_INET, &si_other.sin_addr, message.ip, INET_ADDRSTRLEN);
    return rlen;
}

void WifiSend(SOCKET s, Send_Message message)
{
    struct sockaddr_in si_other;
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);

    inet_pton(AF_INET, message.ip, &(si_other.sin_addr));

    if (sendto(s, (char *)&message.pcMessage, sizeof(PC_Message), 0, (struct sockaddr*) &si_other, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d", WSAGetLastError());
    }
}

void WifiDestroy(SOCKET s)
{
    closesocket(s);
    WSACleanup();
}