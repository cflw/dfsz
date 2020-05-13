#pragma once
#include <cmath>
#include <numbers>
#include <boost/rational.hpp>
#include <cflw数学.h>
#include <cflw数学_向量.h>
#include <cflw数学_平面几何.h>
#include <cflw数学_图形.h>
#include <cflw数学_矩阵.h>
#include <cflw数学_杂烩.h>
#include <cflw物理_二维.h>
#undef max
#undef min
namespace 东方山寨 {
namespace 数学 = cflw::数学;
namespace 物理 = cflw::物理;
using t向量2 = 数学::S向量2;
using t向量3 = 数学::S向量3;
using t向量4 = 数学::S向量4;
using t圆形 = 数学::S圆形;
using t矩形 = 数学::S矩形;
using t旋转矩形 = 数学::S旋转矩形;
using t直线 = 数学::S直线2;
using t线段 = 数学::S线段2;
using t颜色 = 数学::S颜色;
using t矩阵4 = 数学::S矩阵4;
using t分数 = boost::rational<int>;
using t位置计算 = 数学::C位置计算<float>;
}	//namespace 东方山寨