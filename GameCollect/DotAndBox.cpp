#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


//DotAndBox dotandbox;
// 配列を使用して描画した点の座標を保存
Point drawnPoints[MAX_POINTS];
int numDrawnPoints = 0;

// 新しい座標情報を保存する配列
int numDrawnLines = 0;
LineInfo Line[MAX_POINTS];
LineInfo data[MAX_POINTS] = {};


LineInfo savedLines[MAX_POINTS] = {};
int numSavedLines;

LineInfo lineinfo[MAXLINENUMBER];
int numLines[MAXLINENUMBER] = { 0 };

DotAndBox::DotAndBox() : guidePointflg(false)
{
	endX = 0;
	endY = 0;

	pointerX = 450;
	pointerY = 275;

	int ScreenWidth = SCREEN_WIDTH;
	int ScreenHeight = SCREEN_HEIGHT;

	// グリッド内の点を描画(ドットの開始位置が定数化しているため今度修正 startX, startY, rows, columnsの変更)
	gridSize = 150;  // グリッドの間隔
	startX = 480;   // 開始X座標
	startY = 250;   // 開始Y座標

	Drawflg = false;

	selectedPointX = 0;
	selectedPointY = 0;

	drawnPointX = 0;
	drawnPointY = 0;

	numDrawnLines = 0;

	selectedLine.LinestartX = 0;
	selectedLine.LinestartY = 0;
	selectedLine.LineendX = 0;
	selectedLine.LineendY = 0;

	// savedLines 配列を初期化
	for (int i = 0; i < MAX_POINTS; ++i) {
		savedLines[i] = {}; // デフォルトコンストラクタで初期化
	}

	for (int i = 0; i < 20; i++)
	{
		Line_check[i] = 0;
	}
	for (int i = 0; i < 5; i++)
	{
		Box_check[i] = 0;
	}

	currentturn = 0;

	Bcnt = 4;
	Rcnt = 0;

	OnClicked = 0;
}

DotAndBox::~DotAndBox() {

}

void DotAndBox::DrawGridOfPoints(int startX, int startY, int gridSize, int rows, int columns) const {
	int lineThickness = 5;  // 線の太さ
	int originalrows = rows;
	int originalcolumns = columns;
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int x = startX + i * gridSize;
			int y = startY + j * gridSize;
			DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);
		}
	}
	// ガイドの描画
	int guideX, guideY;
	GetNearestPoint(pointerX, pointerY, startX, startY, gridSize, rows, columns, guideX, guideY);
	DrawCircle(guideX, guideY, 12, GetColor(0, 255, 0), TRUE, 3);  // ガイドを黄緑で描画

}

void DotAndBox::Update() {

	g_Oldkey = g_Nowkey;
	g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Keyflg = g_Nowkey & ~g_Oldkey;

	// 移動後の位置を一時的に計算
	int tempX = pointerX;
	int tempY = pointerY;

	if (Keyflg & PAD_INPUT_LEFT) {
		tempX -= GetgridSize();  // 左に移動
	}
	if (Keyflg & PAD_INPUT_RIGHT) {
		tempX += GetgridSize();  // 右に移動
	}
	if (Keyflg & PAD_INPUT_UP) {
		tempY -= GetgridSize();  // 上に移動
	}
	if (Keyflg & PAD_INPUT_DOWN) {
		tempY += GetgridSize();  // 下に移動
	}

	// 画面からはみ出ないように修正
	if (tempX > GetgridSize() * 3 && tempX < SCREEN_WIDTH - GetgridSize() * 3) {
		pointerX = tempX;
	}

	if (tempY > GetgridSize() && tempY < SCREEN_HEIGHT - GetgridSize()) {
		pointerY = tempY;
	}

	if (Keyflg & PAD_INPUT_A) {
		if (guidePointflg) {
			GetLineNumber(guidePointX, guidePointY, pointerX, pointerY);

			AddLineInfo(guidePointX, guidePointY, pointerX, pointerY);

			guidePointflg = false;
		}
		else {

			// ガイド点を保存
			guidePointX = pointerX;
			guidePointY = pointerY;
			guidePointflg = true;

			Drawflg = true;
		}

	}

	BoxCheck(Line_check);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int x = startX + i * gridSize;
			int y = startY + j * gridSize;
			DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);

			// 描画した点の座標を保存
			if (numDrawnPoints < MAX_POINTS) {
				drawnPoints[numDrawnPoints].x = x;
				drawnPoints[numDrawnPoints].y = y;
				numDrawnPoints++;

				// 描画した点の座標を渡す
				SetDrawnPoint(x, y);

			}
		}
	}

	SetgridSize(gridSize);
}

