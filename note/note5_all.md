### 目标
在gazebo中跑orb_slam2这个slam框架。
### 步骤
>orb_slam2是一个完成度比较高的项目，基本可以当作库来使用了，正常使用来说，orb_slam2提供的接口都是要通过opencv::Mat这个格式的imgae作为input，一般使用的话，是先驱动camera（由于我跑的是orb_slam2的depth模式，接下来所有的camera都是指depth camera），然后通过串口或者某种方式得到数据流，然后转化成Mat格式，然后调用orb_slam2的接口传入数据，然后库便会返回位姿（在ros里面叫做tf)。这篇文章主要是介绍如何在仿真里面跑slam框架，所以对具体的slam算法和步骤不做介绍。

然而现在问题是，我们并没有具体的环境和硬件，我们是想要在电脑上完成这一切，也就是仿真，由于我只用过gazebo和ros，所以我选择用gazebo来仿真环境，获得我们所需要的一切数据，通过ros系统提供的接口来接收和解析数据。既然选择用gazebo来获取一切所需要的数据，那么便要在gazebo中完成一切现实中的任务，即找到一个合适的场景（纹理要多），一台深度摄像机，一台可以移动的机器人，一个可以控制机器人的方法。

综上所述，我们把任务分解为以下两个部分

[1. 创建一个机器人](note3_urdf.md)

[2. 控制该机器人移动，并且在该机器人身上搭建camera](note4_gazebo_plugins.md)

以上两个步骤完成的文件为[vechile.xacro](../urdf/vechile.xacro)

3. 将camera的数据传入orb_slam系统
>这一个步骤基本上来说就是按照[orb_slam2的github](https://github.com/raulmur/ORB_SLAM2)来弄就可以完成安装了，当然过程中我遇到了一些错误,是编译ros部分遇到的错误,可以参考[这个连接](https://blog.csdn.net/sinat_38343378/article/details/78883919)
