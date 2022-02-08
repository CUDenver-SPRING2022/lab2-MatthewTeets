# Lab 2
#### Name: Matthew Teets
#### Date: 2/8/22
#### Class: CSCI 3800

#

This project creates a rudimentary server-client program that allows communinication between a stream server program and a stream client program.

#

### **The two programs:**
- server2.c
  - Creates and binds a stream socket to the server address
  - Server remains open, listening for data from the client program
  - Messages from the client is processed and printed to the terminal
  - These steps are looped until the program is manually terminated using [Control + C]
- client2.c
  - Creates a stream socket
  - Promts the user for a message to send to the server
  - If successfully sent, conformation message will be displayed on both server and client side
  - These steps loop until the user sends the message 'STOP' to the server
    - This will terminate the client’s connection to the server
    
#

### **How to run:**
- Connect to CSE-grid
  - Example: ssh username@csegrid.ucdenver.pvt
  - Connect two terminal windows to this Linux server
    - One for the server and one for the client
- cd to the file containing the c programs and makefile

#

- Terminal window used to run server2.c
```
  $ host csci-gnode-NUM   (This will give the IP address for the server)
  $ make -f Makefile      
  $ ./server2 [SERVER-PORT-NUMBER]   (any number >= 1000)         
```
Example: $ ./server2 1234

#

- Terminal window used to run client2.c
```
  $ make -f Makefile
  $ ./client2 [SERVER-IP-ADDRESS] [SERVER-PORT-NUMBER]
```
Example: $ ./client2 132.534.194.53 1234
  
  
  
  
