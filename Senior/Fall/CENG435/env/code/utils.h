//
// Created by Göktuğ Ekinci on 6.12.2022.
//
#include <stdlib.h>

#ifndef HW1_UTILS_H
#define HW1_UTILS_H

// PACKET FRAME
struct Frame{
    unsigned short ACK;
    char data[14];

};


#endif //HW1_UTILS_H
