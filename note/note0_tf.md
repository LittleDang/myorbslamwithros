## 学习tf
### 主要通过[roswiki的tf](http://wiki.ros.org/tf/Tutorials)教程来学习的.
***
### 记录几个指令
```bash
rosrun tf view_frames #保存tf树
rosrun rqt_tf_tree rqt_tf_tree #查看tf树，实时可以刷新那种，类似rqt_graph
rosrun tf tf_echo [reference_frame] [target_frame]
#查看从ref到target的tf
#eg.
rosrun tf tf_echo t1 t2 #t12=t1w*tw2
rosrun rviz rviz #直接打开rviz添加tf，可以直接直观的看出tf的变化和关系
```
***
### 编写[broadcaster](../src/turtle_tf_broadcaster.cpp)
主要功能就是接收从turtlesim那里发过来的一个topic(turtle1/pose),这个只是一个记录了相对于world的姿态信息的话题，并没有添加到tf树里面，而这个程序做的就是订阅这个topic然后将它包装后发送到tf树里面，程序的话主要就是学习一下格式而已，可以当作模板使用。
```bash
rostopic info /turtle1/pose 
Type: turtlesim/Pose

Publishers: 
 * /sim (http://dang-OMEN-by-HP-Laptop:35773/)

Subscribers: None
#可以看到这是个话题，类型是turtlesim/Pose
rosmsg info turtlesim/Pose 
float32 x
float32 y
float32 theta
float32 linear_velocity
float32 angular_velocity
```
然后对应的launch文件也只是启动一下turtlesim，默认生成了一只叫做turtle1的小海龟，同时启动一个teleop_key用来操作小海龟，同时启动两个braodcaster节点，一个传参数turtle1，一个传参数turtle2
***
### 编写[listener](../src/turtle_tf_listener.cpp)(代码因为后面教程的原因做了一些改动，主要就是把turtle1换成了carrot1)
主要功能就是先调用spwan服务产生一只默认的小海龟(turtle2)，然后调用
```c
listener.lookupTransform("/turtle2", "/turtle1",ros::Time(0), transform);
```
得到T21，然后根据这个T21,然海龟2时刻以与海龟1相对于海龟2的方向成正比的角速度和距离成正比的线速度移动。

注意一下这个函数
```c
listener.lookupTransform("/turtle2", "/turtle1",ros::Time(0), transform);
//得到的是T21，即1在2里的表示，对应的功能为P2=T21*P1，即将一个表示在坐标系1里的点转换为表示在坐标系2里面。
```
***
### 添加一个[Frame](../src/turtle_tf_listener.cpp)
这里的代码没什么值得说的，值得注意的是tf tree 的任何一个tf只允许一个唯一的parent，但是允许有多个children。
***
### tf and time
tf tree每时每刻都在变化，并且tf tree会记录每个tf对应的timestamp，并且有一个缓存区缓存过去一定时间内的tf tree，默认是10s,如果我们是为了取最新的tf，直接像之前调用的一样将时间置为ros::Time(0)，即可
```c
listener.lookupTransform("/turtle2", "/carrot1",ros::Time(0), transform);
```
但是如果要取特定时间的tf，只要确保缓存区里面有这个tf，将时间改为目标时间即可。

但是有一种情况例如，我要取将来的tf，例如`ros::Time::now()`,由于tf树存储和计算等等有一定的开销，导致当前tf tree其实最新的记录距离现在的时间还有一定的距离，这个时候可以调用
```c
ros::Time now = ros::Time::now();
listener.waitForTransform("/turtle2", "/turtle1",now,ros::Duration(3.0));
listener.lookupTransform("/turtle2", "/turtle1",now, transform);
```
`waitForTransform`这个函数会阻塞线程直到timeout或者tf tree已经更新了目标的时间对应的tf。
***
### Time travel with tf
这里主要就是学习一下怎么求frame1在time1时间与frame2在time2时间之间的transform。直接看代码
```c
    ros::Time now = ros::Time::now();
    ros::Time past = now - ros::Duration(5.0);
    listener.waitForTransform("/turtle2", now,
                              "/turtle1", past,
                              "/world", ros::Duration(1.0));
    listener.lookupTransform("/turtle2", now,
                             "/turtle1", past,
                             "/world", transform);
```
这份代码做的事情就是求让now时刻的turtle2到past时刻的turtle1的变换。