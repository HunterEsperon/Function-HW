#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Character Types
#define _Player 0
#define _Enemy 1
// Stat Types
#define _Health 0
#define _Damage 1
#define _Heal 2
//Orders
#define _Attack 1
#define _HealthPotion 2
#define _Retreat 3
//bool
#define _False 0
#define _True 1

// X = Character Types, Y = Stat Types
int Characters [2][3] = {{100, 20, 60}, {100, 30, 60}};
//Did the player retreat
int PlayerRetreated = _False;

//executes order
void ExecuteOrder(int Character, int order);
//Character Deals Damage to another Character
void DealDamage(int attackingCharacter, int attackedCharacter);
//Heal Character
void Heal(int Character);
//returns a random order
int GetOrder();

int main()
{
	while(Characters[_Player][_Health] > 0 && Characters[_Enemy][_Health] && PlayerRetreated == _False)
	{
		int playerOrder, enemyOrder = GetOrder();

		printf("\nPlayers Hp: %d", Characters[_Player][_Health]);
		printf("\nEnemys Hp: %d", Characters[_Enemy][_Health]);

		puts("\n1. attack \n2. Heal \n3. Retreat");
		printf("%s", "What do you want to do: ");
		scanf("%d", &playerOrder);

		ExecuteOrder(_Player, playerOrder);
		ExecuteOrder(_Enemy, enemyOrder);
	}

	printf("\nPlayers Hp: %d", Characters[_Player][_Health]);
	printf("\nEnemys Hp: %d", Characters[_Enemy][_Health]);

	return 0;
}

void ExecuteOrder(int Character, int order)
{
	switch(order)
	{
		case _Attack:
			if(Character == _Player)
			{
				DealDamage(Character, _Enemy);
				printf("\nPlayer attacked. Dmg: %d", Characters[Character][_Damage]);
			}
			else
			{
				DealDamage(Character, _Player);
				printf("\nEnemy attacked. Dmg: %d", Characters[Character][_Damage]);
			}
		break;
		case _HealthPotion:
			Heal(Character);
			if(Character == _Player)
			{
				printf("\nPlayer healed. Hp: %d", Characters[Character][_Heal]);
			}
			else
			{
				printf("\nEnemy healed. Hp: %d", Characters[Character][_Heal]);
			}
		break;
		case _Retreat:
		PlayerRetreated = _True;
		break;
	}

	if(PlayerRetreated == _True)
	{
		puts("As you turn to run you take an arrow to the knee and your life as an adventurer is over.");
	}
}

void DealDamage(int attackingCharacter, int attackedCharacter)
{
	Characters[attackedCharacter][_Health] -= Characters[attackingCharacter][_Damage];
}

void Heal(int Character)
{
	Characters[Character][_Health] += Characters[Character][_Heal];
}

int GetOrder()
{
	srand(time(NULL));
	return rand() % 2 + 1;
}
