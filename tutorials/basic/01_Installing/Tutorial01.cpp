/*****************************************************************************************
 * Desc: Tutorial a) 01 Installing
 *****************************************************************************************/

#include "Tutorial01.h"

IND_Surface *mSurfaceBack, *mpieces[4], *mplayer_icons[4], *mquestionimage[17], *mquestionimage2[11];
IND_Entity2d *mBack, *mTextSmallWhite, *mTextPlayer, *mTextPlayers[4];
IND_Entity2d *player_piece[4], *player_icons[4], *questionimage;
IND_Font *mFontSmall;
IND_Camera2d *mCameraTerrain, *mCameraGui;

float planet_origin_x = 200.0f;
float planet_origin_y = 200.0f;
float planet_angle = 0.f;
Table table;

int num = 0; // starting position

Questions questions;

vector<Player> players;


bool loadQImage(void) {
    
    for (int i = 0; i < 17; i++) {
        stringstream ts;
        
        ts << "../../questions/Identifica/Imagem";
        ts << i+1;
        ts << ".jpg";
        mquestionimage[i] = IND_Surface::newSurface();
        if (!mI->_surfaceManager->add(mquestionimage[i], ts.str().c_str(), IND_ALPHA, IND_32))
            return false;
    }
    
    for (int i = 0; i < 11; i++) {
        stringstream ts;
        
        ts << "../../questions/Distingue/Imagem";
        ts << char('A' + (char)i);
        ts << ".jpg";
        mquestionimage2[i] = IND_Surface::newSurface();
        if (!mI->_surfaceManager->add(mquestionimage2[i], ts.str().c_str(), IND_ALPHA, IND_32))
            return false;
    }
        
    return true;
}

bool loadResources (void) {
    // Loading Background
	mSurfaceBack = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceBack, "../../resources/trivia_board.jpg", IND_OPAQUE, IND_32)) return false;
	
	loadQImage();
	
	
	// Loading pieces
	for (int i = 0; i < 4; ++i) {
		mpieces[i] = IND_Surface::newSurface();
		if (!mI->_surfaceManager->add(mpieces[i], "../../resources/piece_empty.jpg", IND_ALPHA, IND_32))
			return false;
	}
	
	mplayer_icons[0] = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mplayer_icons[0], "../../resources/Number-1-icon.png", IND_ALPHA, IND_32)) return false;
	mplayer_icons[1] = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mplayer_icons[1], "../../resources/Number-2-icon.png", IND_ALPHA, IND_32)) return false;
	mplayer_icons[2] = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mplayer_icons[2], "../../resources/Number-3-icon.png", IND_ALPHA, IND_32)) return false;
	mplayer_icons[3] = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mplayer_icons[3], "../../resources/Number-4-icon.png", IND_ALPHA, IND_32)) return false;
	
	
    // Creating 2d entity for the background
    mBack = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(0, mBack);					// Entity adding
	mBack->setSurface(mSurfaceBack);					// Set the surface into the entity
 
    
	// load the pieces for each of the players
	for (int i = 0; i < 4; ++i) {
		player_piece[i] = IND_Entity2d::newEntity2d();
		mI->_entity2dManager->add(0, player_piece[i]);					// Entity adding
		player_piece[i]->setSurface(mpieces[i]);					// Set the surface into the entity
		player_piece[i]->setShow(false);
		
		player_icons[i] = IND_Entity2d::newEntity2d();
		mI->_entity2dManager->add(0, player_icons[i]);					// Entity adding
		player_icons[i]->setSurface(mplayer_icons[i]);
		player_icons[i]->setShow(false);
	}
        
    // Font
	mFontSmall = IND_Font::newFont();
	if (!mI->_fontManager->add(mFontSmall, "../../resources/font_small.png", "../../resources/font_small.xml", IND_ALPHA, IND_32))
		return false;
    
    // ----- Font creation -----
    
	mTextSmallWhite = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(1, mTextSmallWhite);		// Entity adding in layer 1 (gui)
	mTextSmallWhite->setFont(mFontSmall);			// Set the font into the entity
    
	mTextSmallWhite->setLineSpacing(18);
	mTextSmallWhite->setCharSpacing(-8);
	mTextSmallWhite->setPosition(740, 110, 4);
	mTextSmallWhite->setAlign(IND_LEFT);
	
	mTextPlayer = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(1, mTextPlayer);		// Entity adding in layer 1 (gui)
	mTextPlayer->setFont(mFontSmall);			// Set the font into the entity
    
	mTextPlayer->setLineSpacing(18);
	mTextPlayer->setCharSpacing(-8);
	mTextPlayer->setPosition(15, 15, 4);
	mTextPlayer->setAlign(IND_CENTER);
	
	for (int i = 0; i < 4; ++i) {
	
		mTextPlayers[i] = IND_Entity2d::newEntity2d();
		mI->_entity2dManager->add(1, mTextPlayers[i]);		// Entity adding in layer 1 (gui)
		mTextPlayers[i]->setFont(mFontSmall);			// Set the font into the entity
    
		mTextPlayers[i]->setLineSpacing(18);
		mTextPlayers[i]->setCharSpacing(-8);
		mTextPlayers[i]->setPosition(15, 15, 4);
		mTextPlayers[i]->setAlign(IND_CENTER);
	}
	
	
	// Creating 2d entity for the question image
    questionimage = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(0, questionimage);					// Entity adding
	//	questionimage->setSurface(mquestionimage);					// Set the surface into the entity
	//	questionimage->setScale(0.7, 0.7);
	questionimage->setPosition(730, 370, 0);
	questionimage->setShow(false);

    
    
    // Camera used for moving along the terrain
	mCameraTerrain = new IND_Camera2d(mI->_window->getWidth () / 2, mI->_window->getHeight() / 2);
    
    // Camera used for showing the menu options, fps, etc (this camera dosen't change)
	mCameraGui = new IND_Camera2d(mI->_window->getWidth () / 2, mI->_window->getHeight() / 2);

}

