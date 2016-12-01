#include "SystemListener.hpp"

#include <stdlib.h>
#include <time.h>

SystemListener::SystemListener(){
    srand((unsigned int) time (NULL));
    for (int i=0; i<16; i++) {
        _id = _id*2 + rand()%2;
    }
}
