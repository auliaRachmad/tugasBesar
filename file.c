#include <stdio.h>  // Menyertakan pustaka standar input-output
#include <stdlib.h> // Menyertakan pustaka standar untuk fungsi umum seperti malloc dan rand
#include <windows.h> // Menyertakan pustaka untuk pengaturan sistem Windows seperti gotoxy
#include <conio.h>  // Menyertakan pustaka untuk fungsi input tanpa menunggu Enter seperti getch
#include <time.h>   // Menyertakan pustaka untuk fungsi waktu seperti srand dan time

#include "file.h"

void fileWriteBoard(Tangga tangga[4], Ular ular[4]){
    FILE* fptr = fopen("board.bin", "wb");

    for(int i = 0; i < 4; i++){
    	fwrite(&ular[i], sizeof(Ular), 1, fptr);
	}
	for(int i = 0; i < 4; i++){
    	fwrite(&tangga[i], sizeof(Tangga), 1, fptr);
	}
    fclose(fptr);
}

void fileReadBoard(Tangga tangga[4], Ular ular[4]){
    FILE* fptr = fopen("board.bin", "rb");
    for (int i = 0; i < 4; i++){
    	fread(&ular[i], sizeof(Ular), 1, fptr);
	}
	for (int i = 0; i < 4; i++){
    	fread(&tangga[i], sizeof(Tangga), 1, fptr);
	}
    fclose(fptr);
}

int cekFileBoard(){
	int a;
	FILE* fptr;
	
	if ((fptr = fopen("board.bin", "rb")) == NULL){
		return 0;
	}
	
	fread(&a, sizeof(int), 1, fptr);
	
	fclose(fptr);
	
	if(a =! 0){
		return 1;
	}else{
		return 0;
	}
}

void fileClearBoard(){
	FILE* fptr = fopen("board.bin", "wb");
	fclose(fptr);
}

void addHighscore(Score score){
	FILE* fptr = fopen("Score.dat", "a");
	
	fwrite(&score, sizeof(Score), 1, fptr);
	
	fclose(fptr);
}

void readHighscore(Score score[10]){
	FILE* fptr = fopen("Score.dat", "r");
	
	fseek(fptr, 0, SEEK_END);
	int structAmount = (int) ftell(fptr) / (int) sizeof(Score);
	
	Score players[structAmount];
	
	rewind(fptr);
	
	structAmount = 0;
    while (fread(&players[structAmount], sizeof(Score), 1, fptr)) {
        structAmount++;
    }

    fclose(fptr);
    
    for (int i = 0; i < structAmount -1; i++) {
        for (int j =0; j < structAmount - i -1; j++) {
            if (players[j].score < players[j+1].score) {
                Score temp = players[j];
                players[j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < 10; i++){
    	score[i] = players[i];
	}
}

void fileWritePlayer(int jmlhPemain, Pemain pemain[4]){
	FILE* fptr = fopen("Players.dat", "w");
	
	for (int i = 0; i < jmlhPemain; i++){
		fwrite(&pemain[i], sizeof(Pemain), 1, fptr);
	}
	
	fclose(fptr);
}

void fileReadPlayer(int status, int jmlhPemain, Pemain pemain[4]){
	FILE* fptr = fopen("Players.dat", "r");
	
	for(int i = 0; i < jmlhPemain; i++){
		fread(&pemain[i], sizeof(Pemain), 1, fptr);
	}
	
	if(status == 1){
		for (int i = 0; i < jmlhPemain; i++){
		  pemain[i].posisi = 0;
	      pemain[i].giliran = i;
	      pemain[i].dadu = 0;
	      pemain[i].jumlahLemparan = 0;
		}
	}
	
	fclose(fptr);
}

void fileClearPlayer(){
	FILE* fptr = fopen("Players.dat", "w");
	
	fclose(fptr);
}

void fileWriteJmlhPlayers(int jmlhPemain){
	FILE* fptr = fopen("Pemain.dat", "w");
	
	fprintf(fptr ,"%d", jmlhPemain);
	
	fclose(fptr);
}

void fileReadJmlhPlayers(int *jmlhPemain){
	FILE* fptr = fopen("Pemain.dat", "r");

	fscanf(fptr ,"%d", &*jmlhPemain);
	//fread(&*jmlhPemain, sizeof(int), 1, fptr);
	
	fclose(fptr);
}

void fileClearJmlhPlayers(){
	FILE* fptr = fopen("Pemain.dat", "w");
	fclose(fptr);
}