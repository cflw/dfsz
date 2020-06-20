#include "脚本.h"
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
		a.fs纹理(m纹理_夜空);
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
	tp模型 m模型_夜空;
	tp纹理 m纹理_夜空;
	float m移动 = 0;
	数学::S相机 m相机;
};
class C测试关卡 : public C关卡 {
public:
	C测试关卡() {
		f注册关卡(L"测试关卡");
	}
	class C弹幕 : public C关卡事件 {
	public:
		void f事件_执行() override {
			if (m计时.f滴答()) {
				const t向量2 v发射坐标 = t向量2(0, 50) + t向量2::fc方向r(50, t);
				auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
				constexpr float c子弹速度 = 400;
				const float v子弹方向 = 计算::f预判自机狙(fg自机坐标(), fg自机速度(0.5f), v发射坐标, c子弹速度);
				v子弹制造机.m参数.m坐标 = v发射坐标;
				v子弹制造机.m参数.m速度 = t向量2::fc方向r(c子弹速度, v子弹方向);
				for (auto v循环0 : v子弹制造机.f循环(200)) {
					v循环0.f变换_圆形();
					v子弹制造机.f产生子弹<C普通子弹>();
				}
			}
			t += c帧秒<float>;
		}
		float t = 0;
		C计时器 m计时{0.1f};
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
			v敌机工厂.m参数.fs坐标({0, c框架范围y});
			v敌机工厂.m参数.m目标 = t向量2::c零;
			v敌机工厂.m参数.m移动时间 = 5;
			v敌机工厂.m参数.m样式 = (int)E敌机::e敌机00蓝;
			v敌机工厂.m参数.m生命值 = 100;
			auto v敌机 = v敌机工厂.f产生敌机<C敌机0>();
			//auto v图形工厂 = C游戏::fg资源().f工厂_图形();
			//v图形工厂.f产生图形<C分血条>(*v敌机);
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
			v王->fs生命值(100);
			m王战->fs时间(11);
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
			v王->fs生命值(100);
			m王战->fs时间(11);
			f计算难度();
		}
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto v子弹工厂 = C游戏::fg内容().f工厂_子弹();
				v子弹工厂.m参数.m坐标 = m王战->fg王()->fg坐标();
				v子弹工厂.m参数.m速度 = t向量2::fc方向r(100, m方向 += 1);
				for (auto v循环0 : v子弹工厂.f循环(10)) {
					v循环0.f变换_圆形();
					v子弹工厂.f产生子弹<C普通子弹>();
				}
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
		}
		C计时器 m计时;
		float m方向 = 0;
	};
	class C王战0 : public C关卡事件 {
		void f事件_初始化() override {
			//敌机
			auto v敌机工厂 = C游戏::fg内容().f工厂_敌机();
			v敌机工厂.m参数.fs坐标({0, c框架范围y});
			v敌机工厂.m参数.m目标 = t向量2::c零;
			v敌机工厂.m参数.m移动时间 = 5;
			v敌机工厂.m参数.m样式 = (int)E敌机::e敌机00蓝;
			auto v敌机 = v敌机工厂.f产生王();
			图形模板::f分血条(*v敌机);
			//王战
			auto &v王战 = C游戏::fg内容().fg王战控制();
			v王战.f王战开始(10);
			v王战.fs王(v敌机);
			v王战.f事件<C王战0_0>();
			f动作_结束();
		}
	};
	class C切换关卡 : public C关卡事件 {
	public:
		void f事件_执行() override {
			m关卡->f切换关卡(fg注册关卡(L"测试关卡1"), 1);
			f动作_结束();
		}
	};
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m关卡->fc脚本();
		//关卡事件列表
		//v脚本.f场景<C场景>();
		//v脚本.f事件<C产生道具>();
		v脚本.f事件<C弹幕_边框>();
		//v脚本.f事件<C产生敌机>();
		//v脚本.f等待(3);
		//v脚本.f事件<C切换关卡>();
		//v脚本.f事件<C王战0>();
		//v脚本.f等待(1);
		//v脚本.f事件(C关卡效果::F显示标题({L"主标题", L"场景"}));

		//对话
	
		//C对话脚本 v对话;
		//static C简单工厂<I对话立绘> v立绘工厂;
		//const auto &va文本 = C游戏::fg资源().fg普通文本();
		//v对话.f显示立绘(v立绘工厂, 0, false);
		//v对话.f对话(va文本[L"s1.boss0.name"], false);
		//v对话.f显示立绘(v立绘工厂, 1, true);
		//v对话.f对话(va文本[L"s1.boss1.name"], true);
		//v对话.f立绘聚焦(0);
		//v对话.f对话(va文本[L"s1a.0"], false);
		//v对话.f立绘聚焦(1);
		//v对话.f对话(va文本[L"s1a.1"], true);
		//v脚本.f对话(v对话);
		//m关卡->f切换关卡(fg注册关卡(L"测试子弹类"));
	}
} g测试关卡;
class C测试关卡1 : public C关卡 {
public:
	C测试关卡1() {
		f注册关卡(L"测试关卡1");
	}
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m关卡->fc脚本();
		m关卡->f设置场景(nullptr);
	}
} g测试关卡1;
class C测试子弹类 : public C关卡 {
public:
	C测试子弹类() {
		f注册关卡(L"测试子弹类");
	}
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
			v子弹制造机.m参数.m速度 = {10, 0};
			v子弹制造机.m参数.fs长度(4);
			v子弹制造机.m参数.fs宽度(4);
			v子弹制造机.m参数.fs样式((int)E子弹::e大光弹);
			v子弹制造机.m参数.fs绘制((int)E画子弹::e高光);
			for (auto v循环0 : v子弹制造机.f循环(16)) {
				v循环0.f变换_圆形();
				v子弹制造机.f产生子弹<C大子弹>();
			}
			f动作_结束();
		}
	};
	class C测试曲线激光 : public C关卡事件 {
	public:
		class C激光0 : public C曲线激光 {
		public:
			void f事件_执行() override {
				f动作_旋转d(60);
			}
		};
		void f事件_执行() override {
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			v子弹制造机.m参数.m速度 = {200, 0};
			v子弹制造机.m参数.fs样式((int)E子弹::e曲线激光);
			v子弹制造机.m参数.fs长度(50);
			v子弹制造机.m参数.fs绘制((int)E画子弹::e高光);
			for (auto v循环0 : v子弹制造机.f循环(32)) {
				v循环0.f变换_圆形();
				v子弹制造机.f产生子弹<C激光0>();
			}
			f动作_结束();
		}
	};
	class C测试连续子弹 : public C关卡事件 {
	public:
		static constexpr int c数量 = 4;
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
				v子弹制造机.m参数.m速度 = {0, -100};
				v子弹制造机.m参数.fs样式((int)E子弹::e环圆弹);
				v子弹制造机.m参数.fs绘制((int)E画子弹::e高光);
				auto v连续 = C连续子弹::C连接工具();
				for (auto v循环0 : v子弹制造机.f循环(c数量)) {
					v循环0.f变换_扇形(0.2f);
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
			v子弹制造机.m参数.fs绘制((int)E画子弹::e高光);
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
			v子弹制造机.m参数.fs绘制((int)E画子弹::e高光);
			for (auto v循环0 : v子弹制造机.f循环(1)) {
				v循环0.f变换_圆形();
				v子弹制造机.f产生子弹<C激光0>();
			}
			f动作_结束();
		}
	};
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m关卡->fc脚本();
		//v脚本.f场景<C场景>();
		v脚本.f等待(0.5f);
		//v脚本.f事件<C测试普通子弹>();
		//v脚本.f等待(1);
		//v脚本.f事件<C测试大子弹>();
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
} g测试子弹类;