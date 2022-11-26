module;
#include <cflw时间.h>
#include "输入.h"
#include "数学包含.h"
#include "玩家.h"
export module 东方山寨.游戏输入_录像;
import 东方山寨.游戏输入;
import 东方山寨.录像_结构;
import 东方山寨.录像_功能;
namespace 时间 = cflw::时间;
namespace 输入 = cflw::输入;
export namespace 东方山寨 {
class C游戏输入_录像 final : public I游戏输入 {
public:
	C游戏输入_录像(C输入引擎 &a输入, const 时间::C计帧器 &a计帧器):
		mp输入(&a输入),
		mp计帧器(&a计帧器) {
	}
	void f更新() override {
		const auto &v方向键 = mp输入->fg方向();
		m方向 = t向量2(v方向键.x, v方向键.y);
		S录像帧 v帧;
		v帧.m方向 = m方向;
		v帧.m帧速率 = lround(mp计帧器->fg帧速率());
		const auto &v按键组 = mp输入->fg按键组();
		for (输入::t数量 i = 0; i != v按键组.m使用数量; ++i) {
			v帧.m按键[i] = v按键组.m这次[i];
		}
		mp录像->f录制帧(v帧);
	}
	void f事件_切换关卡(int a关卡, const void *a保存数据) override {
		mp录像->f新建关卡(a关卡, *(const C玩家::S成绩 *)a保存数据);
	}
	const t向量2 &fg方向() const override {
		return m方向;
	}
	const 输入::C按键组 &fg按键组() const override {
		return mp输入->fg按键组();
	}
	const C输入引擎 *mp输入 = nullptr;
	C录像机 *mp录像 = nullptr;
	const 时间::C计帧器 *mp计帧器 = nullptr;
	t向量2 m方向;
};
class X回放结束 {
};
class C游戏输入_回放 final : public I游戏输入 {
public:
	C游戏输入_回放(C输入引擎 &a输入) {
		mp输入 = &a输入;
	}
	void f更新() override {
		if (mp回放->fi结束()) {
			throw X回放结束();
		}
		mp当前帧 = &mp回放->f回放帧();
		m按键组.f覆盖上次();
		for (输入::t数量 i = 0; i != c按键数量; ++i) {
			m按键组.m这次[i] = mp当前帧->m按键[i];
		}
	}
	void f事件_切换关卡(int a关卡, const void *a保存数据) override {
		mp回放->f回放关卡(a关卡);
	}
	const t向量2 &fg方向() const override {
		return mp当前帧->m方向;
	}
	const 输入::C按键组 &fg按键组() const override {
		return m按键组;
	}
	C回放机 *mp回放 = nullptr;
	const C输入引擎 *mp输入 = nullptr;
	const S录像帧 *mp当前帧 = nullptr;
	输入::C按键组 m按键组{c按键数量};
};
}	//namespace 东方山寨