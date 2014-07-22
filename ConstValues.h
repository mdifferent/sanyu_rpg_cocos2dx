#ifndef __CONSTVALUES_H__
#define __CONSTVALUES_H__

static const int PLAYER_SPRITE_HEIGHT = 180;
static const int PLAYER_SPRITE_WIDTH = 200;
static const int TOP_BORDER_HEIGHT = 80;
static const char NAME_FONT[] = "Arial";
static const int NAME_FONT_SIZE = 20;
static const int MENU_FONT_SIZE = 20;
static const int HP_NUM_FONT_SIZE = 16;

static const char CELL_FONT[] = "Arial";
static const int CELL_FONT_SIZE = 25;
static const int CELL_WIDHT = 300;
static const int CELL_HEIGHT = 40;

static const int TOP_HP = 999;

static const float BACK_WIDTH = 461;
static const float BACK_HEIGHT = 327;
static const float BACK_LABEL_HEIGHT = 24;
static const char p_skill[] = "SKILL SELECT";
static const char p_item[] = "ITEM SELECT";

static const int SPECIAL_ATTACK_DURATION = 10;
static const int BUBBLE_SPEED = 50;
static const int BUBBLE_MAX_COUNT = 10;
static const float SPECIAL_TARGET_SCALE = 1.2f;
static const int BUBBLE_SUCCESS_HIT = 10;
static const int BUBBLE_FAILED_PERCENT = 0.05;

//Target type
static const char ENEMY_ONE[] = "敌方单体";
static const char ENEMY_ALL[] = "敌方全体";
static const char PLAYER_ONE[] = "我方单体";
static const char PLAYER_ALL[] = "我方全体";

//Bubble texture path
static const char BUBBLE_PLIST_PATH[] = "sanyu/animesanpuru65.plist";
static const char BUBBLE_TEXTURE_PATH[] = "sanyu/animesanpuru65.png";

//MainMenu file path
static const char MAINMENU_BG_PATH[] = "sanyu/mainmenu/titleback_1.png";
static const char MAINMENU_BTN_START_PATH[] = "sanyu/mainmenu/start.png";
static const char MAINMENU_BTN_LOAD_PATH[] = "sanyu/mainmenu/load.png";
static const char MAINMENU_BTN_EXTRA_PATH[] = "sanyu/mainmenu/extra.png";
static const char MAINMENU_BTN_SYSTEM_PATH[] = "sanyu/mainmenu/system.png";
static const char MAINMENU_BTN_EXIT_PATH[] = "sanyu/mainmenu/exit.png";
static const char MAINMENU_BTN_CG_PATH[] = "sanyu/mainmenu/cg.png";
static const char MAINMENU_BTN_MUSIC_PATH[] = "sanyu/mainmenu/music.png";
static const char MAINMENU_BTN_REWARD_PATH[] = "sanyu/mainmenu/reward.png";

//Monsters file path
static const char MONSTER1_PATH[] = "sanyu/monsters/monster_1.png";
static const char MONSTER2_PATH[] = "sanyu/monsters/monster_2.png";

#endif