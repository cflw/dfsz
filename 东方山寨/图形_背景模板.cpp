#include "游戏.h"
#include "图形引擎.h"
#include "图形工厂.h"
#include "图形_背景.h"
namespace 东方山寨::图形模板 {
std::shared_ptr<C背景> f全屏静态背景(const S纹理 &a纹理) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m图层 = (int)E图层::e背景;
	v参数.m纹理 = a纹理;
	return v图形工厂.f产生图形<C背景>(v参数, C游戏::fg图形().fg背景管理());
}
std::shared_ptr<C背景> f符卡展开背景(const S纹理 &a纹理, const t向量2 &a坐标) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m透明度 = 0.5f;
	v参数.m图层 = (int)E图层::e前景;
	v参数.m纹理 = a纹理;
	return v图形工厂.f产生图形<C背景>(v参数, C游戏::fg图形().fg背景管理());
}
std::shared_ptr<C背景> f符卡淡入背景(const S纹理 &a纹理) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m透明度 = 0.5f;
	v参数.m图层 = (int)E图层::e前景;
	v参数.m纹理 = a纹理;
	return v图形工厂.f产生图形<C背景>(v参数, C游戏::fg图形().fg背景管理());
}
}	//namespace 东方山寨::图形模板