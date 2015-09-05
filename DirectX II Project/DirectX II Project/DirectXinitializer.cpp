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
	InitSwapChain(window, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);
	InitViewPort(0, 1, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT, 1);

	Mycam.InitMatrices(BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	InitVertexBuffers();
	InitIndexBuffers();

	InitTextures();

	InitSampler();
	InitSRVs();

	InitDepthStencils();
	InitDepthStencilViews();

	InitShaders();

	InitInputLayouts();

	InitConstBuffers();
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

void DxInit::InitVertexBuffers()
{
	Model.LoadObject("test pyramid.obj", &vertices, &uvs, &normals);

	D3D11_BUFFER_DESC VertexBuffDescript;
	ZeroMemory(&VertexBuffDescript, sizeof(VertexBuffDescript));
	VertexBuffDescript.ByteWidth = sizeof(_OBJ_VERT_) * 776;
	VertexBuffDescript.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBuffDescript.Usage = D3D11_USAGE_IMMUTABLE;

	//Lab 8 //copy over
	D3D11_SUBRESOURCE_DATA VertexData;
	ZeroMemory(&VertexData, sizeof(VertexData));
	VertexData.pSysMem = Cube_data;

	DxDevice->CreateBuffer(&VertexBuffDescript, &VertexData, &VertexBuffer);

	//D3D11_BUFFER_DESC VertexBuffDescript;
	//ZeroMemory(&VertexBuffDescript, sizeof(VertexBuffDescript));
	//VertexBuffDescript.ByteWidth = (unsigned int)(sizeof(XMFLOAT3) * vertices.size());
	//VertexBuffDescript.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//VertexBuffDescript.Usage = D3D11_USAGE_IMMUTABLE;
	//VertexBuffDescript.StructureByteStride = sizeof(XMFLOAT3);
	//
	//D3D11_SUBRESOURCE_DATA VertexData;
	//ZeroMemory(&VertexData, sizeof(VertexData));
	//VertexData.pSysMem = &vertices;
	//
	//DxDevice->CreateBuffer(&VertexBuffDescript, &VertexData, &VertexBuffer);

}

void DxInit::InitIndexBuffers()
{
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
}

void DxInit::InitTextures()
{
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

	//DxDevice->CreateTexture2D(&DxTextureDesc, DxTextureData, &Dx2DTexture);
	HRESULT hr;
	hr = CreateDDSTextureFromFile(DxDevice, L"metallock.dds", NULL, &DxShaderResourceView);
}

void DxInit::InitSampler()
{
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
}

void DxInit::InitSRVs()
{
	//D3D11_SHADER_RESOURCE_VIEW_DESC DxShaderViewDesc;
	//ZeroMemory(&DxShaderViewDesc, sizeof(DxShaderViewDesc));
	//DxShaderViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//DxShaderViewDesc.Texture2D.MostDetailedMip = 0;
	//DxShaderViewDesc.Texture2D.MipLevels = 11;
	//DxShaderViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//DxDevice->CreateShaderResourceView(Dx2DTexture, &DxShaderViewDesc, &DxShaderResourceView);
}

void DxInit::InitDepthStencils()
{
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = SwapDescrip.BufferDesc.Width;
	descDepth.Height = SwapDescrip.BufferDesc.Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	DxDevice->CreateTexture2D(&descDepth, NULL, &DxDeviceDepthStencil);
}

void DxInit::InitDepthStencilViews()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	// Create the depth stencil view
	DxDevice->CreateDepthStencilView(DxDeviceDepthStencil, // Depth stencil texture
		&descDSV, // Depth stencil desc
		&DxStencilView);  // [out] Depth stencil view

	// //Bind the depth stencil view
	//DxDeviceContext->OMSetRenderTargets(1,          // One rendertarget view
	//	&DxRenderTargetView,      // Render target view, created earlier
	//	DxStencilView);     // Depth stencil view for the render target
}

