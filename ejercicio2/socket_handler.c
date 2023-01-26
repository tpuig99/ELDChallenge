#include <stdio.h>
#include "socket_handler.h"
#include <string.h>

int socketCreate() {
     int handle = 0;
     
     if ((handle = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
         return -1;
     }
     return handle;
}

int socketConnect(int handle, const char *ip, unsigned short port){
     struct sockaddr_in serv_addr;     
     serv_addr.sin_family = AF_INET;

     serv_addr.sin_port = htons(port);
     
     if (inet_pton(AF_INET, ip, &serv_addr.sin_addr)<= 0) {
          return -1;
     }
     
     if (connect(handle, (struct sockaddr*)&serv_addr,sizeof(serv_addr))< 0) {
          return -1;
     }
     return 0;
}

int socketRead(int handle, unsigned char *data, int maxTimeout){
     struct timeval timeout;      
     timeout.tv_sec = maxTimeout;
     timeout.tv_usec = 0;
     
     if (setsockopt (handle, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof timeout) < 0){
          return -1;
     }

     if (setsockopt (handle, SOL_SOCKET, SO_SNDTIMEO, &timeout,sizeof timeout) < 0){
          return -1;
     }

     return read(handle, data, 1024);
}

int socketWrite(int handle, const unsigned char *data){
     return send(handle, data, strlen(data), 0);

}

int socketClose( int handle ){
     return close(handle);
}
