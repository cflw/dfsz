#pragma once
#include <map>
#include "��ѧ����.h"
#include "����.h"
#include "�Ի�����.h"
namespace ����ɽկ {
class C�ؿ��¼�;
class C�ؿ��ű�;
class C��������;
class I����;
typedef void(*tf�ؿ�)(C�ؿ��ű� &);
class C�ؿ�;
class C�л�;
//=============================================================================
// �ؿ�����
//=============================================================================
enum class E�ؿ��¼�״̬ {
	e��ʼ��,
	e����,
};
class C�ؿ��¼�״̬ {
public:
	C�ؿ��¼�״̬(const std::shared_ptr<C�ؿ��¼�> &);
	C�ؿ��¼� &fg�¼�() const;
	bool fi����() const;
	bool fi����() const;	//������෴
	void f����();
public:
	std::shared_ptr<C�ؿ��¼�> m�¼�;
	t��־ m��־;
	float m��ʼʱ�� = 0;
	float m�ȴ� = 0;
};
class C�ؿ����� {
public:
	enum E��־ {
		e��ս,
		e�Ի�,
	};
	typedef std::vector<std::shared_ptr<C�ؿ��¼�״̬>> ta�¼�;
	void f��ʼ��_����(C�������� &, C�Ի����� &);
	void f��ʼ��(C�ؿ� &);
	void f����();
	void f�л��ؿ�(C�ؿ� &, float = 0);
	C�ؿ��ű� fc�ű�();
	void f����();
	void f����¼�(std::shared_ptr<C�ؿ��¼�״̬>);
	void f���ó���(std::shared_ptr<I����>);
	void f����_��ʼ�Ի�(tp�Ի��ű�);	//��ʼ�Ի�,ͬʱ��ͣ����ʱ��
	std::shared_ptr<C�ؿ��¼�״̬> fg�¼�(int);
	void f����_�����Ѷ�();
	void f����_�����Ѷ�(const boost::rational<int> &);
	float fg����ʱ��() const;
private:
	void f�ϲ��¼�();
public:
	ta�¼� ma�¼�;
	ta�¼� ma���¼�;
	C�������� *m���� = nullptr;
	C�Ի����� *m�Ի� = nullptr;
	t��־ m��־;
	float m����ʱ�� = 0;
	C�ؿ� *m�ؿ� = nullptr;
};
class C�ؿ��ű� {	//�������ӹؿ����ݵ���
public:
	C�ؿ��ű�(C�ؿ����� *);
	//�ű��¼�
	std::shared_ptr<C�ؿ��¼�״̬> operator ()(const std::function<void()> &);	//�� f�¼� һ��
	template<typename t, typename...t����> std::shared_ptr<C�ؿ��¼�״̬> f�¼�(t���� &&...);
	std::shared_ptr<C�ؿ��¼�״̬> f�¼�(const std::function<void()> &);
	template<typename t, typename...t����> std::shared_ptr<C�ؿ��¼�״̬> f����(t���� &&...);
	std::shared_ptr<C�ؿ��¼�״̬> f�Ի�(tp�Ի��ű�);
	//�ű�ʱ��
	void fʱ���(float);
	void f�ȴ�(float);
private:
	std::shared_ptr<C�ؿ��¼�״̬> f���¼�_(const std::shared_ptr<C�ؿ��¼�> &);
private:
	C�ؿ����� *m�ؿ����� = nullptr;
	float m��ʼʱ�� = 0;
	float m����ʱ�� = 0;
};
//=============================================================================
// �ؿ��ӿ�
//=============================================================================
class C�ؿ� : public I�¼� {
public:
	using ta�ؿ� = std::map<std::wstring, C�ؿ� *>;
	static ta�ؿ� &fg�ؿ���();
	static C�ؿ� &fgע��ؿ�(const std::wstring &);
	void fע��ؿ�(const std::wstring &);
	C�ؿ����� *m�ؿ� = nullptr;
};
//�ؿ��¼�
class C�ؿ��¼� : public I�¼� {
public:
	void f����_��ͣ(float);
	void f����_����();
	float fg��ͣʱ��() const;
public:
	C�ؿ��¼�״̬ *m״̬ = nullptr;
	C�ؿ����� *m�ؿ�;
};
//����ؿ��¼�
class C�ؿ�Ч���¼� : public C�ؿ��¼� {
public:
	C�ؿ�Ч���¼�(const std::function<void()> &);
	void f�¼�_ִ��() override;
	std::function<void()> mf;
};
class C�ؿ������¼� : public C�ؿ��¼� {
public:
	C�ؿ������¼�(const std::shared_ptr<I����> &);
	void f�¼�_ִ��() override;
	std::shared_ptr<I����> m����;
};
class C�л��ؿ��¼� : public C�ؿ��¼� {
public:
	C�л��ؿ��¼�(C�ؿ� &);
	void f�¼�_ִ��() override;
	C�ؿ� *m�ؿ� = nullptr;
};
//=============================================================================
// �ؿ��ű�ʵ��
//=============================================================================
template<typename t, typename...t����> std::shared_ptr<C�ؿ��¼�״̬> C�ؿ��ű�::f�¼�(t���� &&...a����) {
	static_assert(std::is_base_of<C�ؿ��¼�, t>::value, "����̳���C�ؿ��¼�");
	return f���¼�_(std::make_shared<t>(a����...));
}
template<typename t, typename...t����> std::shared_ptr<C�ؿ��¼�״̬> C�ؿ��ű�::f����(t���� &&...a����) {
	static_assert(std::is_base_of<I����, t>::value, "����̳���I����");
	return f���¼�_(std::make_shared<C�ؿ������¼�>(std::make_shared<t>(a����...)));
}
}	//namespace ����ɽկ