#include "TDevice.h"

ID3D11Device*			g_pd3dDevice;
ID3D11DeviceContext*	g_pContext;

HRESULT TDevice::CreateDevice()
{
	HRESULT hr = S_OK;

	//1)����̽� ����.
	UINT Flags = 0;
	Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	//���̷�Ʈ�������� �������� ģ���ϰ� �˷��ش�. ����׽ÿ��� �˷��ִ°ɷ�.
#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};

	//pFeatureLevels�� �����̴�.
	UINT FeatureLevels = 2;

	//�ϵ����� �����ϴ°� �׷���ī�尡 �����ϴ°�.
	D3D_DRIVER_TYPE DriverType[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	//GPU�� ����
		D3D_DRIVER_TYPE_WARP,		//CPU�� ����
		D3D_DRIVER_TYPE_REFERENCE,	//CPU�� ����
	};

	UINT numDriverType = sizeof(DriverType) / sizeof(D3D_DRIVER_TYPE);

	//Alt + Enter ���� �ڵ�.
	/*IDXGIAdapter* pAdapter = NULL;
	m_pDXGIFactory->EnumAdapters(0, &pAdapter);*/

	for (int iMode = 0; iMode < numDriverType; iMode++)
	{
		//D3D_FEATURE_LEVEL_11_0�� ���� ���´�.
		D3D_FEATURE_LEVEL retFL;

		//Alt + Enter ���� �ڵ�.
		//if (SUCCEEDED(D3D11CreateDevice(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, Flags,
		//	pFeatureLevels, FeatureLevels, D3D11_SDK_VERSION, &m_pd3dDevice, &retFL, &m_pContext)))
		if (SUCCEEDED(D3D11CreateDevice(NULL, DriverType[iMode], NULL, Flags,
			pFeatureLevels, FeatureLevels, D3D11_SDK_VERSION, &m_pd3dDevice, &retFL, &m_pContext)))
		{
			if (retFL != D3D_FEATURE_LEVEL_11_0)
			{
				Release();
				continue;
			}
			break;
		}
	}

	g_pd3dDevice = m_pd3dDevice;
	g_pContext = m_pContext;
	return hr;
}

HRESULT TDevice::CreateDX11GIFactory()
{
	HRESULT hr = S_OK;

	//Create DXGIFactory
	if (FAILED(hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pDXGIFactory)))
	{
		return false;
	}

	return hr;
}

HRESULT TDevice::CreateSwapChain()
{
	//����� ����°�.
	ZeroMemory(&m_sd, sizeof(DXGI_SWAP_CHAIN_DESC));

	m_sd.BufferDesc.Width = g_rtClient.right;
	m_sd.BufferDesc.Height = g_rtClient.bottom;
	m_sd.BufferDesc.RefreshRate.Numerator = 60;
	m_sd.BufferDesc.RefreshRate.Denominator = 1;			//60�ް� �츣�� 1/60(�ֻ���)
	m_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//������� �뵵.
	m_sd.BufferCount = 1;									//������� ����.
	m_sd.OutputWindow = g_hWnd;
	m_sd.Windowed = true;
	m_sd.SampleDesc.Count = 1;							//�ѹ��� �Ѹ���. ������ �Ѹ��� ��Ƽ�ٸ����.

	//�ʱ��ػ󵵴�� ����. ��üȭ�� ��ȯ�ÿ� �ڵ����� ����ȭ�� �ػ󵵷� ����Ǵ°� ���´�.
	m_sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	

	HRESULT hr = S_OK;
	m_pDXGIFactory->CreateSwapChain(m_pd3dDevice, &m_sd, &m_pSwapChain);

	return hr;
}

HRESULT TDevice::SetRenderTarget()
{
	HRESULT hr = S_OK;
	// 2)����Ÿ�� �� ����
	ID3D11Texture2D* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

	//������ ���õ� �޼ҵ�� m_pd3dDevice�� ����
	//������ ������ ����� m_pContext
	m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);

	//GetBuffer�� ���� ���ϴ� �۾��� �ѵڿ��� ������ �����ؾ��Ѵ�.Release();
	pBackBuffer->Release();
	m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	return hr;
}

