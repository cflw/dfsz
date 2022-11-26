module;
#include "程序实现.h"
#include "游戏常量.h"
#include "数学包含.h"
#include "界面引擎.h"
#include "界面图形.h"
#include "游戏.h"
export module 东方山寨.游戏状态控制;
import 东方山寨.游戏输入控制;
export namespace 东方山寨 {
class C游戏状态控制 {
public:
	C游戏状态控制(C程序实现 &a实现):
		mp实现(&a实现) {
	}
	static constexpr float c切换渐变速度 = c帧秒<float> *2;
	using tf切换 = bool (C游戏状态控制:: *)();
	void f切换计算() {	//每帧都会调用
		if (m新状态 != E游戏状态::e无) {
			bool vi已切换 = (this->*mf切换)();
			if (vi已切换) {
				m状态 = m新状态;
				m新状态 = E游戏状态::e无;
				m切换渐变 = 0;
			}
		} else {	//不在切换中
			m黑屏渐变 = 数学::f线性渐变<float>(m黑屏渐变, 0, c切换渐变速度);
		}
	}
	void f切换游戏状态(E游戏状态 a状态, E窗口 a窗口 = E窗口::e无) {
		m新状态 = a状态;
		m切换窗口 = a窗口;
		mf切换 = fg切换函数(m状态, a状态);
	}
	bool fi游戏中() const {
		return m状态 == E游戏状态::e游戏中 || m状态 == E游戏状态::e游戏菜单;
	}
	//游戏状态切换函数
	static tf切换 fg切换函数(E游戏状态 a前, E游戏状态 a后) {
		using t切换 = std::tuple<E游戏状态, E游戏状态, tf切换>;
		static const t切换 ca切换[] = {
			t切换(E游戏状态::e载入中, E游戏状态::e主菜单, &f切换_载入中_主菜单),
			t切换(E游戏状态::e载入中, E游戏状态::e游戏中, &f切换_载入中_游戏中),
			t切换(E游戏状态::e主菜单, E游戏状态::e游戏中, &f切换_主菜单_游戏中),
			t切换(E游戏状态::e游戏中, E游戏状态::e游戏菜单, &f切换_游戏中_游戏菜单),
			t切换(E游戏状态::e游戏菜单, E游戏状态::e游戏中, &f切换_游戏菜单_游戏中),
			t切换(E游戏状态::e游戏中, E游戏状态::e主菜单, &f切换_游戏中_主菜单),
			t切换(E游戏状态::e游戏菜单, E游戏状态::e主菜单, &f切换_游戏中_主菜单),
			t切换(E游戏状态::e游戏中, E游戏状态::e通关, &f切换_游戏中_通关),
			t切换(E游戏状态::e主菜单, E游戏状态::e退出程序, &f切换_主菜单_退出),
		};
		for (const auto &[v前, v后, vf切换] : ca切换) {
			if (v前 == a前 && v后 == a后) {
				return vf切换;
			}
		}
		throw;	//没有合适的切换函数
	}
	bool f切换_载入中_主菜单() {
		f切入_主菜单();
		m黑屏渐变 = 1;
		return true;
	}
	bool f切换_载入中_游戏中() {
		f切入_游戏中();
		m黑屏渐变 = 1;
		return true;
	}
	bool f切换_主菜单_游戏中() {
		if (f切换_渐变滴答()) {
			f切出_主菜单();
			f切入_游戏中();
			return true;
		}
		return false;
	}
	bool f切换_游戏中_主菜单() {
		if (f切换_渐变滴答()) {
			f切出_游戏中();
			f切入_主菜单();
			return true;
		}
		return false;
	}
	bool f切换_游戏中_游戏菜单() {
		f切入_游戏菜单();
		return true;	//弹出什么窗口在 f游戏中弹出菜单 中确定
	}
	bool f切换_游戏菜单_游戏中() {
		if ((m切换渐变 += c切换渐变速度) >= 1) {
			f切出_游戏菜单();
			return true;
		}
		return false;
	}
	bool f切换_游戏中_通关() {
		if (f切换_渐变滴答()) {
			f切出_游戏中();
			f切入_主菜单();	//没有通关画面,先回到主菜单
			return true;
		}
		return false;
	}
	bool f切换_主菜单_退出() {
		if (f切换_渐变滴答()) {
			f切出_主菜单();
			SendMessageW(mp实现->m窗口, WM_CLOSE, 0, 0);
		}
		return false;
	}
	bool f切换_渐变滴答() {
		m切换渐变 += c切换渐变速度;
		m黑屏渐变 += c切换渐变速度;
		return m切换渐变 >= 1;
	}
	void f切入_主菜单() {
		mp实现->m界面->f切换下个窗口(E窗口::e主菜单);
	}
	void f切入_游戏中() {
		//m任务_资源.wait();
		mp实现->m游戏->f开始();
	}
	void f切入_游戏菜单() {
		mp实现->m界面->f切换下个窗口(m切换窗口);
	}
	void f切出_主菜单() {
		mp实现->m界面->f关闭窗口();
		mp实现->m界面图形->f关闭图形();
	}
	void f切出_游戏中() {
		mp实现->m游戏->f结束();
	}
	void f切出_游戏菜单() {
		mp实现->m界面->f关闭窗口();
	}
public:
	C程序实现 *mp实现 = nullptr;
	E游戏状态 m状态 = E游戏状态::e载入中;
	E游戏状态 m新状态 = E游戏状态::e无;
	tf切换 mf切换 = nullptr;	//在状态切换时调用的函数
	E窗口 m切换窗口;
	float m切换渐变 = 0;
	float m黑屏渐变 = 0;
};
}	//namespace 东方山寨