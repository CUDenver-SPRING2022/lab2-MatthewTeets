// Student: Matthew Teets
// Date: 2/8/22
// Class: CSCI 3800
// Description: This program generates a simple stream client socket that will be compatible with a stream server program.

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

// This function allows the client to send data to the server
int sendData(char *buffer, int sd, struct sockaddr_in server_address);

int main(int argc, char *argv[]) {
    
    int sd; // Functions as the socket descriptor
    struct sockaddr_in server_address; // Provides the address for the datagram server
    int portNumber; // Receives the port number for the server (entered on the command line)
    char serverIP[29]; // Receives the IP address of the server (entered on the command line)
    int rc; // All return code sent to this variable
    
    // Error handling: checks client arguments for IP and port number
    if (argc < 3)
    {
        printf("Usage is: client <ipaddr> <portnumber> \n");
        exit(1);
    }
    
    sd = socket(AF_INET, SOCK_STREAM, 0); // Creates the socket
    
    // Gets the IP address and port number from the command line
    portNumber = strtol(argv[2], NULL, 10); // Converts the string inside argv[2] to a long int
    strcpy(serverIP, argv[1]); // Copies the string from argv[1] into the serverIP variable
    
    // Structure containing the address of the server
    server_address.sin_family = AF_INET; // Sets the address family for the transport address
    server_address.sin_port = htons(portNumber); // Changes the portNumber to a network order byte and binds it
    server_address.sin_addr.s_addr = inet_addr(serverIP); // Makes the serverIP variable a usable internet address
    
    // Error handling: checks return code when connecting to server
    rc = connect(sd, (struct sockaddr *) &server_address, sizeof(server_address));
    if (rc < 0) {
        printf("Error when trying to connect.");
        exit(1);
    }
    
    // Client to server messaging/connection loop
    for (;;) {
        char clientMsg[25]; // Empty array to store the client message
        char stop[] = "STOP"; // Used to compare against the user's message
        memset(clientMsg, '\0', 25); // Sets all elements of clientMsg to NULL
        printf("Enter message: \n"); // User prompt
        scanf("%s", clientMsg); // Converts the user inputted array of characters into a string
        
        if (strcmp(clientMsg, stop) == 0) // If user input == 'STOP' close connection to server
        {
            printf("\nClient program has ended. \n"); // Client ending message
            break; // Breaks out of the for loop and exits the program
            
        } else { // Else continue and send message to server
            printf("You are sending '%s'. \n", clientMsg); // Prints to the console string stored inside buffer
            printf("The length of the string is %lu bytes. \n", strlen(clientMsg)); // Prints to the console the usigned int length of the string
            sendData(clientMsg, sd, server_address); // Takes client info and sends message to server
        }
    }
    return 0;
}

int sendData(char *buffer, int sd, struct sockaddr_in server_address){
    
    int rc = 0; // Create blank return code variable
    
    /*
       All information being sent out to the server :
            sd                                   ->  socket descriptor
            clientMsg                            ->  data being sent
            strlen(buffer)                       ->  how many bytes of data being sent
            0                                    ->  flags
     */
    
    rc = send(sd, buffer, strlen(buffer), 0);
    
    // Error handling: checks if message was sent
    if(rc <= 0)
    {
        printf("ERROR: No bytes were sent to server... \n");
        exit(1);
    }
    
    printf("Sent %d bytes. \n \n", rc); // Prints to the console the signed decimal int of number of bytes
    
    return(0);
}

