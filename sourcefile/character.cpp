#include "character.h"

void CChar::Draw(float x, float y, int hp ,int HP)
{
	// ���g
	DrawBox(x, y, x + (hp * HPSIZEW), y + HPSIZEH, GREEN, TRUE);
	
	// �g
	DrawLineBox(x, y, x + (HP * HPSIZEW), y + HPSIZEH, WHITE);
}
