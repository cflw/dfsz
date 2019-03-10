#pragma once
#include <math.h>
namespace 东方山寨 {
//启动
constexpr wchar_t c启动文件[] = L"~/boot/dfylc0.json";
constexpr wchar_t c窗口标题[] = L"东方月亮船";
//时间
constexpr double c计算频率 = 240;
constexpr double c帧秒 = 1.0 / c计算频率;
//字体&名称
constexpr wchar_t c数字字体[] = L"Consolas";
constexpr wchar_t c文本字体[] = L"微软雅黑";
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
constexpr float c屏幕范围x = 320;
constexpr float c屏幕范围y = 240;
constexpr float c屏幕范围r = 400;
constexpr float c自机移动限制范围 = 16;
constexpr float c移动范围x = c边框范围x - c自机移动限制范围;
constexpr float c移动范围y = c边框范围y - c自机移动限制范围;
const float c移动范围r = hypot(c移动范围x, c移动范围y);
constexpr float c自机初始坐标y = -c边框范围y + 64;
//方向
enum E方向 {
	e左 = 0x01,
	e上 = 0x02,
	e右 = 0x04,
	e下 = 0x08,
	e左右 = e左 | e右,
	e上下 = e上 | e下,
	e上下左右 = e上 | e下 | e左 | e右,
};
//细节
constexpr float c王战倒计时0 = 10;
constexpr float c王战倒计时1 = 5;
//调试常量
#ifdef _DEBUG
constexpr bool c调试_总开关 = true;
#else
constexpr bool c调试_总开关 = false;
#endif
constexpr bool c调试_自机无敌 = c调试_总开关 && true;
constexpr bool c调试_调试信息 = c调试_总开关 && true;

}