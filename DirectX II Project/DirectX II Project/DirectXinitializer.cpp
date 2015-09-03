#include "DirectXinitializer.h"
#include "Cube.h"
#include "crosshatch.h"

void DxInit::CreateMyWindow(HINSTANCE hinst, WNDPROC proc)
{
	// ****************** BEGIN WARNING ***********************// 
	// WINDOWS CODE, I DON'T TEACH THIS YOU MUST KNOW IT ALREADY! 
	application = hinst;
	appWndProc = proc;

	WNDCLASSEX  wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = appWndProc;
	wndClass.lpszClassName = L"DirectXApplication";
	wndClass.hInstance = application;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	//wndClass.hIcon			= LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FSICON));
	RegisterClassEx(&wndClass);

	RECT window_size = { 0, 0, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT };
	AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);

	window = CreateWindow(L"DirectXApplication", L"Graphics II Project", WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, window_size.right - window_size.left, window_size.bottom - window_size.top,
		NULL, NULL, application, NULL);

	ShowWindow(window, SW_SHOW);
	//********************* END WARNING ************************//
}

void DxInit::Initalize()
{
	//Make function to handle all this
	InitSwapChain(window, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);
	InitViewPort(0, 1, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT, 1);

	//////
	D3D11_BUFFER_DESC VertexBuffDescript;
	ZeroMemory(&VertexBuffDescript, sizeof(VertexBuffDescript));
	VertexBuffDescript.ByteWidth = sizeof(_OBJ_VERT_) * 776;
	VertexBuffDescript.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBuffDescript.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA VertexData;
	ZeroMemory(&VertexData, sizeof(VertexData));
	VertexData.pSysMem = Cube_data;

	DxDevice->CreateBuffer(&VertexBuffDescript, &VertexData, &VertexBuffer);
	////////

	////////
	D3D11_BUFFER_DESC IndexBuffDesc;
	ZeroMemory(&IndexBuffDesc, sizeof(IndexBuffDesc));
	IndexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBuffDesc.CPUAccessFlags = NULL;
	IndexBuffDesc.ByteWidth = sizeof(unsigned int) * 1692;

	D3D11_SUBRESOURCE_DATA IndexData;
	ZeroMemory(&IndexData, sizeof(IndexData));
	IndexData.pSysMem = Cube_indicies;

	DxDevice->CreateBuffer(&IndexBuffDesc, &IndexData, &IndexBuffer);
	//////////

	/////////
	D3D11_TEXTURE2D_DESC DxTextureDesc;
	ZeroMemory(&DxTextureDesc, sizeof(DxTextureDesc));
	DxTextureDesc.Width = crosshatch_width;
	DxTextureDesc.Height = crosshatch_height;
	DxTextureDesc.MipLevels = 11;
	DxTextureDesc.ArraySize = 1;
	DxTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	DxTextureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	DxTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	DxTextureDesc.SampleDesc.Count = 1;

	D3D11_SUBRESOURCE_DATA DxTextureData[11]; //copy over
	for (int i = 0; i < 11; i++)
	{
		DxTextureData[i].pSysMem = &crosshatch_pixels[crosshatch_leveloffsets[i]];
		DxTextureData[i].SysMemPitch = (crosshatch_width >> i) * sizeof(UINT);
		DxTextureData[i].SysMemSlicePitch = 0;
	}

	DxDevice->CreateTexture2D(&DxTextureDesc, DxTextureData, &Dx2DTexture);
	///////////

	///////
	D3D11_SAMPLER_DESC DxSamplerDesc;
	ZeroMemory(&DxSamplerDesc, sizeof(DxSamplerDesc));
	DxSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	DxSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	DxSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	DxSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	DxSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	DxSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	DxSamplerDesc.MinLOD = -D3D11_FLOAT32_MAX;
	DxDevice->CreateSamplerState(&DxSamplerDesc, &DxSampler);
	///////

	//////
	D3D11_SHADER_RESOURCE_VIEW_DESC DxShaderViewDesc;
	ZeroMemory(&DxShaderViewDesc, sizeof(DxShaderViewDesc));
	DxShaderViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	DxShaderViewDesc.Texture2D.MostDetailedMip = 0;
	DxShaderViewDesc.Texture2D.MipLevels = 11;
	DxShaderViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	DxDevice->CreateShaderResourceView(Dx2DTexture, &DxShaderViewDesc, &DxShaderResourceView);
	//////



	//DxInitializer.InitShaders();
}