void DotAndBox::Draw() const {

	// ポインターを描画
	DrawCircle(pointerX - 30, pointerY + 30, 10, GetColor(0, 255, 0), TRUE);

	// グリッド内の点を描画(ドットの開始位置が定数化しているため今度修正 startX, startY, rows, columnsの変更)
	//int gridSize = 150;  // グリッドの間隔
	//int startX = 480;   // 開始X座標
	//int startY = 250;   // 開始Y座標
	int rows = 3;       // 行数
	int columns = 3;    // 列数



	DrawGridOfPoints(startX, startY, gridSize, rows, columns);

	SetFontSize(30);
	DrawSavedLine(lineinfo, Line_check);

	DxLib::DrawFormatString(480, 100, GetColor(100, 100, 255), "Blue : %d", Bcnt);
	DxLib::DrawFormatString(660, 100, GetColor(255, 0, 0), "Red : %d", Rcnt);
	
	if (Bcnt + Rcnt == 4) {
		if (Bcnt == Rcnt) {
			SetFontSize(100);
			DxLib::DrawFormatString(425, 300, GetColor(0, 255, 0), "引き分け");
		}
		else if (Bcnt > Rcnt) {
			SetFontSize(100);
			DxLib::DrawFormatString(425, 300, GetColor(50, 50, 255), "青の勝ち");
		}
		else if (Bcnt < Rcnt) {
			SetFontSize(100);
			DxLib::DrawFormatString(425, 300, GetColor(255, 0, 0), "赤の勝ち");
		}
	}
}

int DotAndBox::Result() {

	SetBcnt(Bcnt);
	SetRcnt(Rcnt);

	if (BoxCheck(Line_check) != 0) {
		for (int i = 0; i < MAXBOX; i++) {
			if (Box_check[i] == 1) {
				Bcnt++;
			}
			else if (Box_check[i] == 2 ) {
				Rcnt++;

			}
		}
	}

	if(Bcnt + Rcnt == 4)
	if (Bcnt == Rcnt) {
		return 1;
	}
	else if (Bcnt > Rcnt) {
		return 2;
	}
	else if (Bcnt < Rcnt) {
		return 3;
	}
	return 0;
}


void DotAndBox::SetDrawnPoint(int x, int y) {
	drawnPointX = x;
	drawnPointY = y;

	SetPointer(x, y);
}

int DotAndBox::GetDrawnPointX() {
	return drawnPointX;
}

int DotAndBox::GetDrawnPointY() {
	return drawnPointY;
}

void DotAndBox::SetgridSize(int size) {
	gridSize = size;
}

int DotAndBox::GetgridSize() const {
	return gridSize;
}

void DotAndBox::GetNearestPoint(int pointerX, int pointerY, int startX, int startY, int gridSize, int rows, int columns, int& nearestX, int& nearestY) const {

	LineInfo line;
	line.LinestartX = startX;
	line.LinestartY = startY;
	line.LineendX = endX;
	line.LineendY = endY;

	int linestartX = line.LinestartX;
	int linestartY = line.LinestartY;
	int lineendX = line.LineendX;
	int lineendY = line.LineendY;

	double lineLength = sqrt(pow(endX - startX, 2) + pow(endY - startY, 2));
	double u = ((pointerX - startX) * (endX - startX) + (pointerY - startY) * (endY - startY)) / (lineLength * lineLength);

	if (u < 0.0) {
		// カーソルが線分の始点よりも前にある場合
		nearestX = linestartX;
		nearestY = linestartY;
	}
	else if (u > 1.0) {
		// カーソルが線分の終点よりも後ろにある場合
		nearestX = endX;
		nearestY = endY;
	}
	else {
		// カーソルが線分上にある場合
		nearestX = static_cast<int>(linestartX + u * (endX - linestartX));
		nearestY = static_cast<int>(linestartY + u * (endY - linestartY));
	}

	double minDistance = sqrt(pow(startX - pointerX, 2) + pow(startY - pointerY, 2));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int x = startX + i * gridSize;
			int y = startY + j * gridSize;
			double distance = sqrt(pow(x - pointerX, 2) + pow(y - pointerY, 2));

			if (distance < minDistance) {
				minDistance = distance;
				nearestX = x;
				nearestY = y;
			}
		}
	}
}

