module;
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <cflw时间.h>
#include "输入.h"
#include "游戏常量.h"
#include "游戏设置.h"
#include "程序设置.h"
#include "玩家.h"
export module 东方山寨.录像_功能;
import 东方山寨.录像_结构;
namespace 时间 = cflw::时间;
namespace 输入 = cflw::输入;
export namespace 东方山寨 {
class C录像机 {
public:
	void f新建录像(const S程序设置 &a程序设置, const S游戏设置 &a游戏设置) {
		m录像 = std::make_unique<C录像>();
		m录像->m录像信息.m玩家名称 = a程序设置.m玩家名称;
		m录像->m录像信息.m游戏设置 = a游戏设置;
		m录像->m录像信息.m开始时间 = 时间::fg现在();
	}
	void f结束录像() {
		m录像->m录像信息.m结束时间 = 时间::fg现在();
		m录像->m录像信息.m关卡数量 = m录像->m关卡信息.size();
	}
	void f新建关卡(int a关卡, const C玩家::S成绩 &a玩家成绩) {
		if (m关卡信息) {
			m关卡信息->m分数 = a玩家成绩.m得分;
		}
		m关卡信息 = &m录像->m关卡信息.emplace_back();
		m关卡信息->m关卡 = a关卡;
		++m录像->m录像信息.m关卡数量;
		ma录像帧 = &m录像->m关卡数据[a关卡];
		ma录像帧->reserve(c计算频率<int> * 60 * 10);	//预留10分钟
	}
	void f录制帧(const S录像帧 &a帧) {	//在游戏计算中生成录像帧
		ma录像帧->push_back(a帧);
		++m关卡信息->m帧数;
	}
public:
	std::unique_ptr<C录像> m录像;	//正在记录的录像
	S关卡信息 *m关卡信息 = nullptr;	//正在记录的关卡
	std::vector<S录像帧> *ma录像帧 = nullptr;
	size_t m帧 = 0;	//用来统计数量
};
class C回放机 {
public:
	void f回放关卡(int a关卡) {
		ma录像帧 = &m录像->m关卡数据.at(a关卡);
		m帧 = 0;
	}
	const S录像帧 &f回放帧() {
		return ma录像帧->at(m帧++);
	}
	float fg时间() const {
		return (float)m帧 / 240.f;
	}
public:
	std::unique_ptr<const C录像> m录像;	//正在回放的录像
	const std::vector<S录像帧> *ma录像帧 = nullptr;
	size_t m帧 = 0;	//用来计算时间
};
}	//namespace 东方山寨