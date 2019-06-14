#pragma once
#include <map>
#include <用户界面_接口.h>
#include "音频引擎.h"
namespace 东方山寨 {
class C界面音频 : public 用户界面::I音频设备 {
public:
	void f初始化(C音频引擎 &);
	void f播放音效(const 用户界面::S声音参数 &) override;
	C播放控制 *m播放控制 = nullptr;
	std::map<用户界面::E声音, 音频::t声音 *> ma声音;
};
}	//namespace 东方山寨