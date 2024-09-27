# Custom Raycaster

![Screen Recording 2024-08-25 at 2 05 35 PM](https://github.com/user-attachments/assets/2b517ee9-8c0e-47c3-b76a-80ef53cb8e89)


Built a raycasting engine in C++ using the SFML library. World is contained by a 2D array tilemap. Uses DDA (Digital differential analyzer) algorithm to calculate player's distance from walls. Used articles and videos for refrence, but the code and math was done 100% by yours truly 😛. I've added the excecutable (*./cmake-smfl-project/cmake-build-debug/bin/main*) if you want to try running it yourself. The code and CMake file are here as well, but setting up SFML is super finiky so no promises there. Was a super fun project overall and I've linked the resources I found helpful if anyone wants to give it a go

---
#### Resources
[Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) A good starting point and pretty in depth overview of everything.

[DDA Algorithm](https://www.youtube.com/watch?v=NbSee-XM7WA&t=1425s) A much more in depth explanation of the DDA algorithm.
