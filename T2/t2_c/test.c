#include <stdio.h>
typedef struct CHESSBOARD {
    int curPlayer;
    int hole1[7];
    int hole2[7];
    int player1Score;
    int player2Score;
}ChessBoard;
ChessBoard chessBoard;
void show() {
    printf("current_player: %d\n", chessBoard.curPlayer);
    printf("score1:%d score2:%d\n", chessBoard.player1Score, chessBoard.player2Score);
    for (int i = 1; i <= 6; i++) {
        printf("%d ", chessBoard.hole2[i]);
    }
    printf("\n");
    for (int i = 1; i <= 6; i++) {
        printf("%d ", chessBoard.hole1[i]);
    }
    printf("\n");
}
//操作一次 如果违规，返回-1，成功返回0
int operate(int holeNo, int player, ChessBoard *cb) {
    if (cb->curPlayer != player) {
        return -1;
    }
    int target;
    if (player == 1) {
        int chessNum = cb->hole1[holeNo];
        cb->hole1[holeNo] = 0;
        if (chessNum == 0) {
            return -1;
        }
        for (int i = 1; i <= chessNum; i++) {
            target = (holeNo + i) % 13;
            target = (target == 0 ? 13 : target);
            if (target <= 6) {
                cb->hole1[target]++;
            } else if (target == 7) {
                cb->player1Score++;
            } else {
                cb->hole2[target - 7]++;
            }
        }
        //判断是否需要切换玩家
        if (target != 7) {
            cb->curPlayer = 2;
        } else if (target < 7 && cb->hole1[target] == 1 && cb->hole2[7 - target] > 0) {
            cb->player1Score += cb->hole1[target] + cb->hole2[7 - target];
            cb->hole1[target] = 0;
            cb->hole2[7 - target] = 0;
        }

    }
    if (player == 2) {
        int chessNum = cb->hole2[holeNo];
        cb->hole2[holeNo] = 0;
        if (chessNum == 0) {
            return -1;
        }
        for (int i = 1; i <= chessNum; i++) {
            target = (holeNo + i) % 13;
            target = (target == 0 ? 13 : target);
            if (target <= 6) {
                cb->hole2[target]++;
            } else if (target == 7) {
                cb->player2Score++;
            } else {
                cb->hole1[target - 7]++;
            }
        }
        //判断是否需要切换玩家
        if (target != 7) {
            cb->curPlayer = 1;
        } else if (target < 7 && cb->hole2[target] == 1 && cb->hole1[7 - target] > 0) {
            cb->player2Score += cb->hole2[target] + cb->hole1[7 - target];
            cb->hole2[target] = 0;
            cb->hole1[7 - target] = 0;
        }
    }
    show();
    return 0;
}

//若无人胜利，返回0，否则返回玩家编号
int checkFinished(ChessBoard *cb) {
    int hole2Sum = 0, hole1Sum = 0;
    for (int i = 1; i <= 6; i++) {
        hole1Sum += cb->hole1[i];
        hole2Sum += cb->hole2[i];
    }
    if (hole1Sum == 0) {
        cb->player1Score += hole2Sum;
    } else if (hole2Sum == 0) {
        cb->player2Score += hole1Sum;
    } else {
        return 0;
    }
    return cb->player1Score >= cb->player2Score ? 1 : 2;
}

int mancalaResult(int flag, int seq[], int size) {
    for (int i = 1; i <= 6; i++) {
        chessBoard.hole1[i] = 4;
        chessBoard.hole2[i] = 4;
    }
    chessBoard.curPlayer = flag;
    chessBoard.player1Score = 0;
    chessBoard.player2Score = 0;
    for (int i = 0; i < size; i++) {
        int player = seq[i] / 10;
        int holeNo = seq[i] % 10;
        int err = operate(holeNo, player, &chessBoard);
        if (err != 0) {
            return 30000 + i;
        }
        int winner = checkFinished(&chessBoard);
        if (winner != 0) {
            if (i != size - 1) {
                return 30000 + i;
            }
            return 15000 + (flag == 1 ? 
                chessBoard.player1Score - chessBoard.player2Score : chessBoard.player2Score - chessBoard.player1Score);
        }
    }
    return 20000 + (flag == 1 ? chessBoard.player1Score : chessBoard.player2Score);
}

int main() {
    mancalaResult(1, {13,16,26,12,16,11,22,25,13,16,15,21,16,14,25,22,16,15,24,16,14,23,15,21,16,14,24,12,26,13,16,15,16,14,16,15,25,16,11,26}, 40);
}