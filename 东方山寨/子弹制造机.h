#pragma once
#include <optional>
#include <experimental/generator>
#include "数学包含.h"
#include "基础.h"
#include "基础_属性数组.h"
#include "基础_扩展数组.h"
#include "基础_对象数组.h"
#include "基础_缓冲数组.h"
namespace 东方山寨 {
typedef std::optional<float> t计算;
class C子弹;
struct S子弹属性;
class I图形管线;
class I画子弹;
class C子弹图形缓冲;
//==============================================================================
// 子弹制造机
//==============================================================================
struct S子弹参数 {	//产生子弹所需的参数
	t向量2 m坐标;
	t向量2 m速度;
	t向量2 m缩放;
	t向量2 m长宽;	//缩放和长宽只能同时存在一个,长宽会覆盖缩放
	t颜色 m颜色[2];
	float m出现 = 0;
	C属性数组<S子弹属性>::t指针 m样式;
	C扩展数组<I画子弹>::t指针 m绘制;
	C属性数组<S子弹属性>::t指针 m缓存_样式;
	C扩展数组<I画子弹>::t指针 m缓存_绘制;
	S子弹参数();	//设置默认值
	void fs坐标(const t向量2 &);
	void fs速度(const t向量2 &);
	void fs速度_到自机(float 大小);
	void fs顶色(const t颜色 &);
	void fs底色(const t颜色 &);
	void fs长度(float);
	void fs宽度(float);
	void fs样式(int);
	void fs绘制(int);
	void fs子弹基础(const C子弹 &);
	void fs立即出现(bool);
};
class C子弹制造机 {
public:
public:
	class C循环 {
	public:
		class C变换 {
		public:
			C变换(C循环 &a循环, int a计数) :
				m参数(&a循环.m工厂->m参数), m计数(a计数), m总数(a循环.m总数) {
			}
			//循环基本属性
			int fg计数() const;
			int fg总数() const;
			float fg百分比() const;
			//循环计算函数
			float f计算(t标志) const;
			float f计算_正弦波(float 振幅, float 频率, t计算 计算 = std::nullopt) const;
			t向量2 f计算_速度变换(float 大小, float 方向, t计算 计算 = std::nullopt) const;
			t向量2 f计算_速度线性插值(const t向量2 &, t计算 计算 = std::nullopt) const;
			t向量2 f计算_速度平滑插值(const t向量2 &, t计算 计算 = std::nullopt) const;
			//循环变换函数
			void f变换_备份();
			void f变换_还原();
			void f变换_圆形(int = 1, t计算 计算 = std::nullopt);	//方向按圆形变化
			void f变换_椭圆(float 短轴变化);
			void f变换_扇形(float 间隔, t计算 计算 = std::nullopt);
			void f变换_速度(float 大小, float 方向, t计算 计算 = std::nullopt);	//速度大小方向直接变化
			void f变换_速度线性插值(const t向量2 &, t计算 计算 = std::nullopt);	//xy分量的插值
			void f变换_速度平滑插值(const t向量2 &, t计算 计算 = std::nullopt);	//大小方向分量的插值
			void f变换_颜色(int, const t颜色 &, t计算 计算 = std::nullopt);	//颜色插值
			void f变换_坐标插值(const t向量2 &, t计算 计算 = std::nullopt);
			void f变换_坐标前移(float, t计算 计算 = std::nullopt);
			void f变换_坐标平移(const t向量2 &移动, t计算 计算 = std::nullopt);	//绝对移动
		public:
			S子弹参数 *m参数 = nullptr, *m备份 = nullptr;
			int m计数 = 0, m总数 = 0;
		};
		class C迭代器 {
		public:
			C迭代器(C循环 &a循环, int a计数):
				m循环(&a循环), m计数(a计数) {
			}
			C迭代器 &operator ++() {
				++m计数;
				m循环->f参数还原();
				return *this;
			}
			bool operator !=(const C迭代器 &a) {
				return m计数 != a.m计数;
			}
			C变换 operator *() {
				return C变换(*m循环, m计数);
			}
			C循环 *m循环;
			int m计数;
		};
		C循环(C子弹制造机 &, int 次数);
		//循环控制
		C迭代器 begin() {
			return C迭代器(*this, 0);
		}
		C迭代器 end() {
			return C迭代器(*this, m总数);
		}
		C变换 f变换(int a次数) {
			return C变换(*this, a次数);
		}
		void f参数备份() {
			m参数备份 = m工厂->m参数;
		}
		void f参数还原() {
			m工厂->m参数 = m参数备份;
		}
	public:
		S子弹参数 m参数备份;
		C子弹制造机 *m工厂 = nullptr;
		int m总数 = 0;
	};
	class C实现 {
	public:
		void f初始化_环境(const C游戏速度 &);
		void f初始化_数组(C对象数组<C子弹> &, C缓冲数组<C子弹图形缓冲> &);
		void f初始化_资源(const C属性数组<S子弹属性> &, const C扩展数组<I图形管线> &);
		bool fi有空();
		void f产生子弹(const std::shared_ptr<C子弹> &, S子弹参数 &);//调用"f产生子弹"前需要调用"f分配"
		C对象数组<C子弹> *ma子弹 = nullptr;
		C缓冲数组<C子弹图形缓冲> *ma子弹图形缓冲 = nullptr;
		const C游戏速度 *m游戏速度 = nullptr;
		const C属性数组<S子弹属性> *ma子弹属性 = nullptr;
		const C扩展数组<I图形管线> *ma画子弹 = nullptr;
	};
	using t循环生成器 = std::experimental::generator<C循环::C变换>;
	using tf循环模板 = std::function<t循环生成器(C子弹制造机&)>;
	C子弹制造机(C实现 &);
	~C子弹制造机();
	std::shared_ptr<C子弹> f产生子弹();	//产生普通子弹
	template<typename t, typename...t参数> std::shared_ptr<t> f产生子弹(t参数 &&...a参数);
	C循环 f循环(int);
	t循环生成器 f循环(const tf循环模板 &);
	bool f实现_i有空();
	void f实现_产生子弹(const std::shared_ptr<C子弹> &);//不检查数组直接产生,如果不能产生会触发断言
	S子弹参数 m参数;	//公开的
private:
	C实现 *m实现 = nullptr;	//在游戏实现中管理子弹制造机实现
};
template<typename t, typename...t参数> std::shared_ptr<t> C子弹制造机::f产生子弹(t参数 &&...a参数) {
	static_assert(std::is_base_of<C子弹, t>::value);
	if (f实现_i有空()) {
		std::shared_ptr<t> v子弹 = std::make_shared<t>(a参数...);
		f实现_产生子弹(v子弹);
		t::f接口_具体类型初始化(v子弹);
		return v子弹;
	}
	return nullptr;
}
//==============================================================================
// 循环模板
//==============================================================================
C子弹制造机::tf循环模板 F循环模板_旋转(float 旋转角, int 次数, int 边细分, float 坐标前移倍数 = 1, float 速度插值 = 1);
C子弹制造机::tf循环模板 F循环模板_正多边形(int 角数, int 边细分, float 坐标前移倍数 = 1, float 速度插值 = 1);
C子弹制造机::tf循环模板 F循环模板_锐多角星(int 角数, int 边细分, float 坐标前移倍数 = 1, float 速度插值 = 1);
C子弹制造机::tf循环模板 F循环模板_钝多角星(int 角数, int 边细分, float 坐标前移倍数 = 1, float 速度插值 = 1);
}