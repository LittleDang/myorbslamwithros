### [ros_control](http://gazebosim.org/tutorials/?tut=ros_control)
ros control这个东西好像是用来直接控制每个关节的，学着学着好像学错了，现在暂时用不上，等之后用的上再来学习。

要使用ros_control的话，必须有transmission element 作用在joints上
对于transmisson来说，最重要的三个tags是
* joint name：这个名字必须是urdf中已经存在的关节
* type：说明这个transmisson的类型，当前只有一种实现"transmission_interface/SimpleTransmission"
* hardwareInterface:这个标签存在在actuator和joint tags里面。这个是用来告诉gazebo_ros_control插件应该载入哪种来形的硬件接口(position,velocity,effort interfaces).目前好像也只有effort interfaces实现了

除了要有transmission tags外，还必须载入gazebo插件
```XML
<gazebo>
  <plugin name="gazebo_ros_control" filename="libgazebo_ros_control.so">
    <robotNamespace>/MYROBOT</robotNamespace>
  </plugin>
</gazebo>
```
这个插件有几个可选的子elements：
* robotNamespace:这个插件的实例所使用的ros namespace，默认为机器人的名字在urdf里定义的
* controlPeriod:controller更新的周期，默认为gazebo的周期
* robotParam：机器人在参数服务器里的名字，默认为‘/robot_description'
* robotSimType:自定义机器人所使用的仿真接口，默认为'DefaultRobotHWSim'
