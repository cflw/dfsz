#pragma once
#include <cmath>
namespace 东方山寨 {
//范围
constexpr long c标准尺寸x = 640;
constexpr long c标准尺寸y = 480;
constexpr float c边框范围x = 192;
constexpr float c边框范围y = 224;
const float c边框范围r = (float)hypot(c边框范围x, c边框范围y);
constexpr float c边框宽度 = 4;
constexpr float c边框半宽 = c边框宽度 * 0.5f;
constexpr float c外边框范围x = c边框范围x + c边框宽度;
constexpr float c外边框范围y = c边框范围y + c边框宽度;
const float c外边框范围r = (float)hypot(c外边框范围x, c外边框范围y);
constexpr float c框架范围x = 320;
constexpr float c框架范围y = 240;
constexpr float c框架范围r = 400;
constexpr float c外框架范围x = c框架范围x + c边框宽度;
constexpr float c外框架范围y = c框架范围y + c边框宽度;
}	//namespace 东方山寨