void DxInit::InitInputLayouts()
{
	D3D11_INPUT_ELEMENT_DESC TriLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	DxDevice->CreateInputLayout(TriLayout, 3, Trivial_VS, sizeof(Trivial_VS), &layout);
}

void DxInit::InitConstBuffers()
{
	D3D11_BUFFER_DESC ConstBuffDescript;
	ZeroMemory(&ConstBuffDescript, sizeof(ConstBuffDescript));
	ConstBuffDescript.ByteWidth = sizeof(MatrixTrio);
	ConstBuffDescript.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// ConstBuffDescript.StructureByteStride = sizeof(MatrixTrio);
	ConstBuffDescript.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstBuffDescript.Usage = D3D11_USAGE_DYNAMIC;

	DxDevice->CreateBuffer(&ConstBuffDescript, NULL, &ConstBuffer);
}

void DxInit::InitShaders()
{
	DxDevice->CreateVertexShader(Trivial_VS, sizeof(Trivial_VS), NULL, &DxVertexShader);
	DxDevice->CreatePixelShader(Trivial_PS, sizeof(Trivial_PS), NULL, &DxPixelShader);
}

bool DxInit::Run()
{
	////
	MrTimer.Signal();
	if (MrTimer.TotalTime() > 360)
		MrTimer.Restart();
	////

	///////
	MatrixTrio world;
	world.WorldMatrix = XMMatrixIdentity();
	world.WorldMatrix = XMMatrixMultiply(XMMatrixRotationY(XMConvertToDegrees((float)MrTimer.Delta() * 0.05f)), Mycam.GetMatrix().WorldMatrix);
	
	Mycam.SetMatrix(world, 1);
	
	Mycam.CameraTranslation();
	Mycam.CameraRotation();
	////////

	///////
	DxDeviceContext->OMSetRenderTargets(1, &DxRenderTargetView, DxStencilView);
	/////

	/////
	DxDeviceContext->RSSetViewports(1, &DxViewPort);
	/////

	/////
	float Color[4] = { 0, 0.0f, 1.0f, 1 };
	DxDeviceContext->ClearRenderTargetView(DxRenderTargetView, Color);
	DxDeviceContext->ClearDepthStencilView(DxStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	/////

	/////
	D3D11_MAPPED_SUBRESOURCE  RotateSub;
	ZeroMemory(&RotateSub, sizeof(RotateSub));
	DxDeviceContext->Map(ConstBuffer, NULL, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, NULL, &RotateSub);
	memcpy(RotateSub.pData, &Mycam.GetMatrix(), sizeof(Mycam.GetMatrix()));
	DxDeviceContext->Unmap(ConstBuffer, NULL);
	/////

	/////
	DxDeviceContext->VSSetConstantBuffers(1, 1, &ConstBuffer);
	//////

	//////
	unsigned int pStrides = sizeof(_OBJ_VERT_);
	unsigned int pOffset = 0;
	DxDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &pStrides, &pOffset);

	DxDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//////////

	///////
	DxDeviceContext->VSSetShader(DxVertexShader, 0, 0);
	DxDeviceContext->PSSetShader(DxPixelShader, 0, 0);
	///////

	//////
	DxDeviceContext->IASetInputLayout(layout);
	/////

	/////
	DxDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	/////

	/////
	DxDeviceContext->PSSetSamplers(0, 1, &DxSampler);
	/////

	/////
	DxDeviceContext->PSSetShaderResources(0, 1, &DxShaderResourceView);
	//////

	/////
	DxDeviceContext->DrawIndexed(1692, 0, 0);
	/////

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
	ConstBuffer->Release();
//	ConstSceneBuffer->Release();

	DxVertexShader->Release();
	DxPixelShader->Release();

	layout->Release();

	DxStencilView->Release();
	DxDeviceDepthStencil->Release();

	VertexBuffer->Release();
	IndexBuffer->Release();

	DxSampler->Release();
	DxShaderResourceView->Release();

	UnregisterClass(L"DirectXApplication", application);
}