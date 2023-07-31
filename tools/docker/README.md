# docker

## docker 简介

**容器**： 系统平滑移植， 容器虚拟化技术

镜像就是应用：包括源码、配置环境、运行环境、运行依赖包、甚至内核等等

基于Go语言的云开源项目，“build, ship and run any app, anwhere",通过对应用组件的封装、分发、部署、运行等生命周期的管理，使用户的APP及运行环境做到“一次镜像，处处运行"

虚拟机缺点： 启动慢，资源占用多，冗余步骤多

linux 容器：与系统其他部分隔离开的一系列进程，从另一个镜像运行，由该镜像提供支持进程所需的全部文件，包含应用的所有依赖项。

容器中进程直接运行于宿主的内核，没有硬件虚拟



## docker基本组成

- 镜像（image)
  类似类模板，类的定义，一个只读的模板，可以用于创建多个容器
- 容器(container)
  类似**根据类模板实例化**，容器时用镜像创建的运行实例，每个容器相互隔离，保证安全。可以视为简易版linux环境和运行在其中的应用程序。
- 仓库(repository)
  存放镜像文件的场所，docker hub,国内的公开仓库，阿里云和网易云等等

docker 是一个Client-Server结构的系统，守护进程运行在主机上，通过Socker连接从客户端访问，守护进程从客户端接受命令并管理运行在主机上的容器。后端是一个松耦合的架构，众多模块各司其职。

基本架构：

![docker架构](./images/docker架构.jpeg)运行流程如下：

1.用户使用Docker Client与 Docker Daemon建立通信，并发送请求给后者。

2.Docker Daemon作为Docker架构主体部分，首先提供Docker Server的功能使其可以接受Docker Client的请求。

3.Docker Engine 执行Docker 内部的一系列工作，每一项工作以job行书存在；

4.job运行过程中，当需要容器镜像时，从Docker Registry中下载镜像，并通过奖项管理驱动Graph driver 将下载的镜像以Graph的形式存储

5.当需要为Docker创建网络环境时，通过网络管理驱动Network driver创建并配置Docker容器网络环境。

6.当需要限制Docker容器运行资源或执行用户指令等操作，通过Exec driver完成。

7.Libcontainer是一项独立的容器管理包，Network driver及Exec driver都是通过Libcontainer实现对容器的操作。

小总结：

docker 相较于虚拟机有更少的抽象层，不需要进行硬件资源虚拟化

docker使用宿主机的内核，不需要加载操作系统OD内核

## docker 安装

docker并非一个通用的容器工具，依赖于正在运行的linux内核环境，其他系统想要使用，需要部署一个虚拟的linux环境

