#pragma once
#include <map>
#include <vector>
#include <cflw�Ӵ�.h>
#include "ͼ�ΰ���.h"
#include "��ѧ����.h"
#include "����.h"
#include "����_����.h"
namespace ����ɽկ {
class Iͼ��;
class Iͼ�ι���;
struct S�������;
struct S��ά����;
class Cģ��;
class C������;
class C���㹤��;
class Cģ�͹���;
class C��ͼƬ;
class C����ά;
class C����ҳɼ�;
using t��ͼƬ = class C��ͼƬ;
class Cͼ�β�;
class Cͼ�ι���;
class Cͼ�ι���;
//=============================================================================
// ͼ������
//=============================================================================
class Cͼ������ {
public:
	Cͼ������();
	~Cͼ������();
	void f��ʼ��(HWND, float ����);
	void f��ʼ��_s��Ⱦ���(const int &);
	void f����();
	void f��Ⱦ��ʼ();
	void f��Ⱦ����();
	//��Ҫ����
	��ά::C��ά &fg��ά() const;
	��ά::C��ά &fg��ά() const;
	��ά::C�ı����� &fg�ı�����();
	��ά::tp��ȾĿ�� fg��ά��ȾĿ��() const;
	��ά::C����ת�� &fg��ά�������() const;
	//����
	void fsͼ�ι���(Iͼ�ι��� *);
	//��Դ&����
	C��������<tp����> &fg����();
	C������ &fg������();
	C��������<S�������> &fg�������();
	C���㹤�� &fg���㹤��();
	C��������<Cģ��> &fgģ��();
	Cģ�͹��� &fgģ�͹���();
	ID3D11Buffer *fg��ά��������();
	��ɫ��::C��ɫ������ &fg��ɫ������();
	Cͼ�ι��� &fgͼ�ι���();
	C��������<Iͼ��> &fgͼ������();
	Cͼ�ι��� f����_ͼ��();
	std::shared_ptr<Cͼ�ι���> f����_ͼ��p();
	//��Ԥ��ͼ��
	void f���߿�();
	void f��ʮ��(const t����2 &, const float &�뾶 = 16);
	void f��������Ϣ(const std::wstring &);
	//������
	std::shared_ptr<��ά::C��ͼ��> fc��ͼ��();
	��ά::C��ͼ�� &fg��ͼ��();
	std::shared_ptr<��ά::C���ı�> fc���ı�();
	��ά::C���ı� &fg���ı�();
	C��ͼƬ &fg��ͼƬ();
	C����ά &fg����ά();
	C����ҳɼ� &fg����ҳɼ�();
	//����
	float fg��Ⱦ��() const;	//��Ϸ�ٶ��޹�
	float fg��Ⱦ֡() const;
public:
	//����
	std::unique_ptr<��ά::C��ά> m��ά;
	std::unique_ptr<��ά::C��ά> m��ά;
	��ά::C�ı����� m�ı�;
	tp���� m��ά��������;	//��ά
	Iͼ�ι��� *mͼ�ι���;
	float m���� = 1;
	const int *m��Ⱦ��� = nullptr;
	//��Դ
	C��������<tp����> ma����;
	std::unique_ptr<C������> m������;
	C��������<S�������> ma�������;
	std::unique_ptr<C���㹤��> m���㹤��;
	C��������<Cģ��> maģ��;
	std::unique_ptr<Cģ�͹���> mģ�͹���;
	std::unique_ptr<��ɫ��::C��ɫ������> m��ɫ������;
	std::unique_ptr<Cͼ�ι���> mͼ�ι���;
	//����
	std::shared_ptr<��ά::C��ͼ��> m��ͼ��;
	std::shared_ptr<��ά::C��ͼ��> m���߿�;
	std::shared_ptr<��ά::C��ͼ��> m��ʮ��;
	std::shared_ptr<��ά::C���ı�> m���ı�;
	std::shared_ptr<��ά::C���ı�> m�������ı�;
	std::unique_ptr<C��ͼƬ> m��ͼƬ;
	std::unique_ptr<C����ά> m����ά;
	std::unique_ptr<C����ҳɼ�> m����ҳɼ�;
};
//=============================================================================
// ��ά����,һ�����������һ��Ƭ��
//=============================================================================
struct S������� {
	enum E��λ {
		e��, e��, e��, e��
	};
	float m����[4], m����[4];	//��,��,��,��
	float fg����x(float ��ֵ) const;
	float fg����y(float ��ֵ) const;
	float fg����x(float ��ֵ) const;
	float fg����y(float ��ֵ) const;
	float fg��() const;
	float fg��() const;
};
struct S���㶥�� {
	t����2 m����;
	t����2 m����;
	float m͸����;
};
class C��ͼƬ : public Iͼ�ι��� {
public:
	static const unsigned int c���㻺������ = 1000;
	static const unsigned int c������������ = c���㻺������ * 2;
	C��ͼƬ(Cͼ������ &, ��ά::C��ά &);
	~C��ͼƬ();
	void f׼��() override;
	void fˢ��() override;
	void fs����(const t����2 &);
	void fs͸����(float);
	void fs����(tp����);
	void f�任_����();
	void f�任_��ת(const t����3 &xyz);
	void f�任_��ת(float z);
	void f�任_��ת(float x, float y);
	void f�任_����(float x, float y);
	void f��ͼƬ(const S�������&);
public:
	//������Դ
	��ά::C��Ⱦ���� &m��Ⱦ����;
	��ά::C��Ⱦ״̬ &m��Ⱦ״̬;
	t�Զ����� m����;
	tp������ɫ�� m������ɫ��;
	tp������ɫ�� m������ɫ��; 
	tp���벼�� m���벼��;
	//���Ʊ���
	t����2 m����;
	t����4 m����;
	float m͸����;
	tp���� m����;
	tp���� m��������;
};
 
}	//namespace ����ɽկ