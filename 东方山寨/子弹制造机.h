#pragma once
#include <optional>
#include <experimental/generator>
#include "��ѧ����.h"
#include "����.h"
#include "����_����.h"
namespace ����ɽկ {
typedef std::optional<float> t����;
class C�ӵ�;
struct S�ӵ�����;
class I���ӵ�;
class C�ӵ�;
//==============================================================================
// �ӵ������
//==============================================================================
struct S�ӵ����� {	//�����ӵ�����Ĳ���
	t����2 m����;
	t����2 m�ٶ�;
	t����2 m���� = t����2(1, 1);
	t����2 m���� = t����2::c��;
	t��ɫ m��ɫ[2];
	C��������<S�ӵ�����>::tָ�� m��ʽ;
	C��չ����<I���ӵ�>::tָ�� m����;
	C��������<S�ӵ�����>::tָ�� m����_��ʽ;
	C��չ����<I���ӵ�>::tָ�� m����_����;
	S�ӵ�����();
	void fs����(const t����2 &);
	void fs�ٶ�(const t����2 &);
	void fs�ٶ�_���Ի�(float ��С);
	void fs��ɫ(const t��ɫ &);
	void fs��ɫ(const t��ɫ &);
	void fs����(float);
	void fs���(float);
	void fs��ʽ(int);
	void fs����(int);
	void fs�ӵ�����(const C�ӵ� &);
};
class C�ӵ������ {
public:
public:
	class Cѭ�� {
	public:
		class C�任 {
		public:
			C�任(Cѭ�� &aѭ��, int a����) :
				m����(&aѭ��.m����->m����), m����(a����), m����(aѭ��.m����) {
			}
			//ѭ����������
			int fg����() const;
			int fg����() const;
			float fg�ٷֱ�() const;
			//ѭ�����㺯��
			float f����(t��־) const;
			float f����_���Ҳ�(float ���, float Ƶ��, t���� ���� = std::nullopt) const;
			t����2 f����_�ٶȱ任(float ��С, float ����, t���� ���� = std::nullopt) const;
			t����2 f����_�ٶ����Բ�ֵ(const t����2 &, t���� ���� = std::nullopt) const;
			t����2 f����_�ٶ�ƽ����ֵ(const t����2 &, t���� ���� = std::nullopt) const;
			//ѭ���任����
			void f�任_����();
			void f�任_��ԭ();
			void f�任_Բ��(int = 1, t���� ���� = std::nullopt);	//����Բ�α仯
			void f�任_��Բ(float ����仯);
			void f�任_����(float ���, t���� ���� = std::nullopt);
			void f�任_�ٶ�(float ��С, float ����, t���� ���� = std::nullopt);	//�ٶȴ�С����ֱ�ӱ仯
			void f�任_�ٶ����Բ�ֵ(const t����2 &, t���� ���� = std::nullopt);	//xy�����Ĳ�ֵ
			void f�任_�ٶ�ƽ����ֵ(const t����2 &, t���� ���� = std::nullopt);	//��С��������Ĳ�ֵ
			void f�任_��ɫ(int, const t��ɫ &, t���� ���� = std::nullopt);	//��ɫ��ֵ
			void f�任_�����ֵ(const t����2 &, t���� ���� = std::nullopt);
			void f�任_����ǰ��(float, t���� ���� = std::nullopt);
			void f�任_����ƽ��(const t����2 &�ƶ�, t���� ���� = std::nullopt);	//�����ƶ�
		public:
			S�ӵ����� *m����, *m����;
			int m����, m����;
		};
		class C������ {
		public:
			C������(Cѭ�� &aѭ��, int a����):
				mѭ��(&aѭ��), m����(a����) {
			}
			C������ &operator ++() {
				++m����;
				return *this;
			}
			bool operator !=(const C������ &a) {
				return m���� != a.m����;
			}
			C�任 operator *() {
				return C�任(*mѭ��, m����);
			}
			Cѭ�� *mѭ��;
			int m����;
		};
		Cѭ��(C�ӵ������ &, int ����);
		//ѭ������
		C������ begin() {
			return C������(*this, 0);
		}
		C������ end() {
			return C������(*this, m����);
		}
		C�任 f�任(int a����) {
			return C�任(*this, a����);
		}
		void f��������() {
			m�������� = m����->m����;
		}
		void f������ԭ() {
			m����->m���� = m��������;
		}
	public:
		S�ӵ����� m��������;
		C�ӵ������ *m����;
		int m����;
	};
	class Cʵ�� {
	public:
		void f��ʼ��_����(const C��Ϸ�ٶ� &);
		void f��ʼ��_����(C��������<C�ӵ�> &);
		void f��ʼ��_��Դ(const C��������<S�ӵ�����> &, const C��չ����<I���ӵ�> &);
		bool fi�п�();
		void f�����ӵ�(std::shared_ptr<C�ӵ�>, S�ӵ����� &);//����"f�����ӵ�"ǰ��Ҫ����"f����"
		C��������<C�ӵ�> *ma�ӵ� = nullptr;
		const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
		const C��������<S�ӵ�����> *ma�ӵ����� = nullptr;
		const C��չ����<I���ӵ�> *ma���ӵ� = nullptr;
	};
	using tѭ�������� = std::experimental::generator<Cѭ��::C�任>;
	using tfѭ��ģ�� = std::function<tѭ��������(C�ӵ������&)>;
	C�ӵ������(Cʵ�� &);
	~C�ӵ������();
	std::shared_ptr<C�ӵ�> f�����ӵ�();	//������ͨ�ӵ�
	template<typename t, typename...t����> std::shared_ptr<t> f�����ӵ�(const t���� &...a����);
	Cѭ�� fѭ��(int);
	tѭ�������� fѭ��(const tfѭ��ģ�� &);
	bool fʵ��_i�п�();
	void fʵ��_�����ӵ�(std::shared_ptr<C�ӵ�>);//���������ֱ�Ӳ���,������ܲ����ᴥ������
	S�ӵ����� m����;	//������
private:
	Cʵ�� *mʵ��;	//����Ϸʵ���й����ӵ������ʵ��
};
template<typename t, typename...t����> std::shared_ptr<t> C�ӵ������::f�����ӵ�(const t���� &...a����) {
	static_assert(std::is_base_of<C�ӵ�, t>::value, "����̳���C�ӵ�");
	if (fʵ��_i�п�()) {
		std::shared_ptr<t> v�ӵ� = std::make_shared<t>(a����...);
		fʵ��_�����ӵ�(v�ӵ�);
		t::f�ӿ�_�������ͳ�ʼ��(v�ӵ�);
		return v�ӵ�;
	}
	return nullptr;
}
//==============================================================================
// ѭ��ģ��
//==============================================================================
C�ӵ������::tfѭ��ģ�� Fѭ��ģ��_��ת(float ��ת��, int ����, int ��ϸ��, float ����ǰ�Ʊ��� = 1, float �ٶȲ�ֵ = 1);
C�ӵ������::tfѭ��ģ�� Fѭ��ģ��_�������(int ����, int ��ϸ��, float ����ǰ�Ʊ��� = 1, float �ٶȲ�ֵ = 1);
C�ӵ������::tfѭ��ģ�� Fѭ��ģ��_������(int ����, int ��ϸ��, float ����ǰ�Ʊ��� = 1, float �ٶȲ�ֵ = 1);
C�ӵ������::tfѭ��ģ�� Fѭ��ģ��_�۶����(int ����, int ��ϸ��, float ����ǰ�Ʊ��� = 1, float �ٶȲ�ֵ = 1);
}