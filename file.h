#ifndef file_h
#define file_h

#include "game.h"

void fileWriteBoard(Tangga tangga[4], Ular ular[4]);
void fileReadBoard(Tangga tangga[4], Ular ular[4]);
void fileClearBoard();
int cekFileBoard();
void addHighscore(Score score);
void readHighscore(Score score[10]);
void fileWritePlayer(int jmlhPemain, Pemain pemain[4]);
void fileReadPlayer(int status, int jmlhPemain, Pemain pemain[4]);
void fileClearPlayer();
void fileWriteJmlhPlayers(int jmlhPemain);
void fileReadJmlhPlayers(int *jmlhPemain);
void fileClearJmlhPlayers();

#endif