#include "界面音频.h"
#include "游戏.h"
namespace 东方山寨 {
void C界面音频::f初始化(C音频引擎 &a引擎) {
	m播放控制 = &a引擎.fg播放控制();
	const auto f添加音效 = [this, &va声音 = a引擎.fg声音()](用户界面::E声音 a声音, const std::wstring &a名称) {
		if (auto v声音 = va声音[a名称]) {
			ma声音.emplace(a声音, v声音.get());
		}
	};
	f添加音效(用户界面::E声音::e方向键切换按键焦点, L"声音.界面音效.选择");
}
void C界面音频::f播放音效(const 用户界面::S声音参数 &a) const {
	if (auto v找 = ma声音.find(a.m声音); v找 != ma声音.end()) {
		m播放控制->f播放音效l(*v找->second);
	}
}
}	//namespace 东方山寨