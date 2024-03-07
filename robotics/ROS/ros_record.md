# ROS小技巧
## 工具
1. [topic_tools](http://wiki.ros.org/topic_tools)工具
```xml
 <node pkg="topic_tools" type="relay" name="vlp_relay" args="/velodyne_points /input_pointcloud" />
 <node pkg="topic_tools" type="relay" name="front_lidar_relay" args="/lidar_front_points /input_pointcloud" />
 <node name="pose_throttler" type="throttle" pkg="topic_tools" args="messages $(arg robot_name)/ground_truth/pose_with_covariance 10 /msf_core/pose" />
```
`relay`节点，将一个话题重新发不到另一个话题，并且可以合并不同的话题；
`throttle` 限制消息的发布频率


# Gazebo
在工作空间下的mesh//model.sdf可以直接使用<url>model://模型名称<url>

## 在Gazebo环境中添加机器人
创建机器人使用多个文件共同创建,可以将其放在同一个[urdf文件夹](./files/urdf)下,该文件夹下个文件的功能如下：
```json
sensors.urdf.xacro // 设置传感器插件位置
head.xacro // 计算常见形状的转动惯量
k331.gazebo  // IMU， GPS 与控制器插件
k331_robot.urdf.xacro  // 机器人主题的形状与gazebo环境之间的交互
```
下面记录一些重要的语法信息
```xml
<!-- 引入文件-->
<xacro:include filename="$(find vehicle_simulator)/urdf/k331.gazebo" /> 
<!-- 设置参数-->
<xacro:property name="lidar_holder_radius" value="0.05"/>
<!-- 两个重要概念  link代表关节 与 joint表示关节之间的相对位置-->
<link name="lidar_holder">
    <!-- 可视化-->
    <visual>
      <origin xyz="0 0 0" rpy="0 0 0"/>
      <geometry>
        <cylinder radius="${lidar_holder_radius}" length="${lidar_z-0.01}"/>
      </geometry>
    </visual>
    <!-- 碰撞信息，一般与<visual>相同-->
    <collision>
      <origin xyz="0 0 0" rpy="0 0 0"/>
      <geometry>
        <cylinder radius="${lidar_holder_radius}" length="${lidar_z}"/>
      </geometry>
    </collision>
    <!-- 转动惯量，规则物体具有固定公式-->
    <inertial>
      <mass value="1e-5" />
      <origin xyz="0 0 0" rpy="0 0 0"/>
      <inertia ixx="1e-6" ixy="0" ixz="0" iyy="1e-6" iyz="0" izz="1e-6" />
    </inertial>
  </link>
  <!-- type="fixed"表示固定， type = "continuous"表示可以绕某一轴旋转-->
  <joint name="lidar_holder_joint" type="fixed">
    <origin xyz="0.0 0 ${lidar_z / 2}" rpy="0 0 0"/>
    <parent link="base_link"/>
    <child link="lidar_holder"/>
    <!-- 旋转轴-->
    <axis xyz="0 1 0" />
  </joint>

<!--常用概念：宏，类似于函数，如下文中轮子的宏，包含控制器等诸多模块-->
<!--*joint_pose 与 <xacro:insert_block name="joint_pose" />对应，使用时直接插入代码快-->

<xacro:macro name="add_wheel" params="name *joint_pose">
    <link name="${name}_wheel">
      <visual>
        <origin xyz="0 0 0" rpy="${PI /2} 0 0"/>
        <geometry>
          <cylinder radius="${wheel_radius}" length="${wheel_length}"/>
        </geometry>
      </visual>

      <collision>
        <origin xyz="0 0 0" rpy="${PI /2} 0 0"/>
        <geometry>
          <cylinder radius="${wheel_radius}" length="${wheel_length}"/>
        </geometry>
      </collision>

      <xacro:cylinder_inertial_matrix m="${wheel_mass}" r="${wheel_radius}" h="${wheel_length}"/>
    </link>

    <joint name="${name}_joint" type="continuous">
      <xacro:insert_block name="joint_pose" />
      <parent link="base_link"/>
      <child link="${name}_wheel"/>
      <axis xyz="0 1 0" />
    </joint>

    <!--设置了车轮在Gazebo中的属性-->
    <gazebo reference="${name}_wheel">
    <!--是否允许自身碰撞-->
      <selfCollide>false</selfCollide>
    <!--静摩擦-->
      <mu1>1.0</mu1>
    <!--动摩擦-->
      <mu2>0.5</mu2>
      <kp value="10000000.0" />
      <kd value="1.0" />
    <!--定义了摩擦里方向-->
      <fdir1 value="1 0 0" />
    </gazebo>
    <!--固定格式，定义传动系统，将车轮的传动传递给机器人模型-->
    <transmission name="${name}_joint_trans">
      <type>transmission_interface/SimpleTransmission</type>
      <joint name="${name}_joint">
        <hardwareInterface>hardware_interface/VelocityJointInterface</hardwareInterface>
      </joint>
      <actuator name="${name}_actuator">
        <hardwareInterface>hardware_interface/VelocityJointInterface</hardwareInterface>
        <mechanicalReduction>1</mechanicalReduction>
      </actuator>
    </transmission>
  </xacro:macro>

  <!-- 安装使用轮子时，需要注意坐标系之间的相互关系，理论上轮子与车体坐标系应该一致-->

```

## 创建Gazebo环境
重点是`xxx.world`文件的编写，简单示例如下：
```xml
<?xml version="1.0" ?>
<sdf version="1.5">
  <world name="my_world">
    <include>
      <uri>model://my_robot</uri>
    </include>
    <include>
      <uri>model://table</uri>
      <pose>0 0 0.75 0 0 0</pose>
    </include>
    <!-- 较为重要的模块 ，定义仿真的物理属性-->

    <physics type="ode">
      <!-- Physics configuration settings -->
      <solver>：定义 ODE 求解器的参数，如类型、迭代次数和 SOR（Successive Over Relaxation）参数。
      <constraints>：定义约束条件的参数，如接触力补偿因子、误差修正因子等。
      <max_step_size>：定义仿真的最大步长。
      <real_time_factor> 和 <real_time_update_rate>：定义仿真的实时因子和更新频率。
      <gravity>：定义仿真世界的重力。
    </physics>
  </world>
</sdf>
```

## 在Gazebo环境中加载机器人
创建机器人
```xml
<launch>

<arg name="robot_namespace" default="k331_robot" />

  <arg name="x" default="0.0" />
  <arg name="y" default="0.0" />
  <arg name="z" default="1.0" />
  <arg name="yaw" default="0" />

  <!-- controller related  使用该控制器，生成的机器人应该在一个group内-->
  <rosparam command="load" file="$(find vehicle_simulator)/config/control_sim_k331.yaml" />
  <node name="controller_spawner" pkg="controller_manager" type="spawner"
    args="k331_joint_publisher k331_velocity_controller" /> 
  
  <!-- k331 robot -->
  <param name="robot_description"
    command="$(find xacro)/xacro $(find vehicle_simulator)/urdf/k331.urdf.xacro name:=$(arg robot_namespace)"/>
  <!-- 制定位置，生成机器人  -->
  <node name="k331_spawner" pkg="gazebo_ros" type="spawn_model"
	    args="-urdf -model $(arg robot_namespace) -param robot_description
      -x $(arg x) -y $(arg y) -z $(arg z) -R 0 -P 0 -Y $(arg yaw)" />

  <!-- related node -->
  <node name="joint_state_publisher" pkg="joint_state_publisher" type="joint_state_publisher" />
  <node name="robot_state_publisher" pkg="robot_state_publisher" type="robot_state_publisher">
    <param name="publish_frequency" type="double" value="100.0"/> 
  </node> 

</launch>
```
加载gazebo环境
```xml
 <include file="$(find gazebo_ros)/launch/empty_world.launch" >
    <!-- <arg name="paused" value="$(arg paused)"/> -->
    <arg name="use_sim_time" value="$(arg use_sim_time)"/>
    <arg name="gui" value="$(arg gui)"/>
    <arg name="headless" value="$(arg headless)"/>
    <arg name="debug" value="0"/>
    <!-- <arg name="verbose" value="$(arg verbose)"/> -->
    <arg name="world_name" value="$(find vehicle_simulator)/world/$(arg world_name).world"/>
  </include>

```
**使用ode文件加载的Gazebo环境中，imu无法正常使用**

## 速度平滑器

## 杂项
ros::TransportHints().tcpNoDelay() 订阅中的一个可选参数，用于指定 ROS 传输层的提示。在这里，tcpNoDelay() 提示告诉 ROS 尽量减少延迟，通过 TCP 连接传输消息。

