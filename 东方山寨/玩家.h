#pragma once
#include "基础.h"
#include "输入.h"
#include "玩家子弹发射基础.h"
#include "自机.h"
#include "子机.h"
#include "轨迹.h"
namespace 东方山寨 {
struct S游戏设置;
class C玩家;
struct S自机属性;
enum class E玩家发射;
struct S子机属性;
class I子机移动;
//玩家常量
const int c玩家数量 = 1;
//==============================================================================
// 各种值
//==============================================================================
class C分数值 {
public:
	void f计算();
	void f加分(long long);
public:
	long long m实际值 = 0;
	long long m显示值 = 0;
};
class C吸收值 {
public:
	static const float c减少速度;
	static const float c上限;
	operator int() const;
	void f计算();
	void f加();
	void f满();
public:
	float m值 = 0;
};
//==============================================================================
// 玩家
//==============================================================================
//玩家类
class C玩家 {
public:
	enum E标志 {
		e正常,
		e正在挂掉,
		e正在复活,
		e射击,	//按z
		e炸弹,
		e低速移动,	//按shift
	};
	struct S成绩 {
		long long m得分;
		boost::rational<int> m残机;
		boost::rational<int> m炸弹;
		boost::rational<int> m火力;
		int m最大点;
		int m擦弹;
		C吸收值 m吸收;
	};
	static constexpr float c复活时间 = 2;
	static constexpr float c复活距离 = 64;	//总长
	C玩家();
	//void f构造_成绩文本();
	void f初始化_环境(const C游戏速度 &);
	void f初始化_在关卡开始();	//每一关都调用
	void f输入按键(const t向量2 &, const 输入::C按键组 &);
	void f计算();
	void f更新();
	void f初始化_在游戏开始(const S游戏设置 &);	//进入游戏调用
	void f初始化_玩家成绩图形();
	void f销毁_在游戏结束();	//
	//玩家状态变化
	void f发射_发射子弹();
	void f发射_停止发射子弹();
	void f复活();
	t向量2 f计算复活位置();
	void f发射_抑制发射子弹(float 时间, bool 立即停止 = true);
	void f发射_抑制发射炸弹(float 时间);
	//一个玩家的设置
	void fs自机(int);
	void fs子机(int);
	void fs炸弹(int);
	bool f发射_i可发射子弹() const;
	bool f发射_i可发射炸弹() const;
	bool fi可复活() const;
public:	//包含自机&子机&成绩
	C自机 m自机;
	C子机组 m子机组;
	S成绩 m成绩;
	C实时轨迹 m轨迹;
	std::mutex m成绩锁;
public:	//变量
	t标志 m标志;
	float m低速渐变;	//[0(高速),1(低速)]
	float m复活时间;	//减
	float m抑制子弹 = 0, m抑制炸弹 = 0;
	//C边框文本 m成绩文本;
	t向量2 m方向键;
	const C游戏速度 *m游戏速度 = nullptr;
	std::vector<std::shared_ptr<I图形>> ma玩家成绩;
	std::unique_ptr<C玩家子弹发射器> m发射炸弹;
};
}	//namespace 东方山寨