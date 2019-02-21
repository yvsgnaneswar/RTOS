# Database Engine
The Database Engine consists of a server and five clients. Client requests the file. Server reads the contents of the file requested by the client from the server directory. The contents of the file read by the server are sent to the client. The server and client communicate through **Message Queue**. Two message queues are used for the communication. All the requests from the clients are being sent through one message queue along with client ID named as mtype in the code. The server recieves the requests irrespective of client ID and procceses the request and replies back through the second queue with client ID recieved with the request. The client recieves the reponse from the server if the client ID matches.
## Commands to run

To start the server

*gcc server.c -o server*

To start the client

*gcc client1.c -o client1*

for running client1 and similarly for another clients.

Input that should be given on the client side:

*GET testc.txt*

here testc.txt is the file client is requesting the server. the contents of the file gets displayed on the terminal of client.

## Performance Data
Requests could not be raised parallely since clients are being run on multiple windows from same PC. The service time calculated doesn't seem to be reliable as it is getting effected by background processes and appears to be scattered.

Service time( in micro seconds):

Sl.No | 1 client | 2 clients | 5 clients |
------|----------|-----------|-----------|
   1  |    22    |     28    |    28     |
   2  |    24    |     26    |    23     |
   3  |    36    |     32    |    27     |
   4  |    42    |     26    |    23     |
   5  |    26    |     32    |    26     |
