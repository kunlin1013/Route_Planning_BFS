## Use Breadth-first Search(BFS) to implement route planning.

### Reference 
https://blog.csdn.net/jiangcheng2016/article/details/110353740

### Briefly describe
Breadth-first search starts from the starting point and expands outward, checking whether neighboring points are accessible. It requires a **queue** to store the next point to be checked, thereby obtaining the shortest path.

### Other function
- Multipoint navigation
  - e.g., Four points : (1048,370)、(649,823)、(139,832)、(347,1556)
  ![Multipoint navigation](https://github.com/kunlin1013/Route_Planning_BFS/blob/main/img/Multipoint_navigation.png)

- For car or for people?
  - If driving, one must avoid taking some small roads.
  - Approach: for people, use the raw image; for cars, apply a 5x5 rectangle structuring element for **opening** the image.
  - Opening result: in car mode, some of the smaller roads will be cleared.
  ![Opening result](https://github.com/kunlin1013/Route_Planning_BFS/blob/main/img/opening.png)
  - e.g., Points : (185,815)、(350,621)、(657,770)、(340,835)、(306,1027)
  ![For car or for people?](https://github.com/kunlin1013/Route_Planning_BFS/blob/main/img/For%20car%20or%20people.png)

### Directory structure
```
|
|-- img: Images for the README.md
|
|-- Route_Planning.cpp: Design some function for route planning
```







