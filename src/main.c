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
    bool isblocking;
};

const struct CharacterClass PLAYERCLASSES[MAXCLASSES] = {
    {"Warrior", 60, 35, 40},
    {"Archer", 80, 50, 25},
    {"Mage", 40, 100, 30}};

const struct CharacterClass ENEMYCLASSES[MAXCLASSES] = {
    {"Goblin", 25, 0, 8},
    {"Orc", 120, 10, 43},
    {"Troll", 300, 280, 130}};

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

// GAME INITIALIZATION //

void class_select(int classchoice, const struct CharacterClass characterclass[], struct Character *character);

void player_class(struct Character *player);

void enemy_select(struct Character *enemy);

void initialize_game(struct Character *player, struct Character *enemy);

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
    bool is_alive = true;
    srand(time(NULL));

    while (is_alive)
    {
        printf(
            "======================\n"
            "\n"
            "     MONSTER ARENA\n"
            "\n"
            "======================\n");

        // DATA INITIALIZATION SECTION //

        struct Character player;
        struct Character enemy;

        struct Character *player_p = &player;
        struct Character *enemy_p = &enemy;

        initialize_game(player_p, enemy_p);

        // ACTIVE GAME LOOP //

        bool in_arena = true;

        while (in_arena)
        {
            // CHARACTER COMBAT SECTION //

            combat(player_p, enemy_p);

            // GAME OVER AND RESTART LOOP //

            if (is_dead(enemy_p))
            {
                printf("\nYou winn>_<\n\n");
                enemy_select(enemy_p);
                display_class_info(enemy_p);
            }
            else
            {
                is_alive = false;
                in_arena = false;

                printf("\nYou lose..\n");
                printf("\nTry again? (Y/N): ");

                char retry;
                scanf(" %c", &retry);

                if (retry == 'Y' || retry == 'y')
                {
                    is_alive = true;
                }
            }
        }
    }
    return 0;
}

// FUNCTION DEFINITION //

void class_select(int classchoice, const struct CharacterClass characterclass[], struct Character *character)
{
    character->characterclass = characterclass[classchoice - 1];
    character->currenthp = character->characterclass.basehp;
    character->isblocking = false;
}

void player_class(struct Character *player)
{
    int class_choice;
    printf("\n1. Warrior\n2. Archer\n3. Mage\n");
    printf("\n\n> Choose class: ");
    scanf("%d", &class_choice);

    class_select(class_choice, PLAYERCLASSES, player);
}

void enemy_select(struct Character *enemy)
{
    int choice_enemy;
    printf("\n1. Goblin\n2. Orc\n3. Troll\n\n");
    printf("Choose your opponent: ");
    scanf("%d", &choice_enemy);

    class_select(choice_enemy, ENEMYCLASSES, enemy);
}

void initialize_game(struct Character *player, struct Character *enemy)
{
    printf("\n\n> Enter name: ");
    scanf("%s", player->name);
    printf("\n\n> Name: %s\n\n", player->name);

    player_class(player);
    display_class_info(player);
    enemy_select(enemy);
    display_class_info(enemy);
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
    if (!character->isblocking)
    {
        character->currenthp -= damage_amount;
        character->currenthp = max(0, character->currenthp);
    }
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
    player->isblocking = false;

    switch (choice)
    {
    case 1:
        take_damage(player->characterclass.attack_power, enemy);
        printf("\nSuccessfully dealt %d damage", player->characterclass.attack_power);
        printf("\n> Enemy health: %d\n", enemy->currenthp);
        break;
    case 2:
        player->isblocking = true;
        printf("\nYou blocked\n");
        break;
    case 3:
        heal(30, player);
        printf("\nSuccessfully healed..");
        printf("\n> Current Hp: %d\n", player->currenthp);
        break;
    case 4:
        printf("\nYou ran away from the fight...\n");
        break;
    default:
        break;
    }
}

void enemy_turn(int choice, struct Character *player, struct Character *enemy)
{
    enemy->isblocking = false;

    switch (choice)
    {
    case 1:
        take_damage(enemy->characterclass.attack_power, player);
        printf("\nEnemy attacked!");
        printf("\n> Current Hp: %d\n", player->currenthp);
        break;
    case 2:
        enemy->isblocking = true;
        printf("\nEnemy blocked..\n");
        break;
    }
}

void combat(struct Character *player, struct Character *enemy)
{
    int turn = 0;
    bool isfighting = true;

    while (isfighting)
    {
        turn++;

        if (turn % 2)
        {
            int combat_choice;
            printf("\n1. Attack\n2. Block\n3. Heal\n4. Run away\n\n");
            printf("> ");
            scanf("%d", &combat_choice);

            player_turn(combat_choice, player, enemy);
            if (combat_choice == 4)
            {
                isfighting = false;
            }
        }
        else
        {

            int enemy_combat_choice;
            enemy_combat_choice = (rand() % (2 - 1 + 1)) + 1;

            enemy_turn(enemy_combat_choice, player, enemy);
        }

        if (is_dead(enemy) || is_dead(player))
        {
            isfighting = false;
        }
    }
}
