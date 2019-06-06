#ifndef _INDEXBUFFER
#define _INDEXBUFFER

#include "d3d11.h"
#include "wrl/client.h"
#include "LOG.h"


class IndexBuffer
{
public:
	bool Create(Microsoft::WRL::ComPtr<ID3D11Device> & device, DWORD *data, UINT numIndices, LOG * logger)
	{
		this->bufferSize = numIndices;

		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(DWORD)*numIndices;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;


		D3D11_SUBRESOURCE_DATA indexBufferData;
		indexBufferData.pSysMem = data;
		HRESULT hr = device->CreateBuffer(&indexBufferDesc, &indexBufferData, buffer.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create pixel buffer."); return false;}
		return true;
	}

	ID3D11Buffer * GetBuffer()
	{
		return buffer.Get();
	}

	ID3D11Buffer * const * GetBufferPtr()
	{
		return buffer.GetAddressOf();
	}

	UINT GetIndiciesNum()
	{
		return bufferSize;
	}


private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT bufferSize;
	LOG * logger;
};

#endif