#pragma once
#include "音频包含.h"
#include "基础_数组.h"
namespace 东方山寨 {
class C声音工厂;
class C播放控制;
//音频引擎
class C音频引擎 {
public:
	void f初始化();
	void f计算();
	void f销毁();
	C声音工厂 &fg声音工厂();
	C播放控制 &fg播放控制();
	C属性数组<tp声音> &fg声音();
	std::unique_ptr<音频::C音频> m音频;
	std::unique_ptr<C播放控制> m播放控制;
	std::unique_ptr<C声音工厂> m声音工厂;
	C属性数组<tp声音> ma声音;
};
//播放控制
class C播放控制 {
public:
	enum E混合 {
		e音效s,
		e音效m,
		e音效l,
		e音乐,
		e数量,
	};
	static constexpr float c播放间隔 = 1.f / 60.f;
	static constexpr float c音效s = 0.25f;
	static constexpr float c音效m = 0.5f;
	static constexpr float c音效l = 1;
	void f初始化_接口(音频::C音频 &);
	void f计算();
	void f销毁();
	void f播放音效s(const 音频::C声音 &);
	void f播放音效m(const 音频::C声音 &);
	void f播放音效l(const 音频::C声音 &);
	void f播放音乐(const 音频::C声音 &);
	void fs音效音量(float);
	void fs音乐音量(float);
	float fg音效音量() const;
	float fg音乐音量() const;
	音频::C音频 *m音频 = nullptr;
	音频::C播放控制 m播放;
	音频::tp播放 m音乐 = 0;
	tp混合 ma混合[e数量] = {};
};
//声音工厂
class C声音工厂 {
public:
	void f初始化_接口(音频::C音频 &);
	void f初始化_数组(C属性数组<tp声音> &);
	tp声音 f创建声音(int 标识, const std::wstring &);
	音频::C音频 *m音频 = nullptr;
	C属性数组<tp声音> *ma声音 = nullptr;
};
}