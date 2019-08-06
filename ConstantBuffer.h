#ifndef _CONSTANT_BUFFER_
#define _CONSTANT_BUFFER_

#include <d3d11.h>
#include <wrl/client.h>

template<class T>
class ConstantBuffer
{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	T * data;

public:
	ConstantBuffer():data(NULL) {}

	void SetData(T * data) 
	{ 
		this->data = data; 
	}

	T * GetData(T * data) 
	{
		return this->data; 
	}

	ID3D11Buffer * Get()
	{
		return buffer.Get();
	}

	ID3D11Buffer * const * GetAddressOf()
	{
		return buffer.GetAddressOf();
	}


	bool Init(ID3D11Device * device, ID3D11DeviceContext * context)
	{
		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.ByteWidth = (UINT)(sizeof(T) - (16 - sizeof(T)%16));
		desc.StructureByteStride = 0;

		HRESULT hr = device->CreateBuffer(&desc, 0, buffer.GetAddressOf());

		if(FAILED(hr)) return false;

		return true;
	}

	bool ApplyChange(ID3D11DeviceContext * context)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		HRESULT hr = context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		if(FAILED(hr))
			return false;

		CopyMemory(mappedResource.pData, data, sizeof(T));
		context->Unmap(buffer.Get(), 0);
		return true;
	}

};

#endif