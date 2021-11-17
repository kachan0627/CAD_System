#pragma once
class CVertex
{
public:
	CVertex();
	CVertex(float px, float py);
	~CVertex();
private:
	// x���W
	float x;
	// y���W
	float y;
	bool ThroughFlag = false;
	// �|�C���^
	CVertex *Next_Vertex;
public:
	void SetX(float px);
	float GetX(void);
	void GetX(float *nx);
	void SetY(float py);
	float GetY(void);
	void GetY(float *ny);
	void SetNextVertex(CVertex *pn);
	CVertex *GetNextVertex(void);
	void GetXY(float xy[2]);
	void GetXY(float *nx, float *ny);
	void SetThroughFlag(bool b);
	bool GetThroughFlag();
};