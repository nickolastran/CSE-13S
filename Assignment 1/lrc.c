#include "names.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, RIGHT, CENTER } Position;

const Position die[6] = {DOT, DOT, DOT, LEFT, CENTER, RIGHT };


int main(void) {
	int num_players;

	printf("Number of players(3 to 10)? ");
	int scanf_result = scanf("%d", &num_players);

	if (scanf_result < 1 || num_players < 3 || num_players > 10) {
		fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
		num_players = 3;
	}
	
	unsigned seed;
	printf("Random-number seed? ");
	scanf_result = scanf("%u ", &seed);

	if (scanf_result < 1) {
		fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
		seed = 4823;
	}

	srandom(seed);

	int players_chips[num_players];
	for (int i = 0; i < num_players; i++) {
		players_chips[i] = 3;
	}

	int index = 0;
	while (1) {
		int rolls = players_chips[index] > 3 ? 3 : players_chips[index];

		if (rolls > 0) {
			printf("%s:", player_name[index]);
		}

		for (int i = 0; i < rolls; i++) {
			Position roll = die[random() % 6];
			switch (roll) {
				case LEFT:
					players_chips[index]--;
					players_chips[(index + 1) % num_players]++;
					break;
				case CENTER:
					players_chips[index]--;
					break;
				case RIGHT:
					players_chips[index]--;
					players_chips[(index - 1 + num_players) % num_players]++;
					break;
				default:
					break;
			}
		}

		if (rolls > 0) {
			printf(" ends her turn with %d\n", players_chips[index]);
		}

		int winnerCount = 0;
		int winnerIndex = 0;

		for (int i = 0; i < num_players; i++) {
			if (players_chips[i] > 0) {
				winnerCount++;
				winnerIndex = i;
			}
		}

		if (winnerCount == 1) {
			printf("%s won!\n", player_name[winnerIndex]);
			break;
		}
		index = (index + 1) % num_players;
	}
	return 0;
}
