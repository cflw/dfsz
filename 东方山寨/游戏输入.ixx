module;
#include "输入.h"
#include "数学包含.h"
export module 东方山寨.游戏输入;
namespace 输入 = cflw::输入;
export namespace 东方山寨 {
class I游戏输入 {	//接收输入并传递到游戏中
public:
	virtual ~I游戏输入() = default;
	virtual void f更新() = 0;	//更新输入数据,在游戏输入中调用
	virtual void f事件_切换关卡(int a关卡) {}	//用来切换录像和回放的关卡
	virtual const t向量2 &fg方向() const = 0;
	virtual const 输入::C按键组 &fg按键组() const = 0;
};
class C游戏输入 final : public I游戏输入 {
public:
	C游戏输入(C输入引擎 &a输入):
		mp输入(&a输入) {
	}
	void f更新() override {
		const auto &v方向键 = mp输入->fg方向();
		m方向 = t向量2(v方向键.x, v方向键.y);
	}
	const t向量2 &fg方向() const override {
		return m方向;
	}
	const 输入::C按键组 &fg按键组() const override {
		return mp输入->fg按键组();
	}
	const C输入引擎 *mp输入 = nullptr;
	t向量2 m方向;
};
}	//namespace 东方山寨