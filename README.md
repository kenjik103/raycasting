# Textured Raycaster

![Screen Recording 2025-01-29 at 10 10 26 PM](https://github.com/user-attachments/assets/f4d90924-514b-40d7-9cc7-634c36501156)

![Screen Recording 2024-08-25 at 2 05 35 PM](https://github.com/user-attachments/assets/2b517ee9-8c0e-47c3-b76a-80ef53cb8e89)


Built a texutred raycasting engine in C++ using Raylib for graphics. World is contained by a 2D array tilemap. Uses DDA (Digital differential analyzer) algorithm to calculate player's distance from walls. Texture mapping was done via LodePNG and a lot of math. LodePNG for decoding PNG texutres into color values, and math for mapping those colors onto walls.

---
#### Resources
[Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) A good starting point and pretty in depth overview of everything.

[DDA Algorithm](https://www.youtube.com/watch?v=NbSee-XM7WA&t=1425s) A much more in depth explanation of the DDA algorithm.
