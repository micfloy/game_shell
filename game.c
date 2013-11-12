/**
 * Author: Michael Bentley
 * Date Last Modified: 11/11/13
 * Description: Implements game files for a basic, LCD-displayed game.
 *
 */

#include <msp430g2553.h>
#include "game.h"
#include "../LCD/LCD.h"
#include "../buttons/button.h"

// Initializes the player to the starting point.
unsigned char initPlayer() {
	return 0x80;
}

// Prints the player to a location.
void printPlayer(unsigned char player) {
	writeCommandByte(player);
	writeDataByte('*');
}

// Clears the player character on the display.
void clearPlayer(unsigned char player) {
	writeCommandByte(player);
	writeDataByte(' ');
}

// Moves the player in the direction indicated by the button pushed.  Uses edge conditions to prevent the player from moving off of the screen.
unsigned char movePlayer(unsigned char player, unsigned char button) {
	clearPlayer(player);

	switch (button) {
	case UP:

		if (player >= 0xC0) {
			player -= 0x40;
		}

		break;

	case DOWN:

		if (player < 0xC0) {
			player += 0x40;
		}

		break;

	case LEFT:
		// Checks the left edge of the top and bottom row to keep the player on the screen.
		if (((player > 0x80) && (player <= 0x87))
				|| ((player > 0xC0) && (player <= 0xC7))) {
			player -= 1;
		}

		break;

	case RIGHT:
		// Checks the right edge of the top and bottom row to keep the player on the screen.
		if (((player >= 0x80) && (player < 0x87))
				|| ((player >= 0xC0) && (player < 0xC7))) {
			player += 1;
		}

		break;
	}

	printPlayer(player);

	return player;
}

//  Returns a 1 or 0 depending on if the player has reached the bottom-right corner of the screen.
char didPlayerWin(unsigned char player) {
	return player == 0xC7;
}
