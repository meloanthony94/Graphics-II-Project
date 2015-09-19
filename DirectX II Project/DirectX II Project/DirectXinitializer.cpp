#include "DirectXinitializer.h"

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
	InitViewPort(0, 1, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT, 2);

	InitRasterizer();

	Mycam.InitMatrices(BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	InitVertexBuffers();

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
	SwapDescrip.SampleDesc.Count = 4;
	SwapDescrip.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
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

void DxInit::InitRasterizer()
{
	D3D11_RASTERIZER_DESC _rasterDesc;
	_rasterDesc.AntialiasedLineEnable = true; // changed to true
	_rasterDesc.CullMode = D3D11_CULL_BACK;
	_rasterDesc.DepthBias = 0;
	_rasterDesc.DepthBiasClamp = 0.0f;
	_rasterDesc.DepthClipEnable = true;
	_rasterDesc.FillMode = D3D11_FILL_SOLID;
	_rasterDesc.FrontCounterClockwise = false;
	_rasterDesc.MultisampleEnable = true; // changed to true
	_rasterDesc.ScissorEnable = false;
	_rasterDesc.SlopeScaledDepthBias = 0.0f;

	DxDevice->CreateRasterizerState(&_rasterDesc, &DxRasterState);
}

void DxInit::InitViewPort(float minDepth, float maxDepth, float width, float height, unsigned int NumOfViewPorts)
{
	ZeroMemory(&DxViewPort, sizeof(D3D11_VIEWPORT));
	DxViewPort.MinDepth = minDepth;
	DxViewPort.MaxDepth = maxDepth;
	DxViewPort.Width = width;
	DxViewPort.Height = height;
	DxDeviceContext->RSSetViewports(0, &DxViewPort);

	ZeroMemory(&DxViewPort2, sizeof(D3D11_VIEWPORT));
	DxViewPort2.MinDepth = minDepth;
	DxViewPort2.MaxDepth = maxDepth;
	DxViewPort2.Width = width / 4;
	DxViewPort2.Height = height / 4;
	DxDeviceContext->RSSetViewports(1, &DxViewPort2);
}

void DxInit::InitVertexBuffers()
{
	vector<Send_To_VRAM> Cube;
	Model.CreateStar(Cube, &index);
	
	D3D11_BUFFER_DESC VertexBuffDescript;
	ZeroMemory(&VertexBuffDescript, sizeof(VertexBuffDescript));
	VertexBuffDescript.ByteWidth = sizeof(Send_To_VRAM) * Cube.size();
	VertexBuffDescript.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBuffDescript.Usage = D3D11_USAGE_IMMUTABLE;
	
	D3D11_SUBRESOURCE_DATA VertexData;
	ZeroMemory(&VertexData, sizeof(VertexData));
	VertexData.pSysMem = &Cube[0];
	
	DxDevice->CreateBuffer(&VertexBuffDescript, &VertexData, &VertexBuffer);
	InitIndexBuffers();

	//.obj
	Model.LoadObject("Spider-Man_Scarlet_Spider.obj", &vertices, &uvs, &normals, &index2);

	D3D11_BUFFER_DESC VertexBuffDescript2;
	ZeroMemory(&VertexBuffDescript2, sizeof(VertexBuffDescript2));
	VertexBuffDescript2.ByteWidth = (unsigned int)(sizeof(Send_To_VRAM) * vertices.size());
	VertexBuffDescript2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBuffDescript2.Usage = D3D11_USAGE_IMMUTABLE;
	VertexBuffDescript2.StructureByteStride = sizeof(Send_To_VRAM);
	
	D3D11_SUBRESOURCE_DATA VertexData2;
	ZeroMemory(&VertexData2, sizeof(VertexData2));
	VertexData2.pSysMem = &vertices[0];
	
	DxDevice->CreateBuffer(&VertexBuffDescript2, &VertexData2, &VertexBuffer2);
	//InitIndexBuffers();


	Thingys TempThingy;
	/////////////////////
	MatrixTrio CubeMatrix;
	CubeMatrix.WorldMatrix;

	TempThingy.Pos = { 0.5, 0, 0 };
	TempThingy.Rotation = { 0, 0, 0 };

	TempThingy.WorldMatrix = XMMatrixMultiply(XMMatrixRotationRollPitchYaw(TempThingy.Rotation.x, TempThingy.Rotation.y, TempThingy.Rotation.z),
							XMMatrixTranslation(TempThingy.Pos.x, TempThingy.Pos.y, TempThingy.Pos.z));


	MyThings.push_back(TempThingy);
	/////////////////////////////////
	MatrixTrio SpideyMatrix;
	SpideyMatrix.WorldMatrix;

	TempThingy.Pos = { 1, -2, 0 };
	TempThingy.Rotation = { 0, /*XMConvertToRadians(180.0f)*/0, 0 };

	TempThingy.WorldMatrix = XMMatrixMultiply(XMMatrixRotationRollPitchYaw(TempThingy.Rotation.x, TempThingy.Rotation.y, TempThingy.Rotation.z),
												XMMatrixTranslation(TempThingy.Pos.x, TempThingy.Pos.y, TempThingy.Pos.z));

	TempThingy.WorldMatrix = XMMatrixScaling(0.5,0.5,0.5);
	MyThings.push_back(TempThingy);
	////////////////////////
}

void DxInit::InitIndexBuffers()
{
	D3D11_BUFFER_DESC IndexBuffDesc;
	ZeroMemory(&IndexBuffDesc, sizeof(IndexBuffDesc));
	IndexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBuffDesc.CPUAccessFlags = NULL;
	IndexBuffDesc.ByteWidth = sizeof(unsigned int) * index.size();
	
	D3D11_SUBRESOURCE_DATA IndexData;
	ZeroMemory(&IndexData, sizeof(IndexData));
	IndexData.pSysMem = &index[0];
	
	DxDevice->CreateBuffer(&IndexBuffDesc, &IndexData, &IndexBuffer);
}

void DxInit::InitTextures()
{
	//D3D11_TEXTURE2D_DESC DxTextureDesc;
	//ZeroMemory(&DxTextureDesc, sizeof(DxTextureDesc));
	//DxTextureDesc.Width = crosshatch_width;
	//DxTextureDesc.Height = crosshatch_height;
	//DxTextureDesc.MipLevels = 11;
	//DxTextureDesc.ArraySize = 1;
	//DxTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//DxTextureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//DxTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	//DxTextureDesc.SampleDesc.Count = 1;
	//
	//D3D11_SUBRESOURCE_DATA DxTextureData[11]; //copy over
	//for (int i = 0; i < 11; i++)
	//{
	//	DxTextureData[i].pSysMem = &crosshatch_pixels[crosshatch_leveloffsets[i]];
	//	DxTextureData[i].SysMemPitch = (crosshatch_width >> i) * sizeof(UINT);
	//	DxTextureData[i].SysMemSlicePitch = 0;
	//}

	//DxDevice->CreateTexture2D(&DxTextureDesc, DxTextureData, &Dx2DTexture);

	CreateDDSTextureFromFile(DxDevice, L"Scarlet_Spiderman_D.dds", NULL, &DxShaderResourceView);

	//Create other texture in another thread
	TexutreThread ThreadTexture;
	ThreadTexture.ThreadDevice = &DxDevice;
	ThreadTexture.ThreadSRV = &DxShaderResourceView2;

	std::thread mrThread(LoadME, &ThreadTexture);
	mrThread.join();
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
	descDepth.SampleDesc.Count = 4;
	descDepth.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
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
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
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
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		//{ "INSTANCE", 0, DXGI_FORMAT_R32G32B32_OFLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	DxDevice->CreateInputLayout(TriLayout, 4, Trivial_VS, sizeof(Trivial_VS), &layout);
}

void DxInit::InitConstBuffers()
{
	D3D11_BUFFER_DESC ConstBuffDescript;
	ZeroMemory(&ConstBuffDescript, sizeof(ConstBuffDescript));
	ConstBuffDescript.ByteWidth = sizeof(MatrixTrio);
	ConstBuffDescript.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    //ConstBuffDescript.StructureByteStride = sizeof(MatrixTrio);
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
	Mycam.CameraTranslation();
	Mycam.CameraRotation();
	////////

	///////
	DxDeviceContext->OMSetRenderTargets(1, &DxRenderTargetView, DxStencilView);
	/////

	/////
	float Color[4] = { 0, 0.0f, 0.5f, 1 };

	DxDeviceContext->ClearRenderTargetView(DxRenderTargetView, Color);
	DxDeviceContext->ClearDepthStencilView(DxStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	/////
	MyThings[0].WorldMatrix = XMMatrixMultiply(XMMatrixRotationY(XMConvertToDegrees((float)MrTimer.Delta() * 0.05f)), MyThings[0].WorldMatrix);
	Mycam.SetWorldMatrix(MyThings[0].WorldMatrix);
	D3D11_MAPPED_SUBRESOURCE Cube;
	ZeroMemory(&Cube, sizeof(Cube));
	DxDeviceContext->Map(ConstBuffer, NULL, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, NULL, &Cube);
	memcpy(Cube.pData, &Mycam.GetMatrix(), sizeof(Mycam.GetMatrix()));
	DxDeviceContext->Unmap(ConstBuffer, NULL);

	/////
	//D3D11_MAPPED_SUBRESOURCE  RotateSub;
	//ZeroMemory(&RotateSub, sizeof(RotateSub));
	//DxDeviceContext->Map(ConstBuffer, NULL, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, NULL, &RotateSub);
	//memcpy(RotateSub.pData, &Mycam.GetMatrix(), sizeof(Mycam.GetMatrix()));
	//DxDeviceContext->Unmap(ConstBuffer, NULL);
	/////

	/////
	DxDeviceContext->VSSetConstantBuffers(1, 1, &ConstBuffer);
	//////

	///////
	DxDeviceContext->VSSetShader(DxVertexShader, 0, 0);
	DxDeviceContext->PSSetShader(DxPixelShader, 0, 0);
	///////

	//////
	DxDeviceContext->IASetInputLayout(layout);
	/////

	/////
	DxDeviceContext->PSSetSamplers(0, 1, &DxSampler);
	/////


#pragma region Cube

	/////
	DxDeviceContext->RSSetViewports(1, &DxViewPort);
	/////

	//////
	unsigned int pStrides = sizeof(Send_To_VRAM);
	unsigned int pOffset = 0;
	DxDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &pStrides, &pOffset);

	DxDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//////////

	/////
	DxDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	/////

	/////
	DxDeviceContext->PSSetShaderResources(0, 1, &DxShaderResourceView);
	DxDeviceContext->PSSetShaderResources(1, 1, &DxShaderResourceView2);
	//////

	/////
	DxDeviceContext->DrawIndexed(index.size(), 0, 0);
	/////

#pragma endregion


#pragma region SpiderMan	
	MyThings[1].WorldMatrix = XMMatrixMultiply(XMMatrixRotationY(XMConvertToDegrees((float)MrTimer.Delta() * 0.05f)), MyThings[1].WorldMatrix);

	Mycam.SetWorldMatrix(MyThings[1].WorldMatrix);
	D3D11_MAPPED_SUBRESOURCE Spidey;
	ZeroMemory(&Spidey, sizeof(Spidey));
	DxDeviceContext->Map(ConstBuffer, NULL, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, NULL, &Spidey);
	memcpy(Spidey.pData, &Mycam.GetMatrix(), sizeof(Mycam.GetMatrix()));
	DxDeviceContext->Unmap(ConstBuffer, NULL);

	DxDeviceContext->VSSetConstantBuffers(1, 1, &ConstBuffer);

	unsigned int pStrides2 = sizeof(Send_To_VRAM);
	unsigned int pOffset2 = 0;
	DxDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer2, &pStrides2, &pOffset2);

	//DxDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	DxDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DxDeviceContext->Draw(index2.size(), 0);
#pragma endregion 


#pragma region Cube View 2

	/////
	DxDeviceContext->RSSetViewports(1, &DxViewPort2);
	/////

	//////
	DxDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &pStrides, &pOffset);

	DxDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//////////

	/////
	DxDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	/////

	/////
	DxDeviceContext->PSSetShaderResources(0, 1, &DxShaderResourceView);
	DxDeviceContext->PSSetShaderResources(1, 1, &DxShaderResourceView2);
	//////

	/////
	DxDeviceContext->DrawIndexed(index.size(), 0, 0);
	/////

