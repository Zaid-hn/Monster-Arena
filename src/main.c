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
    int basemana;
    int baseattackpower;
};

struct Character
{
    const struct CharacterClass *characterclass;

    int maxhp;
    int currenthp;

    int attack_power;
    int mana;

    bool isblocking;
};

struct Player
{
    char name[31];
    struct Character character;

    int level;
    int xp;
    int level_xp;
    int stat_points;
};

struct Enemy
{
    struct Character character;

    int xp_reward;
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

void display_classes(const struct CharacterClass classes[]);

void display_stats(struct Character *character);

void display_stat_points(struct Player *player);

void initialize_character(const struct CharacterClass characterclass[], struct Character *character);

void player_select(struct Player *player);

void enemy_select(struct Enemy *enemy);

void get_player_name(struct Player *player);

void initialize_game(struct Player *player, struct Enemy *enemy);

void display_char_info(struct Character *character);

// COMBAT FUNCTIONS //

void take_damage(int damage_amount, struct Character *character);

bool is_dead(const struct Character *character);

void heal(int heal_amt, struct Player *palyer);

void character_attack(struct Character *attack_char, struct Character *char2);

void player_attack(struct Player *player, struct Enemy *enemy);

void enemy_attack(struct Enemy *enemy, struct Player *player);

int player_action();

int enemy_action();

bool player_turn(struct Player *player, struct Enemy *enemy);

void enemy_turn(struct Player *player, struct Enemy *enemy);

void combat(struct Player *player, struct Enemy *enemy);

// EXPERIENCE SYSTEM //

void give_xp(struct Player *player, struct Enemy *enemy);

void level_up(struct Player *player);

int *select_stat(struct Player *player);

void spend_stat_points(struct Player *player, int *stat);

void increase_stats(struct Player *player);

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

        struct Player player;
        struct Enemy enemy;

        struct Player *player_p = &player;
        struct Enemy *enemy_p = &enemy;

        initialize_game(player_p, enemy_p);

        // ACTIVE GAME LOOP //

        bool in_arena = true;