void DotAndBox::SelectNearestPointOnLine(int pointerX, int pointerY) {
	int nearestPointX, nearestPointY;

	for (int i = 0; i < numDrawnLines; ++i) {
		const LineInfo& line = data[i];

		// カーソルが線上の点を選択
		GetNearestPoint(pointerX, pointerY, line.LinestartX, line.LinestartY, 3, 3, 3, nearestPointX, nearestPointY);

		// 選択された点の座標を保存
		SetDrawnPoint(nearestPointX, nearestPointY);
		Drawflg = true;

		// 新しい線の情報を作成
		LineInfo newLine = { nearestPointX, nearestPointY, drawnPointX, drawnPointY };

		// 選択された線の情報を更新
		selectedLine = newLine;

	}
}

void DotAndBox::DrawGuideLine(int startX, int startY, int endX, int endY, int color, int thickness) const {
	DrawLine(startX, startY, endX, endY, color, thickness);
}

void DotAndBox::AddLineInfo(int startX, int startY, int endX, int endY) {
	int lineNumber = GetLineNumber(startX, startY, endX, endY); // GetLineNumber 関数を呼び出して線の番号を取得

	 //Xの始点が終点より大きいとき
	if (startX > endX) {
		int x = startX;
		startX = endX;
		endX = x;
	}
	//Yの始点が終点より大きいとき
	if (startY > endY) {
		int y = startY;
		startY = endY;
		endY = y;
	}

	// 座標の保存
	lineinfo[lineNumber].LinestartX = startX;
	lineinfo[lineNumber].LinestartY = startY;
	lineinfo[lineNumber].LineendX = endX;
	lineinfo[lineNumber].LineendY = endY;
	lineinfo[lineNumber].Drawnturn = GetLineColor();

	Line_check[lineNumber] = 1;

	this->SwitchTurn();

}

bool DotAndBox::IsAlreadyLined(const int Line_check[], int lineIndex) {
	if (Line_check[lineIndex] == 1) {
		return true;   // 重複あり
	}
	return false; // 重複なし
}

void DotAndBox::DrawSavedLine(const LineInfo lineinfo[MAXLINENUMBER], const int Line_check[]) const {
	for (int i = 0; i < MAXLINENUMBER; ++i) {
		const LineInfo& line = lineinfo[i];
		if (Line_check[i] != 0) {
			// 線の始点座標と終点座標が両方ともゼロでない場合に描画処理を行う
			if (line.LinestartX != 0 && line.LinestartY != 0 && line.LineendX != 0 && line.LineendY != 0) {
				DrawGuideLine(line.LinestartX, line.LinestartY, line.LineendX, line.LineendY, line.Drawnturn, 3);
				//dotandbox.BoxCheck(Line_check);
			}
		}
	}
}

void DotAndBox::DrawCreatedBox(const LineInfo lineinfo[MAXLINENUMBER], const int Line_check[]) const {
	for (int i = 0; i < MAXLINENUMBER; ++i) {
		const LineInfo& line = lineinfo[i];
		if (Line_check[i] != 0) {
		}
	}
}

bool DotAndBox::IsValidLine(const LineInfo lineinfo[MAXLINENUMBER], const int line_check[]) const {
	for (int i = 0; i < MAXLINENUMBER; ++i) {
		const LineInfo& line = lineinfo[i];
		// 縦横の線のみ描画する場合
		if (line.LinestartX != line.LineendX && line.LinestartY != line.LineendY) {
			return false;
		}

		// 一定の長さ以下の線は描画しない場合（例：gridSizeの1.5倍以下）
		double length = sqrt(pow(line.LineendX - line.LinestartX, 2) + pow(line.LineendY - line.LinestartY, 2));
		if (length <= GetgridSize() * 1.5) {
			return false;
		}
		//線がすでに引かれている場合
	   /* if (!IsAlreadyLined)*/
			// 同じ点を押した場合
		if (line.LinestartX == line.LineendX && line.LinestartY == line.LineendY) {
			return false;
		}
	}

	return true;
}

void DotAndBox::SwitchTurn() {
	if (currentturn == 1) {
		currentturn = 2; // ターンをプレイヤー2に切り替える
	}
	else {
		currentturn = 1; // ターンをプレイヤー1に切り替える
	}
}

int DotAndBox::GetLineColor() {
	if (GetCurrentTurn() == 1) {
		return GetColor(255, 0, 0); // プレイヤー1のターンなら青を返す
	}
	else {
		return GetColor(0, 0, 255); // プレイヤー2のターンなら赤を返す
	}
}

