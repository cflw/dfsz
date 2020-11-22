#pragma once
#include <cflw工具.h>
#include <cflw图形_d3d11.h>
#include <cflw图形_d2d.h>
#include <cflw图形_d3d着色器.h>
namespace 东方山寨 {
namespace 工具 = cflw::工具;
namespace 二维 = cflw::图形::d2d;
namespace 三维 = cflw::图形::d3d11;
namespace 纹理 = cflw::图形::dx纹理;
namespace 着色器 = cflw::图形::d3d着色器;
using t顶点格式 = 三维::C顶点格式;
using t自动缓冲 = 三维::C自动缓冲;
using t画图形 = 二维::C画图形;
using tp纹理 = 三维::tp纹理;
}	//namespace 东方山寨