void movePieces (void) {
	
	for (int i = 0; i < players.size(); ++i) {
		unsigned position = players[i].getPosition();
		
		switch (position) {
			case 0: player_icons[i]->setPosition(365.0, 40.0, 0.0); break;
			case 1: player_icons[i]->setPosition(432.0, 42.0, 0.0); break;
			case 2: player_icons[i]->setPosition(478.0, 55.0, 0.0); break;
			case 3: player_icons[i]->setPosition(523.0, 80.0, 0.0); break;
			case 4: player_icons[i]->setPosition(562.0, 110.0, 0.0); break;
			case 5: player_icons[i]->setPosition(600.0, 140.0, 0.0); break;
			case 6: player_icons[i]->setPosition(630.0, 178.0, 0.0); break;
			case 7: player_icons[i]->setPosition(650.0, 239.0, 0.0); break;
			case 8: player_icons[i]->setPosition(670.0, 303.0, 0.0); break;
			case 9: player_icons[i]->setPosition(670.0, 354.0, 0.0); break;
			case 10: player_icons[i]->setPosition(660.0, 405.0, 0.0); break;
			case 11: player_icons[i]->setPosition(648.0, 452.0, 0.0); break;
			case 12: player_icons[i]->setPosition(627.0, 498.0, 0.0); break;
			case 13: player_icons[i]->setPosition(600.0, 539.0, 0.0); break;
			case 14: player_icons[i]->setPosition(540.0, 568.0, 0.0); break;
			case 15: player_icons[i]->setPosition(490.0, 614.0, 0.0); break;
			case 16: player_icons[i]->setPosition(440.0, 631.0, 0.0); break;
			case 17: player_icons[i]->setPosition(388.0, 638.0, 0.0); break;
			case 18: player_icons[i]->setPosition(338.0, 638.0, 0.0); break;
			case 19: player_icons[i]->setPosition(290.0, 631.0, 0.0); break;
			case 20: player_icons[i]->setPosition(245.0, 614.0, 0.0); break;
			case 21: player_icons[i]->setPosition(189.0, 577.0, 0.0); break;
			case 22: player_icons[i]->setPosition(134.0, 539.0, 0.0); break;
			case 23: player_icons[i]->setPosition(100.0, 501.0, 0.0); break;
			case 24: player_icons[i]->setPosition(80.0, 455.0, 0.0); break;
			case 25: player_icons[i]->setPosition(65.0, 406.0, 0.0); break;
			case 26: player_icons[i]->setPosition(50.0, 355.0, 0.0); break;
			case 27: player_icons[i]->setPosition(50.0, 303.0, 0.0); break;
			case 28: player_icons[i]->setPosition(80.0, 240.0, 0.0); break;
			case 29: player_icons[i]->setPosition(92.0, 174.0, 0.0); break;
			case 30: player_icons[i]->setPosition(123.0, 136.0, 0.0); break;
			case 31: player_icons[i]->setPosition(155.0, 97.0, 0.0); break;
			case 32: player_icons[i]->setPosition(200.0, 70.0, 0.0); break;
			case 33: player_icons[i]->setPosition(248.0, 48.0, 0.0); break;
			case 34: player_icons[i]->setPosition(299.0, 30.0, 0.0); break;
			case 35: player_icons[i]->setPosition(365.0, 103.0, 0.0); break;
			case 36: player_icons[i]->setPosition(365.0, 141.0, 0.0); break;
			case 37: player_icons[i]->setPosition(365.0, 179.0, 0.0); break;
			case 38: player_icons[i]->setPosition(365.0, 217.0, 0.0); break;
			case 39: player_icons[i]->setPosition(365.0, 256.0, 0.0); break;
			case 40: player_icons[i]->setPosition(582.0, 263.0, 0.0); break;
			case 41: player_icons[i]->setPosition(546.0, 276.0, 0.0); break;
			case 42: player_icons[i]->setPosition(510.0, 289.0, 0.0); break;
			case 43: player_icons[i]->setPosition(474.0, 300.0, 0.0); break;
			case 44: player_icons[i]->setPosition(439.0, 310.0, 0.0); break;
			case 45: player_icons[i]->setPosition(505.0, 516.0, 0.0); break;
			case 46: player_icons[i]->setPosition(480.0, 485.0, 0.0); break;
			case 47: player_icons[i]->setPosition(458.0, 453.0, 0.0); break;
			case 48: player_icons[i]->setPosition(434.0, 425.0, 0.0); break;
			case 49: player_icons[i]->setPosition(411.0, 395.0, 0.0); break;
			case 50: player_icons[i]->setPosition(231.0, 520.0, 0.0); break;
			case 51: player_icons[i]->setPosition(255.0, 487.0, 0.0); break;
			case 52: player_icons[i]->setPosition(276.0, 456.0, 0.0); break;
			case 53: player_icons[i]->setPosition(300.0, 426.0, 0.0); break;
			case 54: player_icons[i]->setPosition(323.0, 395.0, 0.0); break;
			case 55: player_icons[i]->setPosition(150.0, 261.0, 0.0); break;
			case 56: player_icons[i]->setPosition(186.0, 275.0, 0.0); break;
			case 57: player_icons[i]->setPosition(221.0, 287.0, 0.0); break;
			case 58: player_icons[i]->setPosition(257.0, 299.0, 0.0); break;
			case 59: player_icons[i]->setPosition(294.0, 310.0, 0.0); break;
		}
	}
    
}

