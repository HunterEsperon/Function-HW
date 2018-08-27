#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Character Types
#define _Player 0
#define _Enemy 1
//User Types]
#define _Archer 0
#define _Swordsmen 1
//Enemy Types
#define _Oger 0
#define _Witch 1
// Character Info Types
#define _Health 0
#define _Damage 1
#define _HealAmount 2
#define _NumberOfHeals 3
#define _Retreated 4
// Orders
#define _Attack 1
#define _Heal 2
#define _Retreat 3
// Bool
#define _False 0
#define _True 1

// X = Character Types, Y = Character Info Types
int Characters [2][5] = {{100, 20, 60, 5, _False}, {100, 20, 60, 5, _False}};
int Users [2][5] = {{30, 6, 15, 2, _False}, {40, 4, 15, 2, _False}};
int Enemies [2][5] = {{50, 8, 0, 0, _False}, {25, 5, 25, 5, _False}};

// Sets up Characters for Game
int SetupGame();
// Executes a order
void ExecuteOrder(int Character, int order);
// Character Deals Damage to another Character. returns damage done
int DealDamage(int attackingCharacter, int attackedCharacter);
// Heal Character
void Heal(int Character);
// Returns a random order
int GetOrder(int Character);

int main()
{
	system("cls");
	srand(time(NULL));

	int quitGame = _False;

	// Game Loop
	while(quitGame == _False)
	{
	  quitGame =	SetupGame();
		//printf("php %d ehp %d ahp %d\n", Characters[_Player][_Health], Characters[_Enemy][_Health], Users[_Archer][_Health]);
		// Combat loop
		while(Characters[_Player][_Health] > 0 && Characters[_Enemy][_Health] > 0 && Characters[_Player][_Retreated] == _False && Characters[_Enemy][_Retreated] == _False)
		{
			int playerOrder, enemyOrder = GetOrder(_Enemy);

			// Prints the player and enemy health
			puts("\n____________________________________________________________________");
			printf("\n\nPlayers Hp: %d\n", Characters[_Player][_Health]);
			for(int i = 0; i < Characters[_Player][_Health]; i++)
			{
				printf("%s", "*");
			}
			puts(" ");
			printf("\nEnemys Hp: %d\n", Characters[_Enemy][_Health]);
			for(int i = 0; i < Characters[_Enemy][_Health]; i++)
			{
				printf("%s", "*");
			}
			puts(" ");

			// Asks the player to choose a order
			printf("\n1. Attack \t| Base Damage: %d \n2. Heal \t| Heals: %d \n3. Retreat", Characters[_Player][_Damage], Characters[_Player][_NumberOfHeals]);
			printf("\n%s", "What do you want to do: ");
			scanf("%d", &playerOrder);

			// Executes the player and enemy orders
			puts("\n____________________________________________________________________");
			ExecuteOrder(_Player, playerOrder);
			ExecuteOrder(_Enemy, enemyOrder);
		}
		puts("\n____________________________________________________________________");
		printf("\nPlayers Hp: %d", Characters[_Player][_Health]);
		printf("\nEnemys Hp: %d\n", Characters[_Enemy][_Health]);
	}

	return 1;
}

