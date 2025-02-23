export module 东方山寨.对话控制;
export import <map>;
export import "基础.h";
export import "基础_对象工厂.h";
export import "输入.h";
export import 东方山寨.对话基础;
import 东方山寨.关卡;
import 东方山寨.图形.对话框;
import "游戏.h";
import "图形工厂.h";
import "输入.h";
import 东方山寨.图形.对话立绘;
export namespace 东方山寨 {
class C关卡控制;
class C对话框;
class I对话立绘;
class I图形建造机;
class C对话控制 {
public:
	static constexpr float c跳过间隔 = 0.1f;
	static constexpr float c按住确定跳过的等待时间 = 1;
	~C对话控制();
	void f初始化_环境(C关卡控制 &);
	void f计算();
	void f输入按键(const 输入::C按键组 &);
	void f开始(tp对话脚本);
	void f结束();
	void f按键控制_下一个();	//按z时调用
	void f按键控制_跳过();	//按ctrl,或持续按z时调用
	bool fi对话中() const;
	bool fi结束() const;
	void f添加对话图形(const std::shared_ptr<I粒子> &);	//集中控制
	//控制
	void f控制_新对话框(const S对话参数_对话 &);
	void f控制_显示立绘(const S对话参数_显示立绘 &);
	void f控制_立绘状态(const S对话参数_立绘状态 &);
	void f控制_立绘表情(const S对话参数_立绘表情 &);
	void f控制_等待();	//等待按键才能执行下一个事件,和继续互斥
	void f控制_继续();	//继续执行下一个事件,和等待互斥
private:
	void f内部_执行对话事件();
	void f内部_结束对话框();
	void f内部_立绘焦点(I对话立绘 *);
	tp对话脚本 m对话脚本;
	ta对话事件::const_iterator m当前对话;
	std::shared_ptr<C对话框> m当前对话框;
	std::map<int, std::shared_ptr<I对话立绘>> ma对话立绘;
	std::vector<std::shared_ptr<I粒子>> ma对话图形;	//对话过程中产生的图形,对话结束后强制消失
	I对话立绘 *m当前立绘 = nullptr;
	C关卡控制 *m关卡 = nullptr;
	float m跳过等待 = 0;	//减
	float m自动等待 = 0;	//加,没有操作时等一段时间自动下一个对话
	float m自动间隔 = 10;	//时间根据字符数调整
	float m输入_确定时间 = 0;	//按住z的时间
	bool m等待 = false;
};
}	//namespace 东方山寨
module: private;
namespace 东方山寨 {
//==============================================================================
// 对话控制
//==============================================================================
C对话控制::~C对话控制() {
}
void C对话控制::f初始化_环境(C关卡控制 &a关卡) {
	m关卡 = &a关卡;
}
void C对话控制::f计算() {
	m跳过等待 -= c帧秒<float>;
	m自动等待 += c帧秒<float>;
	if (m跳过等待 <= 0) {	//防止同时间内调用下一个
		if (m自动等待 > m自动间隔) {
			f内部_执行对话事件();
		}
	}
}
void C对话控制::f输入按键(const 输入::C按键组 &a按键) {
	const auto v确定键 = a按键.fg按键((输入::t索引)E按键::e确定);
	if (v确定键.fi按下()) {
		m输入_确定时间 += c帧秒<float>;
		if (v确定键.fi刚按下()) {
			f按键控制_下一个();
			return;
		}
		if (m输入_确定时间 >= c按住确定跳过的等待时间) {
			f按键控制_跳过();
			return;
		}
	} else {
		m输入_确定时间 = 0;
	}
	const auto v跳过键 = a按键.fg按键((输入::t索引)E按键::e跳过);
	if (v跳过键.fi按下()) {
		f按键控制_跳过();
		return;
	}
}
void C对话控制::f开始(tp对话脚本 a脚本) {
	m对话脚本 = a脚本;
	m当前对话 = m对话脚本->cbegin();
	f内部_执行对话事件();
	m跳过等待 = c跳过间隔;
	m关卡->f事件_开始对话();
}
void C对话控制::f结束() {
	//对话框
	f内部_结束对话框();
	//立绘
	for (const auto &[v标识, v立绘] : ma对话立绘) {
		v立绘->f动作_结束();
	}
	for (const auto &v粒子 : ma对话图形) {
		v粒子->fs剩余生命(0.5f);
	}
	ma对话立绘.clear();
	m关卡->f事件_结束对话();
}
void C对话控制::f按键控制_下一个() {
	f内部_执行对话事件();
}
void C对话控制::f按键控制_跳过() {
	if (m跳过等待 <= 0) {	//防止同时间内调用下一个
		f内部_执行对话事件();
	}
}
bool C对话控制::fi对话中() const {
	return m关卡->m标志[C关卡控制::E标志::e对话];
}
bool C对话控制::fi结束() const {
	return !fi对话中();
}
void C对话控制::f添加对话图形(const std::shared_ptr<I粒子> &a图形) {
	ma对话图形.push_back(a图形);
}
void C对话控制::f控制_新对话框(const S对话参数_对话 &a) {
	f内部_结束对话框();
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m图层 = (int)E图层::e对话;
	m当前对话框 = v图形工厂.f产生图形<C对话框>(v参数, a);
}
void C对话控制::f控制_显示立绘(const S对话参数_显示立绘 &a) {
	assert(ma对话立绘.find(a.m标识) == ma对话立绘.end());	//必须没有
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m图层 = (int)E图层::e立绘;
	v参数.m标志[I对话立绘::E初始化标志::e方向] = ft对话方向(a.m方向);
	auto v图形0 = v图形工厂.f产生图形(v参数, *a.m立绘工厂);
	assert(v图形0 != nullptr);	//可能因为达到图形上限而导致异常.这里不应该用断言,以后改掉
	assert(std::dynamic_pointer_cast<I对话立绘>(v图形0));	//检查创建的图形对象是否是对话立绘
	auto v图形 = std::static_pointer_cast<I对话立绘>(v图形0);
	ma对话立绘[a.m标识] = v图形;
	f内部_立绘焦点(v图形.get());
}
void C对话控制::f控制_立绘状态(const S对话参数_立绘状态 &a) {
	auto vp立绘 = ma对话立绘.at(a.m标识).get();
	switch (a.m状态) {
	case E立绘状态::e聚焦:
		f内部_立绘焦点(vp立绘);
		break;
	case E立绘状态::e消失:
		vp立绘->f动作_结束();
		ma对话立绘.erase(a.m标识);
		break;
	default:
		throw;
	}
}
void C对话控制::f控制_立绘表情(const S对话参数_立绘表情 &a) {
	auto vp立绘 = ma对话立绘.at(a.m标识).get();
	vp立绘->f动作_表情(a.m表情);
}
void C对话控制::f控制_等待() {
	m等待 = true;
}
void C对话控制::f控制_继续() {
	m等待 = false;
}
void C对话控制::f内部_执行对话事件() {
	m等待 = false;
	//循环脚本
	if (m当前对话 == m对话脚本->cend()) {
		f结束();
		return;
	}
	while (m当前对话 != m对话脚本->cend()) {
		(*m当前对话)(*this);
		++m当前对话;
		if (m等待) {
			break;
		}
	}
	//其它
	m跳过等待 = c跳过间隔;
	m自动等待 = 0;
}
void C对话控制::f内部_结束对话框() {
	if (m当前对话框) {
		m当前对话框->f动作_结束();
		m当前对话框 = nullptr;
	}
}
void C对话控制::f内部_立绘焦点(I对话立绘 *a立绘) {
	if (m当前立绘) {
		m当前立绘->f动作_失焦();
	}
	a立绘->f动作_聚焦();
	m当前立绘 = a立绘;
}
}	//namespace 东方山寨