## Typora安装 for Centos 7 



### 1. 软件版本

* typora 版本 ： `Typora-linux-x64.tar.gz`

>Typora官网：https://www.typora.io/
>
>官网快捷键说明： http://support.typora.io/Shortcut-Keys/



解压

~~~bash
tar -zxvf Typora-linux-x64.tar.gz 
~~~



### 2. Typora 安装

1. 安装 `libXScrnSaver`

~~~bash
# yum install libXScrnSaver-devel.x86_64
~~~





2. 找到 `Typora` 的解压目录



​	我的是在

> /下载/bin

把/bin目录下的 `Typora-linux-x64` 转移到 `/opt/typora`

~~~terminal
cp /下载/bin/Typora-linux-x64  /opt/typora/
~~~





2. 编辑 ～/.bashrc

* 添加以下内容：

~~~bash
export PATH=$PATH:/opt/typora/Typora-linux-x64/
~~~



所以博客上都会写  注意：`/opt/typora/Typora-linux-x64/` 是 Typora的解压目录





3. 运行软件

~~~bash
# Typora
~~~



### 3. 另外

​	如果出现吐核错误



![image-20200307131422963](/home/zhangze/.config/Typora/typora-user-images/image-20200307131422963.png)





1. 根据提示，找到`/opt/typora/Typora-linux-x64/chrome-sandbox`



~~~bash
cd /opt/typora/Typora-linux-x64/
~~~





2. 修改所属成员以及成员组；

   

~~~bash
# chown root:root chrome-sandbox 
~~~



3. 修改权限为`4755`



~~~bash
# chmod 4755 chrome-sandbox 
~~~



​	最后，可以看到chrome sandbox权限、用户都修改成功。

![image-20200307131920164](/home/zhangze/.config/Typora/typora-user-images/image-20200307131920164.png)



## 运行Typora



~~~bash
$ Typora
~~~