void TDevice::SetViewPort()
{
	// 3)����Ʈ ����
	// ȭ�� ��ü�� ä����.
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = g_rtClient.right;
	vp.Height = g_rtClient.bottom;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pContext->RSSetViewports(1, &vp);			//RasterizerStage�� ����.
}
void TDevice::DeleteDeviceResources(UINT iWidth, UINT iHeight)
{
}
HRESULT TDevice::CreateDeviceResources(UINT iWidth, UINT iHeight)
{
	return S_OK;
}

HRESULT TDevice::ResizeDevice(UINT iWidth, UINT iHeight)
{
	if (m_pd3dDevice == NULL) return -1;

	HRESULT hr = S_OK;

	//����Ÿ���� �η� �����ϰ� ����
	m_pContext->OMSetRenderTargets(0, NULL, NULL);
	DeleteDeviceResources(iWidth, iHeight);

	if (m_pRenderTargetView) m_pRenderTargetView->Release();

	//������� ũ�⸦ �����Ѵ�.
	m_pSwapChain->ResizeBuffers(m_sd.BufferCount, m_sd.BufferDesc.Width, m_sd.BufferDesc.Height,
		m_sd.BufferDesc.Format, m_sd.Flags);

	//����Ÿ�ٺ� ������ �����Ѵ�.
	if (FAILED(hr = SetRenderTarget()))
	{
		return hr;
	}

	SetViewPort();

	CreateDeviceResources(iWidth, iHeight);
	return hr;
}
bool TDevice::Init()
{
	HRESULT hr;
	if (FAILED(hr = CreateDX11GIFactory()))
	{
		return false;
	}


	if (FAILED(hr = CreateDevice()))
	{
		return false;
	}

	
	if (FAILED(hr = CreateSwapChain()))
	{
		return false;
	}

	if (FAILED(hr = SetRenderTarget()))
	{
		return false;
	}

	SetViewPort();

	//Alt + Enter Ű�� ���´�.
	if (FAILED(hr = m_pDXGIFactory->MakeWindowAssociation(NULL, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
	{
		return hr;
	}
	return true;
}

bool TDevice::PreRender()
{
	//RGB 255�� 0-1�ǰ����� ������. RGBA
	float color[4] = { 1, 1, 0, 1 };
	m_pContext->ClearRenderTargetView(m_pRenderTargetView, color);
	return true;
}
bool TDevice::PostRender()
{
	//����ۿ��ִ°� �չ��۷� �ٲ۴�.
	m_pSwapChain->Present(0, 0);
	return true;
}
bool TDevice::Render()
{
	////����, ĳ����, ����Ʈ, UI
	return true;
}

bool TDevice::Release()
{
	//������ �������� Release�Ѵ�.
	if (m_pRenderTargetView)	m_pRenderTargetView->Release();
	if (m_pSwapChain)			m_pSwapChain->Release();
	if (m_pd3dDevice)			m_pd3dDevice->Release();
	if (m_pContext)				m_pContext->Release();
	if(m_pDXGIFactory)			m_pDXGIFactory->Release();

	m_pRenderTargetView = NULL;
	m_pSwapChain = NULL;
	m_pd3dDevice = NULL;
	m_pContext = NULL;
	m_pDXGIFactory = NULL;


	return true;
}

TDevice::TDevice() : m_pDXGIFactory(NULL), m_pRenderTargetView(NULL), m_pSwapChain(NULL), m_pd3dDevice(NULL), m_pContext(NULL)
{
	/*m_pDXGIFactory = NULL;
	m_pRenderTargetView = NULL;
	m_pSwapChain = NULL;
	m_pd3dDevice = NULL;
	m_pContext = NULL;*/
}


TDevice::~TDevice()
{
}