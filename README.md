# README
This program is my independent homework project for CS220: Intermediate Programming. I received 97.5% on this project. It is a program that takes intuitive and human-readable command and automatically paint an image. In short, it is like the drawing program on Windows. The difference is that the user would pre-specify your commands in a text file instead of interacting with a graphical UI.

# To start
The cs220_paint program takes two command line arguments. The first is the filename of the command file, and the second is the filename of the output image file to create. As an example, the following invocation would process the commands in cmd/test.txt to produce the image file img/test_out.txt:

`$ ./cs220_paint cmd/test.txt img/test_out.txt`

I also developed a `txt2png` tool that would help the user visualize it. For example:

`./txt2png img/test_out.txt png/test_out.png`

# Supporting functionalities
The cs220_paint program reads a graphics command file and generates an image file with the result of rendering the drawing operations specified in the command file. The commands which this program supports include:
- c: set drawing color, followed by three integers (RGB)
- r: draw a filled rectangle, followed by the coordinates of the upper left corner and the width and height of the rectangle
- e: draw a filled ellipse, followed by the coordinates of the two focal points
- f: perform a flood fill operation, followed by the coordinates of the starting pixel

# Demo
Here's an example command file:
```
320 240
c 0 200 200
r 100 80 140 96
c 72 0 128
e 160.0 75.0 26.7 175.1 344.9
c 212 212 0
r 180 180 44 4
r 220 160 44 4
r 180 200 84 4
r 180 180 4 24
r 220 160 4 24
r 260 160 4 44
c 208 167 0
f 251 168
e 120 3 309 86 440
```
The resulting image:

![image](https://jhu-ip.github.io/cs220-s22/assign/img/test.png)

