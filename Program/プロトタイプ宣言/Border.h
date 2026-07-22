#pragma once
#include<stdio.h>
#include"Border.h"

//プロトタイプ宣言
//こういう関数があるんですよ、というのをコンパイラに教えておく
//中身は後で詳しく説明するので、
// こんな関数が見つかったらいったんコンパイルは通して

//文法
//戻り値の型　関数名（引数）;

void DrawBorder(void);
void DrawMultiBorder(int count);
