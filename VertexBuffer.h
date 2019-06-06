#ifndef _VERTEXBUFFER
#define _VERTEXBUFFER

#include "d3d11.h"
#include "wrl/client.h"
#include "LOG.h"

template <class T>
class VertexBuffer
{
public:
	bool Create(Microsoft::WRL::ComPtr<ID3D11Device> & device, T *data, UINT numVertices, LOG * logger)
	{
		this->bufferSize = numVertices;
		this->stride = (UINT)(sizeof(T));

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(T) * numVertices;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = data;

		HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, this->buffer.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create vertex buffer."); return false;}
		return true;
	}

	bool GetBuffer()
	{
		return buffer;
	}

	ID3D11Buffer ** GetBufferPtr()
	{
		return buffer.GetAddressOf();
	}

	UINT GetStride()
	{
		return stride;
	}

	UINT * GetStridePtr()
	{
		return &stride;
	}

	UINT GetVerticesNum()
	{
		return bufferSize;
	}


private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT stride;
	UINT bufferSize;
	LOG * logger;
};

#endif