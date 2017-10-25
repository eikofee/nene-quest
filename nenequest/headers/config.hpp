#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Window/Keyboard.hpp>
#include <stdlib.h>
using namespace sf;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Player Controls 
//
//CKB : Controls KeyBoard
const Keyboard::Key CKB_P1_MOVE_UP = Keyboard::Up;
const Keyboard::Key CKB_P1_MOVE_DOWN = Keyboard::Down;
const Keyboard::Key CKB_P1_MOVE_LEFT = Keyboard::Left;
const Keyboard::Key CKB_P1_MOVE_RIGHT = Keyboard::Right;
const Keyboard::Key CKB_P1_ATTACK = Keyboard::Space;
const Keyboard::Key CKB_P1_JUMP = Keyboard::Unknown;	//TODO
const Keyboard::Key CKB_P1_SPECIAL = Keyboard::Unknown;	//TODO
const Keyboard::Key CKB_P1_PAUSE = Keyboard::Unknown;	//TODO

const Keyboard::Key CKB_P2_MOVE_UP = Keyboard::Z;		//Beware : AZERTY layout
const Keyboard::Key CKB_P2_MOVE_DOWN = Keyboard::S;
const Keyboard::Key CKB_P2_MOVE_LEFT = Keyboard::Q;		//Beware : AZERTY layout
const Keyboard::Key CKB_P2_MOVE_RIGHT = Keyboard::D;
const Keyboard::Key CKB_P2_ATTACK = Keyboard::A;		//Beware : AZERTY layout
const Keyboard::Key CKB_P2_JUMP = Keyboard::Unknown;	//TODO
const Keyboard::Key CKB_P2_SPECIAL = Keyboard::Unknown;	//TODO
const Keyboard::Key CKB_P2_PAUSE = Keyboard::Unknown;	//TODO

const Keyboard::Key CKB_MENU_ENTER = Keyboard::Return;

//CGP : Controls GamePad
//soon

///////////////////////////////////////////////////////////////////////////////
// Settings
//
// DSP : Display
const int DSP_FPS_LIMIT = 60;
const int DSP_RESOLUTION = 1080;	// Choose either 1080 or 720
const bool DSP_FULLSCREEN = false;
///////////////////////////////////////////////////////////////////////////////
// External Resources
//
// GFP : Game File Paths
const string GFP_LEVEL_FOLDER_PATH = "levels";

// GSP : Game Sprite Paths
const string GSP_PROJ_ARROW = "img/weapon_arrow.png";
const string GSP_PROJ_FLAME = "img/icon_fire.png";

const string GSP_EFFECT_ARROW_IMPACT = "img/icon_damage.png";

const string GSP_PLAYER_P1 = "img/player1.png";
const string GSP_PLAYER_P2 = "img/player2.png";

const string GSP_ENEMY_BOAR = "img/enemy_boar_anim.png";
const string GSP_ENEMY_DRAGON = "img/enemy_dragon.png";

const string GSP_WEAPON_BOW = "img/weapon_bow.png";
const string GSP_WEAPON_AXE = "img/weapon_axe.png";
const string GSP_WEAPON_SWORD = "img/weapon_sword.png";
const string GSP_WEAPON_GREATSWORD = "img/weapon_sword2.png";

const string GSP_ITEM_ONIGIRI = "img/item_onigiri.png";

const string GSP_BREAKABLE_CHEST = "img/obj_chest.png";
const string GSP_BREAKABLE_BARREL = "img/obj_barrel.png";

const string GSP_OBST_BRIDGE = "img/background_bridge.png";

const string GSP_UI_HEALTHBAR_P1_ICON = "img/icon_p1.png";
const string GSP_UI_HEALTHBAR_P2_ICON = "img/icon_p2.png";
const string GSP_UI_TITLESCREEN_TITLE = "img/titlescreen.png";
const string GSP_UI_TITLESCREEN_CURSOR = "img/cursor.png";

// TTF : Fonts
const string TTF_JAPF = "fonts/JapanSans100.ttf";
///////////////////////////////////////////////////////////////////////////////
// Game Modifiers
//
//DMG : Damage Modifiers
const int DMG_ARROW = 1;
const int DMG_BOAR = 1;

//HP : Initial HP
const int HP_PLAYER = 100;

//MS : Move Speed
#endif