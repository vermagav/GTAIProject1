/*
 * Configuration Settings for the Project
 * Ideally, these should be imported from a .ini file
 */
#ifndef _CONFIG_H
#define _CONFIG_H

// Step size for home agent and adversary
const int STEP_SIZE_HOMEAGENT = 5;
const int STEP_SIZE_ADVERSARY = 1;

// Start position of home agent
const int STARTX_HOMEAGENT = 1;
const int STARTY_HOMEAGENT = 1;

// Number of enemies
const int NUM_ENEMIES = 10;

// Number of moves per second
const int NUM_MOVES_PER_SEC = 1;

// Difficulty mode for adversary's movement
enum DifficultyMode
{
	RANDOM_EASY,
	RANDOM_NORMAL,
	RANDOM_INTELLIGENT,
	NUM_OF_MODES
};

#endif