# Database Engine
The Database Engine consists of a server and five clients. Client requests the file. Server reads the contents of the file requested by the client from the server directory. The contents of the file read by the server are sent to the client. The server and client communicate through **Socket**.
## Commands to run

To start the server

*gcc server.c -o server*

To start the client

*gcc client1.c -o client1*

for running client1 and similarly for another clients.

Input that should be given on the client side:

*GET test.txt*

here test.txt is the file client is requesting the server. the contents of the file gets displayed on the terminal of client.

## Performance Data
Requests could not be raised parallely since clients are being run on multiple windows from same PC. The service time calculated doesn't seem to be reliable as it is getting effected by background processes and appears to be scattered.

Service time( in micro seconds):

S.No | 1 client | 2 clients | 5 clients |
------|----------|-----------|-----------|
   1  |    58    |     60    |    58     |
   2  |    59    |     65    |    62     |
   3  |    42    |     64    |    60     |
   4  |    48    |     61    |    63     |
   5  |    31    |     60    |    59     |
