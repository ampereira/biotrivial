//
//  player.h
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#ifndef __IndielibTutorials__player__
#define __IndielibTutorials__player__

#include <string>
#include <iostream>
#include <algorithm>
#include "dice.h"
#include "questions.h"
#include "table.h"
#include "slot.h"
#include "Indie.h"



#define RESPONDE 0
#define COMPLETA 1
#define ACERTA_NA_PALAVRA 2
#define IDENTIFICA 3
#define DISTINGUE 4


using namespace std;

class Player {
    string name;
    bool types_completed [5];
    unsigned position;
    Dice dice;
    Questions *questions;
    Table table;
    vector<Slot> possible_positions;
    bool origin_flag;
	Question *current_question;
	unsigned rolled;
    
public:
    unsigned origin;

	string getName (void);
	unsigned getRolled (void);
	unsigned getPosition (void);
	bool* getCompleted (void);
    Player (string, Questions*, Table&, unsigned);
	
	void moveInCircle (unsigned, unsigned);
	void moveInCenterOutward (unsigned, unsigned);
	void moveInCenterInward (unsigned, unsigned);
    
	bool won (void);
	
    template<class T>
    bool findPreviousPosition (vector<T>, T);
    vector<Slot> availableMoves (void);
    void getSlotsAtDistance (Slot, unsigned);
    Question* move (unsigned);
	int answer (int);
	int answer (string);
};

#endif /* defined(__IndielibTutorials__player__) */
