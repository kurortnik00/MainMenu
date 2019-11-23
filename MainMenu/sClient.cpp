//#include "sClient.h"
//
//
//sClient::sClient()
//{
//}
//
//sClient::~sClient()
//{
//}
//
//
//
//int sClient::Init()
//{
//    if ( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
//        error( const_cast<char *>( "ERROR opening socket") );
//
//    if ( ( server = gethostbyname( serverIp ) ) == NULL ) 
//        error( const_cast<char *>("ERROR, no such host\n") );
//    
//    bzero( (char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
//    serv_addr.sin_port = htons(portno);
//    if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
//        error( const_cast<char *>( "ERROR connecting") );
//
//    sendData(5);
//    data = getData();
//    printf("%d ->  %d\n",n, data );
//}
//
//void sClient::error(char *msg) {
//	perror(msg);
//	exit(0);
//}
//
//void sClient::sendData(int x) {
//	int n;
//
//	char buffer[32];
//	sprintf(buffer, "%d\n", x);
//	if ((n = write(sockfd, buffer, strlen(buffer))) < 0)
//		error(const_cast<char *>("ERROR writing to socket"));
//	buffer[n] = '\0';
//}
//
//int sClient::getData() {
//	char buffer[32];
//	int n;
//
//	if ((n = read(sockfd, buffer, 31)) < 0)
//		error(const_cast<char *>("ERROR reading from socket"));
//	buffer[n] = '\0';
//	return atoi(buffer);
//}
//
//void sClient::endConnection()
//{
//	sendData(sockfd, -2);
//	close(sockfd);
//	return 0;
//}
