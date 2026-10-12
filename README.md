# Small-pray-predator-simulation

## In short
This is a simulation of 2 species, 'O' and 'X', 'O' run away from 'X', 'X' run away from it self, 'O' are attracted to other 'O's and attract 'X's, when a 'X' chatches a 'O', the 'O' became a 'X', when a 'O' are too close to a 'X', it spowns other 'O's.

## project resume
This is a small agent based simulation, with 2 species, the 'O' (pray), and the 'X' (predator), each member of the species is a element of a vector, the type of those vectors is 'Cell', a class defined in the library, the 'Cell' class has 7 attributes, row, column, row velocity, column velocity, a simbol ("simbolo" in italian, i wrote most of the words in italian), a Point p ("Point" is a struct define in the library with 2 attributes, row, and column) and a cooldown (every time the cooldown reaches 0 the pray can multiply creating clones of it self above and under it self).

I didn't use any graphics library, the simulation runs on a matrix MxM (with M defined under the libraries), every step i remove the old position from the map, 
