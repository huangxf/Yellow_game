#include "Core.h"

bool Core::InitDevcie(HWND hWnd)
{
	if(hWnd == NULL)
		return false;

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};


		DXGI_SWAP_CHAIN_DESC swap_chain_desc = { 0 };

		swap_chain_desc.BufferDesc.Width = this->width;
		swap_chain_desc.BufferDesc.Height = this->height;
		//swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
		//swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;	

		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.SampleDesc.Quality = 0;

		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.OutputWindow = hWnd;
		swap_chain_desc.Windowed = TRUE;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		D3D_FEATURE_LEVEL level;
		
		//SwapChain
		HRESULT hr;
		hr = D3D11CreateDeviceAndSwapChain(NULL, //default Adapter
			D3D_DRIVER_TYPE_HARDWARE,
			NULL, //FOR SOFTWARE DRIVER TYPE
			D3D11_CREATE_DEVICE_BGRA_SUPPORT, //FLAGS FOR RUNTIME LAYERS
			featureLevels, //FEATURE LEVELS ARRAY
			7, //# OF FEATURE LEVELS IN ARRAY
			D3D11_SDK_VERSION,
			&swap_chain_desc, //Swapchain description
			this->swapChain.GetAddressOf(), //Swapchain Address
			this->device.GetAddressOf(), //Device Address
			&level, //Supported feature level
			context.GetAddressOf()); //Device Context Address

		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Device or SwapChain."); return false;}

		//Back buffer
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Back buffer."); return false;}

		//Render Target View
		hr = this->device->CreateRenderTargetView(backBuffer.Get(), NULL, this->renderTargetView.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Render Target View."); return false;}

		//Texture
		D3D11_TEXTURE2D_DESC depthStencilDesc = { 0 };
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		hr = this->device->CreateTexture2D(&depthStencilDesc, NULL, this->depthStencilBuffer.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Texture."); return false;}

		//Depth stencil
		hr = this->device->CreateDepthStencilView(this->depthStencilBuffer.Get(), NULL, this->depthStencilView.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Depth stencil view."); return false;}

		this->context->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), this->depthStencilView.Get());

		CD3D11_DEPTH_STENCIL_DESC depthstencildesc(D3D11_DEFAULT);
		depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

		hr = this->device->CreateDepthStencilState(&depthstencildesc, this->depthStencilState.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Depth stencil State."); return false;}

		//Viewport
		CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(this->width), static_cast<float>(this->height));
		this->context->RSSetViewports(1, &viewport);
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Viewport."); return false;}

		//Rasterizer
		CD3D11_RASTERIZER_DESC rasterizerDesc(D3D11_DEFAULT);
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		hr = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizerState.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Rasterizer."); return false;}

		//Sampler
		CD3D11_SAMPLER_DESC sampDesc(D3D11_DEFAULT);
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		hr = this->device->CreateSamplerState(&sampDesc, this->samplerState.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Sampler."); return false;}		

		return true;

}

bool Core::InitShaders()
{


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"NORMAL",   0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};

	UINT numElements = ARRAYSIZE(layout);

	if (!vertexShader.Create(device, L"F:/codebase/yellow/Yellow/Debug/vertexshader.cso", layout, numElements, logger))
		return false;

	if (!pixelShader.Create(device, L"F:/codebase/yellow/Yellow/Debug/pixelshader.cso", logger))
		return false;

	return true;
}

bool Core::InitScene()
{
	using namespace DirectX;
	VertexPositionNormalTexture vertices[] = {
		VertexPositionNormalTexture(XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f)),
		VertexPositionNormalTexture(XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)),
		VertexPositionNormalTexture(XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f)),
		VertexPositionNormalTexture(XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f))
	};


	DWORD indices[] = {
		0,1,2,
		0,2,3
	};

	if(!vertexBuffer.Create(device, vertices, 4, logger)) {
		if(logger != NULL) logger->Add(L"Cannot create vertex buffer.");
		return false;
	}
	
	if(!indexBuffer.Create(device, indices, 6, logger)) {
			if(logger != NULL) logger->Add(L"Cannot create index buffer.");
		return false;	
	}


	HRESULT hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"F:/codebase/yellow/Yellow/Debug/DirectX_logo.jpg", NULL, texture.GetAddressOf());
	if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot load texture."); return false;}

	return true;

}

bool Core::Render()
{
	float bgcolor[] = { 0.5f, 1.0f, 1.0f, 1.0f };
	this->context->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
	this->context->ClearDepthStencilView(this->depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	this->context->IASetInputLayout(this->vertexShader.GetInputLayout().Get());
	this->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->context->RSSetState(this->rasterizerState.Get());
	this->context->OMSetDepthStencilState(this->depthStencilState.Get(), 0);
	this->context->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());
	this->context->VSSetShader(vertexShader.GetShader().Get(), NULL, 0);
	this->context->PSSetShader(pixelShader.GetShader().Get(), NULL, 0);


	UINT offset = 0;
	this->context->PSSetShaderResources(0, 1, this->texture.GetAddressOf());
	this->context->IASetVertexBuffers(0, 1, vertexBuffer.GetBufferPtr(), vertexBuffer.GetStridePtr(), &offset);
	this->context->IASetIndexBuffer(indexBuffer.GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
	this->context->DrawIndexed(indexBuffer.GetIndiciesNum(), 0, 0);


	this->swapChain->Present(1, NULL);
	return true;
}
