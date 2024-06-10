module;
#include "玩家子弹制造机.h"
#include "玩家子弹发射基础.h"
#include "玩家.h"
#include "玩家炸弹扩展.h"
export module 东方山寨.玩家炸弹发射;
export import cflw.工具.单例;
namespace 工具 = cflw::工具;
export namespace 东方山寨 {
class C玩家炸弹发射管理 : public 工具::C弱单例<C玩家炸弹发射管理> {
public:
	C玩家炸弹发射管理() = default;
	void f初始化_环境(const C玩家子弹制造机 &a工厂, C玩家 &a发射环境);
	void f全屏清弹(const t向量2 &坐标 = t向量2::c零, float 最大半径 = 玩家炸弹::C全屏清弹::c最大半径, bool 产生道具 = false) const;
	const C玩家子弹制造机 *m工厂;
	S玩家子弹参数 m参数;
	C玩家发射环境 m发射环境;
};
}	//namespace 东方山寨
module: private;
namespace 东方山寨 {
void C玩家炸弹发射管理::f初始化_环境(const C玩家子弹制造机 &a工厂, C玩家 &a玩家) {
	m工厂 = &a工厂;
	m发射环境.m玩家 = &a玩家;
	m参数.m发射环境 = &m发射环境;
}
void C玩家炸弹发射管理::f全屏清弹(const t向量2 &a坐标, float a半径, bool a道具) const {
	S玩家子弹参数 v参数 = m参数;
	v参数.m坐标 = a坐标;
	m工厂->f产生炸弹<玩家炸弹::C全屏清弹>(v参数, a半径, a道具);
}
}	//namespace 东方山寨