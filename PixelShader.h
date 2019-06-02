#ifndef _PIXELSHADER
#define _PIXELSHADER

#include "d3d11.h"
#include "wrl/client.h"
#include <d3dcompiler.h>
#include <string>
#include "LOG.h"


class PixelShader
{
public:
	bool Create(Microsoft::WRL::ComPtr<ID3D11Device> & device , std::wstring path, LOG * logger);
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetShader() {return  shader;}
	Microsoft::WRL::ComPtr<ID3D10Blob> GetBuffer() { return shader_buffer; }
	

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
	Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer;
};

#endif

