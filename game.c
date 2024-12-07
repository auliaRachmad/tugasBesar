#include <stdio.h>  // Menyertakan pustaka standar input-output
#include <stdlib.h> // Menyertakan pustaka standar untuk fungsi umum seperti malloc dan rand
#include <windows.h> // Menyertakan pustaka untuk pengaturan sistem Windows seperti gotoxy
#include <conio.h>  // Menyertakan pustaka untuk fungsi input tanpa menunggu Enter seperti getch
#include <time.h>   // Menyertakan pustaka untuk fungsi waktu seperti srand dan time

#include "game.h"
#include "file.h"

void tampilMainMenu(){
  printf("\033[0;32m+----------------------------------------+\n");
  printf("|             Selamat Datang             |\n");
  printf("|          Permainan Ular Tangga         |\n");
  printf("+----------------------------------------+\033[0m\n");
  printf("MAIN MENU\n1. Mulai\n2. Highscore\n3. How To Play\n4. Exit\n");
  inputMainMenu();
}

void inputMainMenu(){
  int numMenu;
  printf("Masukkan Menu Yang Ingin Anda Pilih : ");
  scanf("%d", &numMenu);
  
  int a = cekFileBoard();

  if(numMenu > 0 && numMenu <=4){
    switch (numMenu)
    {
    case 1:
      clearLayar();
      
      if (a == 1) {
      	tampilContinue();
	  } else {
	  	tampilGameplay();
	  }
      
      break;
    
    case 2:
      tampilHighscore();
      break;

    case 3:
      clearLayar();
      howToPlay();
      break;
    
    case 4:
      clearLayar();
      printf("TERIMA KASIH TELAH BERMAIN........");
      exit(1);
      break;
    }
  }else {
    printf("\nPilihan anda tidak ada dalam menu\nMohon memasukkan angka yang sesuai\n\n");
    tampilMainMenu();
  }
}

void tampilHighscore(){
	clearLayar();
	Score score[10];
	
	readHighscore(score);

	for(int i = 0; i < 10; i++){
		printf("%s\t\t\t%d\n", score[i].nama, score[i].score);
	}
	
	printf("Tekan apapun untuk kembali ke main menu.....");
	
	int n = getch();
	
	if(n){
		clearLayar();
		tampilMainMenu();
	}
}

void howToPlay(){
	printf("\033[0;32mPANDUAN BERMAIN\n");
	printf("========================================================================================================================\n");
	printf("1. Klik Mulai pada main menu.\n");
	printf("2. Pilih mode yang anda inginkan, terdapat 2 mode yaitu Multiplayer dan juga Singleplayer.\n");
	printf("3. Inputkan jumlah pemain ataupun komputer untuk dimainkan bersama.\n");
	printf("4. Masukkan nama untuk setiap pemain manusia.\n");
	printf("5. Pada tampilan papan, anda dapat melihat posisi anda berada.\n");
	printf("6. Anda dapat menekan 'spasi / space' untuk melakukan roll dice sesuai giliran yang ditentukan pada saat mengisi nama.\n");
	printf("7. Pemenang ditentukan ketika bidaknya tepat berdiri pada petak nomor 100.\n");
	printf("8. Sebagai rintangan, kami membuat masing-masing 4 buah rintangan berupa ular dan tangga.\n");
	printf("9. Gunakan juga kesempatan roll dice tambahan ketika anda mendapatkan angka 6 saat mengocok dadu.\n");
	printf("10. Besaran skor ditentukan dari berapa jumlah lemparan dadu untuk mencapai petak nomor 100.\n");
	printf("11. Semakin sedikit lemparan maka akan semakin besar skor yang didapatkan.\n");
	printf("12. Hanya pemenanglah yang mendapatkan hak untuk dicantumkan pada tampilan highscore.\n");
	printf("========================================================================================================================\n\033;[0m");
	printf("Tekan apapun untuk kembali ke main menu.....");
	
	int n = getch();
	
	if(n){
		clearLayar();
		tampilMainMenu();
	}
}

