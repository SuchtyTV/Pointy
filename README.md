# Pointy
**This code is rather a exercise than is an actually useful program.**
This command-line tool compiles a list of points and triangles into a python-code, 
which will display all these shapes in a diagram when executed.

For example.:
~~~~
(1.2,45,6)
(7,8,5)
(10,77,88)
(99999,1,1)
R((1,1,1),(2,2,2),(1,3,4))
(5,7,6)
(1,2,3)
(4,5,6)
R((2,3,4),(9,9,9),(3,4,5))
  P(2,1,1)
~~~~

--> 
~~~~
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

from mpl_toolkits.mplot3d import Axes3D 
from itertools import chain 
import matplotlib.pyplot as plt

zs = []
xs = []
ys = []

fig = plt.figure()
axrec = Axes3D(fig)
ax = fig.add_subplot(111, projection='3d')

points =  [
(1.2,5,6),
(1.2,7,6),
(1.2,5,6),
(1.2,8,6),
(7,8,5),
(5,7,6),
(1,2,3),
(4,5,6),
(2,1,1),
]

triangles =  [
((1,1,1),(2,2,2),(1,3,4)),
((2,3,4),(9,9,9),(3,4,5)),
]

for val in points:
  (x,y,z) = val
  xs.append(x)
  ys.append(y)
  zs.append(z)

tri_points = list(chain.from_iterable(triangles))
x, y, z = zip(*tri_points)
tri_idx = [(3 * i, 3 * i + 1, 3 * i + 2) for i in range(len(triangles))]
ax = plt.figure().gca(projection='3d')
ax.plot_trisurf(x, y, z, triangles=tri_idx)

ax.scatter(xs, ys, zs, marker='o')

plt.show()

~~~~

This can then be executed with:
~~~~
python3 filename.py
~~~~

which will show:

![Outcome](https://serving.photos.photobox.com/25541494cc4bccdebb50a027258628d3a3585a7bd38bb6f81111106457e570efe63ab2e6.jpg)

## **Supported platforms:**

* Unix/Unix-like platforms

## **Usement:**

To use the programm first create a file containing the shapes you want to display:

~~~~
cat >> data.txt
...
~~~~

Then execute the compiled program with:

~~~~
./Program data.txt >> dest.py
...
~~~~

You can then execute the python-script:

~~~~
python3 dest.py
...
~~~~
