#include "FlappyGame/GameManager.h"
#include <iostream>
#include <time.h>
using namespace std;

int main() {

	srand((unsigned int)time(NULL)); //random seed

	GameManager gameManager;
	gameManager.Start();

	return 0;
}