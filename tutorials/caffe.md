## caffe配置

### 基础环境

|环境|版本|
|---|---|
Ubuntu |16.04|
CUDA |9.0|
Miniconda3 |Python=3.7|

### 依赖安装

    sudo apt-get update
    sudo apt-get install -y libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler
    sudo apt-get install -y --no-install-recommends libboost-all-dev
    sudo apt-get install -y libatlas-base-dev
    sudo apt-get install -y libgflags-dev libgoogle-glog-dev liblmdb-dev

### 编译caffe

因为detect模型中使用了ssd网络作为框架，所以需要caffe的ssd分支

[下载地址](https://github.com/weiliu89/caffe/tree/ssd)

切换到对应分支

    cd caffe
    git checkout ssd 
    cp Makefile.config.example Makefile.config

[参考Makefile.config](../src/caffe/Makefile.config)

其中的路径可能需要根据实际情况修改

开头的`USE_CUDNN := 1`根据CUDA版本是否适配来选择是否取消，用于加速，不一定要有

编译

    make -16

由于使用了Python3,但是默认libboost_python符号链接指向了python2.7，因此需要做如下处理

    cd /usr/lib/x86_64-linux-gnu
    rm libboost_python.so
    ln -s libboost_python-py35.so libboost_python.so

添加caffe-python包到python路径中

    echo "export PYTHONPATH=$PYTHONPATH:/root/caffe/python" >> /etc/profile
    source /etc/profile

同样要注意路径

安装caffe需要的python依赖

    pip install scikit-image

编译python接口部分

    make py
    make test -j8

测试

    python
    import caffe

## 读入模型并绘图

### 依赖安装

    pip uninstall protobuf
    pip install --no-binary=protobuf protobuf
    pip install graphviz
    pip install pydot

注意，使用apt安装

    sudo apt-get install graphviz

### 绘图

[python代码](../src/caffe/draw.py)

需要下载好模型文件，并留意相关路径