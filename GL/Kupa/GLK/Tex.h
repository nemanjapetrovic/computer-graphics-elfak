#pragma once
class CTex
{
public:
	UINT id;
	CTex();
	~CTex();
	void PrepareTexture(bool lightEnabled);
	void LoadTexture(CString fileName);
	void Select();
	void Release();
};