void renderScene (void) {

    movePieces();
	
	for (int j = 0; j < players.size(); ++j)
	switch (j) {
		case 0: player_piece[j]->setPosition(1.0, 20.0, 4.0); break;
		case 1: player_piece[j]->setPosition(650.0, 20.0, 0.0); break;
		case 2: player_piece[j]->setPosition(1.0, 600.0, 0.0); break;
		case 3: player_piece[j]->setPosition(650.0, 600.0, 0.0); break;
	}
    
    // -------- Render -------
    
    //mI->_render->clearViewPort(60, 60, 60);
    mI->_render->beginScene();
    mI->_render->clearViewPort(0, 0, 0);
    
    // --- Layer 0 (terrain) ---
    mI->_render->setViewPort2d(0, 0, mI->_window->getWidth(), mI->_window->getHeight());
    mI->_render->setCamera2d(mCameraTerrain);
    mI->_entity2dManager->renderEntities2d(0);
    
    // --- Layer 1 (gui) ---
    
    //mI->_render->setViewPort2d(0, 0, mI->_window->getWidth(), mI->_window->getHeight());
    mI->_render->setCamera2d(mCameraGui);
    //mI->_render->blitFillRectangle(800, 10, 240, 80, 128, 128, 128, 128);
    //mI->_render->blitRectangle(800, 10, 240, 80, 255, 255, 255, 128);
    mI->_entity2dManager->renderEntities2d(1);
    
    mI->_render->endScene();

}

int anyoneWon (void) {
	for (int i = 0; i < players.size(); ++i) {
		if (players[i].won())
			return i;
	}
	
	return -1;
}

void setPieces (int p) {
	bool *types = players[p].getCompleted();
	
	stringstream ts;
	
	ts << "../../pieces/piece_";
	
	if (types[1])
		ts << "g";
	if (types[2])
		ts << "p";
	if (types[3])
		ts << "b";
	if (types[4])
		ts << "o";
	if (types[0])
		ts << "r";
	
	ts << ".jpg";
	
	mI->_surfaceManager->add(mpieces[p], ts.str().c_str(), IND_ALPHA, IND_32);
	player_piece[p]->setSurface(mpieces[p]);
}

