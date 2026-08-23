#include "init.h"

int init_status_register(byte_t* flags){
    if(!flags){
        return -1;
    }

    *flags = 0u;

    *flags |= (1u << 1);

    return 0;
}