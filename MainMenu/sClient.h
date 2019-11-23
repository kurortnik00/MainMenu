#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
//#include <arpa/inet.h> 
//
//class sClient
//{
//public:
//	sClient();
//	~sClient();
//
//	void error(char *msg);
//	void sendData(int x);
//	int getData();
//	int Init();
//	void endConnection();
//
//private:
//	int sockfd, portno = 27015, n;
//	char serverIp[] = "192.168.0.53";
//	struct sockaddr_in serv_addr;
//	struct hostent *server;
//	char buffer[256];
//	int data;
//};

