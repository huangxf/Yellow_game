#include "PixelShader.h"

bool PixelShader::Create(std::wstring path)
{
	HRESULT hr = D3DReadFileToBlob(path.c_str(), this->shader_buffer.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot read Pixel Shader file."); return false;}

	hr = device->CreatePixelShader(this->shader_buffer.Get()->GetBufferPointer(), this->shader_buffer.Get()->GetBufferSize(), NULL, this->shader.GetAddressOf());
		if(FAILED(hr)) { if(logger != NULL) logger->Add(L"Cannot create Pixel Shader."); return false;}

	return true;
}