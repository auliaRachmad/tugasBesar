#ifndef game_h
#define game_h

#define MAP_SIZE 100
#define COORD_X 1
#define COORD_Y 1
#define ROWS 10
#define COLUMNS 10
#define MIN_POSITION 2  // Petak minimal (tidak boleh 1)
#define MAX_POSITION 99 // Petak maksimal (tidak boleh 100)
#define HUMAN 1
#define COM 0

typedef struct 
{
    int id;
    char namaPemain[20];
    char inisial[3];
    int posisi;
    int jumlahLemparan;
    int giliran;
    int dadu;
    int status;
}Pemain;

typedef struct
{
    int id;
    int mulut;
    int ekor;
}Ular;

typedef struct
{
    int id;
    int bawah;
    int atas;
}Tangga;

typedef struct
{
	char nama[20];
	int score;
}Score;

void tampilMainMenu();
void inputMainMenu();
void tampilGameplay();
void inputGameplay();
void inputPemain();
void inputKom();
void tampilHighscore();
void backToMainMenu();
void tampilContinue();
void howToPlay();

void petak(int x, int y);
void board(int x, int y, int jmlhPemain, Pemain pemain[4]);
int generateRandom(int min, int max);
void generateUlar(int *snakeHead, int *snakeTail);
void tampilUlar(int arrNum[10][10], Ular ular[4]);
void generateTangga(int *ladderTop, int *ladderBottom);
void tampilTangga(int arrNum[10][10], Tangga tangga[4]);
void numPetak(int size, int jmlhPemain, Pemain pemain[4]);
void tampilNumPetak(int x, int y, int arrNum [10][10]);
void tampilPemain(int jmlhPemain, Pemain pemain[4], int arrNum[10][10]);
void infoPemain(int x, int y, Pemain pemain);

void tampilHasilDadu();
int lemparDadu();
int cekMenang(Pemain pemain);
void getSix(Pemain *pemain);
void setPemain(int jmlhPemain, int status);
void inputNamaPemain(Pemain *pemain, int id, int status);
void gameStart(int jmlhPemain ,Pemain pemain[4]);
void giliran(Pemain *pemain);
void game(int jmlhPemain, Pemain pemain[4]);
void gamePause();
void continueGame();
void movePemain(Pemain *pemain);
void champion(int jmlhPemain, Pemain pemain);
void continueGame(); // Fungsi untuk melanjutkan permainan

void gotoxy(int x, int y); // Fungsi untuk memindahkan kursor ke koordinat tertentu
void clearLayar(); // Fungsi untuk membersihkan layar

#endif