#define STRING_LENGTH 46

string processString (string line){
	int i1 = 0;
	int i2 = 0;
	//char newline[8192];
	stringstream newline;
	
	for (string::iterator i = line.begin(); i != line.end(); ++i) {
		if (i2 > 38 && *i == ' ') {
			newline << '\n';
			i2 = 0;
			i1++;
		}
		
		/*if (i2 == 46) {
			newline[i1] = '\n';
			i2 = 0;
			i1++;
		}*/
		if (*i == '\n')
			i2 = 0;

		newline << *i;
		i1++;
		i2++;
		
	}
	
	return newline.str();
}

void loadQuestions (void) {
	ifstream f1 ("../../questions/completa.txt");
	ifstream f2 ("../../questions/responde.txt");
	ifstream f3 ("../../questions/identifica.txt");
	ifstream f4 ("../../questions/distingue.txt");
	ifstream f5 ("../../questions/acerta.txt");
	
	// create COMPLETA questions
	while (!f1.eof()) {
		char q[8192];
		char aux[8192];
		vector<string> a;
		unsigned correct;
		
		// read question
		f1.getline(q, 8192, '\n');
		
		// read answers
		int i = 0;
		while (f1.getline(aux, 8192, '\n') && i < 4) {
			// correct answer
			if(aux[1] != ')')
				correct = atoi(&aux[0]) - 1;
			else
				a.push_back(aux);
			
			++i;
		}
		questions.createQuestion(q, a, correct, COMPLETA);
	}
	
	// create RESPONDE questions
	while (!f2.eof()) {
		char q[8192];
		char aux[8192];
		vector<string> a;
		unsigned correct;
		
		// read question
		f2.getline(q, 8192, '\n');
		
		// read answers
		int i = 0;
		while (f2.getline(aux, 8192, '\n') && i < 5) {
			// correct answer
			if(aux[1] != ')')
				correct = atoi(&aux[0]) - 1;
			else
				a.push_back(aux);
			
			++i;
		}
		questions.createQuestion(q, a, correct, RESPONDE);
	}
	
	// create IDENTIFICA questions
	
	stringstream img;
    int aux_id1 = 0;
	while (!f3.eof()) {
		char q[8192];
		char aux[8192];
		char image[8192];
		vector<string> a;
		unsigned correct;
		
		// read question
		f3.getline(q, 8192, '\n');
		
		// read answers
		img.str("");
		img << "../../questions/Identifica/";
		int i = 0;
		while (f3.getline(aux, 8192, '\n') && i < 5) {
			// correct answer
			
			if (aux[0] == 'I' && aux[1] == 'm' && aux[2] == 'a' && aux[3] == 'g' && aux[4] == 'e' && aux[5] == 'm')
				img << aux;
			else
				if(aux[1] != ')')
					correct = atoi(&aux[0]) - 1;
				else
					a.push_back(aux);

			++i;
		}
		//cout << img.str() << endl;
		questions.createQuestion(q, a, correct, IDENTIFICA, img.str(), aux_id1);
        aux_id1++;
	}
	
	// Distingue
    int aux_id2 = 0;
	while (!f4.eof()) {
		char q[8192];
		char aux[8192];
		char image[8192];
		unsigned correct;
		
		// read question
		f4.getline(q, 8192, '\n');
		
		// read answers
		img.str("");
		img << "../../questions/Distingue/";
		f4.getline(aux, 8192, '\n');
			// correct answer
		correct = atoi(&aux[0]) - 1;
		f4.getline(aux, 8192, '\n');
		img << aux;
		
		
		questions.createQuestion(q, img.str(), correct, DISTINGUE, int(aux[6]- 65));
        aux_id2++;
		f4.getline(aux, 8192, '\n');
	}
	
	// Acerta
	while (!f5.eof()) {
		char q[8192];
		char aux[8192];
		char image[8192];
		unsigned correct;
		
		// read question
		f5.getline(q, 8192, '\n');
		
		f5.getline(aux, 8192, '\n');		
		
		questions.createQuestion(q, aux, ACERTA_NA_PALAVRA);
		f5.getline(aux, 8192, '\n');
	}
}

