#pragma once
#include "�ӵ�ͼ�νӿ�.h"
namespace ����ɽկ {
class C�ӵ�;
class Cͼ������;
//�豸�޹ص��ӵ�����,��"I���ӵ�::f����"��ת������ʾ�õĶ���
class C���ӵ�_���� : public I���ӵ� {
private:
	class Cͼ������;
	struct S����;
	class C���㸳ֵ;
	using t���� = S����;
	using t���� = WORD;
	using tf���� = std::function<t����*(int)>;
	using tf���� = std::function<t����*(int)>;
	static constexpr unsigned int c���㻺������ = 8000;
	static constexpr unsigned int c������������ = c���㻺������ * 2;
	static constexpr float c�� = 0, c�� = 0, c�� = 1, c�� = 1, c�� = 0.5f;
public:	//����
	C���ӵ�_����(Cͼ������ &, ��ά::C��ά &);
	void f׼��() override;
	void fˢ��() override;
	void f���Ƶ�(const C�ӵ�����::C�� &) override;
	void f����ֱ��(const C�ӵ�����::Cֱ�� &, const C�ӵ�����::Cֱ��::ta���� &) override;
	void f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	void f����������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	void f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	tp�ӵ�ͼ������ f���ɵ�(const C�ӵ�����::C�� &) override;
	tp�ӵ�ͼ������ f����ֱ��(const C�ӵ�����::Cֱ�� &, const C�ӵ�����::Cֱ��::ta���� &) override;
	tp�ӵ�ͼ������ f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	tp�ӵ�ͼ������ f����������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	tp�ӵ�ͼ������ f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	void f����ͼ������(const tp�ӵ�ͼ������ &) override;
private:	//�ڲ����ӵ�����
	void f����ӵ�(const C�ӵ� *);
	void f���ӵ�(const C�ӵ� &, const void *a����ָ��, size_t a�����С, const void *a����ָ��, size_t a������С);
	//����
	static void f�Զ�����_����(int, const tf���� &);
	static void f�Զ�����_����(int, int, const tf���� &);
	static int f������������(int ��, int �� = 1);
	//������
	static void f���ɵ�0(const C�ӵ�����::C�� &, const tf���� &, const tf���� &);
	static void f����ֱ��0(const C�ӵ�����::Cֱ�� &, const C�ӵ�����::Cֱ��::ta���� &, const tf���� &, const tf���� &);
	static void f��������0(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &, const tf���� &, const tf���� &);
	static void f����������0(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &, const tf���� &, const tf���� &);
	static void f��������0(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &, const tf���� &, const tf���� &);
	//���亯��
	tf���� F���䶥��();
	tf���� F��������();
	��ά::C��Ⱦ���� *m��Ⱦ����;
	��ά::tpͼ�ι��� mͼ�ι���;
	��ά::tp���� m����;
	t�Զ����� m����;
	����::C�ռ�<t����> m����ռ�;
	����::C�ռ�<t����> m�����ռ�;
	��ά::tp������ m������;
	��ά::tp���� m��������;
};
class C���ӵ�_���� : public I���ӵ� {	//ֻ���ж���
public:
	C���ӵ�_����(��ά::C��ά &);
	void f׼��() override;
	void fˢ��() override;
	void f���Ƶ�(const C�ӵ�����::C�� &) override;
	void f����ֱ��(const C�ӵ�����::Cֱ�� &, const C�ӵ�����::Cֱ��::ta���� &) override;
	void f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	void f����������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	void f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	tp�ӵ�ͼ������ f���ɵ�(const C�ӵ�����::C�� &) override;
	tp�ӵ�ͼ������ f����ֱ��(const C�ӵ�����::Cֱ�� &, const C�ӵ�����::Cֱ��::ta���� &) override;
	tp�ӵ�ͼ������ f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	tp�ӵ�ͼ������ f����������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	tp�ӵ�ͼ������ f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) override;
	void f����ͼ������(const tp�ӵ�ͼ������ &) override;
	static float f����͸����(float ����, float ��ʧ);
private:
	std::shared_ptr<��ά::C��ͼ��> m��ͼ;
};
}//�����ռ����