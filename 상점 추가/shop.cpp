#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void drawShop()
{
	setCursorPosition(Shop1.pos.x, Shop1.pos.y);
	printf("S");
}

void eraseShop()
{
	setCursorPosition(Shop1.pos.x, Shop1.pos.y);
	printf(" ");
}