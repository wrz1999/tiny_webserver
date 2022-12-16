#include <iostream>
#include "def.h"

class ntyevent
{
public:
    int fd;
    int events;
    void *arg;
    
    NCALLBACK callback;

    int status;
    char buffer[BUFFER_LENGTH];
    int length;
    //http
    // int method;
    // char resource[BUFFER_LENGTH];
    // int ret_code;
    // char Content_Type[512];
    //ws
    int state_machine;
};