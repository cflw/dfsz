#pragma once
#include "��ѧ����.h"
#include "ͼ�ΰ���.h"
#include "����.h"
namespace ����ɽկ {
class C�ӵ�;
//==============================================================================
// �ӵ�����
//==============================================================================
class C�ӵ����� {
public:
	enum E������ {
		e����,	//Ϊtrueʱʹ��v��ĳ�Ա����,Ϊfalseʱʹ��v���ĵĳ�Ա����
		eλ��,	//[0,1],���Ϊfalseÿ�����λ��ƽ������
		e����,
		e��ɫ,	//��ûʵ��
		e��,	//ֻ��������ʹ��,ͷ����β�㽫��������
	};
	//��������
	class C�� {
	public:
		struct S���� {
			float m����;
			float m��ʧ;
		};
		const C�ӵ� *m�ӵ�;
		S���� m����;
		C��(const C�ӵ� *);
	};
	class Cֱ�� {
	public:
		struct S���� {
			float mλ��;
			float m��ʧ;
		};
		struct S���� {
			t����2 m����;
			float m����;
		};
		typedef S���� t����;
		typedef std::vector<S����> ta����;
		const C�ӵ� *m�ӵ�;
		t��־ m��־;
		S���� m����;
		int m����;
		Cֱ��(const C�ӵ� *, int);
	};
	class C���� {
	public:
		struct S���� {
			t����2 m����;
			float mλ��;
			float m����;
			float m��ʧ;
			const t��ɫ *m��ɫ[2];
		};
		struct S���� {
			float m����;
		};
		typedef S���� t����;
		typedef std::vector<S����> ta����;
		const C�ӵ� *m�ӵ�;
		t��־ m��־;
		S���� m����;
		int m����;
		C����(const C�ӵ� *, int);
	};
	class C���� {
	public:
		struct S���� {
			t����2 m����;
			float m��ʧ;
			const t��ɫ *m��ɫ[2];
		};
		struct Sƽ���� {
			t����2 m����;
			float m����;
			const t��ɫ *m��ɫ[2];
		};
		struct S���� {
			float m����;
		};
		typedef S���� t����;
		typedef Sƽ���� tƽ����;
		typedef std::vector<S����> ta����;
		const C�ӵ� *m�ӵ�;
		t��־ m��־;
		S���� m����;
		int m��, m��;
		C����(const C�ӵ� *, int, int);
	};
};
//==============================================================================
// ���ӵ��ӿ�
//==============================================================================
class I�ӵ�ͼ������ {
};
using tp�ӵ�ͼ������ = std::shared_ptr<I�ӵ�ͼ������>;
class I���ӵ� : public Iͼ�ι��� {
public:
	virtual void f���Ƶ�(const C�ӵ�����::C�� &) = 0;
	virtual void f����ֱ��(const C�ӵ�����::Cֱ�� &, const C�ӵ�����::Cֱ��::ta���� &) = 0;
	virtual void f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) = 0;
	virtual void f����������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) = 0;
	virtual void f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) = 0;
	virtual tp�ӵ�ͼ������ f���ɵ�(const C�ӵ�����::C�� &) = 0;
	virtual tp�ӵ�ͼ������ f����ֱ��(const C�ӵ�����::Cֱ�� &, const C�ӵ�����::Cֱ��::ta���� &) = 0;
	virtual tp�ӵ�ͼ������ f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) = 0;
	virtual tp�ӵ�ͼ������ f����������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) = 0;
	virtual tp�ӵ�ͼ������ f��������(const C�ӵ�����::C���� &, const C�ӵ�����::C����::ta���� &) = 0;
	virtual void f����ͼ������(const tp�ӵ�ͼ������ &) = 0;
};
}