---
description: >-
  The program takes as a first argument a scene description file with the .cub
  extension
---

# Configuration file

### Base

* Except for the map, each element must begin with its type identifier (composed\
  by one or two characters), followed by its specific information in a strict order.

### Map

* Composed of only 6 possible characters:&#x20;
  * 0 : empty space
  * 1 : wall
  * N,S,E,W : player's start position and orientation
* Closed/Surrounded by walls, if not must return an error.

{% code title="Basic map" %}
```
111111
100101
101001
1100N1
111111
```
{% endcode %}

### Textures

Identifiers for the different wall textures depending on facing direction followed by they path.

* &#x20;NO : North

```
NO ./path_to_the_north_texture
```

* &#x20;SO : South

```
SO ./path_to_the_south_texture
```

* &#x20;WE : West

```
WE ./path_to_the_west_texture
```

* &#x20;EA : East

```
EA ./path_to_the_east_texture
```

### Floor & Ceiling&#x20;

Identifier for colors followed by 3 value separated by a comma range \[0,255] corresponding to RGB values.

* F : Floor

```
F 220,100,0
```

* &#x20;C : Ceiling

```
C 225,30,0
```

### File example

{% code title="config.cub" %}
```
NO ./textures/mossy.xpm
SO ./textures/greystone.xpm
WE ./textures/redbrick.xpm
EA ./textures/colorstone.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001			
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110110111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000000000000000001
10000000000000000001010010001
11000001110101011111011110W0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
{% endcode %}
