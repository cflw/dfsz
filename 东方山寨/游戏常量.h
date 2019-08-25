#pragma once
#include <math.h>
namespace 东方山寨 {
//时间
constexpr double c计算频率 = 240;
constexpr double c帧秒 = 1.0 / c计算频率;
//上限
constexpr unsigned int c子弹上限 = 2000;
constexpr unsigned int c玩家子弹上限 = 1000;
constexpr unsigned int c道具上限 = 2000;
constexpr unsigned int c敌机上限 = 100;
constexpr unsigned int c图形上限 = 5000;
//范围
constexpr long c标准尺寸x = 640;
constexpr long c标准尺寸y = 480;
constexpr float c边框范围x = 192;
constexpr float c边框范围y = 224;
const float c边框范围r = hypot(c边框范围x, c边框范围y);
constexpr float c边框厚度 = 4;
constexpr float c外边框范围x = c边框范围x + c边框厚度;
constexpr float c外边框范围y = c边框范围y + c边框厚度;
const float c外边框范围r = hypot(c外边框范围x, c外边框范围y);
constexpr float c框架范围x = 320;
constexpr float c框架范围y = 240;
constexpr float c框架范围r = 400;
constexpr float c外框架范围x = c框架范围x + c边框厚度;
constexpr float c外框架范围y = c框架范围y + c边框厚度;
constexpr float c自机移动限制范围 = 16;
constexpr float c移动范围x = c边框范围x - c自机移动限制范围;
constexpr float c移动范围y = c边框范围y - c自机移动限制范围;
const float c移动范围r = hypot(c移动范围x, c移动范围y);
constexpr float c自机初始坐标y = -c边框范围y + 64;
//细节
constexpr float c王战倒计时0 = 10;
constexpr float c王战倒计时1 = 5;

}