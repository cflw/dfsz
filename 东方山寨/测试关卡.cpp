#include "脚本.h"
class C测试关卡 : public C关卡 {
public:
	C测试关卡() {
		f注册关卡(L"测试关卡");
	}
	class C弹幕 : public C关卡事件 {
	public:
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
				v子弹制造机.m参数.m颜色[0] = t颜色::fc彩虹(m彩虹);
				v子弹制造机.m参数.m速度 = t向量2::fc方向r(200, m方向);
				//int v阶段 = (int)m渐变;
				//if (m阶段 != v阶段) {
				//	m阶段 = v阶段;
				//	switch (m阶段) {
				//	case 0:	//三角形
				//		for (auto v循环0 : v子弹制造机.f循环(3)) {
				//			const t向量2 v前 = v循环0.f计算_速度变换(0, 数学::c二π / v循环0.fg总数());
				//			v循环0.f变换_圆形();
				//			v循环0.f变换_坐标前移(50);
				//			for (auto v循环1 : v子弹制造机.f循环(20)) {

				//			}
				//		}

				//	}
				//}
				for (auto v循环0 : v子弹制造机.f循环(F循环模板_钝多角星(7, 10, 0.1f))) {
					v子弹制造机.f产生子弹<C普通子弹>();
				}
				m方向 += 数学::c二π<float> / 329.f;
			}
		}
		float m渐变 = 0;
		int m阶段 = -1;
		float m彩虹 = 0;
		float m方向 = 0;
		t向量2 ma旧坐标[60];
		t向量2 ma新坐标[60];
		C计时器 m计时{0.5f};
	};
	class C产生敌机 : public C关卡事件 {
	public:
		class C敌机0 : public C敌机 {
		public:
			void f事件_初始化() override {
			}
			void f事件_执行() override {
				if (v计时_移动.f滴答()) {
					const auto &v自机 = C游戏::fg内容().fg自机();
					f运动_相对横坐标随机移动(v自机.m坐标.x, 50, 10, 100);
					//f运动_速度({-100, 0}, 2);
					//v计时_移动.f停止();
				}
				if (v计时_发射.f滴答()) {
					v子弹制造机.m参数.m坐标 = m坐标;
					v子弹制造机.m参数.m速度 = t向量2::fc方向r(50, v方向);
					for (auto v循环0 : v子弹制造机.f循环(10)) {
						v循环0.f变换_圆形();
						v子弹制造机.f产生子弹<C普通子弹>();
					}
					v方向 += 1;
				}
			}
			void f事件_击破() override {
				//图形
				图形模板::f敌机死亡小爆炸(*this);
				//道具
				//auto v道具制造机 = C游戏::fg内容().f工厂_道具();
				//v道具制造机.m参数.m坐标 = m坐标;
				//v道具制造机.m参数.fs属性((int)E道具::e火力);
				//v道具制造机.f产生道具(10);
			}
		private:
			float v方向 = 0;
			C计时器 v计时_移动{3};
			C计时器 v计时_发射{0.5f};
			C子弹制造机 v子弹制造机 = C游戏::fg内容().f工厂_子弹();
		};
		void f事件_执行() override {
			auto v敌机工厂 = C游戏::fg内容().f工厂_敌机();
			v敌机工厂.m参数.fs坐标({0, c框架范围y});
			v敌机工厂.m参数.m目标 = t向量2::c零;
			v敌机工厂.m参数.m移动时间 = 5;
			v敌机工厂.m参数.m样式 = (int)E敌机::e敌机00蓝;
			v敌机工厂.m参数.m生命值 = 10000;
			auto v敌机 = v敌机工厂.f产生敌机<C敌机0>();
			auto v图形工厂 = C游戏::fg资源().f工厂_图形();
			v图形工厂.f产生图形<C分血条>(*v敌机);
			f动作_结束();
		}
	};
	class C产生道具 : public C关卡事件 {
		void f事件_执行() override {
			if (v计时.f滴答()) {
				v道具制造机->f产生道具(v道具组);
			}
		}
		C计时器 v计时 = {2};
		std::shared_ptr<C道具制造机> v道具制造机 = C游戏::fg内容().f工厂_道具p();
		t道具组 v道具组 = {
			{E道具::e残机碎片, 1},
			{E道具::e火力, 100},
			{E道具::e得点, 10}
		};
	};
	class C王战0_1;
	class C王战0_0 : public C王战事件 {
		void f事件_初始化() override {
			C敌机 *v王 = m王战->fg王();
			v王->fs生命值(100);
			m王战->fs时间(11);
		}
		void f事件_执行() override {
			if (v计时.f滴答()) {
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
		C计时器 v计时{0.1f};
	};
	class C王战0_1 : public C王战事件 {
		void f计算难度() {
			const float v动态难度 = C游戏::fg内容().fg难度().fg动态难度();
			v计时.f重置(1 / v动态难度);
		}
		void f事件_初始化() override {
			C敌机 *v王 = m王战->fg王();
			v王->fs生命值(100);
			m王战->fs时间(11);
			f计算难度();
		}
		void f事件_执行() override {
			if (v计时.f滴答()) {
				auto v子弹工厂 = C游戏::fg内容().f工厂_子弹();
				v子弹工厂.m参数.m坐标 = m王战->fg王()->fg坐标();
				v子弹工厂.m参数.m速度 = t向量2::fc方向r(100, v方向 += 1);
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
		C计时器 v计时;
		float v方向 = 0;
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
			auto v图形工厂 = C游戏::fg资源().f工厂_图形();
			v图形工厂.f产生图形<C分血条>(*v敌机);
			//王战
			auto &v王战 = C游戏::fg内容().fg王战控制();
			v王战.f王战开始(10);
			v王战.fs王(v敌机);
			v王战.f事件<C王战0_0>();
			f动作_结束();
		}
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
			m移动 += c帧秒 * 100;
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
		v脚本.f场景<C场景>();
		v脚本.f事件<C弹幕>();
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
			v子弹制造机.m参数.m速度 = {200, 0};
			v子弹制造机.m参数.fs长度(4);
			v子弹制造机.m参数.fs宽度(4);
			v子弹制造机.m参数.fs样式((int)E子弹::e大光弹);
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
				f动作_旋转(60);
			}
		};
		void f事件_执行() override {
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			v子弹制造机.m参数.m速度 = {200, 0};
			v子弹制造机.m参数.fs样式((int)E子弹::e曲线激光);
			v子弹制造机.m参数.fs长度(50);
			for (auto v循环0 : v子弹制造机.f循环(32)) {
				v循环0.f变换_圆形();
				v子弹制造机.f产生子弹<C激光0>();
			}
			f动作_结束();
		}
	};
	class C测试连续子弹 : public C关卡事件 {
	public:
		void f事件_执行() override {
			if (m计时.f滴答()) {
				auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
				v子弹制造机.m参数.m速度 = {100, 0};
				v子弹制造机.m参数.fs样式((int)E子弹::e环圆弹);
				auto v连续 = C连续子弹::C环形工具();
				for (auto v循环0 : v子弹制造机.f循环(64)) {
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
			v子弹制造机.m参数.m速度 = {200, 0};
			v子弹制造机.m参数.fs样式((int)E子弹::e米弹);
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
		void f事件_执行() override {
			auto v子弹制造机 = C游戏::fg内容().f工厂_子弹();
			v子弹制造机.m参数.m速度 = {200, 0};
			v子弹制造机.m参数.fs样式((int)E子弹::e米弹);
			for (auto v循环0 : v子弹制造机.f循环(32)) {
				v循环0.f变换_圆形();
				v子弹制造机.f产生子弹<C射线激光>();
			}
			f动作_结束();
		}
	};
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m关卡->fc脚本();
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
		v脚本.f事件<C测试射线激光>();
		v脚本.f等待(1);
	}
} g测试子弹类;