# route-curvature

A small and flexible tool written in C to calculate the curvature of a route.

Takes space separated data file as input, but also includes python script to convert GPX in a readable format.
Output is a space separated data file as well, ready to be plotted by gnuplot or similar software.

## Usage
```
route-curvature [options] file

Options:
-s, --smoothness    number of points to calculate curvature from.
                    The more points, the smoother the output gets.
                    (Default value: 5)
-t                  treat input values as cartesic coordinates instead of
                    using mercator projection on geographic coordinates
-o, --output        output file
```

## How it works

TODO

# License

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar
  14 rue de Plaisance, 75014 Paris, France
 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
