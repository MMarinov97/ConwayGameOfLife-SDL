#define SDL_MAIN_HANDLED
#include <engine.h>
#include <iostream>
#include <array>


const int GAME_WIDTH = 200;
const int GAME_HEIGHT = 200;

bool isAlive(const std::vector<std::vector<int>>& game, int x, int y) {

	int alive = 0;

	// Check left
	if (x > 0 && game[x - 1][y] == 1) alive++;
	// Check right
	if (x < GAME_WIDTH - 1 && game[x + 1][y] == 1) alive++;
	// Check above
	if (y > 0 && game[x][y - 1] == 1) alive++;
	// Check below
	if (y < GAME_HEIGHT - 1 && game[x][y + 1] == 1) alive++;
	// Upper left
	if (x > 0 && y > 0 && game[x - 1][y - 1] == 1) alive++;
	// Upper right
	if (x < GAME_WIDTH - 1 && y > 0 && game[x + 1][y - 1] == 1) alive++;
	// Lower left
	if (x > 0 && y < GAME_HEIGHT - 1 && game[x - 1][y + 1] == 1) alive++;
	// Lower right
	if (x < GAME_WIDTH - 1 && y < GAME_HEIGHT - 1 && game[x + 1][y + 1] == 1) alive++;

	// Cell is alive and has less than 2 or more than 3 alive neighbors
	if (game[x][y] == 1 && (alive < 2 || alive > 3)) return false;
	// Cell is dead and has exactly 3 alive neighbors
	if (game[x][y] == 0 && alive == 3) return true;

	// Default case: cell remains in its current state
	return game[x][y];
}

int main(int argc, char **argv) {

	Engine myengine(GAME_HEIGHT, GAME_WIDTH);
	// Create a 640x480 2D array of ints to hold the state of the cells
	// display will hold the current value to be displayed, and swap will hold
	// the data for the next generation
	std::vector<std::vector<int>> display(GAME_WIDTH, std::vector<int>(GAME_HEIGHT));
	std::vector<std::vector<int>> swap(GAME_WIDTH, std::vector<int>(GAME_HEIGHT));

	// Now we iterate through the rows in the display to generate random data
	for (std::vector<int>& row : display) {
		// We use a lambda expression to generate the random points
		std::generate(row.begin(), row.end(), []() {return rand() % 10 == 0 ? 1 : 0;});
	}

	// Main loop of the simulation
	while (true) {
		// Fill the swap with the next gen
		for (int i = 0; i < GAME_WIDTH; i++) {
			for (int j = 0; j < GAME_HEIGHT; j++) {
				swap[i][j] = isAlive(display, i, j) ? 1 : 0;
			}
		}
		// Draw next gen on the screen
		for (int i = 0; i < GAME_WIDTH; i++) {
			for (int j = 0; j < GAME_HEIGHT; j++) {
				if (swap[i][j]) {
					myengine.drawpixel(i, j, 255, 255, 255, 255);
				}
				else {
					myengine.drawpixel(i, j, 0, 0, 0, 255);
				}
			}
		}
		// Copy swap to display for next gen
		// Copy elements from swap to display for next generation
		for (int i = 0; i < GAME_WIDTH; i++) {
			for (int j = 0; j < GAME_HEIGHT; j++) {
				display[i][j] = swap[i][j];
			}
		}
		// Display to the screen
		myengine.update();
		// Delay for 20ms
		SDL_Delay(20);
		// Input
		myengine.input();
		// Clear points
		myengine.clearpixels();
	}
	
	return 0;
}