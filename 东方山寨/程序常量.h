#pragma once
namespace 东方山寨 {
//启动
constexpr wchar_t c启动文件[] = L"~/boot/dfylc0.json";
constexpr wchar_t c窗口标题[] = L"东方月亮船";
//字体&名称
constexpr wchar_t c数字字体[] = L"Consolas";
constexpr wchar_t c文本字体[] = L"微软雅黑";
//调试
#ifdef _DEBUG
constexpr bool c调试_总开关 = true;
#else
constexpr bool c调试_总开关 = true;
#endif
constexpr bool c调试_自机无敌 = c调试_总开关 && true;
constexpr bool c调试_调试信息 = c调试_总开关 && true;
}