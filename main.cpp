#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>

#include <sstream>
#include <cmath>

#pragma comment (lib, "Ws2_32.lib")

// receive
int main()
{

    SOCKET connectSocket;
    SOCKET acceptSocket;
    WSADATA wsaData;
    int wsaerror;
    //initialising WSA
    WORD wVersionRequested{ MAKEWORD(2, 2) };
    try {
        wsaerror = WSAStartup(wVersionRequested, &wsaData);
        if (wsaerror != 0)
            throw std::invalid_argument("WinSock dll found" + (std::string)wsaData.szSystemStatus);

        else {
            std::cout << "WinSock dll found" << std::endl;
            std::cout << "Status: " << wsaData.szSystemStatus << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    //creating socket
    connectSocket = { INVALID_SOCKET };
    try {
        connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (connectSocket == INVALID_SOCKET) {
            WSACleanup();
            throw std::invalid_argument("ERROR at socket creation" + WSAGetLastError());
        }
        else {
            std::cout << "socket created" << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    //bind socket
    sockaddr_in clientservice;
    short port{ 8888 };					//kann programmargument werden
    clientservice.sin_family = AF_INET;
    PCSTR addr{ "127.0.0.1" };			//kann programmargument werden
    InetPton(AF_INET, addr, &clientservice.sin_addr.s_addr);
    clientservice.sin_port = htons(port);
    try {
        if (connect(connectSocket, (SOCKADDR*)&clientservice, sizeof(clientservice)) == SOCKET_ERROR) {
            closesocket(connectSocket);
            WSACleanup();
            throw std::invalid_argument("ERROR at socket binding" + WSAGetLastError());
        }
        else {
            std::cout << "socket bindet" << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << WSAGetLastError() << std::endl;
    }
    std::string halt;
    std::cin >> halt;
    //send data
    for (int i = 0; i < 200;i++) { //Hier kannnst du die anzahl ändern

        try {
            char sBuf[512]{};// "[""G""P""I""B""]""[""A""A""4""5""]""[""0"".""4""7""1""1""]"

            std::stringstream test;
            test << "[[USB][DEV1][MEAS][" << 2 * sin(i) << "]]" << "\n";
            test >> sBuf;

            int bytesend{};
            bytesend = send(connectSocket, sBuf, 512, 0);

            if (bytesend == SOCKET_ERROR) {
                closesocket(connectSocket);
                WSACleanup();
                throw std::invalid_argument("ERROR at sending" + WSAGetLastError());
            }
            else {
                std::cout << std::endl << "Sent: " << sBuf << std::endl;

            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;

        }
    }

    try {
        char sBuf[512]{};// "[""G""P""I""B""]""[""A""A""4""5""]""[""0"".""4""7""1""1""]"



        std::stringstream test;
        test << "end";
        test >> sBuf;

        int bytesend{};
        bytesend = send(connectSocket, sBuf, 512, 0);

        if (bytesend == SOCKET_ERROR) {
            closesocket(connectSocket);
            WSACleanup();
            throw std::invalid_argument("ERROR at sending" + WSAGetLastError());
        }
        else {
            std::cout << std::endl << "Sent: " << sBuf << std::endl;

        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

    }


//cleanup
    closesocket(connectSocket);
    WSACleanup();
    std::cout << "Shutdown succsessful!" << std::endl;
    return 0;
}

