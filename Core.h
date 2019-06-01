#ifndef _CORE
#define _CORE

#include "d3d11.h"
#include "wrl/client.h"
#include "LOG.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"


class Core
{
public:
	bool InitDevcie(HWND hWnd);
	bool InitShaders();
	bool InitScene();
	bool Render();
	

	Core(): width(640),height(480),logger(NULL) {}
	Core(LOG *logger): width(640),height(480),logger(logger) {}

	void SetLogger(LOG *logger) {this->logger = logger;}

private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	int width;
	int height;
	LOG *logger;


};

#endif