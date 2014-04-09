//
//  questions.h
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#ifndef __IndielibTutorials__questions__
#define __IndielibTutorials__questions__

#include "question.h"
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

class Questions {

public:
    vector<Question> questions;
    Questions (void);
    
    void createQuestion (string, vector<string>, unsigned, int);
    void createQuestion (string, string, int);
    void createQuestion (string, vector<string>, unsigned, int, string, int);
	void createQuestion (string, string, unsigned, int, int);
    
    Question getQuestion (void);
    Question* getQuestion (int);
    Question* getQuestionID (unsigned);
};

#endif /* defined(__IndielibTutorials__questions__) */
