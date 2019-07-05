# Pointy
This code is rather a exercise than is an actually useful program.
This command-line tool compiles a list of points and rectangels into a python-code, 
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
points =  [
(1.2,45,6),
(7,8,5),
(10,77,88),
(99999,1,1),
]
points.extend([
(5,7,6),
(1,2,3),
(4,5,6),
(2,1,1),
])
rectangels =  [
((1,1,1),(2,2,2),(1,3,4)),
((2,3,4),(9,9,9),(3,4,5)),
]
print(points)
print(rectangels)
~~~~
