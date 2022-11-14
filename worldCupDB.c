/*==============================================================
| Congratulations on accepting your new position as lead developer and database admin for the 2211 World Cup. As the resident C expert, you have been assigned the task of designing and implementing a database of all teams (nations) which will be used throughout the World Cup.
| Usage: ./worldCupDB (then follow the instructions)
| Description of parameters:
|  team: struct to store team information
|  teamCode: a unique identifier for each team (0-31)
|  teamName: the name of the team
|  groupSeed: the group seed of the team is a a 2-digit number, first digit is the group number (A-H), second digit is the seed number (1-4)
|  kitColour: the colour of the team's kit(intial)
|  updated: whether the team's information has been updated
|  quit: whether the user wants to quit
|  teamList: array to store all teams
|  newTeam: temporary struct to store new team information
|  empty: whether the teamList is empty
*/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define NAMELEN 24

// Define team struct
typedef struct team
{
	int teamCode;								// a unique identifier for each team (0-31)
	char teamName[NAMELEN + 1]; // +1 for null terminator
	char groupSeed[3];					// Group seed is a string of 2 characters
	char kitColor;							// Kit color is a single character
} team;

// Function prototypes
int getche(void);
team createTeam(int teamCode, char teamName[NAMELEN + 1], char groupSeed[2], char kitColor);
int isExist(team teamList[32], int teamCode);
int printTeam(team teamList[32], int teamCode);
int printTeamList(team teamList[32]);

int main(void)
{
	int teamCode, updated = 0, quit = 0;
	char command, kitColor;
	char teamName[NAMELEN + 1], groupSeed[3];
	team teamList[32];
	while (!quit)
	{
		// Greeting
		printf("******************\n* 2211 World Cup *\n******************\n");
		printf("Enter operation code: ");
		// Read in the operation code
		// Accept single character input without pressing enter
		command = getche();
		// Catch arrow keys
		if (command == '\033')
		{
			while (getchar() != '\n')
				;
			continue;
		}
		// Convert to uppercase, and run the corresponding function
		switch (toupper(command))
		{
		case 'I':
			// Insert a team
			printf("\nEnter team code: ");
			if (scanf("%d", &teamCode) != 1 || teamCode < 0 || teamCode > 31)
			{
				while (getchar() != '\n')
					;
				printf("Invalid team code. Team not added.\n");
			}
			// Check if team code already exists
			else if (isExist(teamList, teamCode))
			{
				while (getchar() != '\n')
					;
				printf("Team code already exists. Use \"u\" to update a team.\n");
			}
			else
			{
				while (getchar() != '\n')
					;
				printf("Enter team name: ");
				if (!fgets(teamName, NAMELEN + 1, stdin))
				{
					while (getchar() != '\n')
						;
					printf("Invalid team name. Team not added.\n");
				}
				else
				{
					teamName[strlen(teamName) - 1] = '\0';
					printf("Enter group seed: ");
					// Check group seed validity
					if (!fgets(groupSeed, 3, stdin) || toupper(groupSeed[0]) < 'A' || toupper(groupSeed[0]) > 'H' || groupSeed[1] < '1' || groupSeed[1] > '4')
					{
						while (getchar() != '\n')
							;
						printf("Invalid group seed. Team not added.\n");
					}
					else
					{
						while (getchar() != '\n')
							;
						groupSeed[0] = toupper(groupSeed[0]);
						groupSeed[2] = '\0';
						printf("Enter kit color: ");
						kitColor = toupper(getche());
						printf("\n");
						// Check color plate
						if (kitColor != 'R' && kitColor != 'O' && kitColor != 'Y' && kitColor != 'G' && kitColor != 'B' && kitColor != 'I' && kitColor != 'V')
						{
							printf("Invalid kit color. Team not added.\n");
						}
						else
						{
							// Insert the team
							teamList[teamCode] = createTeam(teamCode, teamName, groupSeed, kitColor);
							printf("Team added.\n");
						}
					}
				}
			}
			break;
		case 'S':
			// Search for a team
			printf("\nEnter team code: ");
			if (scanf("%d", &teamCode) != 1 || teamCode < 0 || teamCode > 31)
			{
				while (getchar() != '\n')
					;
				printf("Invalid team code.\n");
			}
			else
			{
				while (getchar() != '\n')
					;
				printf("\n%-20s%-24s%-20s%-12s\n", "Team Code", "Team Name", "Group Seed", "Kit Color");
				// Print the team with the given team code
				if (!printTeam(teamList, teamCode))
				{
					printf("Team not found.");
				}
				printf("\n");
			}
			break;
		case 'U':
			// update team information
			updated = 0;
			printf("\nEnter team code: ");
			if (scanf("%d", &teamCode) != 1 || teamCode < 0 || teamCode > 31)
			{
				while (getchar() != '\n')
					;
				printf("Invalid team code. Team not updated.\n");
			}
			// Check existence of the team
			else if (!isExist(teamList, teamCode))
			{
				while (getchar() != '\n')
					;
				printf("Team not found. Team not updated.\n");
			}
			else
			{
				while (getchar() != '\n')
					;
				printf("Enter team name (Current: %s): ", teamList[teamCode].teamName);
				if (!fgets(teamName, NAMELEN + 1, stdin))
				{
					while (getchar() != '\n')
						;
					printf("Invalid team name. Team not updated.\n");
				}
				else
				{
					teamName[strlen(teamName) - 1] = '\0';
					printf("Enter group seed (Current: %s): ", teamList[teamCode].groupSeed);
					if (!fgets(groupSeed, 3, stdin) || toupper(groupSeed[0]) < 'A' || toupper(groupSeed[0]) > 'H' || groupSeed[1] < '1' || groupSeed[1] > '4')
					{
						while (getchar() != '\n')
							;
						printf("Invalid group seed. Team not updated.\n");
					}
					else
					{
						while (getchar() != '\n')
							;
						groupSeed[0] = toupper(groupSeed[0]);
						groupSeed[2] = '\0';
						printf("Enter kit color (Current: %c): ", teamList[teamCode].kitColor);
						kitColor = toupper(getche());
						printf("\n");
						if (kitColor != 'R' && kitColor != 'O' && kitColor != 'Y' && kitColor != 'G' && kitColor != 'B' && kitColor != 'I' && kitColor != 'V')
						{
							printf("Invalid kit color. Team not updated.\n");
						}
						// Check if the team information is different from the existing team
						else if (!strcmp(teamList[teamCode].teamName, teamName) || !strcmp(teamList[teamCode].groupSeed, groupSeed) || teamList[teamCode].kitColor != kitColor)
						{
							teamList[teamCode] = createTeam(teamCode, teamName, groupSeed, kitColor);
							printf("Team updated.\n");
						}
						else
						{
							printf("No change is made.\n");
						}
					}
				}
			}
			break;
		case 'P':
			// Print all teams
			if (printTeamList(teamList))
			{
				printf("No teams in database. Use \"i\" to insert a new team.\n");
			}
			break;
		case 'Q':
			// Quit
			printf("\nThanks for using World Cup DBMS!\n");
			quit = 1;
			break;
		default:
			// Catch invalid input
			printf("\nInvalid operation code.\
			\n[Commands]: s (search), u(update), p(print), q(quit).\n");
			break;
		}
	}
}

