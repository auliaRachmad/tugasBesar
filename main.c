#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "game.h"
#include "file.h"

int main(){
    system("mode 192,48");
    srand(time(NULL));
    tampilMainMenu();
    return 0;
}

