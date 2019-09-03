#ifndef __CAMERA__
#define __CAMERA__

#include <d3d11.h>
#include <DirectXMath.h>

class Camera
{
public:
	void UpdateView();

	Camera() {
		view = DirectX::XMMatrixIdentity();
	}

	Camera(DirectX::XMVECTOR & pos, 
		   DirectX::XMVECTOR & right, 
		   DirectX::XMVECTOR & up, 
		   DirectX::XMVECTOR & look): pos(pos), right(right), up(up), look(look)
	{
		front = DirectX::XMVectorSubtract(look, right);
		void UpdateView();
	}

	void SetPos(DirectX::XMVECTOR & pos) { pos = pos; }
	void SetRight(DirectX::XMVECTOR & right) { right = right; }
	void SetUp(DirectX::XMVECTOR & up) { up = up; }
	void SetLook(DirectX::XMVECTOR & look) { look = look; }


	DirectX::XMVECTOR & GetFront() { return front; }
	DirectX::XMVECTOR & GetRight() { return right; }
	DirectX::XMVECTOR & GetUp()	   { return up;    }



	void Move(float speed) 
	{ 
		DirectX::XMFLOAT3 f(DirectX::XMVectorGetX(front) * speed, 0.0f, DirectX::XMVectorGetZ(front) * speed);
		pos = DirectX::XMLoadFloat3(&f);
	}


	DirectX::XMMATRIX & GetView() {return view;}
	

private:
	DirectX::XMVECTOR front;
	DirectX::XMVECTOR right;
	DirectX::XMVECTOR up;
	DirectX::XMVECTOR pos;
	DirectX::XMVECTOR look;
	DirectX::XMMATRIX view;
};

#endif