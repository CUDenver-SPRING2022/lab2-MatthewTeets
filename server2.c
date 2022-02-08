// Student: Matthew Teets
// Date: 2/8/22
// Class: CSCI 3800
// Description: This program generates a simple stream server that will be compatible with a stream client program.

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char * argv[]) {
    
    int sd; // Functions as the socket descriptor
    int rc; // Functions as the return code recieved from the recvfrom
    struct sockaddr_in server_address; // Provides the address for the datagram server
    struct sockaddr_in from_address; // Provides the address from sender
    char buffer[100]; // Where data is stored
    int flags = 0; // Used for socket calls
    socklen_t fromLength = sizeof(struct sockaddr);
    
    int new_sd; // Variable for new sockets
    int flag = 0; // Loop conditional
    
    // Error handling: checks server port number argument
    if (argc < 2)
    {
        printf("Usage is: server <portnumber> \n");
        exit(1);
    }
    
    sd = socket(AF_INET, SOCK_STREAM, 0); // Creates the stream socket
    
    // Set the address of the DGRAM server
    int portNumber = atoi(argv[1]);
    server_address.sin_family = AF_INET; // Sets the address family for the transport address
    server_address.sin_port = htons(portNumber); // Changes the portNumber to a network order byte and binds it
    server_address.sin_addr.s_addr = INADDR_ANY; // Allows connections from any internet address
    
    // Now pass address to the OS/Network
    rc = bind(sd, (struct sockaddr *) &server_address, sizeof(server_address));
    
    // Error handling: checks stream socket binding
    if (rc < 0)
    {
        perror("bind");
        exit(1);
    }
    
    // Error handling: listens/waits for connections from the client
    rc = listen(sd, 5);
    if (rc < 0) {
        printf("Error while listening...");
        exit(1);
    }
    
    // Loop runs indefinitely waiting to receive data from client machine.
    for(;;) {
        // new_sd is the socket that hasn't been connected yet (sd is still being processed)
        // Used only for accepting new connections
        new_sd = accept(sd, (struct sockaddr *) &from_address, &fromLength);
    
        flag = 0; // Used as conditional statement for below while loop

        while (flag == 0) {
            memset(buffer, 0, 100); // Sets all values of the buffer to 0
            
            rc = recv(new_sd, buffer, sizeof(buffer), flags); // Receives message from client
            
            // Error handling: checks if message was received or not
            if (rc <= 0) { // If no message received
                printf("Client has disconnected... \n\n"); // client print message
                close(new_sd); // Close the connection to the client socket
                flag = 1; // New flag value exits while loop
            } else { // If message received
                printf("Received bytes : %d. \n", rc); // Print the number of bytes received
                printf("Client string : '%s' \n", buffer); // Print the message received
            }
        }
    }
    return 0;
}