void tampilContinue(){
	printf("1. Continue\n2. New Game\n");
	int i;
	
	printf("Masukan input menu: ");
	scanf("%d", &i);
	while(i > 2 || i < 0){	
		printf("Masukan input menu: ");
		scanf("%d", &i);
	}
	
	switch (i){
		case 1:
			clearLayar();
			continueGame();
			break;
			
		case 2:
			clearLayar();
			tampilGameplay();
			break;
	}
}

void continueGame(){
	Pemain pemain[4];
	
	int jmlhPemain;
	fileReadJmlhPlayers(&jmlhPemain);
	fileReadPlayer(0, jmlhPemain, pemain);
	board(COORD_X, COORD_Y, jmlhPemain, pemain);
  	game(jmlhPemain, pemain);
}

void tampilGameplay(){
  printf("1. Multiplayer\n2. Singleplayer\n");
  inputGameplay();
}

void inputGameplay(){
  int numGameplay;

  printf("Masukkan Gameplay Yang Anda Inginkan : ");

  scanf("%d", &numGameplay);

  if(numGameplay > 0 && numGameplay <=2){
    switch (numGameplay)
    {
    case 1:
      clearLayar();
      inputPemain();
      break;
    
    case 2:
      clearLayar();
      inputKom();
      break;
    }
  }else{
    printf("Pilihan anda tidak ada dalam menu\nMohon memasukkan angka yang sesuai\n");
    tampilGameplay();
  }
}

void inputPemain(){
  int jmlhPemain;
  printf("Masukkan Jumlah Pemain (2-4) : ");
  scanf("%d", &jmlhPemain);

  while(jmlhPemain < 2 || jmlhPemain > 4){
    printf("Mohon Memasukkan Jumlah Pemain. Minimum 2 dan Maksimal 4 Pemain.\n");
    printf("Masukkan Jumlah Pemain (2-4) : ");
    scanf("%d", &jmlhPemain);
  }
  fileWriteJmlhPlayers(jmlhPemain);
  setPemain (jmlhPemain, HUMAN);
}

void inputKom(){
  int jmlhKom;
  printf("Masukkan Jumlah Bot Komputer (1-3) : ");
  scanf("%d", &jmlhKom);

  while (jmlhKom < 1 || jmlhKom > 3)
  {
    printf("Mohon Memasukkan Jumlah Pemain. Minimum 1 dan Maksimal 3 Pemain.\n");
    printf("Masukkan Jumlah Bot Komputer (1-3) : ");
    scanf("%d", &jmlhKom);
  }
  fileWriteJmlhPlayers(jmlhKom+1);
  setPemain(jmlhKom+1, COM);
}

void backToMainMenu(){
	int i;
	printf("\n\n=======================");
	printf("\n1. Main Lagi\n2. Back To Main Menu\n");
	printf("=======================\n");
	printf("Masukkan input : \033[0m");
	scanf("%d", &i);
	
	while (i < 0 || i > 2){
		printf("Masukkan input yang sesuai : ");
		scanf("%d", &i);
	}
	
	switch(i){
		case 1 :
			clearLayar();
			tampilGameplay();
			break;
		
		case 2 :
			clearLayar();
			tampilMainMenu();
	}
}

void petak(int x, int y){
    gotoxy(x,y);printf("\033[0;33m+---------+");
    gotoxy(x,y+1);printf("|");gotoxy(x+10,y+1);printf("|");
    gotoxy(x,y+2);printf("|");gotoxy(x+10,y+2);printf("|");
    gotoxy(x,y+3);printf("|");gotoxy(x+10,y+3);printf("|");
    gotoxy(x,y+4);printf("+---------+\033[0m");
}

void board(int x, int y, int jmlhPemain, Pemain pemain[4]){
    clearLayar();

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            petak(x + (j*10), y + (i*4));
        }
    }
    for (int i = 0; i < jmlhPemain; i++){
        infoPemain(x + 104, y + 8 + (i*1), pemain[i]);
    }
    numPetak(MAP_SIZE, jmlhPemain, pemain);
    tampilHasilDadu();
    gotoxy(COORD_X, 42);printf("             ");
}

