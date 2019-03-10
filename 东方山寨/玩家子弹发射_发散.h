#pragma once
#include "玩家子弹发射基础.h"
namespace 东方山寨 {
namespace 玩家子弹发射 {
class C发散 : public C玩家子弹发射器 {
public:
	struct S属性 {
		static S属性 fc间隔(int 数量, float 发散0, float 发散1, float 并列0, float 并列1);
		static S属性 fc总(int 数量, float 发散0, float 发散1, float 并列0, float 并列1);
		S属性(int 数量, std::pair<float, float> 发散, std::pair<float, float> 间隔);
		int m数量;
		std::pair<float, float> m向外张开角度;
		std::pair<float, float> m水平坐标间隔;
	};
	class C工厂 : public I工厂<C玩家子弹发射器> {
	public:
		C工厂(const S属性 &);
		C玩家子弹发射器 *f接口_新建() const override;
		std::shared_ptr<S属性> m属性;
	};
	C发散(const std::shared_ptr<S属性> &);
	void f接口_产生子弹() override;
private:
	std::shared_ptr<S属性> m属性;
};
}
}