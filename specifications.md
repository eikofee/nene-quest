# Specifications

*(The list should be extended)*

## Minimum game

The first goal: a game that can be played from start to finish.

1. One or two players walk through one scrolling level, fighting boars,
   breaking chests and picking up weapons and onigiris.
2. The scrolling stops in an arena where the dragon waits.
3. Killing the dragon shows a victory screen. Losing all health shows the
   game over screen.

Everything else in this file comes after that.

## Gameplay

Nene Quest is a 2D side-scrolling action game.
The player goes through a level and fights a unique boss at the end.

## Player

* Player character can move both horizontally and vertically
* Player character can attack
* Player character can change his weapon (available : sword, axe and bow with parabolic shot)
* Player character have a health bar
* Player character can pick up items by touching them
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

## Later

Ideas kept for after the minimum game works:

* Several levels of increasing difficulty (linear progression), with the
  boss at the end of the last one
* Player character can jump (to dodge boars). This was implemented, then
  removed.
* Player *may* have some kind of special attack, like a bomb (ref. sword icons near healthbar) 
  + The special attack depend on the weapon hold by the player
* Player character can ride a horse. The horse increase the speed and act as a shield for the player (with a hidden lifebar)
* Saddle (item) : ride a horse
