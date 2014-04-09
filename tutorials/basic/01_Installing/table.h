//
//  table.h
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#ifndef __IndielibTutorials__table__
#define __IndielibTutorials__table__

#include "slot.h"
#include <vector>

#define NORMAL 8    // no questions on this
#define SPECIAL 9   // advance to X or other stuff
#define RESPONDE 0
#define COMPLETA 1
#define ACERTA_NA_PALAVRA 2
#define IDENTIFICA 3
#define DISTINGUE 4

using namespace std;

class Table {
    vector<Slot> slots;
    
public:
    Table (void);
    
    void buildTable (void);
    
    void addSlot (Slot);
    Slot getSlot (unsigned);
};

#endif /* defined(__IndielibTutorials__table__) */
