#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// MACROS SECTION //

#define MAXCLASSES 3
#define CLASSSTATS 3

// STRUCTS SECTION //

struct CharacterClass
{
    char class[21];

    int basehp;
    int mana;
    int attack_power;
};

struct Character
{
    char name[31];
    struct CharacterClass characterclass;
    int currenthp;
};

// FUNCTION PROTOTYPES //

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void class_initialization(char character_classes[][21], int class_stats[][3], struct CharacterClass characterclass[]);

void class_select(int classchoice, struct CharacterClass characterclass[], struct Character *character);

void display_class_info(struct Character *character);

// COMBAT FUNCTIONS //

void take_damage(int damage_amount, struct Character *character);

bool is_dead(const struct Character *character);

void heal(int heal_amt, struct Character *character);

void player_turn(int choice, struct Character *player, struct Character *enemy);

void enemy_turn(int choice, struct Character *player, struct Character *enemy);

void combat(struct Character *player, struct Character *enemy);

// MAIN SECTION //

int main()
{
    srand(time(NULL));
    printf("======================");
    printf("\n\n     MONSTER ARENA     \n\n");
    printf("======================");

    // DATA INITIALIZATION SECTION //

    struct Character player;
    struct Character enemy;

    struct Character *player_p = &player;
    struct Character *enemy_p = &enemy;

    char player_classes[MAXCLASSES][21] = {
        "Warrior",
        "Archer",
        "Mage"};

    int class_stats[][CLASSSTATS] = {
        {60, 35, 40},
        {80, 50, 25},
        {40, 100, 30}};

    char enemy_classes[MAXCLASSES][21] = {
        "Goblin",
        "Orc",
        "Troll"};

    int enemy_stats[][CLASSSTATS] = {
        {25, 0, 8},
        {120, 10, 43},
        {300, 280, 130}};

    struct CharacterClass characterclass[MAXCLASSES];
    class_initialization(player_classes, class_stats, characterclass);

    struct CharacterClass enemy_class[MAXCLASSES];
    class_initialization(enemy_classes, enemy_stats, enemy_class);

    printf("\n\n> Enter name: ");
    scanf("%s", player.name);
    printf("\n\n> Name: %s\n\n", player.name);

    int class_choice;
    printf("\n1. Warrior\n2. Archer\n3. Mage\n");
    printf("\n\n> Choose class: ");
    scanf("%d", &class_choice);

    class_select(class_choice, characterclass, player_p);
    display_class_info(player_p);

    int choice_enemy;
    printf("\n1. Goblin\n2. Orc\n3. Troll\n\n");
    printf("Choose your opponent: ");
    scanf("%d", &choice_enemy);

    class_select(choice_enemy, enemy_class, enemy_p);
    display_class_info(enemy_p);

    // CHARACTER COMBAT SECTION //

    combat(player_p, enemy_p);

    // TODO - IMPLEMENT GAME OVER AND LOOP //

    if (!is_dead(player_p))
    {
        printf("\nYou winn>_<\n\n");
    }
    else
    {
        printf("\nYou lose..\n");
        printf("\nTry again? (Y/N): \n\n");
    }

    return 0;
}

// FUNCTION DEFINITION //

void class_initialization(char character_classes[][21], int class_stats[][3], struct CharacterClass characterclass[])
{
    for (int i = 0; i < MAXCLASSES; i++)
    {
        strcpy(characterclass[i].class, character_classes[i]);
        characterclass[i].basehp = class_stats[i][0];
        characterclass[i].mana = class_stats[i][1];
        characterclass[i].attack_power = class_stats[i][2];
    }
}

void class_select(int classchoice, struct CharacterClass characterclass[], struct Character *character)
{
    character->characterclass = characterclass[classchoice - 1];
    character->currenthp = character->characterclass.basehp;
}

void display_class_info(struct Character *character)
{
    printf("\n\n===================");
    printf("\n       STATS      \n");
    printf("===================");
    printf("\n\n> Class: %s\n\n--------------------\n\n> Hp: %d\n\n> Mana: %d\n\n> Attack Power: %d\n\n--------------------\n", character->characterclass.class,
           character->currenthp, character->characterclass.mana, character->characterclass.attack_power);
}

void take_damage(int damage_amount, struct Character *character)
{
    character->currenthp -= damage_amount;
    character->currenthp = max(0, character->currenthp);
}

bool is_dead(const struct Character *character)
{
    if (character->currenthp == 0)
    {
        return true;
    }

    return false;
}

void heal(int heal_amt, struct Character *character)
{
    character->currenthp += heal_amt;
    character->currenthp = min(character->currenthp, character->characterclass.basehp);
}

void player_turn(int choice, struct Character *player, struct Character *enemy)
{
    switch (choice)
    {
    case 1:
        take_damage(player->characterclass.attack_power, enemy);
        printf("\nSuccessfully dealt %d damage", player->characterclass.attack_power);
        printf("\n> Enemy health: %d\n", enemy->currenthp);
        break;
    case 2:
        printf("\nYou blocked\n");
        break;
    case 3:
        heal(30, player);
        printf("\nSuccessfully healed..");
        printf("\n> Current Hp: %d\n", player->currenthp);
        break;
    case 4:
        printf("\nYou ran away from the fight...\n");
        printf("Automatic loss\n\n");
        break;
    default:
        break;
    }
}

void enemy_turn(int choice, struct Character *player, struct Character *enemy)
{
    switch (choice)
    {
    case 1:
        take_damage(enemy->characterclass.attack_power, player);
        printf("\nEnemy attacked!");
        printf("\n> Current Hp: %d\n", player->currenthp);
        break;
    case 2:
        printf("\nEnemy blocked..\n");
        break;
    }
}

void combat(struct Character *player, struct Character *enemy)
{
    int turn = 0;

    while (!is_dead(enemy) && !is_dead(player))
    {
        turn++;

        if (turn % 2)
        {
            int combat_choice;
            printf("\n1. Attack\n2. Block\n3. Heal\n4. Run away\n\n");
            printf("> ");
            scanf("%d", &combat_choice);

            player_turn(combat_choice, player, enemy);
        }
        else
        {
            int enemy_combat_choice;
            enemy_combat_choice = (rand() % (2 - 1 + 1)) + 1;

            enemy_turn(enemy_combat_choice, player, enemy);
        }
    }
}
