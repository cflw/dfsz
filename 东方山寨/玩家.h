#pragma once
#include "����.h"
#include "����_����.h"
#include "����.h"
#include "����ӵ��������.h"
#include "�Ի�.h"
#include "�ӻ�.h"
namespace ����ɽկ {
struct S��Ϸ����;
class C���;
struct S�Ի�����;
enum class E��ҷ���;
struct S�ӻ�����;
class I�ӻ��ƶ�;
//��ҳ���
const int c������� = 1;
//=============================================================================
// ����ֵ
//=============================================================================
class C����ֵ {
public:
	void f����();
	void f�ӷ�(long long);
public:
	long long mʵ��ֵ = 0;
	long long m��ʾֵ = 0;
};
class C����ֵ {
public:
	static const float c�����ٶ�;
	static const float c����;
	operator int() const;
	void f����();
	void f��();
	void f��();
public:
	float mֵ = 0;
};
class C�Ѷ� {
public:
	void f�����Ѷ�(const boost::rational<int> &);
	void f�����Ѷ�_����(int p����);
	void f�����Ѷ�();	//�Ի��ҵ�ʱ����
	float fg�����Ѷ�() const;	//ֻ��������
	float fg��̬�Ѷ�() const;
	int m�����Ѷ� = 1;
	int m�����Ѷ� = 0;	//��λ1/100 0000
};
//=============================================================================
// ���
//=============================================================================
//�����
class C��� {
public:
	enum E��־ {
		e����,
		e���ڹҵ�,
		e���ڸ���,
		e���,	//��z
		eը��,
		e�����ƶ�,	//��shift
	};
	struct S�ɼ� {
		long long m�÷�;
		boost::rational<int> m�л�;
		boost::rational<int> mը��;
		boost::rational<int> m����;
		int m����;
		int m����;
		C����ֵ m����;
	};
	static constexpr float c����ʱ�� = 2;
	static constexpr float c������� = 64;	//�ܳ�
	C���();
	//void f����_�ɼ��ı�();
	void f��ʼ��_����(const C��Ϸ�ٶ� &);
	void f���밴��(const t����2 &, const ����::C������ &);
	void f����();
	void f����();
	void f��ʾ() const;
	void f�ؿ���ʼ��();	//ÿһ�ض�����
	void f��Ϸ��ʼ��(const S��Ϸ���� &);	//������Ϸ����
	void f��Ϸ��ʼ��_��ҳɼ�ͼ��();
	//���״̬�仯
	void f����_�����ӵ�();
	void f����_ֹͣ�����ӵ�();
	void f����();
	t����2 f���㸴��λ��();
	void f����_���Ʒ����ӵ�(float ʱ��, bool ����ֹͣ = true);
	void f����_���Ʒ���ը��(float ʱ��);
	//һ����ҵ�����
	void fs�Ի�(int);
	void fs�ӻ�(int);
	void fsը��(int);
	bool f����_i�ɷ����ӵ�() const;
	bool f����_i�ɷ���ը��() const;
	bool fi�ɸ���() const;
public:	//�����Ի�&�ӻ�&�ɼ�
	C�Ի� m�Ի�;
	C�ӻ��� m�ӻ���;
	S�ɼ� m�ɼ�;
	std::mutex m�ɼ���;
public:	//����
	t��־ m��־;
	float m���ٽ���;	//[0(����),1(����)]
	float m����ʱ��;	//��
	float m�����ӵ� = 0, m����ը�� = 0;
	//C�߿��ı� m�ɼ��ı�;
	t����2 m�����;
	const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
	std::vector<std::shared_ptr<Iͼ��>> ma��ҳɼ�;
	std::unique_ptr<C����ӵ�������> m����ը��;
};
}	//namespace ����ɽկ