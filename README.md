# route-curvature

A small and flexible tool written in C to calculate the curvature of a route.

Takes space separated data file as input, but also includes python script to convert GPX in a readable format.
Output is a space separated data file as well, ready to be plotted by gnuplot or similar software.

## Installation

```
$ git clone https://github.com/bluntphenomena/route-curvature.git
$ cd route-curvature
$ make
```

## Usage

```
route-curvature [options] -i file

Options:
-h, --help          prints this help message and exit
-s, --smoothness    number of points to calculate curvature from.
                    The more points, the smoother the output gets.
                    (Default value: 5)
-t                  treat input values as cartesic coordinates instead of
                    using mercator projection on geographic coordinates
-i, --input         input file
-o, --output        output file
```

### Example

```
$ ./route-curvature -s10 -i examples/maglev.dat -o examples/maglev_out.dat
$ gnuplot
gnuplot> plot "examples/maglev_out.dat" using 1:2 with lines
```

![graph](https://raw.githubusercontent.com/bluntphenomena/route-curvature/master/examples/maglev_graph.png)

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
