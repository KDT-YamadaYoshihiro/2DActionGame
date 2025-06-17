#include "character.h"

void CChar::Draw(float x, float y, int hp ,int HP)
{
	// íÜêg
	DrawBox(x, y, x + (hp * HPSIZEW), y + HPSIZEH, GREEN, TRUE);
	
	// òg
	DrawLineBox(x, y, x + (HP * HPSIZEW), y + HPSIZEH, WHITE);
}
