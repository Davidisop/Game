#pragma once
#include "Object_Handling.h"

class Box : public Object_Handling
{

public:
	bool   Set_VertexData();
	bool   update_ConstantBuffer();

public:
	bool Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile);


public:
	Box() {}
	virtual ~Box() {}
};

bool   Box::update_ConstantBuffer()
{
	g_pContext->UpdateSubresource(PipeLineSetup.m_pConstantBuffer, 0, NULL, &m_Constant_Data, 0, 0);

	return true;
}



bool  Box::Set_VertexData()
{
	m_VertexList.resize(36);
	int iner_index = 0;

	//¾Õ¸é

	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	// µÞ¸é
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	// ¿À¸¥ÂÊ
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));


	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	// ¿ÞÂÊ
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));

	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	// À­¸é
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	// ¾Æ·§¸é
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	m_icount_Vertexs = m_VertexList.size();

	return true;
}


bool    Box::Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile)
{
	PipeLineSetup.LoadTexture(pd3dDevice, pTexFile);
	PipeLineSetup.SetBlendState(pd3dDevice);
	PipeLineSetup.CreateVertextBuffer(pd3dDevice, &m_VertexList.at(0), m_icount_Vertexs);
	PipeLineSetup.CreateConstantBuffer(pd3dDevice, &m_Constant_Data);
	PipeLineSetup.CreateVertexShader(pd3dDevice, pVsFile);
	PipeLineSetup.CreateLayout(pd3dDevice);
	PipeLineSetup.CreatePixelShader(pd3dDevice, pPsFile);


	PipeLineSetup.For_Viewport_get_set();
	PipeLineSetup.Create_RasterizerState();
	PipeLineSetup.CreateTexture2D_DepthStencilView();
	PipeLineSetup.CreateDepthStencilState();

	return true;
}