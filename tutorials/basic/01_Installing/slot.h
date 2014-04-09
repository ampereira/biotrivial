//
//  slot.h
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#ifndef __IndielibTutorials__slot__
#define __IndielibTutorials__slot__

#include <vector>


#define NORMAL 8    // no questions on this
#define SPECIAL 9   // advance to X or other stuff
#define RESPONDE 0
#define COMPLETA 1
#define ACERTA_NA_PALAVRA 2
#define IDENTIFICA 3
#define DISTINGUE 4

using namespace std;

class Slot {
    int type;
	bool gives_points;
    unsigned index;
    vector<unsigned> adjacents;
    
public:
    Slot (int, unsigned);
    
	bool givesPoints (void);
	void setPoints (bool);
    int getType (void);
    unsigned getPosition (void);
    vector<unsigned> getAdjacent (void);
    
    void setAdjacent (unsigned);
    bool operator == (Slot);
    bool operator != (Slot);
    bool operator > (Slot);
    bool operator >= (Slot);
    bool operator < (Slot);
    bool operator <= (Slot);
};

#endif /* defined(__IndielibTutorials__slot__) */
