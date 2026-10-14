# Small-pray-predator-simulation

## In short
This is a simulation of 2 species, 'O' and 'X', 'O' run away from 'X', 'X' run away from it self, 'O' are attracted to other 'O's and attract 'X's, when a 'X' chatches a 'O', the 'O' became a 'X', when a 'O' are too close to a 'X', it spawns other 'O's.

## Agents small description
This is a small agent based simulation, with 2 species, the 'O' (pray), and the 'X' (predator), each member of the species is a element of a vector, the type of those vectors is 'Cell', a class defined in the library, the 'Cell' class has 7 attributes, row, column, row velocity, column velocity, a simbol ("simbolo" in italian, i wrote most of the words in italian), a Point p ("Point" is a struct define in the library with 2 attributes, row, and column) and a cooldown (every time the cooldown reaches 0 the pray can multiply creating clones of it self above and under it self).

## graphics 
I didn't use any graphics library, the simulation runs on a matrix MxM (with M defined under the libraries inclusion in the main), the 'O' are light blue while the 'X' are red, this effect is acived using the ANSI escape codes.

## pray-predator behavior 
There is a Cell metod called "CambiaDirezione" (ChangeDirection in english), that define the velocity, it calculate the best direction to minimize the sum of the distance from predators in a defined range, if there are no predator it calcolate the best direction to minimize the distance to the closest pray, both prays and predators go twords pray and run away from predators, the prays move every step of the simulation, the predators move every 2 steps.

## feedback
I’m self-taught, if you have any feedback, feel free to email me at "e.schiavocampo1@gmail.com"
