#pragma once
namespace 东方山寨 {
//启动
constexpr wchar_t c启动文件[] = L"~/boot/dfylc0.xml";
constexpr wchar_t c游戏名称[] = L"东方月亮船";
//字体&名称
constexpr wchar_t c数字字体[] = L"Consolas";
constexpr wchar_t c文本字体[] = L"微软雅黑";
//时间
constexpr wchar_t c标准时间格式[] = L"{:%Y/%m/%d %H:%M:%S}";	//年/月/日 时:分:秒
constexpr wchar_t c紧凑时间格式[] = L"{:%Y%m%d%H%M%S}";	//年月日时分秒
//调试
#ifdef _DEBUG
constexpr bool c调试 = true;
constexpr bool c调试_总开关 = true;
#else
constexpr bool c调试 = false;
constexpr bool c调试_总开关 = true;	//可控制
#endif
constexpr bool c调试_自机无敌 = c调试_总开关 && true;
constexpr bool c调试_调试信息 = c调试_总开关 && true;
}	//namespace 东方山寨