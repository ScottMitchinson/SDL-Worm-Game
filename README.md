# SDL Worm Game with Physics and Pathfinding

A game created using SDL and C++ for a university project. The game contains Physics and Pathfinding that was coded from scratch, as part of the requirements.
This was my first experience of game logic and SDL. I had only used C++ a handful of times before this so code won't be perfect.

## Known Issues

### Hardcoded Values

This code features alot of Hardcoded values, such as the pathfinding map layout, screen sizes and texture names and locations.
Future university projects avoided this, however I have not come back to change this code just yet.

### Value Differences Between Physics and Pathfinding

Both the Pathfinding and the Physics were produced seperately from eachother, instead of together in one project.
Due to this the Physics used the screen pixels as part of the location of objects and the maths behind it.
Pathfinding used a 40x40 grid, so all the locations of the nodes on the grid had to be increased in size by 10 to match the size needed by the Physics.