int SetupGame()
{
	int userChoice = 0;
	puts("\n RPG Game");
	puts("____________________________________________________________________");
	puts("\n1. Archer \n2. Swordsmen \n3. Quit");
	printf("%s", "Pick your user: ");
	scanf("%d", &userChoice);

	switch(userChoice)
	{
		case 1: // Archer
			Characters[_Player][_Health] = Users[_Archer][_Health];
			Characters[_Player][_Damage] = Users[_Archer][_Damage];
			Characters[_Player][_HealAmount] = Users[_Archer][_HealAmount];
			Characters[_Player][_NumberOfHeals] = Users[_Archer][_NumberOfHeals];
			Characters[_Player][_Retreated] = Users[_Archer][_Retreated];
			break;
			case 2: // Swordsmen
			Characters[_Player][_Health] = Users[_Swordsmen][_Health];
			Characters[_Player][_Damage] = Users[_Swordsmen][_Damage];
			Characters[_Player][_HealAmount] = Users[_Swordsmen][_HealAmount];
			Characters[_Player][_NumberOfHeals] = Users[_Swordsmen][_NumberOfHeals];
			Characters[_Player][_Retreated] = Users[_Swordsmen][_Retreated];
		break;
		case 3:
			return _True;
		break;
	}

	puts("\n____________________________________________________________________");
	puts("\n1. Oger \n2. Witch");
	printf("%s", "Pick your user: ");
	scanf("%d", &userChoice);

	switch(userChoice)
	{
		case 1: // Oger
			Characters[_Enemy][_Health] = Enemies[_Oger][_Health];
			Characters[_Enemy][_Damage] = Enemies[_Oger][_Damage];
			Characters[_Enemy][_HealAmount] = Enemies[_Oger][_HealAmount];
			Characters[_Enemy][_NumberOfHeals] = Enemies[_Oger][_NumberOfHeals];
			Characters[_Enemy][_Retreated] = Enemies[_Oger][_Retreated];
			break;
		case 2: // Witch
			Characters[_Enemy][_Health] = Enemies[_Witch][_Health];
			Characters[_Enemy][_Damage] = Enemies[_Witch][_Damage];
			Characters[_Enemy][_HealAmount] = Enemies[_Witch][_HealAmount];
			Characters[_Enemy][_NumberOfHeals] = Enemies[_Witch][_NumberOfHeals];
			Characters[_Enemy][_Retreated] = Enemies[_Witch][_Retreated];
		break;
	}

	return _False;
}

void ExecuteOrder(int Character, int order)
{
	switch(order)
	{
		case _Attack:
			if(Character == _Player)
			{
				if(rand() % 10 > 2)
				{
					// Deal damage and prints damage
					printf("\nPlayer attacked. Dmg: %d", DealDamage(Character, _Enemy));
				}
				else
				{
					printf("\nPlayer missed. Dmg: %d", 0);
				}
			}
			else
			{
				if(rand() % 10 > 2)
				{
					// Deal damage and prints damage
					printf("\nEnemy attacked. Dmg: %d", DealDamage(Character, _Player));
				}
				else
				{
					printf("\nEnemy missed. Dmg: %d", 0);
				}
			}
		break;
		case _Heal:
			if(Characters[Character][_NumberOfHeals] > 0)
			{
				Heal(Character);
				if(Character == _Player)
				{
					printf("\nPlayer healed. Hp: %d", Characters[Character][_HealAmount]);
				}
				else
				{
					printf("\nEnemy healed. Hp: %d", Characters[Character][_HealAmount]);
				}
			}
			else
			{
				if(Character == _Player)
				{
					printf("%s %d\n", "No Heals left", Characters[Character][_NumberOfHeals]);
				}
			}

		break;
		case _Retreat:
		Characters[Character][_Retreated] = _True;
		break;
	}

	if(Characters[Character][_Retreated] == _True)
	{
		if(Character == _Player)
		{
			puts("As you turn to run you take an arrow to the knee and your life as an adventurer is over.");
		}
		else
		{
			puts("\nThe enemy turns away from you and runs.");
		}
	}
}

int DealDamage(int attackingCharacter, int attackedCharacter)
{
	int dmg = Characters[attackingCharacter][_Damage] + (rand() % 5 + 0);
	Characters[attackedCharacter][_Health] -= dmg;
	return dmg;
}

void Heal(int Character)
{
	Characters[Character][_Health] += Characters[Character][_HealAmount];
	Characters[Character][_NumberOfHeals] -= 1;
}

int GetOrder(int Character)
{
	int order = rand() % 5 + 1;

	switch(order)
	{
		case _Heal:
			if(Characters[Character][_NumberOfHeals] > 0 && (Characters[Character][_Health] < Characters[_Player][_Health] || Characters[Character][_Health] < 20))
			{
				return _Heal;
			}
			else
			{
				return _Attack;
			}
		break;
		case _Retreat:
			if(Characters[Character][_Health] < Characters[_Player][_Health] && Characters[Character][_Health] < 10)
			{
				return _Retreat;
			}
			else
			{
				return _Attack;
			}
		break;
		default:
			return _Attack;
	}

	printf("%s Order: %d\n", "Error: order not found returning Attack order", order);
	return _Attack;
}
