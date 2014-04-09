//
//  questions.cpp
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#include "questions.h"

Questions::Questions (void) {
    
}

Question Questions::getQuestion (void) {
    int size = questions.size();
    
    return questions[rand() % size];
}


Question* Questions::getQuestionID (unsigned id) {
	for (int i = 0; i < questions.size(); ++i) {
		if (questions[i].getId() == id) {
			return &questions[i];
		}
	}
}

 
Question* Questions::getQuestion (int _type) {
    int size = questions.size();
    Question *question;
    
    do {
        question = &questions[rand() % size];
    } while (question->getType() != _type || question->wasAsked());
    
    return question;
}


void Questions::createQuestion (string _question, vector<string> _answers, unsigned _correct, int _type) {
    Question new_question (_question, _answers, _correct, _type);
    
    questions.push_back(new_question);
}

// distingue
void Questions::createQuestion (string _question, string _img1, unsigned _correct, int _type, int id) {
    Question new_question (_question, _img1, _correct, _type);
    new_question.setImageID(id);
    
    questions.push_back(new_question);
}

void Questions::createQuestion (string _question, string _answer, int _type) {
    Question new_question (_question, _answer, _type);
    
    questions.push_back(new_question);
}

// identifica
void Questions::createQuestion (string _question, vector<string> _answers, unsigned _correct, int _type, string img, int id) {
    Question new_question (_question, _answers, _correct, _type, img);
    new_question.setImageID(id);
    
    questions.push_back(new_question);
}
