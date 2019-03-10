#include "程序.h"
#include "游戏.h"
#include "图形.h"
#include "画子弹.h"
namespace 东方山寨 {
void f载入_画子弹() {
	auto v图形 = C程序::f图形();
	std::pair<E画子弹, I画子弹*> v画子弹表[] = {
		{E画子弹::e正常, new C画子弹_纹理(v图形->v三维)},
		{E画子弹::e线条, new C画子弹_线条(v图形->v二维)},
	};
	auto &va画子弹 = C游戏::fa画子弹接口();
	for (auto &v : v画子弹表) {
		va画子弹.f添加((int)v.first, v.second);
	}
}
}
