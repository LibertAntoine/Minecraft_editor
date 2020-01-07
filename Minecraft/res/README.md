
#  RBF file instructions

<p align="center">
  <img width="600" src="../Doc/Screenshots/RBF/rbf_3.png?raw=true">
</p>

## Where to put the configuration files
You must put the rbf files in `Minecraft/res/` in the current version of the program you can only have three different files and must either be called `rbf1.txt` `rbf2.txt` or `rbf3.txt`
## Syntax
The program make use of a parser to extract data out of the files.

### Boundaries
You must specify two boundaries, each represents one vertex of any diagonal spanning a cuboid shape that will restrain the generation area. If you specify more boundaries the parser will only keep the last two, and ignore the former.

To tell the parser that the next lines are boundaries simply write `#boundaries`

The coordinates are `x` `y` and `z` expressed in the world space.
```python
#boundaries
-10 0 0 <- this one gets ignored
10 20 0
50 0 10
```
### Control points
You can specify as many control points as you wish. These are a specified as a set of coordinates and the associated weight.

The coordinates are defined in the world space as `x` `y` and `z`.

The weight can be any real value.


To tell the parser that the next lines are boundaries simply write `#controlpoints`
```python
#controlpoints
0 0 0 -1
0 20 10 1.891
-50 30 0 10
```
### The radial function and parameter
The program implements the following 4 radial functions

![equation](https://latex.codecogs.com/gif.latex?%22useless%22%20%3A%20f%28x%29%3D%5Cepsilon%20x)

 ![equation](https://latex.codecogs.com/gif.latex?%22multiquadratic%22%20%3A%20f%28x%29%3D%5Csqrt%7B1&plus;%28%5Cepsilon%20x%29%5E2%7D)
 
 ![equation](https://latex.codecogs.com/gif.latex?%22gaussian%22%20%3A%20f%28x%29%3De%5E%7B-%28%5Cepsilon%20x%29%5E2%7D)
 
 and
 
 ![equation](https://latex.codecogs.com/gif.latex?%22inversequadratic%22%20%3A%20f%28x%29%3D%5Cfrac%7B1%7D%7B1&plus;%28%5Cepsilon%20x%29%5E2%7D)

The coordinates are defined in the world space as `x` `y` and `z`.

You can specify a value for ![equation](https://latex.codecogs.com/gif.latex?%5Cepsilon), it can be any real value. The default is "1.0" so it doesn't have any effect.

To tell the parser that the next line are boundaries simply write `#rbf`
```python
#rbf
inversequadratic 0.1
```
If you don't specify any radial function in the file, the parser will simply use `useless` with 1.0 as the default.
## Using probabilities for stochastic results
By default the program make use of randomization based on the scalar value. To disable this effect you can simply write `#noproba` anywhere in the file.
```python
#noproba
```
## Examples
You can find examples in [this directory](https://github.com/LibertAntoine/Minecraft_editor/tree/master/Doc/Screenshots/RBF) `Doc/Screenshots/RBF/`

![RBF file 6 results in the editor](../Doc/Screenshots/RBF/rbf_6.png?raw=true)
```python
#boundaries
5 10 5
-5 0 -5
#controlpoints
0 -5 0 7
-10 10 -10 -3
10 10 -10 -3
-10 10 10 -3
10 10 10 -3
#rbf
inversequadratic 1
```

![RBF file 7 results in the editor](../Doc/Screenshots/RBF/rbf_7.png?raw=true)
```python
#boundaries
-25 56 0
25 0 0
#controlpoints
0 -2 0 -1
15 0 0 13
-20 0 5 8
3 5 0 -2
7 5 0 -2
7 8 0 8
-3 5 0 -2
0 10 0 -1
0 14 0 -3
0 18 0 -1
3 15 0 6
3 7 0 13
-15 26 0 3
15 26 0 3
#rbf
gaussian 3.50
```
:smile: enjoy!
