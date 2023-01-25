## 基础环境

|环境|版本|
|---|---|
|操作系统|Ubuntu 20.04.1|
|编译器|gcc 9.4.0|
|cmake|3.16.3|
|OpenCV 与 OpenCV_contrib|4.7.0|
|Python|3.8.10|
|Pytorch|1.11.0+cu113|
|CUDA|11.3|
|CuDNN|8.2|

其中，非Ubuntu系统可能会导致apt等命令不可用，非linux系统需要对本节中每一步寻找同等功能的解决方案

cmake版本过低可能会导致测试代码不可用，python版本至少应该为python3，低版本可能导致OpenCV-Python组件无法工作

OpenCV版本不得低于4.5.3，建议采用最新的Release版本4.7.0

Pytorch版本与Python版本，CUDA版本和CuDNN版本有关，需要参考官网

CuDNN版本高于8.0会导致caffe不可用

## 下载

[OpenCV](https://github.com/opencv/opencv/releases) Source Code

[OpenCV_contrib](https://github.com/opencv/opencv_contrib/releases/tag/4.7.0)Source Code

上面两个版本号必须完全一致

[模型文件](https://github.com/WeChatCV/opencv_3rdparty/)

## OpenCV的安装

依赖项安装

    sudo apt-get install -y libcurl4 build-essential pkg-config cmake \
    libopenblas-dev libeigen3-dev libtbb-dev \
    libavcodec-dev libavformat-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev \
    libswscale-dev libgtk-3-dev libpng-dev libjpeg-dev \
    libcanberra-gtk-module libcanberra-gtk3-module

缺乏会导致部分组件无法安装

自建build文件夹后，在文件夹内执行cmake命令

参考cmake命令

    cmake ../opencv-4.7.0 -DCMAKE_BUILD_TYPE=Release -DCMAKE_VERBOSE_MAKEFILE=ON \
	-DCMAKE_INSTALL_PREFIX=opencv4.7-install \
	-DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.7.0/modules -DOPENCV_ENABLE_NONFREE=ON\
	-DBUILD_opencv_python3=ON -DWITH_1394=OFF \
	-DWITH_IPP=ON -DWITH_TBB=ON -DWITH_OPENMP=ON -DWITH_PTHREADS_PF=ON \
	-DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DOPENCV_GENERATE_PKGCONFIG=ON \
	-DWITH_CUDA=ON -DENABLE_FAST_MATH=ON -DCUDA_FAST_MATH=ON -D WITH_CUBLAS=ON \
	-DPYTHON3_LIBRARY=$(python3 -c "from distutils.sysconfig import get_config_var;from os.path import dirname,join ; print(join(dirname(get_config_var('LIBPC')),get_config_var('LDLIBRARY')))") \
	-DPYTHON3_NUMPY_INCLUDE_DIRS=$(python3 -c "import numpy; print(numpy.get_include())") \
	-DPYTHON3_PACKAGES_PATH=$(python3 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())")

需要检查的要点

1. 等号后面不得有空格
2. -DCMAKE_INSTALL_PREFIX为自选的文件夹路径，这是相对于执行cmake命令的地方，即build文件夹的
3. 不支持CUDA第7行可以删去

## 测试

见[test](../src/test-opencv/)

注意CMakeLists.txt中OpenCV_DIR要改为OpenCV安装目录下有OpenCVConfig.cmake  OpenCVConfig-version.cmake  OpenCVModules.cmake  OpenCVModules-release.cmake
文件的目录

其他路径相关也需要检查