void setupPlayers (void) {
	mTextSmallWhite->setText("Quantos jogadores? (1 a 4)");
	int starting_position = 0;
	renderScene();
	
	int option = -1;
	
	while(option == -1) {
		mI->_input->update();
	
		if(mI->_input->onKeyPress(IND_1))
			option = 1;
		if(mI->_input->onKeyPress(IND_2))
			option = 2;
		if(mI->_input->onKeyPress(IND_3))
			option = 3;
		if(mI->_input->onKeyPress(IND_4))
			option = 4;
		if(mI->_input->onKeyPress(IND_ESCAPE))
			exit(0);
	}
	
	stringstream au;
	au << "Escolhido(s) " << option << " jogadore(s)\n\nNome do jogador 1: ";
	
	mTextSmallWhite->setText(au.str().c_str());
	renderScene();
	
	for (int i = 0; i < option; ++i) {
		bool coisas = true;
		stringstream resposta;
		while (coisas) {
			mI->_input->update();
			
			if(mI->_input->onKeyPress(IND_A))
				resposta << "a";
			if(mI->_input->onKeyPress(IND_B))
				resposta << "b";
			if(mI->_input->onKeyPress(IND_C))
				resposta << "c";
			if(mI->_input->onKeyPress(IND_D))
				resposta << "d";
			if(mI->_input->onKeyPress(IND_E))
				resposta << "e";
			if(mI->_input->onKeyPress(IND_F))
				resposta << "f";
			if(mI->_input->onKeyPress(IND_G))
				resposta << "g";
			if(mI->_input->onKeyPress(IND_H))
				resposta << "h";
			if(mI->_input->onKeyPress(IND_I))
				resposta << "i";
			if(mI->_input->onKeyPress(IND_J))
				resposta << "j";
			if(mI->_input->onKeyPress(IND_K))
				resposta << "k";
			if(mI->_input->onKeyPress(IND_L))
				resposta << "l";
			if(mI->_input->onKeyPress(IND_M))
				resposta << "m";
			if(mI->_input->onKeyPress(IND_N))
				resposta << "n";
			if(mI->_input->onKeyPress(IND_O))
				resposta << "o";
			if(mI->_input->onKeyPress(IND_P))
				resposta << "p";
			if(mI->_input->onKeyPress(IND_Q))
				resposta << "q";
			if(mI->_input->onKeyPress(IND_R))
				resposta << "r";
			if(mI->_input->onKeyPress(IND_S))
				resposta << "s";
			if(mI->_input->onKeyPress(IND_T))
				resposta << "t";
			if(mI->_input->onKeyPress(IND_U))
				resposta << "u";
			if(mI->_input->onKeyPress(IND_V))
				resposta << "v";
			if(mI->_input->onKeyPress(IND_X))
				resposta << "x";
			if(mI->_input->onKeyPress(IND_Y))
				resposta << "y";
			if(mI->_input->onKeyPress(IND_Z))
				resposta << "z";
			if(mI->_input->onKeyPress(IND_ESCAPE))
				exit(0);
			if (mI->_input->onKeyPress(IND_RETURN))
				coisas = false;
			if(mI->_input->onKeyPress(IND_BACKSPACE)) {
				int len = strlen(resposta.str().c_str());
				string auxy = resposta.str();
				resposta.str("");
				for (int i = 0; i < len-1; ++i) {
					resposta << auxy[i];
				}
			}
			stringstream haha;
			
			haha << "Escolhido(s) " << option << " jogadore(s)\n\nNome do jogador " << i+1 << ": " << resposta.str();
			mTextSmallWhite->setText(haha.str().c_str());
			renderScene();

		}
		Player pa (resposta.str(), &questions, table, starting_position);
		players.push_back(pa);
	}
	
	// Set player names in the correct position
	for (int j = 0; j < players.size(); ++j) {
		player_piece[j]->setShow(true);
		player_icons[j]->setShow(true);
		switch (j) {
			case 0:
				mTextPlayers[j]->setPosition(47.0, 1.0, 0.0);
				player_piece[j]->setPosition(1.0, 20.0, 4.0);
				break;
			case 1:
				mTextPlayers[j]->setPosition(697.0, 1.0, 0.0);
				player_piece[j]->setPosition(650.0, 20.0, 0.0);
				break;
			case 2:
				mTextPlayers[j]->setPosition(47.0, 580.0, 0.0);
				player_piece[j]->setPosition(1.0, 600.0, 0.0);
				break;
			case 3:
				mTextPlayers[j]->setPosition(697.0, 580.0, 0.0);
				player_piece[j]->setPosition(650.0, 600.0, 0.0);
				break;
		}
		
		mTextPlayers[j]->setText(players[j].getName().c_str());
	}
	renderScene();
}

