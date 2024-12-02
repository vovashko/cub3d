# cub3d
you got cubed

To-dos:
- add 

- check the raycaster:
	- ensure it works as expected
	- need to finalize by checking which ray (vertical or horizontal) is closer to the wall texture

- refactoring and leaks
- find tester

Good things to add(aka bonus):
 - wall collision (i suppose it's a part of having the ray hit the wall and you not allowing a player to go through)
 - minimap (which is a pretty much a 2d representaition of what is happenign on the screen)
 - doors that open and close(exit?)
 - rotate with a mouse
 - sprite(if really want to but may be simpler than I think)


 Done:
	- file validation:
		- check for textures for files to be present (optional use the generic RGB to still keep the game running)
		- all configs should be present for C and F.
		- C and F accept only the color code in RGB range [0, 255]
		- the map should be there
		- checked for leaks

	- map creation:
		- Saving the map in the struct

	- map validation: 
		- ended up doing a different check with checking the chars around every space encountered in the map. if they are not surrounded by spaces or walls ('1') then the map is not correct.
		- for that had to also do normalization of the map, to add a leading space to check for cases when player is in the wall and there are no leading spaces
		- one starting player position based on which side player is facing (N,S,W,E)
		- no unexpected chars
		- map should be fully encircled by the walls, no newlines