[docker官网](https://www.docker.com/)

[docker hub](https://hub.docker.com)

#### 安装

- 首先卸载旧版本

  ```
  bash
  sudo apt-get remove docker docker-engine docker.io containerd runc
  ```
  
- 安装

  ```
  bash
  # 更新
  sudo apt update
  # 安装依赖项
  sudo apt install apt-transport-https ca-certificates curl gnupg2 software-properties-common
  # 配置密钥（使用阿里云)
  curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
  # 添加软件源
  sudo add-apt-repository \
      "deb [arch=amd64] https://mirrors.aliyun.com/docker-ce/linux/ubuntu \
      $(lsb_release -cs) \
      stable"
  # 更新
  sudo apt-get update
  # 安装最新版
  sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
  # 安装指定版本
  # 显示支持的版本
  apt-cache madison docker-ce | awk '{ print $3 }'
  # 选择所需版本安装
  VERSION_STRING=5:24.0.0-1~ubuntu.22.04~jammy
  sudo apt-get install docker-ce=$VERSION_STRING docker-ce-cli=$VERSION_STRING containerd.io docker-buildx-plugin docker-compose-plugin
  # 验证 使用docker命令必须加sudo,不然没有该命令
   sudo docker run hello-world
  
  ```
  
- 镜像加速  

-   

## docker常见命令

### 帮助启动类命令

```bash
# 启动docker
sudo systemctl start docker
# 停止docker
sudo systemctl stop docker
# 重启docker
sudo systemctl restart docker
# 查看docker状态
sudo systemctl status docker
# 开机启动
sudo systemctl enable docker
# 查看docker概要信息
sudo docker info
# 查看docker总体帮助文档
sudo docker --help
# 查看docker命令帮助文档
sudo docker 具体命令 --help
```

### 镜像命令

```bash
# 罗列本地的镜像
docker images
# 其中REPOSITORY代表仓库源，TAG代表镜像标签，版本号，IMAGE ID,镜像ID, CREATED:镜像创建时间， SIZE,镜像大小
-a # 列出本地所有镜像，含历史镜像层
-q # 只显示镜像ID

# 查某个镜像的
docker search image-name(hello-world)
-- limit number # 只罗列出n个镜像
docker search -- limit number image-name(hello-world)

# 下载镜像
docker pull image-name:TAG # 没有tag,默认最新版

# 查看镜像/容器/数据卷所占空间
sudo docker system df

# 删除
docker rmi image-ID
-f  # 强制删除
docker rmi -f $(docker images -qa)  # 全部删除
```

docker 虚悬镜像： 仓库名和标签都是`<none>`的镜像,及虚悬镜像 dangling image

 ### 容器命令

有镜像才能创建容器

```bash
# 新建并启动容器
sudo docker run [OPTIONS] IMSGE [COMMAND] [ARG..]
# options常见指令
--name="容器新名字"
-d  # 后台运行容器并返回容器id,启动守护式容器
-i  # 以交互模式运行容器，通常与-t同时使用
-t  # 为容器重新分配一个伪输入终端，与-i同时使用
sudo docker run -it iamge-name /bin/bash   # /bin/bash 表示在容器中执行命令

# 上述及时启动交互式容器（前台有伪终端，等待交互）
-P  # 指定端口映射
-P  # 随机端口映射,一般使用 -p 6379:6379

# 列出当前正在运行的容器 
docker ps [OPTIONS]
-a  # 所有容器，包括历史信息
-l  # 显示最近创建的容器
-n number  # 显示最近n个创建的容器
-q  # 静默模式，只显示容器编号

# 退出当前容器
exit  # 容器退出
ctrl+p+q  # 容器不退出

# 启动已经停止的容器
docker start 容器ID或容器名

# 重启容器
docker restart container-ID

# 停止容器
docker stop contaner-id

# 强制停止容器
docker kill container-id

# 删除已经停止的容器
docker rm container-id

# 查看容器日志 
docker logs container-id

# 查看容器内运行进程
docker top container-id

# 查看容器内部细节
docker inspect

# 进入正在运行的容器以命令行交互
docker exec -it container-id bashSheel  # 对应ctrl+p+q的退出形式， 推荐
docker attach container-id
# 两者区别， attach 直接进入容器启动命令的终端，不会启动新的进程，exit 会同志容器
# exec 在容器中打开新的终端，并且可以启动新的进程，exit不会停止容器

# 从容器内拷贝文件到主机上
docker cp container-id:path_of_container root_path

# 导入和导出容器
export  # 导出容器的内容作为一个tar归档文件
docker export container-id > file_name.tar

import  # 从tar包中内容创建一个新的文件系统再导入镜像, docker images直接查看
cat file_name.tar | docker import -image_user/image_name:image_tag

```

`docker run -d image-name`问题：docker容器后台运行，必须有一个前台进程，如果容器运行的命名不是那些一直挂起的命令（top, tail等），会自动退出。应该根据具体情况，比如ubuntu,一般需要-it, 而mysql等需要后台运行。

![常见命令](./images/命令图解.jpg)

```bahs
attach    Attach to a running container                 # 当前 shell 下 attach 连接指定运行镜像
build     Build an image from a Dockerfile              # 通过 Dockerfile 定制镜像
commit    Create a new image from a container changes   # 提交当前容器为新的镜像
cp        Copy files/folders from the containers filesystem to the host path   #从容器中拷贝指定文件或者目录到宿主机中
create    Create a new container                        # 创建一个新的容器，同 run，但不启动容器
diff      Inspect changes on a container's filesystem   # 查看 docker 容器变化
events    Get real time events from the server          # 从 docker 服务获取容器实时事件
exec      Run a command in an existing container        # 在已存在的容器上运行命令
export    Stream the contents of a container as a tar archive   # 导出容器的内容流作为一个 tar 归档文件[对应 import ]
history   Show the history of an image                  # 展示一个镜像形成历史
images    List images                                   # 列出系统当前镜像
import    Create a new filesystem image from the contents of a tarball # 从tar包中的内容创建一个新的文件系统映像[对应export]
info      Display system-wide information               # 显示系统相关信息
inspect   Return low-level information on a container   # 查看容器详细信息
kill      Kill a running container                      # kill 指定 docker 容器
load      Load an image from a tar archive              # 从一个 tar 包中加载一个镜像[对应 save]
login     Register or Login to the docker registry server    # 注册或者登陆一个 docker 源服务器
logout    Log out from a Docker registry server          # 从当前 Docker registry 退出
logs      Fetch the logs of a container                 # 输出当前容器日志信息
port      Lookup the public-facing port which is NAT-ed to PRIVATE_PORT    # 查看映射端口对应的容器内部源端口
pause     Pause all processes within a container        # 暂停容器
ps        List containers                               # 列出容器列表
pull      Pull an image or a repository from the docker registry server   # 从docker镜像源服务器拉取指定镜像或者库镜像
push      Push an image or a repository to the docker registry server    # 推送指定镜像或者库镜像至docker源服务器
restart   Restart a running container                   # 重启运行的容器
rm        Remove one or more containers                 # 移除一个或者多个容器
rmi       Remove one or more images       # 移除一个或多个镜像[无容器使用该镜像才可删除，否则需删除相关容器才可继续或 -f 强制删除]
run       Run a command in a new container              # 创建一个新的容器并运行一个命令
save      Save an image to a tar archive                # 保存一个镜像为一个 tar 包[对应 load]
search    Search for an image on the Docker Hub         # 在 docker hub 中搜索镜像
start     Start a stopped containers                    # 启动容器
stop      Stop a running containers                     # 停止容器
tag       Tag an image into a repository                # 给源中镜像打标签
top       Lookup the running processes of a container   # 查看容器中运行的进程信息
unpause   Unpause a paused container                    # 取消暂停容器
version   Show the docker version information           # 查看 docker 版本号
wait      Block until a container stops, then print its exit code   # 截取容器停止时的退出状态值

```

































  

  

  

