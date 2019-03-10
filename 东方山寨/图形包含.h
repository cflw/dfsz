#pragma once
#include <cflw图形_d3d11.h>
#include <cflw图形_d2d.h>
#include <cflw图形_d3d着色器.h>
namespace 东方山寨 {
namespace 二维 = cflw::图形::d2d;
namespace 三维 = cflw::图形::d3d11;
namespace 纹理 = cflw::图形::dx纹理;
namespace 着色器 = cflw::图形::d3d着色器;
using 三维::tp设备;
using 三维::tp设备上下文;
using 三维::tp缓冲;
using 三维::tp纹理;
using 三维::tp顶点着色器;
using 三维::tp几何着色器;
using 三维::tp外壳着色器;
using 三维::tp域着色器;
using 三维::tp像素着色器;
using 三维::tp输入布局;
using t顶点格式 = 三维::C顶点格式;
using t自动缓冲 = 三维::C自动缓冲;
using t画图形 = 二维::C画图形;
}	//namespace 东方山寨