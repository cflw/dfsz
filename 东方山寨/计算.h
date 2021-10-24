#pragma once
#include <tuple>
#include "数学包含.h"
namespace 东方山寨::计算 {
//杂烩
float f插值(const std::pair<float, float> &, float);
int f偶数则加一(int);
int f奇数则加一(int);
//时间
bool f计时(float &计时, float a);
//变化
float f加变化(float 变化, float 时间 = 1);	//根据总变化量计算出每帧变化量
float f乘变化(float 变化, float 时间 = 1);
//图形
float f距离透明度(float 原透明, float 距离);
//运动
void f基本运动计算(t向量2 &, const t向量2 &, float);
float f到目标时间(const t向量2 &原, const t向量2 &目标, float 速度);
t向量2 f到目标速度(const t向量2 &原, const t向量2 &目标, float 时间);
float f预判自机狙(const t向量2 &目标坐标, const t向量2 &目标速度, const t向量2 &发射坐标, float 发射速度);
float f圆周自机狙(const t向量2 &目标坐标, const t向量2 &发射坐标, float 半径, float 角方向);
float f圆周运动半径(float 线速度, float 角速度);
std::tuple<float, float> f圆周运动速度(float 半径, float 时间, float 角度 = 数学::cπ<float>);	//得到线速度和角速度
float f圆周运动角速度(float 半径, float 线速度);
float f静止变速运动加速度(float 距离, float 时间 = 1);	//S=1/2*a*t^2,返回加速度(单位:点/秒^2),之后还需要通过 f加变化 和 v=at 计算出每帧加速度和初速度
std::tuple<float, float> f静止变速运动(float 距离, float 时间 = 1);	//同上,返回初速度和每帧加速度
}	//namespace 东方山寨::计算