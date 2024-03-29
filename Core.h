#ifndef _CORE
#define _CORE

#include "d3d11.h"
#include <DirectXMath.h>
#include "wrl/client.h"
#include "LOG.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "WICTextureLoader.h"
#include "VertexTypes.h"
#include "ConstantBuffer.h"
#include "Camera.h"


class Core
{
public:
	bool InitDevcie(HWND hWnd);
	bool InitShaders();
	bool InitScene();
	bool Render();
	Camera & GetWorldCamera() { return camera; }
	

	Core(): width(640),height(480),logger(NULL) {}
	Core(LOG *logger): width(640),height(480),logger(logger) { }

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

	ConstantBuffer<DirectX::XMMATRIX> matConstantBuffer;

	VertexShader vertexShader;
	PixelShader pixelShader;

	VertexBuffer<DirectX::VertexPositionNormalTexture> vertexBuffer;
	IndexBuffer indexBuffer;

	Camera camera;

	int width;
	int height;
	LOG *logger;


};

#endif
