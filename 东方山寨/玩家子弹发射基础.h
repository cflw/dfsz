#pragma once
#include "基础.h"
#include "玩家子弹制造机.h"
namespace 东方山寨 {
class I玩家发射环境 {
public:
	virtual C玩家 &fg玩家() const = 0;
	virtual t向量2 fg发射坐标() const = 0;
	virtual t向量2 fg中心坐标() const = 0;	//自机的坐标
	virtual t向量2 fg相对坐标() const;
	virtual float fg相对方向r() const;
	virtual const C游戏速度 &fg游戏速度() const;
	virtual const float &fg低速渐变() const;
};
class C玩家发射环境 : public I玩家发射环境 {
public:
	C玩家发射环境(C玩家 &);
	C玩家 &fg玩家() const override;
	t向量2 fg发射坐标() const override;
	t向量2 fg中心坐标() const override;
	const C游戏速度 &fg游戏速度() const override;
	t向量2 fg相对坐标() const override;
	float fg相对方向r() const override;
	const float &fg低速渐变() const override;
	C玩家 *m玩家 = nullptr;
};
class C玩家子弹发射器 {
public:
	static constexpr float c前方向 = 数学::c半π<float>;
	static constexpr float c发射时间 = 0.2f;
	static constexpr float c发射间隔 = 0.05f;
	static constexpr float c速度大小 = 2000;
	C玩家子弹发射器();
	//初始化
	void f初始化_发射环境(std::shared_ptr<I玩家发射环境>);
	void f初始化_时间变量();
	//基础
	void f基础_一键计算(float = c发射间隔);	//在 f接口_计算 中调用
	void f基础_计算时间();
	void f基础_发射间隔(float);	//在发射子弹后调用
	bool f基础_i可发射() const;
	bool f基础_i发射间隔() const;
	bool f基础_i不发射() const;
	void f基础_复位();
	void f基础_s子弹属性(const S玩家子弹属性 *);
	void f属性_s发射间隔(float);
	//接口
	virtual void f接口_初始化();
	virtual void f接口_计算();
	virtual void f接口_复位();
	virtual void f接口_产生子弹();	//由"f接口_计算"调用, 产生子弹
	//外部控制
	void f发射();
	void f计算();
protected:
	//环境
	std::shared_ptr<I玩家发射环境> m发射环境;
	std::shared_ptr<C玩家子弹制造机> m子弹制造机;
	//变量
	float m剩余时间 = 0;	//剩余发射时间
	float m间隔时间 = 0;	//发射间隔
	float m发射时间 = 0;	//已发射时间
	float m发射间隔 = c发射间隔;
};
}	//namespace 东方山寨