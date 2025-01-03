#!/bin/bash

echo "Running tests..."

echo "BAD MAPS:"
echo "Running: maps/bad/color_invalid_rgb.cub"
./cub3d maps/bad/color_invalid_rgb.cub
echo "Running: maps/bad/color_missing.cub"
./cub3d maps/bad/color_missing.cub
echo "Running: maps/bad/color_missing_ceiling_rgb.cub"
./cub3d maps/bad/color_missing_ceiling_rgb.cub
echo "Running: maps/bad/color_missing_floor_rgb.cub"
./cub3d maps/bad/color_missing_floor_rgb.cub
echo "Running: maps/bad/color_none.cub"
./cub3d maps/bad/color_none.cub
echo "Running: maps/bad/empty.cub"
./cub3d maps/bad/empty.cub
echo "Running: maps/bad/file_letter_end.cub"
./cub3d maps/bad/file_letter_end.cub
echo "Running: maps/bad/forbidden.cub" #says valid (maybe leave it as that)
./cub3d maps/bad/forbidden.cub
echo "Running: maps/bad/map_first.cub"
./cub3d maps/bad/map_first.cub
echo "Running: maps/bad/map_middle.cub"
./cub3d maps/bad/map_middle.cub
echo "Running: maps/bad/map_missing.cub"
./cub3d maps/bad/map_missing.cub
echo "Running: maps/bad/map_only.cub"
./cub3d maps/bad/map_only.cub
echo "Running: maps/bad/map_too_small.cub"
./cub3d maps/bad/map_too_small.cub
echo "Running: maps/bad/player_multiple.cub"
./cub3d maps/bad/player_multiple.cub
echo "Running: maps/bad/player_none.cub"
./cub3d maps/bad/player_none.cub
echo "Running: maps/bad/player_on_edge.cub"
./cub3d maps/bad/player_on_edge.cub
echo "Running: maps/bad/textures_dir.cub" #says valid (will be okay when check in check_format will be uncommented)
./cub3d maps/bad/textures_dir.cub
echo "Running: maps/bad/textures_duplicates.cub" #says valid (will be okay when check in check_format will be uncommented)
./cub3d maps/bad/textures_duplicates.cub
echo "Running: maps/bad/textures_forbidden.cub" #says valid (will be okay when check in check_format will be uncommented)
./cub3d maps/bad/textures_forbidden.cub
echo "Running: maps/bad/textures_invalid.cub" #says valid (will be okay when check in check_format will be uncommented)
./cub3d maps/bad/textures_invalid.cub
echo "Running: maps/bad/textures_missing.cub"  
./cub3d maps/bad/textures_missing.cub
echo "Running: maps/bad/textures_none.cub"
./cub3d maps/bad/textures_none.cub
echo "Running: maps/bad/textures_not_xpm.cub" #says valid (we're fine with it)
./cub3d maps/bad/textures_not_xpm.cub
echo "Running: maps/bad/wall_hole_east.cub"
./cub3d maps/bad/wall_hole_east.cub
echo "Running: maps/bad/wall_hole_north.cub"
./cub3d maps/bad/wall_hole_north.cub
echo "Running: maps/bad/wall_hole_south.cub" 
./cub3d maps/bad/wall_hole_south.cub
echo "Running: maps/bad/wall_hole_west.cub" 
./cub3d maps/bad/wall_hole_west.cub
echo "Running: maps/bad/wall_none.cub" 
./cub3d maps/bad/wall_none.cub

# echo "GOOD MAPS:"
# echo "Running: maps/good/cheese_maze.cub"
# ./cub3d maps/good/cheese_maze.cub
# echo "Running: maps/good/creepy.cub"
# ./cub3d maps/good/creepy.cub
# echo "Running: maps/good/dungeon.cub"
# ./cub3d maps/good/dungeon.cub
# echo "Running: maps/good/library.cub"
# ./cub3d maps/good/library.cub
# echo "Running: maps/good/matrix.cub"
# ./cub3d maps/good/matrix.cub
# echo "Running: maps/good/sad_face.cub"
# ./cub3d maps/good/sad_face.cub
# echo "Running: maps/good/square_map.cub"
# ./cub3d maps/good/square_map.cub
# echo "Running: maps/good/subject_map.cub"
# ./cub3d maps/good/subject_map.cub
# echo "Running: maps/good/test_map.cub"
# ./cub3d maps/good/test_map.cub
# echo "Running: maps/good/test_map_hole.cub"
# ./cub3d maps/good/test_map_hole.cub
# echo "Running: maps/good/test_pos_bottom.cub"
# ./cub3d maps/good/test_pos_bottom.cub
# echo "Running: maps/good/test_pos_left.cub"
# ./cub3d maps/good/test_pos_left.cub
# echo "Running: maps/good/test_pos_right.cub"
# ./cub3d maps/good/test_pos_right.cub
# echo "Running: maps/good/test_pos_top.cub"
# ./cub3d maps/good/test_pos_top.cub
# echo "Running: maps/good/test_textures.cub"
# ./cub3d maps/good/test_textures.cub
# echo "Running: maps/good/test_whitespace.cub"
# ./cub3d maps/good/test_whitespace.cub
# echo "Running: maps/good/works.cub"
# ./cub3d maps/good/works.cub