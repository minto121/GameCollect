#include"DxLib.h"
#include"Hex_GameMain.h"
#include"Padinput.h"

//コンストラクタ
Hex::Hex() {
	BackImg = LoadGraph("images/Hex/Background02.png");
	BlueHexImg = LoadGraph("images/Hex/hexagon-B50.png");
	RedHexImg = LoadGraph("images/Hex/hexagon-R50.png");
	BlackHexImg = LoadGraph("images/Hex/hexagon-Black50.png");
	GreenHexImg = LoadGraph("images/Hex/hexagon-G50.png");
	HexImg = LoadGraph("images/Hex/hexagon-50.png");
	Select_i = 6;
	Select_j = 6;
	P_CheckFlg = 0;
	P_CheckCnt = 0;
	ClearFlg = 0;
	E_CheckFlg = 0;
	E_CheckCnt = 0;
	TurnFlg = GetRand(1);
	TurnSave = TurnFlg;
	GameInit();
}
	
//描画以外
AbstractScene* Hex::Update() {
	if (ClearFlg == 0) {
		TurnSave = TurnFlg;
		if (TurnFlg % 2 == 1) {
			Select();
		}
		if (TurnFlg % 2 == 0) {
			TurnSave = TurnFlg;
			Enemy();
		}
		Check_P();
		Check_E();
	}
	else if (ClearFlg == 1) {

	}
	else if (ClearFlg == 2) {

	}
	return this;
}

//描画のみ
void Hex::Draw()const {

	if (ClearFlg == 0) {
		//背景画像
		DrawGraph(0, 0, BackImg, FALSE);

		DrawStage();

		DrawGraph(gStage[Select_i][Select_j].x, gStage[Select_i][Select_j].y, GreenHexImg, TRUE);

		//DrawGraph(gStage[1][2].x, gStage[1][2].y, GreenHexImg, TRUE);

	}
	if (ClearFlg == 1) {
		DrawGraph(0, 0, BackImg, FALSE);
	}
	else if (ClearFlg == 2) {
		DrawGraph(615, 335, GreenHexImg, TRUE);
	}
}

//初期化
void Hex::GameInit() {
	//ステージ初期化
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			gStage[i][j].cnt = 0;
			if (j == 0 && i == 0 || j == 12 && i == 12) {
				gStage[i][j].flg = 3;	//黒
			}
			else if (i == 0 && j != 12 || i == 12) {
				gStage[i][j].flg = 5;	//青
			}
			else if (j == 0 || j == 12) {
				gStage[i][j].flg = 4;	//赤
			}
			else {
				gStage[i][j].flg = 0;	//白
			}
			gStage[i][j].x = (j + i - 1) * -30 + 945;	
			gStage[i][j].y = (j - i - 1) * -17 + 320;	
		}
	}
}

