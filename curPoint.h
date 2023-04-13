

#ifndef DELAUNAYTRIANGULATION_CURPOINT_H
#define DELAUNAYTRIANGULATION_CURPOINT_H

#include "point.h"


class CurPoint
{
public:
    CurPoint(int _index) {
        this->index = _index;
        this->next = NULL;
    };
    inline void set(int _index) {
        index = _index;
    }
    int index;
    CurPoint* next;
};


#endif 
