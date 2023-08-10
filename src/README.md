# FMX Modelling
## Contributors : Anubhab Ray and Manish Kumawat
# Controls
The idea behind controlling the nodes is that we've a
different color for the currently selected node of the model
which we can change using some keys. We can rotate the currently
selected node only in the direction in which it has dof.
The controls are as follows:

## Camera Movements

### Translation
* W for movement along -ve z-axis
* S for movement along +ve z-axis
* A for movement along -ve x-axis
* D for movement along +ve x-axis
* PAGE_UP for movement along +ve y-axis
* PAGE_DOWN for movement along -ve y-axis  

### Scene Rotation
* UP_ARROW for clockwise along x-axis
* DOWN_ARROW for counter-clockwise along x-axis
* LEFT_ARROW for counter-clockwise along y-axis
* RIGHT_ARROW for clockwise along y-axis
* LEFT_BRACKET for counter-clockwise along z-axis
* RIGHT_BRACKET for clockwise along z-axis


## Global Model Controls

Movements and rotations are w.r.t to the axis of the model

### Translation

* T for movement along -ve z-axis
* G for movement along +ve z-axis
* F for movement along -ve x-axis
* H for movement along +ve x-axis
* R for movement along +ve y-axis
* Y for movement along -ve y-axis  

### Rotation 
This is just rotating the root of the tree which is the
first selected node.

## Local Model Controls

### Switching Models
* 1 for previous model
* 2 for next model

### Switching between parts of a model
* q for prev part
* e for next part

### Rotation
* K for clockwise along x-axis
* I for counter-clockwise along x-axis
* U for counter-clockwise along y-axis
* O for clockwise along y-axis
* J for counter-clockwise along z-axis
* L for clockwise along z-axis

# Tree hierarchies 
## Bike
![Bike Tree](/src/screenshots/Bike-Tree.jpeg)
## Rider
![Rider Tree](/src/screenshots/Rider-Tree.jpeg)

# Screenshots

## Bike wireframe
![Bike wireframe](/src/screenshots/Bike-(Wireframe).png)
## Bike colored
![Bike](/src/screenshots/--02.jpg)
## Rider wireframe
![Rider wireframe](/src/screenshots/Rider-(Wireframe).png)
## Rider colored
![Rider](/src/screenshots/--01.jpg)
## Rider & Bike on Track
![Track](/src/screenshots/--03.jpg)
