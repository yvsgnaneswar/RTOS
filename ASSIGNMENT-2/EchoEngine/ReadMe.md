# Echo Engine
The Echo Engine consists of a server and five clients. Client sends a character. Server replies by changing the case of the character if it is an alphabet or replies the same character if it's not an alphabet. The server and client communicate through **Socket**.
## Commands to run

To start the server

*gcc server.c -o server*

To start the client

*gcc client1.c -o client1*

for running client1 and similarly for another clients.

Input that should be given on the client side:

*a (or) B (or) 1 (or) @*

output will be A for a, b for B, 1 for 1 and @ for @

## Performance Data
Messages could not be sent parallely since clients are being run on multiple windows from same PC. The service time calculated doesn't seem to be reliable as it may be getting effected by background processes and appears to be scattered.

Service time( in micro seconds):

S.No | 1 client | 2 clients | 5 clients |
------|----------|-----------|-----------|
   1  |    48    |     61    |    34     |
   2  |    61    |     48    |    59     |
   3  |    62    |     56    |    63     |
   4  |    40    |     61    |    48     |
   5  |    61    |     62    |    61     |
