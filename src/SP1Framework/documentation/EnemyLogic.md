# Enemy Logic

The enemy is one part of the game that serves as a challenge to the player as they try to explore. Without enemies, the game would feel like a "find the exit" game, and in turn, not be fun to the player.

## Rules for enemies

- Enemies must obey collision laws
  > they cannot pass through supposed to be solid objects. This would actually mean that the enemies would be slightly more fair when compared with the player.

- Enemies must be solid; the player cannot walk through the enemy.

- Enemies must be defeatable.

- ~~Enemies must be able to pathfind~~

## The types of enemies

There are two types of enemies:

 - Melee
 - Stationary Ranged


They both have different reactions to the player.

## Behaviour

The enemies follow a set behaviour based on their type. They also have to follow the rules as stated above.

### Melee enemies
The melee enemies will try to move towards the player. The enemy will also have a small charge time before they attack, meaning that players have time to move out of the way before they get attacked.

### Stationary Ranged enemies
The stationary ranged enemies will stand still only when they are shooting. At other times, it will try to move to the 8-directions around the player to attack. Only when they are in one of the eight directions, they will attack (shoot) the player.