int DotAndBox::GetLineNumber(int startX, int startY, int endX, int endY) {

	//Xの始点が終点より大きいとき
	if (startX > endX) {
		int x = startX;
		startX = endX;
		endX = x;
	}
	//Yの始点が終点より大きいとき
	if (startY > endY) {
		int y = startY;
		startY = endY;
		endY = y;
	}

	if (startX == 480) {
		if (startY == 250) {
			if (endX == 630) {
				return 0;
			}
			else if (endX == 480) {
				return 2;
			}
		}
		else if (startY == 400) {
			if (endX == 630) {
				return 5;
			}
			else if (endX == 480) {
				return 7;
			}
		}
		else if (startY == 550) {
			if (endX == 630) {
				return 10;
			}
		}
	}
	else if (startX == 630) {
		if (startY == 250) {
			if (endX == 780) {
				return 1;
			}
			else if (endX == 630) {
				return 3;
			}
		}
		else if (startY == 400) {
			if (endX == 780) {
				return 6;
			}
			else if (endX == 630) {
				return 8;
			}
		}
		else if (startY == 550) {
			if (endX == 780) {
				return 11;
			}
		}
	}
	else if (startX == 780) {
		if (startY == 250) {
			if (endX == 780) {
				return 4;
			}
		}
		else if (startY == 400) {
			if (endX == 780) {
				return 9;
			}
		}
	}
	return -10;
}

int DotAndBox::BoxCheck(const int Line_check[]) {
	if ((Line_check[0] != 0 && Line_check[2] != 0) && Line_check[3] != 0 && Line_check[5] != 0) {
		if (Box_check[0] == 0) {
			Box_check[0] = GetCurrentTurn();
			return 1;
		}
	}
	if ((Line_check[1] != 0 && Line_check[4] != 0) && Line_check[3] != 0 && Line_check[6] != 0) {
		if (Box_check[1] == 0) {
			Box_check[1] = GetCurrentTurn();
			return 1;
		}
	}
	if ((Line_check[7] != 0 && Line_check[10] != 0) && Line_check[5] != 0 && Line_check[8] != 0) {
		if (Box_check[2] == 0) {
			Box_check[2] = GetCurrentTurn();
			return 1;
		}
	}
	if ((Line_check[9] != 0 && Line_check[11] != 0) && Line_check[6] != 0 && Line_check[8] != 0) {
		if (Box_check[3] == 0) {
			Box_check[3] = GetCurrentTurn();
			return 1;
		}
	}
	if (Line_check[3] != 0) {
		if ((Line_check[0] != 0 && Line_check[2] != 0) && Line_check[5] != 0) {
			if (Box_check[0] == 0) {
				Box_check[0] = GetCurrentTurn();
			}
		}
		if ((Line_check[1] != 0 && Line_check[4] != 0) && Line_check[6] != 0) {
			if (Box_check[1] == 0) {
				Box_check[1] = GetCurrentTurn();
			}
		}
		return 1;
	}
	if (Line_check[5] != 0) {
		if ((Line_check[0] && Line_check[2] != 0) && Line_check[3] != 0) {
			if (Box_check[0] == 0) {
				Box_check[0] = GetCurrentTurn();
			}

		}
		if ((Line_check[7] != 0 && Line_check[10] != 0) && Line_check[8] != 0) {
			if (Box_check[2] == 0) {
				Box_check[2] = GetCurrentTurn();
			}
		}
		return 1;
	}
	if (Line_check[6] != 0) {
		if ((Line_check[1] && Line_check[4] != 0) && Line_check[3] != 0) {
			if (Box_check[1] == 0) {
				Box_check[1] = GetCurrentTurn();
			}
		}
		if ((Line_check[9] != 0 && Line_check[11] != 0) && Line_check[8] != 0) {
			if (Box_check[3] == 0) {
				Box_check[3] = GetCurrentTurn();
			}
		}
		return 1;
	}
	if (Line_check[8] != 0) {
		if ((Line_check[7] && Line_check[10] != 0) && Line_check[5] != 0) {
			if (Box_check[2] == 0) {
				Box_check[2] = GetCurrentTurn();
			}
		}
		if ((Line_check[9] != 0 && Line_check[11] != 0) && Line_check[6] != 0) {
			if (Box_check[3] == 0) {
				Box_check[3] = GetCurrentTurn();
			}
		}
		return 1;
	}
	return 0;
}