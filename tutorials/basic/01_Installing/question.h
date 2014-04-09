//
//  question.h
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#ifndef __IndielibTutorials__question__
#define __IndielibTutorials__question__

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

#define NO_TYPE -1
#define RESPONDE 0
#define COMPLETA 1
#define ACERTA_NA_PALAVRA 2
#define IDENTIFICA 3
#define DISTINGUE 4 // e igual a identifica, cola se as imagens antes e ta feito

using namespace std;
static unsigned ids = 0;

class Question {
	unsigned id;
    bool asked;
    int type;
    string question;
	string image;
	string distingue_image;
	string answer;
    vector<string> answers;
    unsigned correct;   // has correct answer index on the vector
    bool correct_defined;
    int image_id;
    
public:
    Question (string, vector<string>, unsigned, int);
    Question (string, vector<string>, unsigned, int, string);
    Question (string, string, int);
    Question (string, string, unsigned, int);
    Question (int);
    Question (void);
    
    string getQuestion (void);
    vector<string> getAnswers (void);
    int getType (void);
	string getImage (void);
	string getCorrect(void);
	unsigned getId (void);
    int getImageID(void);
    void setImageID(int);
    
    bool isCorrectAnswer (unsigned);
    bool isCorrectAnswer (string);
    bool wasAsked (void);
    
    void ask (void);
    
    void setQuestion (string);
    bool setAnswer (string, bool);
    void setType (int);
};

#endif /* defined(__IndielibTutorials__question__) */