void numPetak(int size, int jmlhPemain, Pemain pemain[4]){
    int papan[COLUMNS][ROWS];
    Tangga tangga[4];
    Ular ular[4];

    for (int i = 0; i < 10; i++){
        if(i % 2 == 0){
            for (int j = 0; j < 10; j++){
                papan[i][j] = size--;
            }
        }else{
            for (int j = 9; j >= 0; j--){
                papan[i][j] = size--;
            }
        }
    }
    
    fileReadBoard(tangga, ular);
    
    tampilNumPetak(COORD_X, COORD_Y, papan);
    tampilUlar(papan, ular);
    tampilTangga(papan, tangga);
    tampilPemain(jmlhPemain, pemain, papan);
}

void tampilNumPetak(int x, int y, int arrNum[10][10]){
    x = x + 1;
    y = y + 3;

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            gotoxy(x + (j*10), y + (i*4));printf("%d",arrNum[i][j]);
        }
    }
}

void tampilPemain(int jmlhPemain, Pemain pemain[4], int arrNum[10][10]){
	for (int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			int count = 0;
			int a[4];
			for (int n = 0; n < jmlhPemain; n++){	
				if(pemain[n].posisi == arrNum[i][j]){
					a[count] = n;
					count++;
				}
			}
			if(count == 1){
				gotoxy(COORD_X + 4 + (j*10), COORD_Y + 2 +(i*4));printf("\033[0;36m%c%c\033[0m", pemain[a[0]].inisial[0], pemain[a[0]].inisial[1]);
			}else if (count == 2){
				gotoxy(COORD_X + 4 + (j*10), COORD_Y + 2 +(i*4));printf("\033[0;36m%c%c%c%c\033[0m", pemain[a[0]].inisial[0], pemain[a[0]].inisial[1], pemain[a[1]].inisial[0], pemain[a[1]].inisial[1]);
			}else if (count > 2){
				gotoxy(COORD_X + 4 + (j*10), COORD_Y + 2 +(i*4));printf("\033[0;36m%dplyrs\033[0m", count);
			}
		}
	}
}

int generateRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Fungsi untuk menghasilkan posisi ular
void generateUlar(int *snakeHead, int *snakeTail) {
    do {
        *snakeHead = generateRandom(MIN_POSITION + 10, MAX_POSITION); // Kepala ular (di atas)
        *snakeTail = generateRandom(MIN_POSITION, *snakeHead - 1);   // Ekor ular (di bawah)
    } while ((*snakeHead - 1) / 10 == (*snakeTail - 1) / 10);         // Pastikan kepala dan ekor tidak dalam baris yang sama
}

// Fungsi untuk menghasilkan posisi tangga
void generateTangga(int *ladderTop, int *ladderBottom) {
    do {
        *ladderBottom = generateRandom(MIN_POSITION, MAX_POSITION - 10); // Dasar tangga (di bawah)
        *ladderTop = generateRandom(*ladderBottom + 1, MAX_POSITION);    // Ujung tangga (di atas)
    } while ((*ladderTop - 1) / 10 == (*ladderBottom - 1) / 10);         // Pastikan ujung atas dan dasar tidak dalam baris yang sama
}

void tampilUlar(int arrNum[10][10], Ular ular[4]){
    for(int n = 0; n < 4; n++){
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                if (ular[n].mulut == arrNum[i][j] || ular[n].ekor == arrNum[i][j]){
                    gotoxy(COORD_X + 1 + (j * 10), COORD_Y + 1 + (i * 4));printf("\033[0;31mU%d\033[0m", ular[n].id);
                }
            }
        }
    }
}

void tampilTangga(int arrNum[10][10], Tangga tangga[4]){
    for(int n = 0; n < 4; n++){
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                if (tangga[n].atas == arrNum[i][j] || tangga[n].bawah == arrNum[i][j]){
                    gotoxy(COORD_X + 1 + (j * 10), COORD_Y + 1 + (i * 4));printf("\033[0;32mT%d\033[0m", tangga[n].id);
                }
            }
        }
    }
}

void infoPemain(int x, int y, Pemain pemain){
    gotoxy(x,y);printf("%s (%c%c) : %d", pemain.namaPemain, pemain.inisial[0], pemain.inisial[1], pemain.posisi);
}

