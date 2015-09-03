#include "Defines.h"
#include "Camera.h"

class DxInit
{
	HINSTANCE						application;
	WNDPROC							appWndProc;
	HWND							window;

	ID3D11Device *					DxDevice;
	ID3D11DeviceContext *			DxDeviceContext;
	
	ID3D11RenderTargetView *		DxRenderTargetView;
	
	IDXGISwapChain *				DxSwapChain;
	DXGI_SWAP_CHAIN_DESC			SwapDescrip;
	
	D3D11_VIEWPORT					DxViewPort;
	ID3D11Texture2D *			    Dx2DTexture;
	
	ID3D11Buffer * DxBuffer;
	ID3D11Buffer * ConstBuffer;
	ID3D11Buffer * ConstSceneBuffer;
	
	ID3D11VertexShader * DxVertexShader;
	ID3D11PixelShader * DxPixelShader;
	
	ID3D11InputLayout * layout;
	
	ID3D11DepthStencilView* DxStencilView;
	ID3D11Texture2D* DxDeviceDepthStencil = NULL;
	
	ID3D11Buffer * VertexBuffer;
	ID3D11Buffer * IndexBuffer;
	
	ID3D11SamplerState * DxSampler;
	ID3D11ShaderResourceView * DxShaderResourceView;
	
	unsigned int DxVertCount;

	Camera Mycam;
	XTime MrTimer;

public:

	DxInit(){};
	~DxInit(){};
	void CreateMyWindow(HINSTANCE hinst, WNDPROC proc);

	void Initalize();
	void InitSwapChain(HWND window, int width, int height);
	void InitViewPort(float minDepth, float maxDepth, float width, float height, unsigned int NumOfViewPorts);
	void InitVertexBuffers();
	void InitIndexBuffers();
	void InitTextures();
	void InitSampler();
	void InitSRVs();
	void InitDepthStencils();
	void InitDepthStencilViews();
	void InitInputLayouts();
	void InitConstBuffers();
	void InitShaders();

	bool Run();
	void Resize();
	void Release();
};