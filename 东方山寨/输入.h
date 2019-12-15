#pragma once
#include <map>
#include <cflw输入_win.h>
#include <cflw输入_xi.h>
namespace 东方山寨 {
namespace 输入 = cflw::输入;
namespace 输入w = cflw::输入::win;
namespace 输入x = cflw::输入::xi;
//枚举
enum class E按键 : 输入::t索引 {
	e上, e下, e左, e右,
	e确定,
	e取消,
	e切换,
	e射击,
	e炸弹,
	e低速,
	e释放,
	e跳过,
	e菜单,	//键盘退出键, 手柄开始键
	e数量
};
//映射
inline const std::map<E按键, 输入w::E键盘按键> ca键盘映射 = {
	{E按键::e上, 输入w::E键盘按键::e上},
	{E按键::e下, 输入w::E键盘按键::e下},
	{E按键::e左, 输入w::E键盘按键::e左},
	{E按键::e右, 输入w::E键盘按键::e右},
	{E按键::e确定, 输入w::E键盘按键::z},
	{E按键::e取消, 输入w::E键盘按键::x},
	{E按键::e切换, 输入w::E键盘按键::e左上档},
	{E按键::e射击, 输入w::E键盘按键::z},
	{E按键::e炸弹, 输入w::E键盘按键::x},
	{E按键::e释放, 输入w::E键盘按键::c},
	{E按键::e低速, 输入w::E键盘按键::e左上档},
	{E按键::e跳过, 输入w::E键盘按键::e左控制},
	{E按键::e菜单, 输入w::E键盘按键::e逃脱},
};
inline const std::map<E按键, 输入x::E手柄按键> ca手柄映射 = {
	{E按键::e上, 输入x::E手柄按键::e上},
	{E按键::e下, 输入x::E手柄按键::e下},
	{E按键::e左, 输入x::E手柄按键::e左},
	{E按键::e右, 输入x::E手柄按键::e右},
	{E按键::e确定, 输入x::E手柄按键::a},
	{E按键::e取消, 输入x::E手柄按键::b},
	{E按键::e切换, 输入x::E手柄按键::x},
	{E按键::e射击, 输入x::E手柄按键::a},
	{E按键::e炸弹, 输入x::E手柄按键::b},
	{E按键::e低速, 输入x::E手柄按键::e左肩},
	{E按键::e释放, 输入x::E手柄按键::e右肩},
	{E按键::e菜单, 输入x::E手柄按键::e开始},
};
//输入引擎
class C输入引擎 {
public:
	C输入引擎();
	void f初始化(HWND, float 缩放);
	void f更新();
	const 输入::C按键组 &fg按键组() const;
	输入::S方向 fg方向() const;
	void fs缩放(float);
public:
	输入w::C输入 m输入w;
	输入x::C输入 m输入x;
	输入::tp键盘 m键盘 = nullptr;
	输入::tp鼠标 m鼠标 = nullptr;
	输入::tp手柄 m手柄 = nullptr;
	std::map<输入::t索引, 输入::t索引> m键盘映射;	//<-
	std::map<输入::t索引, 输入::t索引> m手柄映射;	//<-
	输入::C按键组 m按键组{(size_t)E按键::e数量};
	输入::C方向键 m方向键[2] = {};
	输入::S方向 m手柄方向;
};
}	//namespace 东方山寨