void setPemain(int jmlhPemain, int status){
  Pemain pemain[4];
  if(status == 1){
    for (int i = 0; i < jmlhPemain; i++){
      pemain[i].id = i+1;
      inputNamaPemain(&pemain[i], i+1, HUMAN);
      pemain[i].inisial[0] = pemain[i].namaPemain[0];
      pemain[i].inisial[1] = pemain[i].namaPemain[1];
      pemain[i].posisi = 0;
      pemain[i].giliran = i;
      pemain[i].dadu = 0;
      pemain[i].jumlahLemparan = 0;
      pemain[i].status = 1;
    }
  }else{
    pemain[0].id = 1;
    inputNamaPemain(&pemain[0], 1, HUMAN);
    pemain[0].inisial[0] = pemain[0].namaPemain[0];
    pemain[0].inisial[1] = pemain[0].namaPemain[1];
    pemain[0].posisi = 0;
    pemain[0].giliran = 0;
    pemain[0].dadu = 0;
    pemain[0].jumlahLemparan = 0;
    pemain[0].status = 1;

    for (int i = 1; i < jmlhPemain; i++){
      pemain[i].id = i+1;
      inputNamaPemain(&pemain[i], i+1, COM);
      pemain[i].inisial[0] = pemain[i].namaPemain[0];
      pemain[i].inisial[1] = pemain[i].namaPemain[3];
      pemain[i].posisi = 0;
      pemain[i].giliran = i;
      pemain[i].dadu = 0;
      pemain[i].jumlahLemparan = 0;
      pemain[i].status = 0;
    }
  }
  clearLayar();
  gameStart(jmlhPemain, pemain);
}

void inputNamaPemain(Pemain *pemain, int id, int status){
  if (status == 1)
  {
    printf("Masukkan nama Pemain %d: ", id);
    scanf("%s", pemain->namaPemain);
  }
  else{
    sprintf(pemain->namaPemain, "COM%d", pemain->id);
  }
}
 
void gameStart(int jmlhPemain ,Pemain pemain[4]){
  Ular ular[4];
  Tangga tangga[4];
  for(int i = 0; i < 4; i++){
    ular[i].id = i+1;
    tangga[i].id = i+1;
    generateUlar(&ular[i].mulut, &ular[i].ekor);
    generateTangga(&tangga[i].atas, &tangga[i].bawah);
  }
  fileWriteBoard(tangga, ular);
  board(COORD_X, COORD_Y, jmlhPemain, pemain);
  game(jmlhPemain, pemain);
}

void gamePause(){
	int i;
	clearLayar();
	printf("\033[0;36m==================\nGAME PAUSED\n==================\033[0m\n\n");
	printf("\033[0;34m1. Resume\n2. Restart\n3. Main Menu\n");
	printf("Masukkan pilihan menu : ");
	scanf("%d", &i);
	
	while(i < 0 || i > 3){
		printf("Masukkan pilihan menu yang seusai : ");
		scanf("%d", &i);
	}
	
	switch(i){
		case 1 :
			clearLayar();
			continueGame();
			break;
		
		case 2 :
			clearLayar();
			Pemain pemain[4];
			int jmlhPemain;
			fileReadJmlhPlayers(&jmlhPemain);
			fileReadPlayer(1, jmlhPemain, pemain);
			board(COORD_X, COORD_Y, jmlhPemain, pemain);
		  	game(jmlhPemain, pemain);
		  	break;
		
		case 3 :
			clearLayar();
			tampilMainMenu();
	}
}

void tampilHasilDadu(){
  gotoxy(105,2);printf("\033[0;36mTampilan Hasil Dadu");
  gotoxy(105,3);printf("+-----------------+");
  gotoxy(105,4);printf("|");gotoxy(123,4);printf("|");
  gotoxy(105,5);printf("|");gotoxy(123,5);printf("|");
  gotoxy(105,6);printf("|");gotoxy(123,6);printf("|");
  gotoxy(105,7);printf("+-----------------+\033[0m");
}

