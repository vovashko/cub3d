# cub3d
you got cubed

To-dos:

- add file validation: 
	- check for textures for files to be present, otherwise swap for plain colors
	- all configs should be present for C and F.
	- C and F accept only the color code in RGB range [0, 255]
	- the map should be there, 
	- one starting player position based on which side player is facing (N,S,W,E)
	- no unexpected chars
- add map creation:
	- right now using a sample map, but it should be taken from file
	- check whether I skip the lines before the 1 and 0 or how it should be done
	- map should be fully encircled by the walls, no newlines
- check the raycaster:
	- ensure it works as expected
	- need to finalize by checking which ray (vertical or horizontal) is closer to the wall texture


Good things to add(aka bonus):
 - wall collision (i suppose it's a part of having the ray hit the wall and you not allowing a player to go through)
 - minimap (which is a pretty much a 2d representaition of what is happenign on the screen)
 - doors that open and close(exit?)
 - rotate with a mouse
 - sprite(if really want to but may be simpler than I think)