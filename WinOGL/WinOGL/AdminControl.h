#pragma once
#include <gl/GL.h>
#include "math.h"
#include "Shape.h"
#include "Vector.h"
#include "ACDraw.h"
#include "ACMath.h"

typedef struct ACPoint {
	float x;
	float y;
}ACPOINT;

typedef struct ACPoint3 {
	float x;
	float y;
	float z;
}ACPOINT3;

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	CVertex Ve;
	CACDraw ACD;
	CACMath ACM;
private:
	int ButtonMode;
	bool SubButtonMode[2];

	CShape  *NowPointS = NULL;
	CVertex *NowPointV = NULL;
	CShape  *NowLineS = NULL;
	CVertex *NowLineV = NULL;
	CShape  *NowShape = NULL;
	CVertex *LastV_delete = NULL;

	int KeyButton = 0;
	ACPOINT3 WatchValue;

	int BBPoint;
	int BBPointOtherSide;
	bool DrawBBFlag = true;
	ACPOINT NewPoint;
	ACPOINT LastPoint;
	ACPOINT LastBB;
	ACPOINT3 MoveBeforPoint;
	ACPOINT FirstPoint;
	int ShapeCount = 0;
	int ChoiceXYZ = 3;
	int zDeltaValue;
	bool DragFlag = false;
	int DeleteError = 0;

	//çÇÇ≥ÅiébíËÅj
	float high = 0.5;
public:
	void AppendShape();
	void FreeShape();
	void FreeAll();

	void Draw();
	void Draw2();
	void Draw3();

	void SetWorldPoint(float wx, float wy);
	void SetWorldPoint(void);
	void MovePoint(float NowX, float NowY);
	void MovePoint();
	void MoveShape(float x, float y);
	void MoveShape();
	void AddWorldPoint(void);
	void DeleteWorldPoint(void);
	void DeleteShape();
	void ScalingShape(float NowX, float NowY);
	void ScalingShape();
	void TurnShape(float NowX, float NowY);
	void TurnShape();

	void SetFirstPoint(float x, float y);
	float GetFirstPointX();
	float GetFirstPointY();
	void SetNewPoint(float NewX, float NewY);
	float GetNewPointX();
	float GetNewPointY();

	void EndWorldPoint(void);
	int GetHeadVertexCount(void);
	bool GetHeadClosedFlag(void);
	float FirstPointDistance(float x, float y);
	float FirstPointDistance(void);

	bool Judge1(float NewX, float NewY);
	bool Judge2(float NewX, float NewY);
	bool Judge3(float NewX, float NewY);
	bool Judge4(void);
	bool Judge5(void);
	bool JudgeAll();

	void ChoiceNewPoint(float NewX, float NewY);
	void ChoicePoint(float NewX, float NewY);
	void ChoicePoint(float NewX, float NewY, float dis, int n);
	void ChoiceLine(float NewX, float NewY);
	void ChoiceShape(float NewX, float NewY);
	void ClearChoice(void);

	int GetButtonMode();
	void SetButtonMode(int n);
	bool GetSubButtonMode(int n);
	void SetSubButtonMode(int n);
	void SetLastPoint();
	void SetLastPoint(float x, float y);
	void SetMoveBeforPoint(float x, float y);
	bool CheckPoint(CVertex * v, ACPOINT p);
	bool CheckPoint(ACPOINT p, ACPOINT q);
	int GetNowChoice();

	void ChoiceBB(float x, float y);
	int GetBBPoint();
	void ClearBBPoint(int n);
	void SetLastBB();
	void SetDrawBBFlag(bool b);

	void SetWatchMoveValue(float NowX, float NowY);
	void SetWatchValue(float nx, float ny, float nz);
	void SetWatchValue(int del);
	void SetKeyButton(int key);
	void SetXYZ(int which);
	int GetXYZ();
	void SetDColor(float R, float G, float B);
	void GetNowShapeColor(float *R, float *G, float *B);
	void SetDragFlag(bool flag);
	bool IsShapeHeadClosed();
	void CheckShapeHead();
	bool IsShapeHeadNull();
	int GetShapeNum();
	int GetDeleteError();
	float GetHighValue();
	void SetHighValue(float h);
};