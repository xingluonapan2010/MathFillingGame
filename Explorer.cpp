#include"MyRes.h"
#include<string>
int sy = 0;
void GRID::PlayBasicGame() {
	if (MouseIsInIt()) {
		ChangeState(GetMouseInWhatRowNum(), GetMouseInWhatColNum());
		if (NowMouseInWhatRowNum() - 1 >= 1) {
			ChangeState(NowMouseInWhatRowNum() - 1, NowMouseInWhatColNum());
		}
		if (NowMouseInWhatRowNum() + 1 <= this->rows) {
			ChangeState(NowMouseInWhatRowNum() + 1, NowMouseInWhatColNum());
		}
		if (NowMouseInWhatColNum() - 1 >= 1) {
			ChangeState(NowMouseInWhatRowNum(), NowMouseInWhatColNum() - 1);
		}
		if (NowMouseInWhatColNum() + 1 <= this->cols) {
			ChangeState(NowMouseInWhatRowNum(), NowMouseInWhatColNum() + 1);
		}
	}
}

