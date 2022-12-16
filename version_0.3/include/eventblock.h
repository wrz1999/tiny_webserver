#include "ntyevent.h"

class eventblock
{
public:
    eventblock * next;
    ntyevent *events;
};