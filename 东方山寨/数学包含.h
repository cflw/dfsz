#pragma once
#include <boost/rational.hpp>
#include <cflw数学.h>
#include <cflw数学_向量.h>
#include <cflw数学_平面几何.h>
#include <cflw数学_图形.h>
#include <cflw数学_矩阵.h>
#include <cflw数学_杂烩.h>
#undef max
#undef min
namespace 东方山寨 {
namespace 数学 = cflw::数学;
typedef 数学::S向量2 t向量2;
typedef 数学::S向量3 t向量3;
typedef 数学::S向量4 t向量4;
typedef 数学::S圆形 t圆形;
typedef 数学::S矩形 t矩形;
typedef 数学::S旋转矩形 t旋转矩形;
typedef 数学::S线段2 t线段;
typedef 数学::S颜色 t颜色;
using t矩阵4 = 数学::S矩阵4;
using t分数 = boost::rational<int>;
typedef 数学::C位置计算<float> t位置计算;
}	//namespace 东方山寨