# Specifications

*(The list should be extended)*

## Gameplay

Nene Quest is a 2D side-scrolling action game.
The player must go through a succession of levels which increase in difficulty (linear progression), with a unique boss at the end.

## Player

* Player character can move both horizontally and vertically
* Player character can jump (to dodge boars)
* Player character can attack
* Player character can change his weapon (available : sword, axe and bow with parabolic shot)
* Player character have a health bar
* Player *may* have some kind of special attack, like a bomb (ref. sword icons near healthbar) 
  + The special attack depend on the weapon hold by the player
* Player character can pick up items by touching them
* Player character can ride a horse. The horse increase the speed and act as a shield for the player (with a hidden lifebar)
* Player can change his weapon by picking an object (axe, sword1, sword2, bow). Each weapon has a specific range and efficacity.

## Enemies

* Regular enemies : 
  - Boars can run into you from front or behind and only use horizontal movements
  
* Boss
  - The final boss is a dragon with a short range of move and slow movements
  - Dragons can breath fire at player character (medium-range, must be dodged)
  - The player loses a certain amount of lifepoint when going inside the Dragon's hitbox

* Obstacles : 
  - ~~Wodden barrel can hurt you if you run into them~~ (No defined behaviour for barrels)

## Map

* Automatic horizontal scrolling
* Enemies and items follow a pattern defined by a level-design script

## Items

* Onigiri : heal the player (amount to be defined)
* Wood chests : give a random weapon or heal
* Saddle : ride a horse