int lemparDadu(){
  int dadu;
  dadu = (rand() % 6) + 1;

  gotoxy(114,5);printf("%d", dadu);

  return dadu;
}

void movePemain(Pemain *pemain){
	Tangga tangga[4];
	Ular ular[4];
	
	pemain->dadu = lemparDadu();
  if(pemain->dadu > 0){
  	if(pemain->dadu == 6){
  		if(pemain->posisi + pemain->dadu > 100){
  			pemain->posisi = 100 - (pemain->posisi + pemain->dadu - 100);
		  }else{
		  pemain->posisi = pemain->posisi + pemain->dadu;	
		  }
  		getSix(&*pemain);
	  }
    if(pemain->posisi + pemain->dadu > 100){
  			pemain->posisi = 100 - (pemain->posisi + pemain->dadu - 100);
		  }else{
		  pemain->posisi = pemain->posisi + pemain->dadu;	
		  }
    pemain->dadu = 0;
  }
  
  fileReadBoard(tangga,ular);
  
  for (int i = 0; i < 4; i++){
  	if(pemain->posisi == ular[i].mulut){
  		pemain->posisi = ular[i].ekor;
	  }
	  if(pemain->posisi == tangga[i].bawah){
	  	pemain->posisi = tangga[i].atas;
	  }
  }
}

void getSix(Pemain *pemain){
	gotoxy(126,4);printf("ANDA MENDAPATKAN ANGKA 6!!!");
	gotoxy(126,5);printf("SILAHKAN MENGOCOK DADU LAGI");
	int n = getch();
	if(n == ' '){
    movePemain(&*pemain);
    }else if(n == 'q' || n == 'Q' || n == 'p' || n == 'P'){
    	gamePause();
	}
}

void game(int jmlhPemain, Pemain pemain[4]){
	
	int pemenang;
	int menang = 0;
	while (menang != 1){
	  for (int i = 0; i < jmlhPemain; i++){
	    if(pemain[i].giliran == 0){
	      giliran(&pemain[i]);
	      menang = cekMenang(pemain[i]);
	      if(menang == 1){
	      	pemenang = i;
		  }
	      for (int j = 0; j < jmlhPemain; j++){
	      	if(pemain[j].giliran == 0){
	      		pemain[j].giliran = jmlhPemain-1;
			  }else{
			  	pemain[j].giliran =  pemain[j].giliran - 1;
			  }
		  }
		  fileWritePlayer(jmlhPemain, pemain);
	      board(COORD_X, COORD_Y, jmlhPemain, pemain);
	    }
	    if (menang == 1) break;
	 }
	}
	remove("board.bin");
	remove("Players.dat");
	remove("Pemain.dat");
	champion(jmlhPemain, pemain[pemenang]);
}

int cekMenang(Pemain pemain){
	int menang = 0;
	if(pemain.posisi == 100){
 		menang = 1;
	}
	return menang;
}

void champion(int jmlhPemain, Pemain pemain){
	int scorePemain;
	Score score;
	
	scorePemain = (10000-pemain.jumlahLemparan) * jmlhPemain;
	
	clearLayar();
	printf("\033[0;32m===============================\n");
	printf("\033[0;32mSELAMAT KEPADA SANG JUARA!!!!!!\n");
	printf("\033[0;32m===============================\n");
	printf("%s", pemain.namaPemain);
	printf (" dengan score %d", scorePemain);
	
	if(pemain.status == HUMAN){
		sprintf(score.nama, "%s", pemain.namaPemain);
		score.score = scorePemain;
		addHighscore(score);
	}
	
	backToMainMenu();
}

void giliran(Pemain *pemain){
  int n;
  gotoxy(125,2);printf("Kepada %s", pemain->namaPemain);
  gotoxy(125,3);printf("Tekan space...");
  n = getch();
  if(n == ' '){
    movePemain(&*pemain);
  }else if(n == 'q' || n == 'Q' || n == 'p' || n == 'P'){
    	gamePause();
	}
  pemain->jumlahLemparan++;
}

void gotoxy(int x, int y){
    COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void clearLayar(){
    system("cls");
}