#pragma once
#include <boost/rational.hpp>
#include "����.h"
#include "����_����.h"
#include "ͼ��_ͼƬ.h"
#include "����ӵ��������.h"
#include "�ӻ��ƶ��ӿ�.h"
namespace ����ɽկ {
class C���;
class C����ӵ�������;
struct S�ӻ�����;
class I�ӻ��ƶ�;
class C�ӻ� : public C����ͼƬ���� {
public:
	void f����_�ƶ�(const t����2 &Ŀ��);
	void f����_����(const t����2 &Ŀ��);
	void f����();
	void f����();
	void f��ʾ() const;
	const t����2 &fg����() const;
	const SͼƬ�������� &fgͼƬ��������() const;
	void f����_����();
	void f����_��ʧ();
	void f����_s͸����(float);
public:
	t����2 m����, mĿ������;
	float m����֡;
	const C��Ϸ�ٶ� *m��Ϸ�ٶ�;
	const S�ӻ����� *m�ӻ�����;
	std::unique_ptr<C����ӵ�������> m����;
};
class C�ӻ��� {
public:
	void fs�ӻ�����(const S�ӻ����� *);
	const S�ӻ����� &f�ӻ�����() const;
	void f�ؿ���ʼ��();
	void f����_�����ӵ�();
	void f����_ֹͣ�����ӵ�();
	void f����();
	void f����();
	void f��ʾ() const;
	void f�����(C��� &);
	void f����();
	int fgĿ���ӻ���() const;
	ѭ��::C��Χ<std::vector<C�ӻ�>> feʹ��();
	ѭ��::C��Χ<const std::vector<C�ӻ�>> feʹ��c() const;
public:
	std::vector<C�ӻ�> ma�ӻ�;
	const S�ӻ����� *m�ӻ�����;
	std::unique_ptr<I�ӻ��ƶ�> m�ӻ��ƶ�;
	int m����;
	const boost::rational<int> *m����;	//ָ��C���::S�ɼ�::m����
};
struct S�ӻ����� : public SͼƬ�������� {
	int m��������;
	t��չָ��<I����<C����ӵ�������>> m����;
	t��չָ��<I����<I�ӻ��ƶ�>> m�ƶ�;
	t����ָ��<S����ӵ�����> m�ӵ�����;
};

}