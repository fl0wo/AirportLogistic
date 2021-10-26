# AirportLogistic
C++ SFML Dijkstra Geometrical Project


# Dijkstra-Simulator

<div id="top"></div>

[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<p align="middle">
  <img src="https://github.com/fl0wo/AirportLogistic/blob/main/input_files/ezgif1.gif" width="350" height="350"/>
  <img src="https://github.com/fl0wo/AirportLogistic/blob/main/input_files/ezgif2.gif" width="350" height="350"/>
</p>

<p align="middle">
Many airports have moving conveyor belts in the corridors between halls and terminals. Instead of walking on the floor, passengers can choose to stand on a conveyor or, even better, walk on a conveyor to get to the end of the corridor much faster. The brand new Delft City Airport uses a similar system. However, in line with the latest fashion in airport architecture, there are no corridors: the entire airport is one big hall with a bunch of conveyor lines laid out on the floor arbitrarily. To get from a certain point A to a certain point B, a passenger can use any combination of walking on the floor and walking on conveyors. Passengers can hop on or off a conveyor at any point along the conveyor. It is also possible to cross a conveyor without actually standing on it.Walking on the floor goes at a speed of 1 meter/second.Walking forward on a conveyor goes at a total speed of 2 meter/second.Walking in reverse direction on a conveyor is useless and illegal, but you may walk on the floor immediately next to the conveyor. (Conveyors are infinitely thin.) How fast can you get from A to B?
</p>

### Built With

It's a pure C++ project. I've used a graphic library called SFML, really easy to use!

* See the documentation at [SFML](https://www.sfml-dev.org/)

<!-- GETTING STARTED -->
## Getting Started

Just clone the repository, install the following library, and run it in your IDE.
*Change C:/CLibraries/SFML with your SFML location path inside CMakeLists.txt
@DockerFile incoming soon anyway.

### Prerequisites

You only need to install one librabry to make it work:
* Installation guide: [SFML](https://www.sfml-dev.org/tutorials/2.5/start-vc.php)

### Geometric
Something magic is happening when 30° are hitten by the intersect line and the conveyor one.
* Explanation (todo)
<p align="middle">
<img src="https://github.com/fl0wo/AirportLogistic/blob/main/input_files/30degree_funny.gif" width="300" height="300"/>
</p>
<!-- ROADMAP -->
## Roadmap

- [x] Add Animation

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

<!-- MARKDOWN LINKS & IMAGES -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/florian-sabani/
