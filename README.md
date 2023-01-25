# 二维码检测系统

## 腾讯开源系统的运行

步骤见[详细教程](tutorials/tencent.md)

wechat_qrcode使用caffe编写，包含检测模型和超分模型，每个模型有参数文件`prototxt`和模型文件`caffemodel`。

系统使用OpenCV读入caffe模型进行推理，该部分组件保存在OpenCV扩展库opencv_contrib中，其中还包含了Zxing用于二维码数据的具体解析

该组件的核心函数为`detectAndDecode`，完成了定位和解码

该组件可以用C++或Python运行，需要下载参数文件和模型文件，构造带有opencv_contrib的OpenCV，且版本不低于4.5.3