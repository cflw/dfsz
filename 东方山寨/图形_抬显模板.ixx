﻿export module 东方山寨.图形.抬显模板;
export import 东方山寨.图形.抬显;
import "游戏.h";
import "图形工厂.h";
export namespace 东方山寨::图形模板 {
std::shared_ptr<C总血条> f总血条(int 数量);	//边框上方的绿色血条
std::shared_ptr<C分血条> f分血条(const C敌机 &, const t颜色 & = t颜色::c粉);	//敌机周围的血条
std::shared_ptr<C弹幕时间> f弹幕时间(const C王战时间控制 &);	//上方的倒计时
std::shared_ptr<C符卡文本> f符卡文本(const C符卡控制 &);	//右上角的文本
}	//namespace 东方山寨::图形模板
module: private;
namespace 东方山寨::图形模板 {
std::shared_ptr<C总血条> f总血条(int a数量) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m图层 = (int)E图层::e抬显;
	return v图形工厂.f产生图形<C总血条>(v参数, a数量);
}
std::shared_ptr<C分血条> f分血条(const C敌机 &a敌机, const t颜色 &a颜色) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m图层 = (int)E图层::e抬显;
	return v图形工厂.f产生图形<C分血条>(v参数, a敌机, a颜色);
}
std::shared_ptr<C弹幕时间> f弹幕时间(const C王战时间控制 &a时间) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m图层 = (int)E图层::e抬显;
	return v图形工厂.f产生图形<C弹幕时间>(v参数, a时间);
}
std::shared_ptr<C符卡文本> f符卡文本(const C符卡控制 &a符卡控制) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m图层 = (int)E图层::e抬显;
	return v图形工厂.f产生图形<C符卡文本>(v参数, a符卡控制);
}
}	//namespace 东方山寨::图形模板