/*
 * Configuration Settings for the Project
 * Ideally, these should be imported from a .ini file
 */
#ifndef _CONFIG_H
#define _CONFIG_H

// World's Game State
enum GameState
{
	GAMESTATE_RUNNING,
	GAMESTATE_FAIL,
	GAMESTATE_WIN,
	GAMESTATE_COUNT
};

// Step size for home agent and adversary
const int STEP_SIZE_HOMEAGENT = 2;
const int STEP_SIZE_ADVERSARY = 1;

// Start position of home agent
const int STARTX_HOMEAGENT = 0;
const int STARTY_HOMEAGENT = 0;
const int STARTX_GOAL = 140;
const int STARTY_GOAL = 50;

// Boundary constants for the level
const int LEVEL_MIN_X = 0;
const int LEVEL_MAX_X = 140;
const int LEVEL_MIN_Y = 0;
const int LEVEL_MAX_Y = 50;

// Number of enemies
const int NUM_ENEMIES = 50;

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

/* Algorithm Related Config */

	// Radius Computation Buffer
	const int RADIUS_BUFFER = 20;
	// Victory Check Buffer
	const int WIN_BUFFER = 3;
	// Node Heuristic Weightage: Distance from <Home Agent> to <Path Node>
	const double NODE_WEIGHTAGE_D1 = 0.3;
	// Node Heuristic Weightage: Distance from <Path Node> to <Goal>
	const double NODE_WEIGHTAGE_D2 = 0.7;

#endif