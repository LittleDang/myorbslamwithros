#### [gazebo_plugins](http://gazebosim.org/tutorials?tut=ros_gzplugins&cat=connect_ros)
[使用kinetic depth camera plugin](http://gazebosim.org/tutorials/?tut=ros_depth_camera)
```XML
<plugin name="camera_plugin" filename="libgazebo_ros_openni_kinect.so">
          <baseline>0.2</baseline>
          <alwaysOn>true</alwaysOn>
          <!-- Keep this zero, update_rate in the parent <sensor> tag
            will control the frame rate. -->
          <updateRate>0.0</updateRate><!--跟color同步的意思吧-->
          <cameraName>camera_ir</cameraName>
          <imageTopicName>/camera/color/image_raw</imageTopicName>
          <cameraInfoTopicName>/camera/color/camera_info</cameraInfoTopicName>
          <depthImageTopicName>/camera/depth/image_raw</depthImageTopicName>
          <depthImageCameraInfoTopicName>/camera/depth/camera_info</depthImageCameraInfoTopicName>
          <pointCloudTopicName>/camera/depth/points</pointCloudTopicName>
          <frameName>camera_link</frameName><!--点云所在的frame-->
          <pointCloudCutoff>0.5</pointCloudCutoff><!--最小深度-->
          <pointCloudCutoffMax>3.0</pointCloudCutoffMax><!--最大深度-->
          <distortionK1>0</distortionK1><!--畸变参数吧-->
          <distortionK2>0</distortionK2>
          <distortionK3>0</distortionK3>
          <distortionT1>0</distortionT1>
          <distortionT2>0</distortionT2>
          <CxPrime>0</CxPrime>
          <Cx>0</Cx>
          <Cy>0</Cy>
          <focalLength>0</focalLength>
          <hackBaseline>0</hackBaseline>
        </plugin>
```
这个标签要跟在camera标签后面
