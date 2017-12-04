#include "Level.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "menu.h"
#include <windows.h>

int main() {
	int level = getLevelByMenu();
	switch (level)
	{
		case 1:
			runLevelOne();
			break;
		case 2:
			runLevelTwo();
			break;
		case 3:
			runLevelThree();
			break;
		default:
			int msgboxID = MessageBox(
				NULL,
				(LPCWSTR)L"Voc� quebrou o jogo.",
				(LPCWSTR)L"Vacil�o",
				MB_DEFBUTTON2
				);
	}
}
