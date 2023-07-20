module;
#include "脚本.h"
export module 东方山寨.测试关卡;
using namespace 东方山寨;
enum E测试关卡 {
	e测试关卡 = (int)E关卡::e测试,
	e测试关卡1,
	e测试子弹类
};
class C场景 : public I场景 {
public:
	void f接口_初始化() override {
		auto &ma模型 = C游戏::fg图形().fg模型();
		m模型_夜空 = ma模型[L"模型.夜空.低空"];
		auto &ma纹理 = C游戏::fg图形().fg纹理();
		m纹理_夜空 = ma纹理[L"纹理.夜空.低空"];
		m相机.m坐标 = {0, 0, 100};
		m相机.m目标 = {0, 100, 0};
		m相机.m上方 = {0, 0, 1};
	}
	void f接口_计算() override {
		m移动 += c帧秒<float> * 100;
	}
	void f接口_更新() override {

	}
	void f接口_显示(C画三维 &a) const override {
		a.fs世界矩阵(数学::S矩阵4::c单位);
		a.fs相机(m相机);
		a.fs雾范围(0, 500);
		a.fs纹理(*m纹理_夜空);
		//p.fs物体矩阵(数学::S矩阵4::c单位);
		数学::S世界矩阵3 v物体;
		v物体.m缩放.x = 0.5f;
		v物体.m缩放.y = 0.5f;
		for (const auto &v : C场景循环(m移动, 256, -500, 1000)) {
			v物体.m平移.y = v;
			a.fs物体矩阵(v物体.ft矩阵4());
			a.f画模型(*m模型_夜空);
		}
	}
	tp模型 m模型_夜空 = nullptr;
	const S纹理 *m纹理_夜空 = nullptr;
	float m移动 = 0;
	数学::S相机 m相机;
};
class C测试关卡 : public C关卡 {
public:
	class C弹幕 : public C关卡事件 {
	public:
		using t当前弹幕 = C弹幕;
		class C子弹0 : public C普通子弹 {
		public:
			C子弹0(const t当前弹幕 *a当前弹幕, float a角度, float a旋转角):
				m当前弹幕(a当前弹幕),
				m角度(a角度),
				m初始速度大小(std::get<0>(a当前弹幕->c运动0)),
				m旋转角(a旋转角) {
			}
			void f事件_初始化() override {
				m当前速度方向 = m速度.fg方向r();
			}
			void f事件_执行() override {
				m计时 += c帧秒<float>;
				if (m计时 >= 1) {
					switch (m阶段) {
					case 0:
						m初始速度大小 = std::get<0>(m当前弹幕->c运动1);
						m目标速度大小 = 0;
						m当前速度方向 = m角度;
						break;
					case 1:
						m初始速度大小 = 0;
						m目标速度大小 = 200;
						m当前速度方向 = m角度 + m旋转角;
						break;
					case 2:
						f动作_结束();
						return;
					}
					++m阶段;
					m计时 = 0;
				}
				const float v当前速度大小 = std::lerp(m初始速度大小, m目标速度大小, m计时);
				m速度 = t向量2::fc方向r(v当前速度大小, m当前速度方向);
			}
			const t当前弹幕 *m当前弹幕 = nullptr;
			float m角度 = 0;
			float m旋转角 = 0;
			float m初始速度大小 = 0;
			float m目标速度大小 = 0;
			float m当前速度方向 = 0;
			float m计时 = 0;
			int m阶段 = 0;
		};
		void f事件_初始化() override {
		}
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto v子弹工厂 = C游戏::fg内容().f工厂_子弹();
				v子弹工厂.m参数.m坐标 = {0, 50};
				v子弹工厂.m参数.m速度 = {std::get<0>(c运动0), 0};
				v子弹工厂.m参数.m颜色[0] = t颜色::c紫;
				auto vf随机数 = C游戏::fg内容().f工厂_随机数f(std::uniform_real_distribution<float>(-0.1f, 0.1f));
				for (auto v循环0 : v子弹工厂.f循环(600)) {
					v循环0.f变换_圆形();
					const float v圈数 = v循环0.fg百分比() * 12;
					v子弹工厂.f产生子弹<C子弹0>(this, v圈数 * 数学::c二π<float>, m旋转角 + vf随机数());
				}
				m旋转角 = -m旋转角;
			}
		}
		const std::tuple<float, float> c运动0 = 计算::f静止变速运动(100, 1);
		const std::tuple<float, float> c运动1 = 计算::f静止变速运动(60, 1);
		C计时器 m计时 = {3, 9999};
		float m旋转角 = 数学::c半π<float>;
	};
	class C弹幕_测试难度 : public C关卡事件 {
		void f计算难度() {
			auto &v难度 = C游戏::fg内容().fg难度();
			const float v动态难度 = v难度.fg动态难度();
			m数量 = (int)f难度_数量(v动态难度);
			m速度 = f难度_速度(v动态难度);
		}
		void f事件_初始化() override {
			f计算难度();
		}
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto &v难度 = C游戏::fg内容().fg难度();
				auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
				v子弹制造机.m参数.m颜色[0] = t颜色::c红;
				v子弹制造机.m参数.m坐标 = {0, 100};
				v子弹制造机.m参数.m速度 = t向量2::fc方向r(m速度, 0);
				for (auto v循环0 : v子弹制造机.f循环(m数量)) {
					v循环0.f变换_圆形();
					v子弹制造机.f产生子弹<C普通子弹>();
				}
				v难度.f增加难度({1, 20});
				f计算难度();
			}
		}
		tf难度 f难度_速度 = 难度::F线性插值(100, 200, 300, 500);
		tf难度 f难度_数量 = 难度::F线性插值(1, 30, 40, 50);
		int m数量;
		float m速度;
		C计时器 m计时{0.1f};
	};
	class C弹幕_遮罩 : public C关卡事件 {
	public:
		class C子弹0 : public C普通子弹 {
		public:
			void f事件_遮罩(I遮罩 &a遮罩) override {
				if (a遮罩.f判定_点(m坐标)) {
					const auto[v坐标, v速度] = 物理::f反弹运动y(m坐标, m速度, 0);
					m坐标 = v坐标;
					m速度 = v速度;
				}
			}
		};
		class C遮罩0 : public C遮罩<遮罩::C下> {
		public:
			using t基类 = C遮罩<遮罩::C下>;
			using t基类::t基类;
			void f事件_初始化() override {
				m标志[e子弹] = true;
			}
		};
		void f事件_初始化() override {
			auto v遮罩制造机 = C游戏::fg内容().f工厂_遮罩();
			v遮罩制造机.f产生遮罩<C遮罩0>(0);
		}
		void f事件_执行() override {
			if (!m计时.f滴答()) {
				return;
			}
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			v子弹制造机.m参数.m颜色[0] = t颜色::c红;
			v子弹制造机.m参数.m样式 = (int)E子弹::e鳞弹;
			v子弹制造机.m参数.m坐标 = {0, 100};
			v子弹制造机.m参数.m速度 = t向量2::fc方向r(100, m方向);
			v子弹制造机.f产生子弹<C子弹0>();
			m方向 += 0.1f;
		}
		float m方向 = 0;
		C计时器 m计时{0.01f};
	};
	class C弹幕_边框 : public C关卡事件 {
	public:
		class C子弹0 : public C普通子弹 {
		public:
			C子弹0(const 边框::C矩形 &a边框):
				mp边框(&a边框) {
			}
			void f事件_执行() override {
				if (mp边框->f反弹(m坐标, m速度, 0, 1)) {
					m颜色[0] = t颜色::c蓝;
					f动作_结束();
				}
			}
			const 边框::C矩形 *mp边框 = nullptr;
		};
		void f事件_初始化() override {
			C游戏::fg内容().f游戏_切换边框(m边框);
		}
		void f事件_执行() override {
			m时间 += c帧秒<float>;
			const float v移动 = std::sin(m时间) * c边框范围x;
			const float v左 = std::max(-c边框范围x + v移动, -c边框范围x);
			const float v右 = std::min(c边框范围x + v移动, c边框范围x);
			m边框.m矩形.fs左右(v左, v右);
			if (m计时.f滴答()) {
				auto v子弹工厂 = C游戏::fg内容().f工厂_子弹();
				v子弹工厂.m参数.m坐标.x = m边框.m矩形.fg中心().x;
				v子弹工厂.m参数.m坐标.y = 100;
				v子弹工厂.m参数.m速度 = t向量2::fc方向r(200, m时间 * 10);
				v子弹工厂.f产生子弹<C子弹0>(m边框);
			}
		}
		void f事件_结束() override {
			C游戏::fg内容().f游戏_切换边框(边框::C矩形::c标准);
		}
		C计时器 m计时{0.01f};
		边框::C矩形 m边框;
		float m时间 = 0;
	};
	class C产生敌机 : public C关卡事件 {
	public:
		class C敌机0 : public C敌机 {
		public:
			void f事件_初始化() override {
			}
			void f事件_执行() override {
				if (m计时_移动.f滴答()) {
					const auto &v自机 = C游戏::fg内容().fg自机();
					f运动_相对横坐标随机移动(v自机.m坐标.x, 50, 10, 100);
					//f运动_速度({-100, 0}, 2);
					//m计时_移动.f停止();
				}
				if (m计时_发射.f滴答()) {
					m子弹制造机.m参数.m坐标 = m坐标;
					m子弹制造机.m参数.m速度 = t向量2::fc方向r(50, m方向);
					for (auto v循环0 : m子弹制造机.f循环(10)) {
						v循环0.f变换_圆形();
						m子弹制造机.f产生子弹<C普通子弹>();
					}
					m方向 += 1;
				}
			}
			void f事件_击破() override {
				//图形
				图形模板::f敌机死亡小爆炸(*this);
				//道具
				auto v道具制造机 = C游戏::fg内容().f工厂_道具();
				v道具制造机.m参数.m坐标 = m坐标;
				v道具制造机.m参数.fs属性((int)E道具::e火力);
				v道具制造机.f产生道具(10);
			}
		private:
			float m方向 = 0;
			C计时器 m计时_移动{3};
			C计时器 m计时_发射{0.5f};
			C子弹制造机 m子弹制造机 = C游戏::fg内容().f工厂_子弹();
		};
		void f事件_执行() override {
			auto v敌机工厂 = C游戏::fg内容().f工厂_敌机();
			v敌机工厂.m参数.fs入场({0, c框架范围y});
			v敌机工厂.m参数.m目标 = t向量2::c零;
			v敌机工厂.m参数.m移动时间 = 5;
			v敌机工厂.m参数.m样式 = (int)E敌机::e敌机00蓝;
			v敌机工厂.m参数.m生命值 = 1000;
			auto v敌机 = v敌机工厂.f产生敌机<C敌机0>();
			图形模板::f分血条(*v敌机);
			auto v护盾0 = 敌机模板::f护盾(*v敌机, 1000, t颜色::c蓝);
			auto v护盾1 = 敌机模板::f护盾(*v护盾0, 1000, t颜色::c绿);
			f动作_结束();
		}
	};
	class C产生道具 : public C关卡事件 {
	public:
		class C遮罩0 : public C遮罩<遮罩::C圆形> {
		public:
			using t基类 = C遮罩<遮罩::C圆形>;
			using t基类::t基类;
			void f事件_初始化() override {
				m标志[e道具] = true;
			}
			void f遮罩_道具(C道具 &a道具) override {
				if (f判定_点(a道具.m坐标)) {
					const auto [v坐标, v速度] = 物理::f反弹运动_圆形(a道具.m坐标, a道具.m速度, m圆形);
					a道具.m坐标 = v坐标;
					a道具.m速度 = v速度;
				}
			};
		};
		void f事件_初始化() {
			m道具制造机->m参数.m坐标 = t向量2(0, 50);
			auto v遮罩工厂 = C游戏::fg内容().f工厂_遮罩();
			v遮罩工厂.f产生遮罩<C遮罩0>(t圆形::fc坐标半径(t向量2(0, -50), 50));
		}
		void f事件_执行() override {
			if (m计时.f滴答()) {
				m道具制造机->f产生道具(m道具组);
			}
			m道具制造机->f产生道具(m道具组);
			f动作_结束();
		}
		C计时器 m计时 = {2};
		std::shared_ptr<C道具制造机> m道具制造机 = C游戏::fg内容().f工厂_道具p();
		t道具组 m道具组 = {
			{E道具::e残机碎片, 1},
			{E道具::e火力, 100},
			{E道具::e得点, 10}
		};
	};
	class C产生图形 : public C关卡事件 {
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto f随机x = C游戏::fg资源().f工厂_随机数f(std::uniform_real_distribution<float>(-c边框范围x, c边框范围x));
				for (int i = 0; i != 1; ++i) {
					const t向量2 v坐标 = {f随机x(), f随机x()};
					图形模板::f敌机死亡小爆炸0(v坐标, t向量2::c零, t颜色::c白);
				}
			}
		}
		C计时器 m计时{0.02f};
	};
	class C王战0_1;
	class C王战0_0 : public C王战事件 {
		void f事件_初始化() override {
			C敌机 *v王 = m王战->fg王();
			v王->fs生命值(1000);
			m王战->f弹幕_s时间(1);
		}
		void f事件_执行() override {
			if (m计时.f滴答()) {
				t子弹工厂 v子弹工厂 = C游戏::fg内容().f工厂_子弹();
				v子弹工厂.m参数.m坐标 = m王战->fg王()->m坐标;
				v子弹工厂.m参数.fs速度_到自机(100);
				v子弹工厂.f产生子弹<C普通子弹>();
			}
		}
		void f事件_王被击破(C敌机 &p) override {
			图形模板::f敌机死亡小爆炸(p);
			m关卡->f动作_增加难度(1);
		}
		void f事件_时间到() override {
		}
		void f事件_结束() override {
			m王战->f事件<C王战0_1>();
			m王战->f总血条减一();
			S关卡标题 v标题;
			v标题.m标题 = L"1";
			C关卡效果::f显示标题(v标题);
		}
		C计时器 m计时{0.1f};
	};
	class C王战0_1 : public C王战事件 {
		void f计算难度() {
			const float v动态难度 = C游戏::fg内容().fg难度().fg动态难度();
			m计时.f重置(1 / v动态难度);
		}
		void f事件_初始化() override {
			C敌机 *v王 = m王战->fg王();
			v王->fs生命值(1000);
			m王战->f弹幕_s时间(5);
			m王战->f弹幕_s符卡(L"符卡", 10000);
			f计算难度();
			m背景 = 图形模板::f符卡淡入背景(*C游戏::fg图形().fg纹理()[L"纹理.符卡背景.夜雀0"]);
			图形模板::f符卡立绘(L"立绘.纳兹琳.组件.符卡", 符卡立绘::F单向变速(符卡立绘::c左下));
		}
		void f事件_执行() override {
			if (m计时.f滴答()) {
				//auto v子弹工厂 = C游戏::fg内容().f工厂_子弹();
				//v子弹工厂.m参数.m坐标 = m王战->fg王()->fg坐标();
				//v子弹工厂.m参数.m速度 = t向量2::fc方向r(100, m方向 += 1);
				//for (auto v循环0 : v子弹工厂.f循环(10)) {
				//	v循环0.f变换_圆形();
				//	v子弹工厂.f产生子弹<C普通子弹>();
				//}
				auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
				auto vf随机方向 = C游戏::fg内容().f工厂_随机数f(std::uniform_real_distribution<float>(0, 数学::c二π<float>));
				v子弹制造机.m参数.m速度 = t向量2::fc方向r(100, vf随机方向());
				v子弹制造机.f产生子弹<C普通子弹>();
			}
		}
		void f事件_王被击破(C敌机 &p) {
			图形模板::f敌机死亡小爆炸(p);
			f动作_暂停(1);
		}
		void f事件_时间到() override {
			f动作_暂停(1);
		}
		void f事件_结束() override {
			C敌机 *v王 = m王战->fg王();
			图形模板::f敌机死亡小爆炸(*v王);
			v王->f动作_死亡();
			m王战->f王战_结束();
			//m背景->f动作_消失();
			m关卡->f动作_结束关卡(1);
		}
		std::shared_ptr<C背景> m背景;
		C计时器 m计时{0.1f};
		float m方向 = 0;
	};
	class C王战0 : public C关卡事件 {
		void f事件_初始化() override {
			//敌机
			auto v敌机工厂 = C游戏::fg内容().f工厂_敌机();
			v敌机工厂.m参数.fs入场({0, c框架范围y});
			v敌机工厂.m参数.m目标 = t向量2::c零;
			v敌机工厂.m参数.m移动时间 = 5;
			v敌机工厂.m参数.m样式 = (int)E敌机::e敌机00蓝;
			auto v敌机 = v敌机工厂.f产生王();
			图形模板::f分血条(*v敌机);
			//王战
			auto &v王战 = C游戏::fg内容().fg王战控制();
			v王战.f王战_开始(10);
			v王战.fs王(v敌机);
			v王战.f事件<C王战0_0>();
			f动作_结束();
		}
	};
	class C王入场 : public C关卡事件 {
	public:
		void f事件_初始化() override {
			f入场();
		}
		static void f入场() {
			f王入场(E敌机::e敌机00蓝, {0, c框架范围y}, t向量2::c零);
		}
	};
	class C切换关卡 : public C关卡事件 {
	public:
		void f事件_执行() override {
			//m关卡->f切换关卡(C关卡管理::fg关卡(e测试关卡1), 1);
			f动作_结束();
			m关卡->f动作_结束关卡(1);
		}
	};
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m控制->fc脚本();
		//关卡事件列表
		//v脚本.f场景<C场景>();
		//v脚本.f事件<C产生道具>();
		//v脚本.f事件<C弹幕>();
		//v脚本.f事件<C产生敌机>();
		//v脚本.f等待(3);
		//v脚本.f事件<C切换关卡>();
		v脚本.f事件<C王战0>();
		//v脚本.f等待(1);
		v脚本.f事件(C关卡效果::F显示标题({L"主标题", L"场景"}));

		//对话
	
		//C对话脚本 v对话;
		////static C空白立绘建造机 v立绘;
		//static C静态立绘建造机 v立绘{*C游戏::fg资源().fg静态立绘().ma属性[L"立绘.灵梦"]};
		//const auto &va文本 = C游戏::fg资源().fg普通文本();
		//v对话.f显示立绘(v立绘, 0, E对话方向::e从左向右);
		//v对话.f对话(va文本[L"s1.boss0.name"], E对话方向::e从左向右);
		//v对话.f显示立绘(v立绘, 1, E对话方向::e从右向左);
		//v对话.f对话(va文本[L"s1.boss1.name"], E对话方向::e从右向左);
		//v对话.f立绘聚焦(0);
		//v对话.f立绘表情(0, E立绘表情::e高兴);
		//v对话.f对话(va文本[L"s1a.0"], E对话方向::e从左向右);
		//v对话.f立绘聚焦(1);
		//v对话.f立绘表情(1, E立绘表情::e伤心);
		//v对话.f对话(va文本[L"s1a.1"], E对话方向::e从右向左);
		//v脚本.f对话(v对话);
		//m关卡->f切换关卡(C关卡管理::fg关卡(L"测试子弹类"));
	}
};
class C测试关卡1 : public C关卡 {
public:
	class C随机子弹 : public C关卡事件 {
	public:
		void f事件_执行() override {
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			auto vf随机方向 = C游戏::fg内容().f工厂_随机数f(std::uniform_real_distribution<float>(0, 数学::c二π<float>));
			v子弹制造机.m参数.m速度 = t向量2::fc方向r(100, vf随机方向());
			v子弹制造机.f产生子弹<C普通子弹>();
			f动作_结束();
		}
	};
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m控制->fc脚本();
		m控制->f设置场景(nullptr);
		m控制->f动作_结束关卡(1);
		v脚本.f事件(C关卡效果::F显示标题({L"测试关卡1", L"场景1"}));
	}
};
class C测试子弹类 : public C关卡 {
public:
	class C测试普通子弹 : public C关卡事件 {
	public:
		void f事件_执行() override {
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			v子弹制造机.m参数.m速度 = {100, 0};
			for (auto v循环0 : v子弹制造机.f循环(10)) {
				v循环0.f变换_速度(20, 1);
				v子弹制造机.f产生子弹<C普通子弹>();
				for (auto v循环1 : v子弹制造机.f循环(50)) {
					v循环1.f变换_圆形();
					v子弹制造机.f产生子弹<C普通子弹>();
				}
			}
			f动作_结束();
		}
	};
	class C测试大子弹 : public C关卡事件 {
	public:
		void f事件_执行() override {
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			v子弹制造机.m参数.m速度 = {0, -10};
			v子弹制造机.m参数.fs长度(200);
			v子弹制造机.m参数.fs宽度(200);
			v子弹制造机.m参数.fs样式((int)E子弹::e大光弹);
			v子弹制造机.m参数.fs绘制((int)E图形管线::e子弹正常);
			for (auto v循环0 : v子弹制造机.f循环(1)) {
				v循环0.f变换_圆形();
				v子弹制造机.f产生子弹<C大子弹>();
			}
			//v子弹制造机.f产生子弹<C大子弹>();
			f动作_结束();
		}
	};
	class C测试曲线激光 : public C关卡事件 {
	public:
		class C激光0 : public C曲线激光 {
		public:
			C激光0(float a旋转):
				m旋转(a旋转)  {
			}
			void f事件_执行() override {
				f动作_旋转d(m旋转);
			}
			float m旋转;
		};
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
				v子弹制造机.m参数.m速度 = {200, 0};
				v子弹制造机.m参数.fs样式((int)E子弹::e曲线激光);
				v子弹制造机.m参数.fs长度(200);
				v子弹制造机.m参数.fs绘制((int)E图形管线::e子弹正常);
				for (auto v循环0 : v子弹制造机.f循环(36)) {
					v循环0.f变换_圆形();
					v子弹制造机.f产生子弹<C激光0>(m旋转);
				}
				m旋转 = -m旋转;
			}
		}
		C计时器 m计时{1};
		float m旋转 = 60;
	};
	class C测试连续子弹 : public C关卡事件 {
	public:
		static constexpr int c数量 = 64;
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
				v子弹制造机.m参数.m速度 = {0, -100};
				v子弹制造机.m参数.fs样式((int)E子弹::e环圆弹);
				v子弹制造机.m参数.fs绘制((int)E图形管线::e子弹正常);
				auto v连续 = C连续子弹::C环形工具();
				for (auto v循环0 : v子弹制造机.f循环(c数量)) {
					v循环0.f变换_圆形();
					auto vp子弹 = v子弹制造机.f产生子弹<C连续子弹>();
					v连续 += vp子弹;
				}
			}
		}
		C计时器 m计时{1};
	};
	class C测试直线激光 : public C关卡事件 {
	public:
		void f事件_执行() override {
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			v子弹制造机.m参数.m速度 = {50, 0};
			v子弹制造机.m参数.fs样式((int)E子弹::e米弹);
			v子弹制造机.m参数.fs绘制((int)E图形管线::e子弹正常);
			v子弹制造机.m参数.fs长度(20);
			for (auto v循环0 : v子弹制造机.f循环(32)) {
				v循环0.f变换_圆形();
				v子弹制造机.f产生子弹<C直线激光>();
			}
			f动作_结束();
		}
	};
	class C测试射线激光 : public C关卡事件 {
	public:
		class C激光0 : public C射线激光 {
			void f事件_执行() override {
				f动作_旋转d(10);
			}
		};
		void f事件_执行() override {
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			v子弹制造机.m参数.m速度 = {100, 0};
			v子弹制造机.m参数.fs样式((int)E子弹::e米弹);
			v子弹制造机.m参数.fs绘制((int)E图形管线::e子弹正常);
			for (auto v循环0 : v子弹制造机.f循环(1)) {
				v循环0.f变换_圆形();
				v子弹制造机.f产生子弹<C激光0>();
			}
			f动作_结束();
		}
	};
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m控制->fc脚本();
		//v脚本.f场景<C场景>();
		v脚本.f等待(0.5f);
		//v脚本.f事件<C测试普通子弹>();
		//v脚本.f等待(1);
		v脚本.f事件<C测试大子弹>();
		//v脚本.f等待(1);
		//v脚本.f事件<C测试曲线激光>();
		//v脚本.f等待(1);
		//v脚本.f事件<C测试连续子弹>();
		//v脚本.f等待(1);
		//v脚本.f事件<C测试直线激光>();
		//v脚本.f等待(1);
		//v脚本.f事件<C测试射线激光>();
		v脚本.f等待(1);
	}
};
//==============================================================================
// 注册关卡
//==============================================================================
auto g测试关卡0 = C关卡工厂<C测试关卡>(e测试关卡);
auto g符卡练习0 = C符卡练习关卡工厂<C测试关卡::C王入场, C测试关卡::C王战0_1>((int)E关卡::e符卡);
auto g测试关卡1 = C关卡工厂<C测试关卡1>(e测试关卡1);
auto g测试子弹类 = C关卡工厂<C测试子弹类>(e测试子弹类);