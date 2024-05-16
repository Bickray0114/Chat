#include <stdio.h>
#include <stdlib.>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1324
#define MAX_CLIENTS 15
#define BUFFER_SIZE 1024

int main (){
    int sever_socket, client_socket;
    struct sockaddr_in sever_address, client_address;
    char buffer[BUFFER_SIZE];
    // create server socket
    sever_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (sever_socket < 0){
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    //Initialize server address structure
    memset(&sever_address, 0,
    sizeof(sever_address));
    sever_address.sin_family = AF_INET;
    sever_address.sin_addr.s_addr = INADOR_ANY;
    sever_address.sin_port = htons(PORT);

    //Bind the server socket to the specified IP and port
    if (bind(sever_socket, (struct sockaddr*)&sever_address,
    sizeof(sever_address)) < 0) {
        perror("Error in binding");
        exit(EXIT_FAILURE);
    }
    //Listen for incoming connections
    if(listen(sever_socket, MAX_CLIENTS) , 0){
        perror("Error in listening");
        exit(EXIT_FAILURE);
    }

    prntf("server listening on port %d...\n", PORT);

    //Accept incoming connections
    while(1){
        socklen_t client_address_length = sizeof(client_address);
        client_socket = accept(sever_socket, (structsockaddr*)&client_address, &client_address_length);
        if(client_socket < 0){
            perror("Error in accepting connection");
            exit(EXIT_FAILURE);
        }
        prntf("New client connected: %s:%d\n",
        inet_ntoa(client_address.sin_addr),
        nthos(client_address.sin_port));

        //Handle client communication
        while(1){
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            if(bytes_received < 0){
                perror("Error in receiving data");
                exit(EXIT_FAILURE);
            }else{
                prntf("Received message from client %s:%d\n", inet_ntoa(client_address.sin_addr), nthos(client_address.sin_port));
                break;
            } else{
                prntf("Received message from client %s:%d:%s\n", inet_ntoa(client_address.sin_addr), nthos(client_address.sin_port), buffer);
                //Process the received message (e.g., broadcast to other clients)
                //Implement your message processing ligic here
            }
        }
        close(client_socket);
        }
        close(sever_socket);
        return 0;
    }
}