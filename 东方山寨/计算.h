#pragma once
#include "数学包含.h"
namespace 东方山寨 {
namespace 计算 {
//杂烩
float f插值(const std::pair<float, float> &, float);
//时间
bool f计时(float &计时, float a);
//变化
float f加变化(float 变化, float 时间 = 1);
float f乘变化(float 变化, float 时间 = 1);
//图形
float f距离透明度(float 原透明, float 距离);
//运动
void f基本运动计算(t向量2 &, const t向量2 &, float);
float f到目标时间(const t向量2 &原, const t向量2 &目标, float 速度);
t向量2 f到目标速度(const t向量2 &原, const t向量2 &目标, float 时间);
}}