void showInstructions (void) {
	stringstream inst;
	inst << "Como jogar:\n\n1) Selecionar o n'mero de jogadores (1 a 4). O n'mero de jogadores * escolhido atrav*s das teclas num*ricas 1, 2, 3 ou 4.";
	inst << "2) Escrever o(s) nome(s) do(s) jogador(es).\n";
	inst << "3) O jogo inicia na casa 0.\n";
	inst << "4) Lance o dado, pressionando a tecla P, e prima o n'mero que indica a casa para a qual se quer deslocar. Depois de ter escolhido a casa, n{o pode voltar atr<s.\n";
	inst << "5) A cor de cada casa determina o tipo de pergunta associada.\n";
	inst << "6) Responda > pergunta que lhe aparecer no ecr{.\n";
	inst << "7) Para avan=ar e voltar a lan=ar o dado, pressione a tecla \"Enter\".\n";
	inst << "8) Ao responder acertadamente >s perguntas das casas maiores, ou das casas do pent<gono, o jogador ganha uma ficha. Neste caso, o jogador mant*m a sua vez e continua a jogar.\n";
	inst << "9) Ao responder acertadamente >s perguntas das casas normais, o jogador mant*m a sua vez mas n{o ganha fichas.\n";
	inst << "10) Se o jogador errar uma resposta, passa a vez ao pr&ximo jogador.\n";
	inst << "11) O primeiro jogador a completar o respetivo suporte com cinco fichas (uma de cada cor), ganha o jogo.\n";
	inst << "Para saber mais sobre o BioTrivial, consulte o documento Instru=$es, presente na pasta que cont*m o jogo.\n\nPressione P para jogar.";

	string texto = processString(inst.str());

	mTextSmallWhite->setPosition(740, 10, 4);
	mTextSmallWhite->setText(texto.c_str());
	renderScene();
	mTextSmallWhite->setPosition(740, 110, 4);

	bool cousas = true;
	while (cousas) {
		mI->_input->update();
			
		if(mI->_input->onKeyPress(IND_P))
			cousas = false;
				if(mI->_input->onKeyPress(IND_ESCAPE))
					exit(0);
	}
}

