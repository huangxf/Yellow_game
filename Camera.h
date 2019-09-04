#ifndef __CAMERA__
#define __CAMERA__

#include <d3d11.h>
#include <DirectXMath.h>

class Camera
{
public:
	void UpdateView();

	Camera(): fovDegree(60.0f), aspectRatio(640/480), nearZ(0), farZ(100)
	{
		view = DirectX::XMMatrixIdentity();
		projection = DirectX::XMMatrixIdentity();
	}

	Camera(DirectX::XMVECTOR & pos, 
		   DirectX::XMVECTOR & right, 
		   DirectX::XMVECTOR & up, 
		   DirectX::XMVECTOR & look): pos(pos), right(right), up(up), look(look)
	{
		front = DirectX::XMVectorSubtract(look, right);
		void UpdateView();
	}

	void SetPos(DirectX::XMVECTOR & p) { pos = p; }
	void SetRight(DirectX::XMVECTOR & r) { right = r; }
	void SetUp(DirectX::XMVECTOR & u) { up = u; }
	void SetLook(DirectX::XMVECTOR & l) { look = l; front = DirectX::XMVectorSubtract(look, pos); }
	void SetFovDegree(float fov) { fovDegree = fov; }
	void SetAspectRatio(float ratio) { aspectRatio = ratio; }
	void SetNearZ(UINT z) { nearZ = z; }
	void SetFarZ(UINT z) { farZ = z; }




	DirectX::XMVECTOR & GetFront() { return front; }
	DirectX::XMVECTOR & GetRight() { return right; }
	DirectX::XMVECTOR & GetUp()	   { return up;    }
	float GetFovDegree()           { return fovDegree; }
	float GetAspectRatio()         { return aspectRatio; }
	UINT GetNearZ()                { return nearZ; }
	UINT GetFarZ()                 { return farZ; }

	void UpdateProjection()
	{
		float radians = (fovDegree / 360.0f) * DirectX::XM_2PI;
		this->projection = DirectX::XMMatrixPerspectiveFovLH(radians, aspectRatio, nearZ, farZ);
	}

	DirectX::XMMATRIX & GetProjection()
	{
		return projection;
	}



	void Walk(float speed) 
	{ 
		DirectX::XMVECTOR f =  DirectX::XMVectorSet(DirectX::XMVectorGetX(front) * speed, 0.0f, DirectX::XMVectorGetZ(front) * speed, 0.0f);
		pos = DirectX::XMVectorAdd(pos, f);
	}

	void Strade(float speed)
	{
		DirectX::XMVECTOR f =  DirectX::XMVectorSet(DirectX::XMVectorGetX(right) * speed, 0.0f, DirectX::XMVectorGetZ(right) * speed, 0.0f);
		pos = DirectX::XMVectorAdd(pos, f);
	}

	void Yaw(float angle)
	{
		DirectX::XMMATRIX yaw_matrix = DirectX::XMMatrixRotationY(angle);
		right = DirectX::XMVector4Transform(right, yaw_matrix);
		front = DirectX::XMVector4Transform(front, yaw_matrix);
	}

	void Pitch(float angle)
	{
		right = DirectX::XMVector4Normalize(right);
		DirectX::XMMATRIX pitch_matrix = DirectX::XMMatrixRotationAxis(right, angle);
		up = DirectX::XMVector3Transform(up, pitch_matrix);
		front = DirectX::XMVector3Transform(front, pitch_matrix);
	}


	DirectX::XMMATRIX & GetView() {return view;}
	

private:
	DirectX::XMVECTOR front;
	DirectX::XMVECTOR right;
	DirectX::XMVECTOR up;
	DirectX::XMVECTOR pos;
	DirectX::XMVECTOR look;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;

	float fovDegree;
	float aspectRatio;
	UINT  nearZ;
	UINT  farZ;
	

};

#endif