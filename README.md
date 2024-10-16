# Pathfinding with Multiple Agents using A* Algorithm

## About the Project

This project focuses on implementing pathfinding for multiple agents using the A* algorithm. It introduces additional behaviors such as alignment and separation to ensure coherence between agents with minimal impact on their objective direction.

[Watch agents in action](https://www.youtube.com/watch?v=YourVideoLink1)

- **Separation Impact:** 5%
- **Alignment Impact:** 20%

The project aims to create a balance between maintaining individual agent objectives and group coherence, which is essential in scenarios with a high number of agents.

## Features

- **Multi-agent Pathfinding:** Efficient pathfinding for a large number of agents using A*.
- **Dynamic Obstacles:** Ability to add walls and obstacles during runtime.
- **Behavioral Cohesion:** Integration of alignment and separation behaviors.

## Controls

- **Left Click:** Set the objective for the agents.
- **Right Click:** Place a wall that cannot be overtaken by the agents.
- **Wall Placement:** Walls can be dynamically added at runtime to modify paths.
- **A/Q:** Shows A* Path

## Possible Improvements

- **Detailed Collisions:** Improve the collision detection between agents and the environment.
- **Enhanced Grouping:** Create smoother grouping behaviors when agents reach their final location.
- **Dynamic Grid Scaling:** Use a larger grid for open spaces and a smaller one for confined areas to optimize calculations.

## Challenges & Questions

### How to Handle Fog of War in Pathfinding?

- **Dynamic Exploration:** Actors can use a pathfinding algorithm like Depth-First Search (DFS) to explore unknown areas of the map. They generate their own pathfinding grid that updates dynamically as they encounter obstacles.
- **Knowledge Sharing:** When multiple actors progress as a group, they can share their discoveries with each other, collectively building a more accurate representation of the environment. This collaborative knowledge helps them adapt their paths more efficiently to avoid obstacles and find objectives.


### Attacking the Enemy Base with Turrets or Troops Present

- **Solution:** Implement a cost system for tiles on the grid. Tiles near weapons would have a higher cost, encouraging agents to avoid these areas. The tile values should be dynamically adjusted at runtime to reflect changing conditions on the battlefield.


## Screenshots of Performance (FPS)

Below are the screenshots showing the performance of the pathfinding algorithm with different numbers of agents in the environment:

- **1 Agent:**

  ![image](https://github.com/user-attachments/assets/8abb13f7-8b1c-4f9c-89aa-ec0116c36ecd)

- **10 Agents:**

  ![image](https://github.com/user-attachments/assets/8fc45bb7-dcc6-467a-b6b4-732951beef52)

- **100 Agents:**

  ![image](https://github.com/user-attachments/assets/2942bb8a-e96c-42d5-a57b-959b46153715)

- **500 Agents:**

  ![image](https://github.com/user-attachments/assets/bfd2cda4-0ef9-43b0-a90d-7bef02f88952)
