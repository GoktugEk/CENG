#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <queue>
#include "utils.h"
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <vector>




std::queue<Frame> inputQueue; //Inputs that are waiting to be sent
std::queue<Frame> window; //The inputs which are sent but not acked yet

pthread_mutex_t inpmut, winmut;
pthread_t threads[4];
unsigned int BUFFER_SIZE = 1024;
int PORT;
int serverport ;
socklen_t address_size;
struct sockaddr_in clientadd;
int sock_fd;



std::vector<Frame*> splitText(std::string s){

    /*
     * This function clips the string into 16 byte packages, actually we have 14 for the data*/

    std::vector<Frame*> res;

    for (int i = 0; i < s.length(); i+=13) {
        Frame *f = new Frame;
        if(i+13 >= s.length()) strcpy(f->data,s.substr(i).c_str());
        else strcpy(f->data,s.substr(i,13).c_str());
        res.push_back(f);

    }

    return res;
}




// THIS THREAD IS RESPONSIBLE OF GETTING INPUTS AND PUTTING THEM TO THE INPUT QUEUE
void* inputThread(void*p)
{
    unsigned int id = 1;
    while(1) {
        std::string data;

        std::getline(std::cin, data);

        std::vector<Frame*> r;

        data.push_back('\n'); // Must
        r = splitText(data);


        pthread_mutex_lock(&inpmut);

        for (int i = 0; i < r.size(); ++i) { // Pushing chunked packages into the input queue
            r[i]->ACK = id;
            inputQueue.push(*r[i]);
            delete r[i];
            id++;
        }

        pthread_mutex_unlock(&inpmut);
    }

}
// THIS THREAD IS MEASURING TIME BUT NOT COMPLETED YET
void* timer(void*p)
{
    /*
     * We wait for 251 ms to retransmit, if we still didn't have an ACK for the oldest message, we retransmit*/

    int last_id = -1;
    while(1){
        pthread_mutex_lock(&winmut);
        if(window.empty()) {  // window might be empty
            pthread_mutex_unlock(&winmut);
            continue;
        }
        else if(window.front().ACK != last_id){ // if the last message's ack is different from our id, we don't retransmit
            last_id = window.front().ACK;
            pthread_mutex_unlock(&winmut);
        }
        else { // retransmit condition push all the window to the front of the input queue
            pthread_mutex_lock(&inpmut);

            int l = window.size();
            for (int i = 0; i < l; ++i) {
                inputQueue.push(window.front());
                window.pop();
            }
            pthread_mutex_unlock(&winmut);

            for (int i = 0; i < inputQueue.size() - l; ++i) {
                inputQueue.push(inputQueue.front());
                inputQueue.pop();
            }

            pthread_mutex_unlock(&inpmut);
        }
        usleep(1000 * 251); // Wait for 251 ms to retransmit
    }
}


// THIS THREAD IS WAITING FOR THE RESPONSES OF THE SENT MESSAGES
void* listener(void*p){

    /*
     * Listens for the ack, if the ack's id is the same, we delete that message from the window.*/
    while(1){
        Frame f;

        recvfrom(sock_fd, // Get the response from server
                 &f,
                 16,
                 0,(struct sockaddr *) &clientadd,
                 &address_size);

        pthread_mutex_lock(&winmut);
        if(window.empty());
        else if((!strcmp(f.data,"$ACK")) && f.ACK == window.front().ACK){ // if it is an ACK
            window.pop(); //We pop from the window queue since it was a successful message
            pthread_mutex_unlock(&winmut);
        }
        else pthread_mutex_unlock(&winmut);
    }
}


void* server(void*p){
    /*
     * SERVER part of the code, it only receives messages and sends acks if the id is true.
     * */


    // USUAL STUFF ------------------------------------------------
    unsigned int id_expected = 1;
    int PORT = 8080;
    int sock_fd;
    socklen_t address_size;
    struct sockaddr_in serveradd;
    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


    if(sock_fd < 0){
        fprintf(stderr, "Socket Creation Fail!!\n");
        exit(1);
    }

    memset(&serveradd, '\0', sizeof(serveradd));

    serveradd.sin_family = AF_INET;
    serveradd.sin_addr.s_addr = inet_addr("172.24.0.10");
    serveradd.sin_port = htons(PORT);

    address_size = sizeof(serveradd);
    // Server address is ready, I should bind it with socket

    int res = bind(sock_fd, (struct sockaddr *) &serveradd, sizeof(serveradd));
    if (res < 0) {
        fprintf(stderr, "Binding failed!!!\n");
        exit(1);
    }

    // USUAL STUFF END ------------------------------------------------

    unsigned int shut = 0;

    // listening loop
    while(1){

        address_size = sizeof(serveradd);

        Frame *f = new Frame;
        recvfrom(sock_fd, f, 16, 0, (struct sockaddr*)&serveradd, &address_size);


        if(f->ACK == id_expected) { // match the ack id
            id_expected++;
            if (f->data[0] == '\n') shut++;
            else {
                std::cout << f->data;
                shut = 0;
            }
            if (shut >= 3) exit(0);

        }

        Frame respond; // create respond
        strcpy(respond.data, "$ACK");
        respond.ACK = f->ACK;
        sendto(sock_fd, &respond, 16, 0, (struct sockaddr *) &serveradd, sizeof(serveradd));

        delete f;
    }
}


int main(int argc, char *argv[]){
    // USUAL STUFF ----------------------------------------

    PORT = 2222;
    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(sock_fd < 0){
        fprintf(stderr, "Socket Creation Fail!!\n");
        exit(1);
    }

    memset(&clientadd, '\0', sizeof(clientadd));

    clientadd.sin_family = AF_INET;
    clientadd.sin_addr.s_addr = inet_addr("172.24.0.20");
    clientadd.sin_port = htons(PORT);
    // USUAL STUFF END ----------------------------------------

    // Thread creations
    pthread_create(&threads[0],NULL,&inputThread,NULL); //Input taker
    pthread_create(&threads[1],NULL,&listener,NULL); //ACK Listener
    pthread_create(&threads[2],NULL,&server,NULL); // Server for receiving messages
    pthread_create(&threads[3],NULL,&timer,NULL); //Timer to retransmit

    // Two mutexes for input and window queues.
    pthread_mutex_init(&winmut,NULL);
    pthread_mutex_init(&inpmut,NULL);


    unsigned int shut = 0;
    bool t;

    while(1)
    {
        pthread_mutex_lock(&winmut);
        t = window.size() < 4 && !inputQueue.empty(); // If window size, 4, is full, we will not send more packets.
        pthread_mutex_unlock(&winmut);

        if(t){
            Frame f;


            pthread_mutex_lock(&inpmut);
            f = inputQueue.front(); // Take the most recent input from the input list
            inputQueue.pop();
            pthread_mutex_unlock(&inpmut);

            pthread_mutex_lock(&winmut);
            window.push(f);
            pthread_mutex_unlock(&winmut);

            sendto(sock_fd, (char*)&f, 16, 0, (struct sockaddr *) &clientadd, sizeof(clientadd)); // send it
            if(f.data[0] == '\n') shut++; // Shut down calculations ...
            else shut=0;
            if(shut >= 3) return 0;

        }
    }


}