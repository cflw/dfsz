#pragma once
#include "玩家子弹发射基础.h"
#include "玩家子弹扩展.h"
namespace 东方山寨::玩家子弹发射 {
class C自机基础 : public C玩家子弹发射器 {
public:
	void f接口_产生子弹() override;
};
class C灵梦诱导 : public C玩家子弹发射器 {
public:
	static constexpr float c速度大小 = 800;
	static constexpr float c发射间隔 = 0.06f;
	C灵梦诱导();
	void f接口_产生子弹() override;
};
class C灵梦集中 : public C玩家子弹发射器 {
public:
	void f接口_产生子弹() override;
};
class C魔理沙贯穿 : public C玩家子弹发射器 {
public:
	void f接口_计算() override;
	void f接口_产生子弹() override;
	bool fi有子弹() const;
private:
	std::shared_ptr<玩家子弹::C贯穿> m子弹;
};
class C魔理沙范围 : public C玩家子弹发射器 {
public:
	static constexpr float c发射间隔 = 0.1f;
	static constexpr float c速度大小 = 600;
	C魔理沙范围();
	void f接口_产生子弹() override;
};
}