#pragma once
#include "����.h"
#include "����_����.h"
#include "ͼ������.h"
#include "ͼ��_ͼƬ.h"
#include "����ӵ��������.h"
namespace ����ɽկ {
class C���;
struct S�Ի�����;
class C����ӵ�������;
class C�Ի� : public C����ͼƬ���� {
public:
	enum class E�������� {
		e�� = 0,
		e�� = -1,
		e�� = 1,
	};
	static constexpr float c�ж��뾶 = 0.5f;
	static constexpr float c�����뾶 = 32;
	static constexpr float c���߰뾶 = 32;
	static constexpr float c�ƶ��ٶ� = 360;
	static constexpr float c�����ٶ� = 8 / 120.f;
	static constexpr float c����ʱ�� = 0.2f;
	static constexpr float c�޾���ʱ�� = -9999;
	void f�ؿ���ʼ��();
	void f����_�ƶ�(const t����2 &�����);	//0�ٶ�ʱҲҪ����
	void f����_�����ӵ�();
	void f����_ֹͣ�����ӵ�();
	void f����();
	void f����_�ƶ���Χ����();
	void f����();
	void f��ʾ() const;
	void f�����(C��� &);
	//����
	void fs�Ի�����(const S�Ի����� *);
	const t����2 &fg����() const;
	const SͼƬ�������� &fgͼƬ��������() const override;
	const S������� &fg�������() const;
	tԲ�� fg�ж���() const;
	tԲ�� fg������() const;
	tԲ�� fg�����ߵ�() const;
	tԲ�� fg�Ե��ߵ�() const;
	t����2 fg�ƶ�Ԥ��(float aʱ�� = 1) const;
	bool fi�޵�() const;
	bool fi����() const;
	//״̬
	void f�е�();	//���Ի����ӵ��ж��е���
	void f����();	//����Ҽ����е���
	//����
	void f����_s͸����(float);
public:
	t����2 m����;
	t����2 m�ƶ�;
	const S�Ի����� *m�Ի�����;
	float m�޵�ʱ�� = 0;
	float m����ʱ�� = c�޾���ʱ��;
	const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
	std::unique_ptr<C����ӵ�������> m�����ӵ�;
};
struct S�Ի����� : public SͼƬ�������� {
	float m�ж��뾶;
	float m�����뾶;
	float m���߰뾶;
	float m�ƶ��ٶ�;
	t��չָ��<I����<C����ӵ�������>> m�����ӵ�;
	t����ָ��<S����ӵ�����> m�ӵ�����;
};
}