#!/bin/bash

echo "Running tests..."

echo "BAD MAPS:"
echo "Running: maps/bad/color_invalid_rgb.cub"
valgrind ./cub3d maps/bad/color_invalid_rgb.cub
echo "Running: maps/bad/color_missing.cub"
valgrind ./cub3d maps/bad/color_missing.cub
echo "Running: maps/bad/color_missing_ceiling_rgb.cub"
valgrind ./cub3d maps/bad/color_missing_ceiling_rgb.cub
echo "Running: maps/bad/color_missing_floor_rgb.cub"
valgrind ./cub3d maps/bad/color_missing_floor_rgb.cub
echo "Running: maps/bad/color_none.cub"
valgrind ./cub3d maps/bad/color_none.cub
echo "Running: maps/bad/empty.cub"
valgrind ./cub3d maps/bad/empty.cub
echo "Running: maps/bad/file_letter_end.cub"
valgrind ./cub3d maps/bad/file_letter_end.cub
echo "Running: maps/bad/forbidden.cub" #says valid (maybe leave it as that)
valgrind ./cub3d maps/bad/forbidden.cub
echo "Running: maps/bad/map_first.cub"
valgrind ./cub3d maps/bad/map_first.cub
echo "Running: maps/bad/map_middle.cub"
valgrind ./cub3d maps/bad/map_middle.cub
echo "Running: maps/bad/map_missing.cub"
valgrind ./cub3d maps/bad/map_missing.cub
echo "Running: maps/bad/map_only.cub"
valgrind ./cub3d maps/bad/map_only.cub
echo "Running: maps/bad/map_too_small.cub"
valgrind ./cub3d maps/bad/map_too_small.cub
echo "Running: maps/bad/player_multiple.cub"
valgrind ./cub3d maps/bad/player_multiple.cub
echo "Running: maps/bad/player_none.cub"
valgrind ./cub3d maps/bad/player_none.cub
echo "Running: maps/bad/player_on_edge.cub"
valgrind ./cub3d maps/bad/player_on_edge.cub
echo "Running: maps/bad/textures_dir.cub" #says valid (will be okay when check in check_format will be uncommented)
valgrind ./cub3d maps/bad/textures_dir.cub
echo "Running: maps/bad/textures_duplicates.cub" #says valid (will be okay when check in check_format will be uncommented)
valgrind ./cub3d maps/bad/textures_duplicates.cub
echo "Running: maps/bad/textures_forbidden.cub" #says valid (will be okay when check in check_format will be uncommented)
valgrind ./cub3d maps/bad/textures_forbidden.cub
echo "Running: maps/bad/textures_invalid.cub" #says valid (will be okay when check in check_format will be uncommented)
valgrind ./cub3d maps/bad/textures_invalid.cub
echo "Running: maps/bad/textures_missing.cub"  
valgrind ./cub3d maps/bad/textures_missing.cub
echo "Running: maps/bad/textures_none.cub"
valgrind ./cub3d maps/bad/textures_none.cub
echo "Running: maps/bad/textures_not_xpm.cub" #says valid (we're fine with it)
valgrind ./cub3d maps/bad/textures_not_xpm.cub
echo "Running: maps/bad/wall_hole_east.cub"
valgrind ./cub3d maps/bad/wall_hole_east.cub
echo "Running: maps/bad/wall_hole_north.cub"
valgrind ./cub3d maps/bad/wall_hole_north.cub
echo "Running: maps/bad/wall_hole_south.cub" 
valgrind ./cub3d maps/bad/wall_hole_south.cub
echo "Running: maps/bad/wall_hole_west.cub" 
valgrind ./cub3d maps/bad/wall_hole_west.cub
echo "Running: maps/bad/wall_none.cub" 
valgrind ./cub3d maps/bad/wall_none.cub

# echo "GOOD MAPS:"
# echo "Running: maps/good/cheese_maze.cub"
# valgrind ./cub3d maps/good/cheese_maze.cub
# echo "Running: maps/good/creepy.cub"
# valgrind ./cub3d maps/good/creepy.cub
# echo "Running: maps/good/dungeon.cub"
# valgrind ./cub3d maps/good/dungeon.cub
# echo "Running: maps/good/library.cub"
# valgrind ./cub3d maps/good/library.cub
# echo "Running: maps/good/matrix.cub"
# valgrind ./cub3d maps/good/matrix.cub
# echo "Running: maps/good/sad_face.cub"
# valgrind ./cub3d maps/good/sad_face.cub
# echo "Running: maps/good/square_map.cub"
# valgrind ./cub3d maps/good/square_map.cub
# echo "Running: maps/good/subject_map.cub"
# valgrind ./cub3d maps/good/subject_map.cub
# echo "Running: maps/good/test_map.cub"
# valgrind ./cub3d maps/good/test_map.cub
# echo "Running: maps/good/test_map_hole.cub"
# valgrind ./cub3d maps/good/test_map_hole.cub
# echo "Running: maps/good/test_pos_bottom.cub"
# valgrind ./cub3d maps/good/test_pos_bottom.cub
# echo "Running: maps/good/test_pos_left.cub"
# valgrind ./cub3d maps/good/test_pos_left.cub
# echo "Running: maps/good/test_pos_right.cub"
# valgrind ./cub3d maps/good/test_pos_right.cub
# echo "Running: maps/good/test_pos_top.cub"
# valgrind ./cub3d maps/good/test_pos_top.cub
# echo "Running: maps/good/test_textures.cub"
# valgrind ./cub3d maps/good/test_textures.cub
# echo "Running: maps/good/test_whitespace.cub"
# valgrind ./cub3d maps/good/test_whitespace.cub
# echo "Running: maps/good/works.cub"
# valgrind ./cub3d maps/good/works.cub