        while (in_arena)
        {
            // CHARACTER COMBAT SECTION //

            combat(player_p, enemy_p);

            // GAME OVER AND RESTART LOOP //

            if (is_dead(&(enemy_p->character)))
            {
                printf("\nYou winn>_<\n\n");

                give_xp(player_p, enemy_p);
                level_up(player_p);

                enemy_select(enemy_p);
                display_char_info(&(enemy_p->character));
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

void display_classes(const struct CharacterClass classes[])
{
    for (int i = 0; i < 3; i++)
    {
        printf("\n%d. %s", i + 1, classes[i].class);
    }
}

void display_stats(struct Character *character)
{
    printf("\n\n1. Hp: %d\n\n2. Mana: %d\n\n3. Attack Power: %d\n\n", character->currenthp, character->mana, character->attack_power);
}

void display_stat_points(struct Player *player)
{
    printf("Current stat points: %d", player->stat_points);
}

int select_class()
{
    int class_choice;

    printf("\n\n> Choose class: ");
    scanf("%d", &class_choice);

    return class_choice;
}

void initialize_character(const struct CharacterClass characterclass[], struct Character *character)
{
    int classchoice = select_class();

    character->characterclass = &characterclass[classchoice - 1];

    character->maxhp = characterclass[classchoice - 1].basehp;
    character->currenthp = characterclass[classchoice - 1].basehp;

    character->mana = characterclass[classchoice - 1].basemana;
    character->attack_power = characterclass[classchoice - 1].baseattackpower;

    character->isblocking = false;
}

void player_select(struct Player *player)
{
    display_classes(PLAYERCLASSES);
    initialize_character(PLAYERCLASSES, &(player->character));

    player->level = 1;
    player->xp = 0;
    player->level_xp = 40;
    player->stat_points = 0;
}

void enemy_select(struct Enemy *enemy)
{
    display_classes(ENEMYCLASSES);
    initialize_character(ENEMYCLASSES, &(enemy->character));

    enemy->xp_reward = 20;
}

void get_player_name(struct Player *player)
{
    printf("\n\n> Enter name: ");
    scanf("%s", player->name);
    printf("\n\n> Name: %s\n\n", player->name);
}

void initialize_game(struct Player *player, struct Enemy *enemy)
{
    get_player_name(player);

    player_select(player);
    display_char_info(&(player->character));
    enemy_select(enemy);
    display_char_info(&(enemy->character));
}

void display_char_info(struct Character *character)
{
    printf("\n\n===================");
    printf("\n       STATS      \n");
    printf("===================");
    printf("\n\n> Class: %s\n\n--------------------\n\n> Hp: %d\n\n> Mana: %d\n\n> Attack Power: %d\n\n--------------------\n", character->characterclass->class,
           character->currenthp, character->mana, character->attack_power);
}

// ------------------------------------------------------- //

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

void heal(int heal_amt, struct Player *player)
{
    player->character.currenthp += heal_amt;
    player->character.currenthp = min(player->character.currenthp, player->character.maxhp);
}

void character_attack(struct Character *attack_char, struct Character *char2)
{
    take_damage(attack_char->attack_power, char2);
}

void player_attack(struct Player *player, struct Enemy *enemy)
{
    character_attack(&(player->character), &(enemy->character));
}

void enemy_attack(struct Enemy *enemy, struct Player *player)
{
    character_attack(&(enemy->character), &(player->character));
}

int player_action()
{
    int combat_choice;
    printf("\n1. Attack\n2. Block\n3. Heal\n4. Run away\n\n");
    printf("> ");
    scanf("%d", &combat_choice);

    return combat_choice;
}

int enemy_action()
{
    int enemy_combat_choice;
    enemy_combat_choice = (rand() % (2 - 1 + 1)) + 1;

    return enemy_combat_choice;
}

bool player_turn(struct Player *player, struct Enemy *enemy)
{
    player->character.isblocking = false;
    bool continue_combat = true;

    int choice = player_action();

    switch (choice)
    {
    case 1:
        player_attack(player, enemy);
        printf("\nSuccesfully hit\n");
        break;
    case 2:
        player->character.isblocking = true;
        printf("\nYou blocked\n");
        break;
    case 3:
        heal(30, player);
        printf("\nSuccessfully healed..");
        printf("\n> Current Hp: %d\n", player->character.currenthp);
        break;
    case 4:
        continue_combat = false;
        printf("\nYou ran away from the fight...\n");
        break;
    default:
        break;
    }

    return continue_combat;
}

void enemy_turn(struct Player *player, struct Enemy *enemy)
{
    enemy->character.isblocking = false;

    int choice = enemy_action();

    switch (choice)
    {
    case 1:
        enemy_attack(enemy, player);
        printf("\nEnemy attacked!");
        printf("\n> Current Hp: %d\n", player->character.currenthp);
        break;
    case 2:
        enemy->character.isblocking = true;
        printf("\nEnemy blocked..\n");
        break;
    }
}

void give_xp(struct Player *player, struct Enemy *enemy)
{
    player->xp += enemy->xp_reward;
}

void combat(struct Player *player, struct Enemy *enemy)
{
    int turn = 0;
    bool isfighting = true;

    while (isfighting)
    {
        turn++;

        if (turn % 2)
        {
            isfighting = player_turn(player, enemy);
        }
        else
        {
            enemy_turn(player, enemy);
        }

        if (is_dead(&(enemy->character)) || is_dead(&(player->character)))
        {
            isfighting = false;
        }
    }
}

void level_up(struct Player *player)
{
    if (player->xp == player->level_xp)
    {
        printf("> Level Up!!\n\n");

        player->level++;
        player->xp -= player->level_xp;
        player->stat_points += 10;
        player->level_xp *= 2;
        increase_stats(player);
    }
}

int *select_stat(struct Player *player)
{
    int choice_stat;
    scanf("%d", &choice_stat);

    switch (choice_stat)
    {
    case 1:
        return &(player->character.maxhp);
        break;

    case 2:
        return &(player->character.mana);
        break;

    case 3:
        return &(player->character.attack_power);
        break;

    default:
        return 0;
        break;
    }
}

void spend_stat_points(struct Player *player, int *stat)
{
    int invest_points;
    scanf("%d", &invest_points);

    if (!(invest_points > player->stat_points))
    {
        if (!(stat == NULL))
        {
            *stat += invest_points;
            printf("\nStat increased by %d", invest_points);

            player->stat_points -= invest_points;
        }
        else
        {
            printf("\nInvalid stat\n");
        }
    }
    else
    {
        printf("Not enough stat points!!");
    }
}

void increase_stats(struct Player *player)
{
    display_stats(&(player->character));

    printf("\nChoose stat: ");
    int *stat = select_stat(player);

    display_stat_points(player);

    printf("\nSpend stat points: ");
    spend_stat_points(player, stat);
}
