#include <future>
#include <Windows.h>
#include <cflwͼ��_d3d11.h>
#include <cflwͼ��_d2d.h>
#include <cflwʱ��.h>
#include <cflw�Ӵ�.h>
#include "����.h"
#include "����.h"
#include "��������.h"
#include "ͼ������.h"
#include "��Ƶ����.h"
#include "����.h"
#include "��Ϸ.h"
#include "�ؿ�.h"
#include "��־.h"
#include "��Ϸ����.h"
#include "ͼ�ι���.h"
#include "����ͼ��.h"
namespace ����ɽկ {
namespace ʱ�� = cflw::ʱ��;
namespace �Ӵ� = cflw::�Ӵ�;
void f����();
//==============================================================================
// ��֡����
//==============================================================================
class C��֡���� {
public:
	std::shared_ptr<��ά::C���ı�> m���ı�;
	ʱ��::C��֡�� m��֡��;
	int m�����;
	C��֡����(��ά::C��ά &a��ά):
		m���ı�(a��ά.fc���ı�()) {
		m���ı�->m���� = a��ά.fg�������().f����_����();
		m���ı�->fs��ɫ({1,1,1,1});
		��ά::C�ı����� v�ı�����;
		v�ı�����.f��ʼ��();
		��ά::S�ı���ʽ���� v��ʽ;
		v��ʽ.fs�ֺ�(10);
		v��ʽ.fsˮƽ����(��ά::E�ı�ˮƽ����::e��);
		v��ʽ.fs��ֱ����(��ά::E�ı���ֱ����::e��);
		m���ı�->m��ʽ = v�ı�����.fc�ı���ʽ(v��ʽ);
		m��֡��.f����();
	}
	void fs�����(int p�) {
		m����� = p�;
	}
	void f��ʾ() {
		const double v֡����0 = m��֡��.f����();	//ת��������������
		const double v�ٷ��� = v֡����0 / m����� * 100;
		std::wstring v�ı�0 = std::to_wstring(lround(v֡����0));
		v�ı�0 += L"fps\n(";
		v�ı�0 += std::to_wstring(lround(v�ٷ���));
		v�ı�0 += L"%)";
		m���ı�->f�����ı�(v�ı�0);
	}
};
//==============================================================================
// ����ʵ��
//==============================================================================
class C����::Cʵ�� {
public:
	HINSTANCE mʵ��;
	HWND m����;
	int m���ڴ�С[2];
	float m���� = 0;
	ʱ��::C��ʱ�� m��ʱ��;
	����::C�ƴ��� m�ƴ���;
	Cͼ������ mͼ��;
	C�������� m����;
	C��Ƶ���� m��Ƶ;
	C�������� m����;
	C����ͼ�ο��� m����ͼ��;
	C��Ϸ m��Ϸ;
	std::unique_ptr<C��֡����> m��֡����;
	std::unique_ptr<C��־> m��־;
	�Ӵ�::C���뷨���� m���뷨����;
	int m��Ⱦ��� = 1;
	E��Ϸ״̬ m״̬ = E��Ϸ״̬::e������;
	E��Ϸ״̬ m��״̬ = E��Ϸ״̬::e��;
	t��־ m��־;
	//�첽����
	std::future<void> m����_����;
	std::future<void> m����_��Դ;
public:
	Cʵ��(HINSTANCE aʵ��): mʵ��{aʵ��} {
		m��Ϸ.f��ʼ��_ͼ�νӿ�(mͼ��);
		m��Ϸ.f��ʼ��_����ӿ�(m����);
		m��Ϸ.f��ʼ��_��Ƶ�ӿ�(m��Ƶ);
	}
	void f����() {
		//��Ϣѭ��
		MSG msg = {};
		while (msg.message != WM_QUIT) {	//��Ϣѭ��
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//����Ϣʱ�Ĵ���,��Ҫ�޸�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {	//û����Ϣʱ�Ĵ���
				if (m��ʱ��.f�δ�()) {
					f����();
					if (m�ƴ���.f�δ�()) {
						f����();
						f��ʾ();
					}
				}
				f�л�����();
			}
		}	//��Ϣѭ������
	}
	static LRESULT WINAPI f���ڹ���(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		mʵ��->m����.m����w.f������Ϣ(msg, wParam, lParam);
		switch(msg) {
		case WM_DESTROY:
			mʵ��->f����();
			PostQuitMessage(0);
			return 0;
		}
		//ʹ��Ĭ�ϴ���
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	//��������
	void f��������() {
		//ע�ᴰ��
		WNDCLASSEX wc;
		wc.cbSize			= sizeof(WNDCLASSEX);			//ʹ��sizeof(WNDCLASSEX)
		wc.style			= CS_CLASSDC;					//��������
		wc.lpfnWndProc		= f���ڹ���;					//���ڹ���
		wc.cbClsExtra		= 0L;							//��չ:
		wc.cbWndExtra		= 0L;							//��չ:
		wc.hInstance		= mʵ��;						//ʵ�����
		wc.hIcon			= LoadIcon(nullptr, IDI_WINLOGO);	//����Ĭ��ͼ��
		wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);	//����Ĭ�Ϲ��
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW;				//ʹ�ô�����ɫ
		wc.lpszMenuName		= nullptr;							//����Ҫ�˵�
		wc.lpszClassName	= L"������";					//��������
		wc.hIconSm			= nullptr;
		RegisterClassEx(&wc);
		//���㴰�ڴ�С
		//RECT v���ھ��� = {0, 0, 640, 480};
		const DWORD	c������ʽ = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		const DWORD	c������ʽex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		const �Ӵ�::S�ͻ����ߴ� v���ڳߴ� = �Ӵ�::S�ͻ����ߴ�::fc�ߴ���ʽ(800, 600, c������ʽ, c������ʽex);
		//��������
		m���� = CreateWindowExW(
			c������ʽex,
			L"������",	//��������
			c���ڱ���,					//���ڱ���
			c������ʽ,					//������ʽ
			CW_USEDEFAULT, CW_USEDEFAULT,	//����
			v���ڳߴ�.fg��(), v���ڳߴ�.fg��(),		//���ڳߴ�
			GetDesktopWindow(),				//���ھ������
			nullptr,							//�˵����
			wc.hInstance,					//ʵ�����
			nullptr);							//����
		//��ʾ����
		ShowWindow(m����, SW_SHOWDEFAULT);
		UpdateWindow(m����);
		//ȡ���ڿͻ�����С
		const �Ӵ�::S�ͻ����ߴ� v�ͻ����ߴ� = �Ӵ�::S�ͻ����ߴ�::fc����(m����);
		m���ڴ�С[0] = v�ͻ����ߴ�.fg��();
		m���ڴ�С[1] = v�ͻ����ߴ�.fg��();
		m���� = v�ͻ����ߴ�.f���Գߴ�(c��׼�ߴ�x, c��׼�ߴ�y);
	}
	void f��ʼ��() {
		m���뷨����.f��ʼ��(m����);
		m���뷨����.f�ر�();
		mͼ��.f��ʼ��(m����, m����);
		mͼ��.f��ʼ��_s��Ⱦ���(m��Ⱦ���);
		m����.f��ʼ��(m����, m����);
		m��Ƶ.f��ʼ��();
		m����.f��ʼ��(mͼ��.fg��ά(), m����);
		mͼ��.fgͼ�ι���().f��ʼ��_����(m��Ϸ.fg��Դ().fg��Ϸ�ٶ�());
		//m����_���� = std::async(f����);
		f����();
		m��ʱ��.f����(c֡��);
		m��֡���� = std::make_unique<C��֡����>(mͼ��.fg��ά());
		m��־ = std::make_unique<C��־>(mͼ��.fg��ά());
		fs��Ⱦ���(4);
		f��־(C��־::e����, L"����...............");
	}
	void f����() {
		mͼ��.f����();
		m��֡����.reset();
		m��Ƶ.f����();
	}
	void f����() {
		//״̬�л�
		if (m״̬ == E��Ϸ״̬::e������ && m��־[(int)E��Ϸ��־::e����0]) {
			//m����_��Դ = std::async(&C��Ϸ::f��Դ��ʼ��, std::ref(m��Ϸ));
			m��Ϸ.f��Դ��ʼ��();
			f�л���Ϸ״̬(E��Ϸ״̬::e���˵�);
			f��־(C��־::e����, L"������ɣ���ȷ��������");
			//�����ٿ�ʼ��Ϸ�����Ҫ������⻭���������ע�͵�
			//S��Ϸ���� &v���� = C��Ϸ::fg����();
			//v����.m�Ի���ʶ = (int)E�Ի�::eħ��ɳ;
			//v����.m�ӻ���ʶ = (int)E�ӻ�::eħ��ɳ�ᴩ;
			//v����.m���� = 4;
			//f�л���Ϸ״̬(E��Ϸ״̬::e��Ϸ��);
		} else if (m״̬ == E��Ϸ״̬::e���˵�) {
			const bool vȷ�� = m����.m������.f����((����::t����)E����::eȷ��).f�հ���();
			if (vȷ��) {
				f�л���Ϸ״̬(E��Ϸ״̬::e��Ϸ��);
				f��־(C��־::e����, L"��Ϸ��");
			}
		}
		//����
		m����.f����();
		m��Ƶ.f����();
		m����.f����();
		m����ͼ��.f����();
		if (m״̬ == E��Ϸ״̬::e��Ϸ��) {
			m��Ϸ.f����();
		} else {
			mͼ��.fgͼ�ι���().f��Ϸ�����();
		}
		m��־->f����();
	}
	void f����() {
		m����.f����();
		if (m״̬ == E��Ϸ״̬::e��Ϸ��) {
			m��Ϸ.f����();
		} else {
			mͼ��.fgͼ�ι���().f��Ϸ�����();
		}
	}
	void f��ʾ() {
		mͼ��.f��Ⱦ��ʼ();
		if (m״̬ == E��Ϸ״̬::e��Ϸ�� || m״̬ == E��Ϸ״̬::e��Ϸ�˵�) {
			m��Ϸ.f��ʾ();
		} else {
			mͼ��.fgͼ�ι���().f��Ϸ����ʾ();
			mͼ��.fsͼ�ι���(nullptr);
		}
		m����.f��ʾ();
		m��֡����->f��ʾ();
		m��־->f��ʾ();
		const auto &v������� = m����.m���->f����();
		mͼ��.f��ʮ��({v�������.x, v�������.y});
		mͼ��.f��Ⱦ����();
	}
	void f�л�����() {
		if (m��״̬ != E��Ϸ״̬::e��) {
			switch (m��״̬) {
			case E��Ϸ״̬::e���˵�:
				m����.f�л�����(E����::e���˵�);
				break;
			case E��Ϸ״̬::e��Ϸ��:
				//m����_��Դ.wait();
				m��Ϸ.f��Ϸ��ʼ��();
				m��Ϸ.f����ؿ�(C�ؿ�::fgע��ؿ�(L"����������1"));
				m����.f�رմ���();
				break;
			case E��Ϸ״̬::e�˳�:
				SendMessageW(m����, WM_CLOSE, 0, 0);
				break;
			}
			m״̬ = m��״̬;
			m��״̬ = E��Ϸ״̬::e��;
		}
	}
	void fs��Ⱦ���(int a) {
		const float v��ȾƵ�� = c����Ƶ�� / a;
		m�ƴ���.f����(a);
		m��֡����->fs�����(v��ȾƵ��);
		m����.fsʱ��Ƶ��(c����Ƶ��, v��ȾƵ��);
		m��Ⱦ��� = a;
	}
	void f�л���Ϸ״̬(E��Ϸ״̬ a) {
		m��״̬ = a;
	}
	void f���뷨����(bool a) {
		m���뷨����.f����(a);
	}
};
//==============================================================================
// ����
//==============================================================================
std::unique_ptr<C����::Cʵ��> C����::mʵ��;
void C����::f��ʼ��(HINSTANCE p) {
	mʵ�� = std::make_unique<Cʵ��>(p);
	mʵ��->f��������();
	mʵ��->f��ʼ��();
}
void C����::f����() {
	mʵ��->f����();
}
void C����::f����() {
	mʵ��.reset();
}
C��Ϸ &C����::fg��Ϸ() {
	return mʵ��->m��Ϸ;
}
C�������� &C����::fg����() {
	return mʵ��->m����;
}
Cͼ������ &C����::fgͼ��() {
	return mʵ��->mͼ��;
}
C��Ƶ���� &C����::fg��Ƶ() {
	return mʵ��->m��Ƶ;
}
C����ͼ�ο��� &C����::fg����ͼ��() {
	return mʵ��->m����ͼ��;
}
std::filesystem::path C����::f����·��(const std::filesystem::path &aĿ��·��, const std::filesystem::path &a��ǰ�ļ�) {
	using std::filesystem::path;
	const path v����·�� = path(aĿ��·��).make_preferred();
	const std::wstring v�����ַ��� = v����·��.native();
	if (a��ǰ�ļ�.empty()) {
		return (std::filesystem::current_path() / v����·��).lexically_normal();
	} else if (const size_t vλ�� = v�����ַ���.find(std::wstring(L"~") + path::preferred_separator); vλ�� == 0) {
		return (fg����Ŀ¼() / v�����ַ���.substr(2)).lexically_normal();
	} else {
		const path v��ǰĿ¼ = a��ǰ�ļ�.parent_path();
		return (v��ǰĿ¼ / v����·��).lexically_normal();
	}
}
const std::filesystem::path &C����::fg����Ŀ¼() {
	using std::filesystem::path;
	static const path v����Ŀ¼ = []()->path {
		const path v��ǰĿ¼ = std::filesystem::current_path();
		const path v�ϼ�Ŀ¼ = v��ǰĿ¼.parent_path();
		if (const path vĿ¼�� = v�ϼ�Ŀ¼.filename(); vĿ¼�� == L"~") {
			return v�ϼ�Ŀ¼;
		}
		return v��ǰĿ¼ / L"~";
	}();
	assert(std::filesystem::exists(v����Ŀ¼));
	return v����Ŀ¼;
}
void C����::f���뷨����(bool p) {
	mʵ��->f���뷨����(p);
}
int C����::fg��Ⱦ���() {
	return mʵ��->m��Ⱦ���;
}
void C����::f�л���Ϸ״̬(E��Ϸ״̬ a״̬) {
	mʵ��->f�л���Ϸ״̬(a״̬);
}
void C����::fs��Ϸ��־(int a��־, bool aֵ) {
	mʵ��->m��־[a��־] = aֵ;
}
void C����::f��־(int a����, const std::wstring &a�ı�) {
	mʵ��->m��־->f���((C��־::E����)a����, a�ı�);
}
}	//namespace ����ɽկ
//==============================================================================
// ������
//==============================================================================
using ����ɽկ::C����;
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int) {
	C����::f��ʼ��(hInst);
	C����::f����();
	C����::f����();
}