//タイルを置く場所の移動&設置
void Hex::Select() {
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		if (gStage[++Select_i][--Select_j].flg >= 3) {
			Select_j = Select_j + 1;
			Select_i = Select_i - 1;
			if (gStage[Select_i][--Select_j].flg >= 3) {
				Select_j = Select_j + 1;
			}
			if (gStage[++Select_i][Select_j].flg >= 3) {
				Select_i = Select_i - 1;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		if (gStage[--Select_i][++Select_j].flg >= 3) {
			Select_i = Select_i + 1;
			Select_j = Select_j - 1;
			if (gStage[Select_i][++Select_j].flg >= 3) {
				Select_j = Select_j - 1;
			}
			if (gStage[--Select_i][Select_j].flg >= 3) {
				Select_i = Select_i + 1;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		if (gStage[Select_i][--Select_j].flg >= 3) {
			Select_j = Select_j + 1;
			if (gStage[--Select_i][Select_j].flg >= 3) {
				Select_i = Select_i + 1;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		if (gStage[++Select_i][Select_j].flg >= 3) {
			Select_i = Select_i - 1;
			if (gStage[Select_i][++Select_j].flg >= 3) {
				Select_j = Select_j - 1;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		if (gStage[Select_i][Select_j].flg == 0) {
			gStage[Select_i][Select_j].flg = 1;
			Select_i = 6;
			Select_j = 6;
			TurnFlg++;
		}
	}
	/*if (TurnFlg % 2 == 0) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
		{
			if (gStage[Select_i][Select_j].flg == 0) {
				gStage[Select_i][Select_j].flg = 2;
				Select_i = 6;
				Select_j = 6;
				TurnFlg++;
			}
		}
	}*/
}

//ステージ描画
void Hex::DrawStage() const {

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			switch (gStage[i][j].flg) {
			case 0:
				DrawGraph(gStage[i][j].x, gStage[i][j].y, HexImg, TRUE);
				break;
			case 1:
			case 4:
				DrawGraph(gStage[i][j].x, gStage[i][j].y, RedHexImg, TRUE);
				break;
			case 2:
			case 5:
				DrawGraph(gStage[i][j].x, gStage[i][j].y, BlueHexImg, TRUE);
				break;
			case 3:
				DrawGraph(gStage[i][j].x, gStage[i][j].y, BlackHexImg, TRUE);
				break;
			}
		}
	}
}

void Hex::Check_P() {
	//保存用
	int i = 1;
	int j = 1;
	//変更用
	int x = 1;
	int y = 1;
	//カウント保存
	int SaveCnt = P_CheckCnt;

	for (i = 1; i < 12;i++) {
		for (j = 1; j < 12; j++) {
			//最初の列の検査
			if (i == 1) {
				//駒があったら隣接するマスを記憶する
				if (gStage[j][i].flg == 1) {
					x = i;
					y = j;
					//上
					gStage[--y][++x].cnt = 1;
					x = i;
					y = j;
					//下
					gStage[++y][--x].cnt = 1;
					x = i;
					y = j;
					//左上
					gStage[y][++x].cnt = 1;
					x = i;
					//右上
					gStage[--y][x].cnt = 1;
					y = j;
					//左
					gStage[++y][x].cnt = 1;
					y = j;
					//右
					gStage[y][--x].cnt = 1;
					x = i;
					P_CheckCnt++;
					SaveCnt = P_CheckCnt;
				}	//最初の列に駒がなかったら終了
				else if(j == 11){
					if (P_CheckCnt == 0) {
						break;
					}
				}
			}	//次の列の検査（駒がなかったら終了）
			else {
				if (P_CheckCnt != 0) {
					//駒があるマスが記憶されていたら隣接するマスを記憶する
					if (gStage[j][i].flg == 1) {
						if (gStage[j][i].cnt == 1) {
							x = i;
							y = j;
							//上
							gStage[--y][++x].cnt = 1;
							x = i;
							y = j;
							//下
							gStage[++y][--x].cnt = 1;
							x = i;
							y = j;
							//左上
							gStage[y][++x].cnt = 1;
							x = i;
							//右上
							gStage[--y][x].cnt = 1;
							y = j;
							//左
							gStage[++y][x].cnt = 1;
							y = j;
							//右
							gStage[y][--x].cnt = 1;
							x = i;
							P_CheckCnt++;
							//11列検査が継続したときクリアか調べる
							if (i > 10) {
								if (gStage[y][++x].flg == 4) {
									P_CheckFlg = 1;
									break;
								}
								else {
									x = i;
								}
							}//最後まで検査して駒がなかった場合終了
							else if (j == 11 && SaveCnt == P_CheckCnt) {
								SaveCnt = P_CheckCnt;
								P_CheckCnt = 0;
								break;
							}//途中なので継続
							else {
								SaveCnt = P_CheckCnt;
							}
						}
					}
				}
			}
		}

		//クリア条件を満たしていたら終了
		if (P_CheckFlg == 1) {
			ClearFlg = 1;
			P_CheckCnt = 0;
			P_CheckFlg = 0;
			break;
		}
		
		//列に駒がなかったら終了
		if (P_CheckCnt == 0) {
			break;
		}
	}
}

void Hex::Check_E() {
	//保存用
	int i = 1;
	int j = 1;
	//変更用
	int x = 1;
	int y = 1;
	//カウント保存
	int SaveCnt = E_CheckCnt;

	for (i = 1; i < 12; i++) {
		for (j = 1; j < 12; j++) {
			//最初の列の検査
			if (i == 1) {
				//駒があったら隣接するマスを記憶する
				if (gStage[i][j].flg == 2) {
					x = i;
					y = j;
					//上
					gStage[--x][++y].cnt = 2;
					x = i;
					y = j;
					//下
					gStage[++x][--y].cnt = 2;
					x = i;
					y = j;
					//左上
					gStage[x][++y].cnt = 2;
					y = j;
					//右上
					gStage[--x][y].cnt = 2;
					x = i;
					//左
					gStage[++x][y].cnt = 2;
					x = i;
					//右
					gStage[x][--y].cnt = 2;
					y = j;
					E_CheckCnt++;
					SaveCnt = E_CheckCnt;
				}	//最初の列に駒がなかったら終了
				else if (j == 11) {
					if (E_CheckCnt == 0) {
						break;
					}
				}
			}	//次の列の検査（駒がなかったら終了）
			else {
				if (E_CheckCnt != 0) {
					//駒があるマスが記憶されていたら隣接するマスを記憶する
					if (gStage[i][j].flg == 2) {
						if (gStage[i][j].cnt == 2) {
							x = i;
							y = j;
							//上
							gStage[--x][++y].cnt = 2;
							x = i;
							y = j;
							//下
							gStage[++x][--y].cnt = 2;
							x = i;
							y = j;
							//左上o
							gStage[x][++y].cnt = 2;
							y = j;
							//右上o
							gStage[--x][y].cnt = 2;
							x = i;
							//左o
							gStage[++x][y].cnt = 2;
							x = i;
							//右o
							gStage[x][--y].cnt = 2;
							y = j;
							E_CheckCnt++;
							//11列検査が継続したときクリアか調べる
							if (i > 10) {
								if (gStage[++x][y].flg == 5) {
									E_CheckFlg = 1;
									break;
								}
								else {
									x = i;
								}
							}	//最後まで検査して駒がなかった場合終了
							else if (j == 11 && SaveCnt == E_CheckCnt) {
								SaveCnt = E_CheckCnt;
								E_CheckCnt = 0;
								break;
							}//途中なので継続
							else {
								SaveCnt = E_CheckCnt;
							}
						}
					}
				}
			}
		}

		//クリア条件を満たしていたら終了
		if (E_CheckFlg == 1) {
			ClearFlg = 2;
			E_CheckCnt = 0;
			E_CheckFlg = 0;
			break;
		}

		//列に駒がなかったら終了
		if (E_CheckCnt == 0) {
			break;
		}
	}
}

void Hex::Enemy() {

	int x = 1;
	int y = 1;
	int rand = GetRand(1);

	if (TurnFlg == 0) {
		gStage[6][6].flg = 2;
		TurnFlg++;
	}
	else if (TurnFlg == 1) {
		if (gStage[6][6].flg == 0) {
			gStage[6][6].flg = 2;
			TurnFlg++;
		}	
		else if (gStage[4][8].flg != 0) {
		gStage[4][8].flg = 2;
		TurnFlg++;
		}
	}

	if(TurnFlg > 1){
		rand = GetRand(1);
		switch (rand) {	//0:左下 1:左
		case 0:
			for (int i = 1; i < 12; i++) {
				for (int j = 1; j < 12; j++) {
					if (gStage[i][j].flg == 2) {
						x = i;
						y = j;
						rand = GetRand(1);
						switch (rand) {
						case 0:	//左下
							x = x - 2;
							--y;
							//制限
							if (x <= 0 || x > 11 || y <= 0 || y > 11) {
								break;
							}//配置
							else if (gStage[x][y].flg == 0) {
								gStage[x][y].flg = 2;
								x = i;
								y = j;
								TurnFlg++;
								break;
							}
							else {
								x = i;
								y = j;
							}
						case 1:	//左
							++x;
							++y;
							//制限
							if (x <= 0 || x > 11 || y <= 0 || y > 11) {
								break;
							}//配置
							else if(gStage[x][y].flg == 0) {
								gStage[x][y].flg = 2;
								x = i;
								y = j;
								TurnFlg++;
								break;
							}
							else {
								x = i;
								y = j;
								rand = GetRand(2);
								switch(rand){
								case 0:	//下
									if (gStage[++x][--y].flg == 0) {
										gStage[x][y].flg = 2;
										x = i;
										y = j;
										TurnFlg++;
										break;
									}
									else {
										x = i;
										y = j;
									}
								case 1:	//左下１
									if (gStage[++x][y].flg == 0) {
										gStage[x][y].flg = 2;
										x = i;
										y = j;
										TurnFlg++;
										break;
									}
									else {
										x = i;
										y = j;
									}
								case 2:	//左上１
									if (gStage[x][++y].flg == 0) {
										gStage[x][y].flg = 2;
										x = i;
										y = j;
										TurnFlg++;
										break;
									}
									else {
										x = i;
										y = j;
									}
								}
							}
						}
						////右上
						//if (gStage[++i][j - 2].flg == 0 || i <= 11 || i > 0 || j <= 11 || j > 0) {
						//	gStage[i][j].flg = 2;
						//	TurnFlg++;
						//	break;
						//}
						////右
						//else if (gStage[--i][--j].flg == 0 || i <= 11 || i > 0 || j <= 11 || j > 0) {
						//	gStage[i][j].flg = 2;
						//	TurnFlg++;
						//	break;
						//}
						//else {
						//	rand = GetRand(2);
						//	switch (rand) {
						//	case 0:
						//		if (gStage[--i][j].flg == 0) {
						//			gStage[i][j].flg = 2;
						//			TurnFlg++;
						//		}
						//		break;
						//	case 1:
						//		if (gStage[i][--j].flg == 0) {
						//			gStage[i][j].flg = 2;
						//			TurnFlg++;
						//		}
						//		break;
						//	case 2:
						//		if (gStage[++i][--j].flg == 0) {
						//			gStage[i][j].flg = 2;
						//			TurnFlg++;
						//		}
						//		break;
						//	}
						//	break;
						//}
					}
				}
				if (TurnSave != TurnFlg)break;
			}
		case 1:
			for (int i = 12; i > 1; i--) {
				for (int j = 1; j < 12; j++) {
					if (gStage[i][j].flg == 2) {
						
					}
				}
				if (TurnSave != TurnFlg)break;
			}
			break;
		}
	}
	if (TurnSave == TurnFlg) {
		for (int i = 1; i < 12; i++) {
			for (int j = 1; j < 12; j++) {
				if (gStage[j][i].flg == 0) {
					gStage[j][i].flg = 2;
					TurnFlg++;
					break;
				}
			}
			if (TurnSave != TurnFlg)break;
		}
	}
}
