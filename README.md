# Server_Client_COM_Using_IPC_FIFO_and_Syncing_using_Signal
This project demonstrate the Inter-process Communication between server and client using one of the IPC technique FIFO .
#Project : IPC_SERVER_CLIENT

Description : In this project,the inter-process communication between server and Requesting client is demonstrate. Here multiple request is made by multiple Requesting client and the server gets the process done by other muliple processing client.

The communication of raw data from Requesting client(rc1,rc2..etc) to server and processed data from processing client (sum,sub,mul,div) to Requesting client is achieved using FIFO.futher more the order and synchronization of processed data to their respective client is achieved using signals.

FIFO is also known as named pipe ,which follow the rule of FIRST IN FIRST OUT. IT has the ability to be appered in the filesystem(because it has name) so unlike pipe it doesn't require any common ancesstor program,thus makes communication possible between independent process.

Here two pair of FIFO is created for communication between server and Requesting client as well as communication between server and processing client.lets us assume that there are FIFO1,FIFO2,FIFO3,FIFO3

FIFO1: Suppose if we configure this to be used for read purpose at server end and for write purpose from Requesting client end.

FIFO2: we configure this to be used for write purpose at server end and for read purpose from Requesting client end.

FIFO3: Suppose if we configure this to be used for write purpose at server end and for read purpose from Processing client end.

FIFO4: we configure this to be used for read purpose at server end and for write purpose from Processing client end.
so,the process goes like this: 
                                Requesting Client --->sends the raw data---->  Server
                                [rc1,rc2,rc3,rc4]            [FIFO1]
                                         
                                      Server ----->sends the raw data----> Processing Client
                                                           [FIFO3]          [sum,mul,div,sub]
                                
                                Processing Client --->sends the processed data---> Server
                                [sum,sub,mul,div]             [FIFO4]
                                
                                Requesting Client <---sends the raw data<----- Server
                                [rc1,rc2,rc3,rc4]             [FIFO2]
                                
 Now, here synchronisation is achieved using signal eg: SIGINT
