#pragma once
#include <cflw��ѧ_���.h>
#include "����.h"
#include "����_����.h"
#include "��ʶ.h"
#include "ͼ��_ͼƬ.h"
namespace ����ɽկ {
typedef uint16_t t��������;
class C���;
struct S��������;
//==============================================================================
// ����
//==============================================================================
typedef std::function<void(const S�������� &, C��� &)> tf����Ч��;
class C���� : public C����ͼƬ���� {
public:
	enum E��� {
		eʹ��
	};
	static constexpr float c������ٶ� = 64.f;
	static constexpr float c���Ƽ��ٶ� = 10.f;
	static constexpr float c��������ٶ� = 64.f;
	static constexpr float c������ٶ� = 254.f;
	static constexpr float c������뾶 = 32.f;
	static constexpr float c��ʼ�����ٶ� = 128.f;
	static constexpr float c��������ʱ�� = 0.2f;
	static constexpr float c��ʼ�ٶȽ���ʱ�� = 1;
	void f����_ʹ��();
	void f����_����();
	bool f����_iʹ��();
	void f����();
	void f��ʾ() const;
	void f��ʾ����() const;
	//����
	const SͼƬ�������� &fgͼƬ��������() const override;
	const t����2 &fg����() const override;
	tԲ�� fg�ж���() const;
	const S�������� &fg��������() const;
	void fЧ��(C���&);
	bool fi�ڴ�����() const;
	void fs����(C��� *���, float ʱ��);
	bool fw����() const;
	void f�����˶�();
public:
	C������� *m����ָ��;
	const C��Ϸ�ٶ� *m��Ϸ�ٶ�;
	t����2 m����;
	t����2 m�ٶ�;
	t����2 m��ʼ�ٶ�;
	float m�ٶȲ�ֵ = 0;
	t��־ m��־;
	C��� *m������� = nullptr;
	float m�������;
	float m�����ٶ�;	//ÿ�μ���ʱֱ�Ӽӵ�������
	const S�������� *m��������;
};
struct S�������� : public SͼƬ�������� {
	tf����Ч�� mfЧ��;
	int mֵ;
	float m�ж��뾶;
	float m���͸���� = 1;
};
//==============================================================================
// ���������
//==============================================================================
using t������ = std::map<E����, t��������>;
using tp������ = std::shared_ptr<t������>;
class C��������� {
public:
	struct S���� {
		t����2 m����, m�ٶ�;
		C��� *m������� = nullptr;
		t����ָ��<S��������> m��������;
		void fs����(int);
	};
	class Cʵ�� {
	public:
		C��������<C����> *ma����;
		const C��������<S��������> *ma�������� = nullptr;
		const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
		void f��ʼ��_����(const C��Ϸ�ٶ� &);
		void f��ʼ��_����(C��������<C����> &);
		void f��ʼ��_��Դ(const C��������<S��������> &);
		void f��������(S���� &);
		bool fi�п�(const t�������� = 1);
	};
	C���������(Cʵ�� &);
	void f��������();
	void f��������(t��������);
	void f��������(const t������ &);
	S���� m����;
private:
	Cʵ�� *mʵ��;
};
//==============================================================================
// ����Ч��
//==============================================================================
namespace ����Ч�� {
void f�÷�_�̶�(const S�������� &, C��� &);
void f�÷�_����(const S�������� &, C��� &);
void f�л�_ʮ��֮һ(const S�������� &, C��� &);
void fը��_ʮ��֮һ(const S�������� &, C��� &);
void f����_�ٷ�֮һ(const S�������� &, C��� &);
void f����(const S�������� &, C��� &);
}	//namespace ����Ч��
}	//namespace ����ɽկ