#pragma endregion

#pragma region SpiderMan View 2	
	//MyThings[1].WorldMatrix = XMMatrixMultiply(XMMatrixRotationY(XMConvertToDegrees((float)MrTimer.Delta() * 0.05f)), MyThings[1].WorldMatrix);

	//Mycam.SetWorldMatrix(MyThings[1].WorldMatrix);

	//D3D11_MAPPED_SUBRESOURCE Spidey;
	//ZeroMemory(&Spidey, sizeof(Spidey));
	//DxDeviceContext->Map(ConstBuffer, NULL, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, NULL, &Spidey);
	//memcpy(Spidey.pData, &Mycam.GetMatrix(), sizeof(Mycam.GetMatrix()));
	//DxDeviceContext->Unmap(ConstBuffer, NULL);

	DxDeviceContext->VSSetConstantBuffers(1, 1, &ConstBuffer);

	DxDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer2, &pStrides2, &pOffset2);

	//DxDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	DxDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DxDeviceContext->RSSetViewports(1, &DxViewPort2);

	DxDeviceContext->Draw(index2.size(), 0);
#pragma endregion 


	DxDeviceContext->RSSetState(DxRasterState);

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
	VertexBuffer2->Release();
	IndexBuffer->Release();

	DxSampler->Release();
	DxShaderResourceView->Release();
	DxShaderResourceView2->Release();

	DxRasterState->Release();

	UnregisterClass(L"DirectXApplication", application);
}