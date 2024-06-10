#pragma once
#include <concepts>
#include "基础.h"
#include "基础_事件.h"
#include "基础_游戏对象.h"
#include "数学包含.h"
namespace 东方山寨 {
class C数组计数;
class C自机;
class C子机;
class C道具;
class C敌机;
//遮罩主要与各游戏对象判定,本身不做处理
class I遮罩形状 {	//遮罩形状接口
public:
	virtual bool f判定_点(const t向量2 &) const;
	virtual bool f判定_圆形(const t圆形 &) const;
};
template<typename t遮罩形状> concept T遮罩形状 = std::derived_from<t遮罩形状, I遮罩形状>;
//游戏遮罩接口
class I遮罩 : public I事件 {
public:
	enum E标志 {
		e使用,
		e动作,	//决定是否调用 f事件_执行
		e子弹,
		e敌机,
		e道具,
		e玩家,	//对自机和子机生效
		e玩家子弹,	//对玩家子弹生效,不含炸弹
		e自定义,
	};
	//对象
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用();
	//形状
	virtual const I遮罩形状 &f接口_g形状() const = 0;
	bool f判定_点(const t向量2 &) const;
	bool f判定_圆形(const t圆形 &) const;
	//遮罩事件
	virtual void f遮罩_敌机(C敌机 &);
	virtual void f遮罩_自机(C自机 &);
	virtual void f遮罩_子机(C子机 &);
	virtual void f遮罩_道具(C道具 &);
	//动作
	void f动作_结束();
public:
	C数组计数 *m计数指针 = nullptr;
	t标志 m标志;
};
//遮罩类
template<T遮罩形状 t遮罩形状>
class C遮罩 : public t遮罩形状, public I遮罩 {
public:
	using t遮罩形状::t遮罩形状;
	using t遮罩形状::f判定_点;
	using t遮罩形状::f判定_圆形;
	const I遮罩形状 &f接口_g形状() const override {
		return *this;
	}
};
}	//namespace 东方山寨