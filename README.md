**cub3d**  
*You got cubed.*

**Project Overview:**  
This project is a simple 3D raycasting game built using the MLX42 library. It simulates a first-person perspective in a maze-like environment, inspired by classic games like *Wolfenstein 3D*. The game renders walls with solid colors and enforces player collision with the environment.

**Key Features:**  
- **File Validation:**  
  - Ensures all texture files are present or defaults to RGB colors if missing.  
  - Requires all necessary configuration parameters, including floor (`F`) and ceiling (`C`) colors in the RGB range [0, 255].  
  - Validates the presence of a complete and properly formatted map.  

- **Map Handling:**  
  - The map is parsed and stored in a structured format.  
  - Validation ensures the map is fully enclosed by walls with no invalid characters.  
  - Handles player starting position based on direction (N, S, W, E).  
  - Normalizes the map to handle edge cases, preventing players from spawning inside walls.

- **Raycasting Engine:**  
  - Functional raycasting that renders the map using textures from MLX42.  
  - Basic wall collision implemented to prevent the player from moving out of bounds.  

- **Testing:**  
  - Integrated a tester as a Git submodule for consistent testing and validation.