void DxInit::InitSwapChain(HWND window, int width, int height)
{
	ZeroMemory(&SwapDescrip, sizeof(SwapDescrip));
	SwapDescrip.Windowed = TRUE;
	SwapDescrip.SampleDesc.Count = 1;
	SwapDescrip.SampleDesc.Quality = 0;
	SwapDescrip.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapDescrip.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	SwapDescrip.BufferDesc.RefreshRate.Numerator = 60;
	SwapDescrip.BufferDesc.RefreshRate.Denominator = 1;
	SwapDescrip.BufferDesc.Width = width;
	SwapDescrip.BufferDesc.Height = height;
	SwapDescrip.OutputWindow = window;
	SwapDescrip.BufferCount = 1;

	HRESULT hr;
#ifdef _DEBUG
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &SwapDescrip, &DxSwapChain, &DxDevice, NULL, &DxDeviceContext);
#else
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_SINGLETHREADED, NULL,NULL, D3D11_SDK_VERSION, &SwapDescrip, &DxSwapChain, &DxDevice, NULL, &DxDeviceContext);
#endif

	DxSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&Dx2DTexture);
	DxDevice->CreateRenderTargetView(Dx2DTexture, NULL, &DxRenderTargetView);
}

void DxInit::InitViewPort(float minDepth, float maxDepth, float width, float height, unsigned int NumOfViewPorts)
{
	ZeroMemory(&DxViewPort, sizeof(D3D11_VIEWPORT));
	DxViewPort.MinDepth = minDepth;
	DxViewPort.MaxDepth = maxDepth;
	DxViewPort.Width = width;
	DxViewPort.Height = height;
	DxDeviceContext->RSSetViewports(NumOfViewPorts, &DxViewPort);
}

void DxInit::InitShaders()
{
	DxDevice->CreateVertexShader(Trivial_VS, sizeof(Trivial_VS), NULL, &DxVertexShader);
	DxDevice->CreatePixelShader(Trivial_PS, sizeof(Trivial_PS), NULL, &DxPixelShader);
}

bool DxInit::Run()
{
	//DxDeviceContext->OMSetRenderTargets(1, &DxRenderTargetView, DxStencilView);

	DxDeviceContext->OMSetRenderTargets(1, &DxRenderTargetView, NULL);

	DxDeviceContext->RSSetViewports(1, &DxViewPort);

	float Color[4] = { 0, 0.0f, 1.0f, 1 };
	DxDeviceContext->ClearRenderTargetView(DxRenderTargetView, Color);
	//DxDeviceContext->ClearDepthStencilView(DxStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	DxSwapChain->Present(0, 0);
	return true;
}

void DxInit::Resize()
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (Is_FullScreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		screenWidth = BACKBUFFER_WIDTH;
		screenHeight = BACKBUFFER_HEIGHT;
	}

	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;

	window = CreateWindowEx(WS_EX_APPWINDOW, L"DirectXApplication", L"Project", nStyle, 0, 0, screenWidth, screenHeight, NULL, NULL, application, NULL);
}

void DxInit::Release()
{

	DxDevice->Release();
	DxDeviceContext->Release();

	DxRenderTargetView->Release();
	
	DxSwapChain->Release();
	
	Dx2DTexture->Release();
	
//	DxBuffer->Release();
//	ConstBuffer->Release();
//	ConstSceneBuffer->Release();
	
//	DxVertexShader->Release();
//	DxPixelShader->Release();
	
//	layout->Release();
	
//	DxStencilView->Release();
//	DxDeviceDepthStencil->Release();
	
//	VertexBuffer->Release();
//	IndexBuffer->Release();
	
//	DxSampler->Release();
//	DxShaderResourceView->Release();

	UnregisterClass(L"DirectXApplication", application);
}