// getche() reimplement of getch in coino.h, reads from keypress, echoes
// https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
int getche(void)
{
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}

// createTeam() creates a team struct with the given parameters
team createTeam(int teamCode, char teamName[NAMELEN + 1], char groupSeed[2], char kitColor)
{
	team newTeam;
	newTeam.teamCode = teamCode;
	strcpy(newTeam.teamName, teamName);
	strcpy(newTeam.groupSeed, groupSeed);
	newTeam.kitColor = kitColor;
	return newTeam;
}

// isExist() checks if a team with the given teamCode exists in the teamList
int isExist(team teamList[32], int teamCode)
{
	if (teamList[teamCode].teamCode == teamCode)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// printTeam() prints the team with the given teamCode
int printTeam(team teamList[32], int teamCode)
{
	if (!isExist(teamList, teamCode))
	{
		return 0;
	}
	else
	{
		// if the team exists, print it
		printf("%-20d%-24s%-20s", teamList[teamCode].teamCode, teamList[teamCode].teamName, teamList[teamCode].groupSeed);
		switch (teamList[teamCode].kitColor)
		{
		case 'R':
			printf("%-12s", "Red");
			break;
		case 'O':
			printf("%-12s", "Orange");
			break;
		case 'Y':
			printf("%-12s", "Yellow");
			break;
		case 'G':
			printf("%-12s", "Green");
			break;
		case 'B':
			printf("%-12s", "Blue");
			break;
		case 'I':
			printf("%-12s", "Indigo");
			break;
		case 'V':
			printf("%-12s", "Violet");
			break;
		}
		printf("\n");
		return 1;
	}
}

// printTeamList() prints all the teams in the teamList
int printTeamList(team teamList[32])
{
	int empty = 1;
	printf("\n%-20s%-24s%-20s%-12s\n", "Team Code", "Team Name", "Group Seed", "Kit Color");
	for (int i = 0; i < 32; i++)
	{
		if (printTeam(teamList, i))
		{
			empty = 0;
		}
	}
	printf("\n");
	return empty;
}