int IndieLib()
{
	// ----- IndieLib intialization -----
    
    //Sets the working path as the 'exe' directory. All resource paths are relative to this directory
	if (!WorkingPathSetup::setWorkingPathFromExe(NULL)) {
		std::cout<<"\nUnable to Set the working path !";
	}
    
	mI = CIndieLib::instance();
	if (!mI->init())
        return 0;
	
    if (!loadResources())
        return 0;
    
	while (true) {
    table.buildTable();
	loadQuestions();

	mTextSmallWhite->setText("Para jogar pressione P\n\nPara ver as instru=$es pressione I");
	renderScene();
	bool cousas = true;
	while (cousas) {
		mI->_input->update();
			
		if(mI->_input->onKeyPress(IND_I)) {
			showInstructions();
			cousas = false;
		}
		if(mI->_input->onKeyPress(IND_P)) {
			cousas = false;
		}
				if(mI->_input->onKeyPress(IND_ESCAPE))
					exit(0);
	}
    setupPlayers();
	

	
    
	// ----- Main Loop -----
	bool flagsz = true;
	while (!mI->_input->onKeyPress (IND_ESCAPE) && !mI->_input->quit() && flagsz)
	{
		// ----- Input Update ----

		mI->_input->update();
		
		
		
		for (int p = 0; p < players.size(); ++p) {
			stringstream mov;
			
			// Render player name
			mTextPlayer->setPosition(378.0, 340.0, 0.0);
			stringstream pl;
			pl << players[p].getName().c_str();
			mov << "Pressione a tecla P para lan=ar o dado.";
			mTextPlayer->setText(pl.str().c_str());
			mTextSmallWhite->setText(mov.str().c_str());
			renderScene();
			

			bool play = false;
			while (!play) {
				mI->_input->update();
				if (mI->_input->onKeyPress(IND_P))
					play = true;
				if(mI->_input->onKeyPress(IND_ESCAPE))
					exit(0);
			}
			
			int option = -1;
			vector<Slot> aux = players[p].availableMoves();
			
			mov.str("");
			mov << "Rolou " << players[p].getRolled() << ". Para que casa te desejas mover?\n";

			for (unsigned i = 0; i < aux.size(); ++i)
				mov << i+1 << ": " << aux.at(i).getPosition() << "\n";
			
			
			
			mTextSmallWhite->setText(mov.str().c_str());
			renderScene();
				
			// where to move?
			while(option == -1) {
				mI->_input->update();
				
				if(mI->_input->onKeyPress(IND_1))
					option = 1;
				if(mI->_input->onKeyPress(IND_2))
					option = 2;
				if(mI->_input->onKeyPress(IND_3))
					option = 3;
				if(mI->_input->onKeyPress(IND_4))
					option = 4;
				if(mI->_input->onKeyPress(IND_5))
					option = 5;
				if(mI->_input->onKeyPress(IND_6))
					option = 6;
				if(mI->_input->onKeyPress(IND_7))
					option = 7;
				if(mI->_input->onKeyPress(IND_8))
					option = 8;
				if(mI->_input->onKeyPress(IND_9))
					option = 9;
				if(mI->_input->onKeyPress(IND_ESCAPE))
					exit(0);
				
				if (option > aux.size())
					option = -1;
			}
			
			// display question
			Question *q = players[p].move(aux[option - 1].getPosition());
			//players[p].move(aux[option - 1].getPosition());
			//Question *q = questions.getQuestion((unsigned) 45);
			stringstream quest;
			quest.str("");
			quest << "Q: " << q->getQuestion() << "\n\n";

			string auxx = processString(quest.str());
			
			mTextSmallWhite->setText(auxx.c_str());
			renderScene();
			int res;
            
			
			// ve o tipo da questao para o caso de ser das de escrever
			if(q->getType() == ACERTA_NA_PALAVRA) {
				// saca a solucao
				stringstream resposta;
				bool coisas = true;
				while (coisas) {
					mI->_input->update();
				
					if(mI->_input->onKeyPress(IND_A))
						resposta << "a";
					if(mI->_input->onKeyPress(IND_B))
						resposta << "b";
					if(mI->_input->onKeyPress(IND_C))
						resposta << "c";
					if(mI->_input->onKeyPress(IND_D))
						resposta << "d";
					if(mI->_input->onKeyPress(IND_E))
						resposta << "e";
					if(mI->_input->onKeyPress(IND_F))
						resposta << "f";
					if(mI->_input->onKeyPress(IND_G))
						resposta << "g";
					if(mI->_input->onKeyPress(IND_H))
						resposta << "h";
					if(mI->_input->onKeyPress(IND_I))
						resposta << "i";
					if(mI->_input->onKeyPress(IND_J))
						resposta << "j";
					if(mI->_input->onKeyPress(IND_K))
						resposta << "k";
					if(mI->_input->onKeyPress(IND_L))
						resposta << "l";
					if(mI->_input->onKeyPress(IND_M))
						resposta << "m";
					if(mI->_input->onKeyPress(IND_N))
						resposta << "n";
					if(mI->_input->onKeyPress(IND_O))
						resposta << "o";
					if(mI->_input->onKeyPress(IND_P))
						resposta << "p";
					if(mI->_input->onKeyPress(IND_Q))
						resposta << "q";
					if(mI->_input->onKeyPress(IND_R))
						resposta << "r";
					if(mI->_input->onKeyPress(IND_S))
						resposta << "s";
					if(mI->_input->onKeyPress(IND_T))
						resposta << "t";
					if(mI->_input->onKeyPress(IND_U))
						resposta << "u";
					if(mI->_input->onKeyPress(IND_V))
						resposta << "v";
					if(mI->_input->onKeyPress(IND_X))
						resposta << "x";
					if(mI->_input->onKeyPress(IND_Y))
						resposta << "y";
					if(mI->_input->onKeyPress(IND_Z))
						resposta << "z";
					if(mI->_input->onKeyPress(IND_SPACE))
						resposta << " ";
					if(mI->_input->onKeyPress(IND_ESCAPE))
						exit(0);
					if (mI->_input->onKeyPress(IND_RETURN))
						coisas = false;
					if(mI->_input->onKeyPress(IND_BACKSPACE)) {
						int len = strlen(resposta.str().c_str());
						string auxy = resposta.str();
						resposta.str("");
						for (int i = 0; i < len-1; ++i) {
							resposta << auxy[i];
						}
					}
					
					stringstream haha;
					haha.str("");
					haha << "Q: " << q->getQuestion() << "\n\nR: " << resposta.str();
					string xa = processString(haha.str());
					mTextSmallWhite->setText(xa.c_str());
					renderScene();
				}
				
				res = players[p].answer(resposta.str());
			} else
				if (q->getType() == DISTINGUE){
                cout << q->getImage().c_str() << " - " << q->getImageID() << endl;
				//mI->_surfaceManager->add(mquestionimage, q->getImage().c_str(), IND_ALPHA, IND_32);
				questionimage->setSurface(mquestionimage2[q->getImageID()]);
				questionimage->setPosition(250, 300, 0);
				questionimage->setShow(true);
				renderScene();
					int opt = -1;
					while (opt == -1) {
						mI->_input->update();
					
						if(mI->_input->onKeyPress(IND_1))
							opt = 0;
						if(mI->_input->onKeyPress(IND_2))
							opt = 1;
						if(mI->_input->onKeyPress(IND_ESCAPE))
							exit(0);
					}
					res = players[p].answer(opt);
				} else {
				for (int j = 0; j < q->getAnswers().size(); ++j)
					quest << q->getAnswers().at(j) << "\n";

				string auxx = processString(quest.str());
				mTextSmallWhite->setText(auxx.c_str());
				if (q->getType() == IDENTIFICA) {
					//if(mI->_surfaceManager->add(mquestionimage, q->getImage().c_str(), IND_ALPHA, IND_32)) cout << "TAU"<< endl;
                    //loadQImage(q->getImage().c_str());
					questionimage->setSurface(mquestionimage[q->getImageID()]);
					questionimage->setPosition(250, 300, 1);
					questionimage->setShow(true);
					renderScene();
					int opt = -1;
					// answer
					while(opt == -1) {
						mI->_input->update();
						
						if(mI->_input->onKeyPress(IND_1))
							opt = 0;
						if(mI->_input->onKeyPress(IND_2))
							opt = 1;
						if(mI->_input->onKeyPress(IND_3))
							opt = 2;
						if(mI->_input->onKeyPress(IND_ESCAPE))
							exit(0);
					}
					
					res = players[p].answer(opt);
				} else {
			
				renderScene();
			
				option = -1;
				// answer
				while(option == -1) {
					mI->_input->update();
					
					if(mI->_input->onKeyPress(IND_1))
						option = 1;
					if(mI->_input->onKeyPress(IND_2))
						option = 2;
					if(mI->_input->onKeyPress(IND_3))
						option = 3;
					if(mI->_input->onKeyPress(IND_4))
						option = 4;
					if(mI->_input->onKeyPress(IND_ESCAPE))
						exit(0);
				}
			
				res = players[p].answer(option - 1);
			}
			}
			srand(time(NULL));
			unsigned value = rand() % 3;
			if (res != -1) {
				stringstream certo;
				switch (value) {
					case 0: certo << "Boa! Acertaste!"; break;
					case 1: certo << "A tua resposta est< correta. Est<s no bom caminho!"; break;
					case 2: certo << "Muito bem, " << players[p].getName() << "!"; break;
				}
				string fin = processString(certo.str());
				mTextSmallWhite->setText(fin.c_str());
				if(res > 0)
					setPieces(p);
					
				p--;
			} else {
				stringstream errado;
				errado << "Q: " << q->getQuestion() << "\n\n";
				switch (value) {
					case 0: errado << "N{o desanimes, a resposta certa seria: " << q->getCorrect(); break;
					case 1: errado << "Oh que pena... Devias ter escolhido: " << q->getCorrect(); break;
					case 2: errado << "Cabe=a erguida! J< sabes que da pr&xima vez a resposta certa *: " << q->getCorrect(); break;
				}
				string fin = processString(errado.str());
				mTextSmallWhite->setText(fin.c_str());
			}
			
			questionimage->setShow(false);

			renderScene();
			
			int var = anyoneWon();
			
			if (var != -1) {
				stringstream as;
				as << "O " << players[var].getName() << " ganhou!!\n\nVoltar a jogar: P\n Sair: E";
				mTextSmallWhite->setText(as.str().c_str());
				renderScene();
				option = -1;
				// answer
				while(option == -1) {
					mI->_input->update();
					
					if(mI->_input->onKeyPress(IND_P))
						option = 1;
					if(mI->_input->onKeyPress(IND_E))
						option = 2;
				}
				if (option == 2) {
					sleep(2);
					exit(0);
				} else
					flagsz = false;
			}
			option = -1;
			// answer
			while(option == -1) {
				mI->_input->update();
				
				if(mI->_input->onKeyPress(IND_RETURN))
					option = 1;
			}
		}
	}
	}

	// ----- Indielib End -----

	mI->end();

	return 0;
}
