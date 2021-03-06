/*
    Filename: gameoflife.cpp
    Problem: #13 pg 436
    Description: Make the game of life program.
    Author: Joshua Rodriguez
    Email: ewized@gmail.com
    Date: 11/06/2013
*/
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Global Constants
const int WIDTH = 80;
const int HEIGHT = 23;
const char SPACE = ' ';
const char BLOCK = '*';
bool empty = false;

// Function declaration.
void print_world(char [][WIDTH]);
void generate_world(char [][WIDTH]);
void generation_world(char [][WIDTH], char [][WIDTH]);
bool check_cell(char [][WIDTH], int, int);
long get_seed();
bool repeat();

// Rule them all with the main function.
int main() {
    // The WORLD
    char world[HEIGHT][WIDTH];
    char world_two[HEIGHT][WIDTH];
    int generations = 1;

    // Seed the random generator.
    long seed = get_seed();
    srand(seed);

    // Generate and Print the world.
    generate_world(world);
    do {
        generations++;
        print_world(world);
        generation_world(world, world_two);
        if (!empty) {
            cout << "Press enter to go to the next generation. "
                 << "Press any key then enter to end. ";
        }
        else {
            cout << "All will be dead, press enter to end.";
        }
    } while(repeat() && !empty);

    // Spit out generations.
    cout << "You went through " << generations << " generations. "
         << "Your seed was " << seed << "." << endl;

    return 0;
}

// Seed the world.
long get_seed() {
    long results = time(0);
    cout << "Enter a seed to generate the world: ";
    cin >> results;
    return results;
}

// Birth and death of the generation.
void generation_world(char world[][WIDTH], char world_two[][WIDTH]) {
    int births = 0;
    // Check array.
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            bool birth = check_cell(world, x, y);
            if (birth) {
                world_two[y][x] = BLOCK;
                births++;
            }
            else {
                world_two[y][x] = SPACE;
            }
        }
    } 

    // When births is zero set empty to true and stop the loop.
    if (births == 0) {
        empty = true;
    }

    // Copy the array.
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            world[y][x] = world_two[y][x];
        }
    }
}

// Check if the cell should live or die.
bool check_cell(char world[][WIDTH], int x, int y) {
    int living = 0;
    bool results = false;

    // Counts the number of living cells.
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (world[y+i][x+j] == BLOCK)
                living++;
        }
    }

    // Decides upon the rules to keep the cell alive or kill it.
    if (world[y][x] == BLOCK) {
        living--;
        if (living == 2 || living == 3)
            results = true;
    }
    else {
        if (living == 3)
            results = true;
    }

    return results;
}

// Generate the world.
void generate_world(char world[][WIDTH]) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            int rand = random() % 8;
            char type;
            if (rand > 0) {
                type = SPACE;
            }
            else {
                type = BLOCK;
            }
            world[y][x] = type;
        }
    }
}

// Print the world to the screen.
void print_world(char world[][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            cout << world[y][x];
            if (x+1 == WIDTH) {
                cout << endl;
            }
        }
    }
}

// Loop the generation when the use get to end of line.
bool repeat() {
    char line = cin.get();
    if (line == '\n') {
        return true;
    }
    else {
        return false;
    }
}
