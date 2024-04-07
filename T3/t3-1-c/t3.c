typedef struct CHESSBOARD {
    int hole1[7];
    int player1Score;
    int player2Score;
    int hole2[7];
    int curPlayer;
}ChessBoard;

ChessBoard chessBoard;
//操作一次 如果违规，返回-1，成功返回0
int operate(int holeNo, int player, ChessBoard *cb) {
    if (cb->curPlayer != player) {
        return -player;
    }
    int target;
    if (player == 1) {
        int chessNum = cb->hole1[holeNo];
        cb->hole1[holeNo] = 0;
        if (chessNum == 0) {
            return -player;
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
        }
        if (target < 7 && cb->hole1[target] == 1 && cb->hole2[7 - target] > 0) {
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
        }
        if (target < 7 && cb->hole2[target] == 1 && cb->hole1[7 - target] > 0) {
            cb->player2Score += cb->hole2[target] + cb->hole1[7 - target];
            cb->hole2[target] = 0;
            cb->hole1[7 - target] = 0;
        }
    }
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
        cb->player2Score += hole2Sum;
        for (int i = 1; i <= 6; i++) {
            cb->hole2[i] = 0;
        }
    } else if (hole2Sum == 0) {
        cb->player1Score += hole1Sum;
        for (int i = 1; i <= 6; i++) {
            cb->hole1[i] = 0;
        }
    } else {
        return 0;
    }
    return cb->player1Score >= cb->player2Score ? 1 : 2;
}

void forcedFinish(int player, ChessBoard *cb) {
    for (int i = 1; i <= 6; i++) {
        cb->hole1[i] = 0;
        cb->hole2[i] = 0;
    }
    if (player == 1) {
        cb->player2Score = 48 - cb->player1Score;
    } else {
        cb->player1Score = 48 - cb->player2Score;
    }
}

int mancalaBoard(int flag, int seq[], int size) {
    for (int i = 1; i <= 6; i++) {
        chessBoard.hole1[i] = 4;
        chessBoard.hole2[i] = 4;
    }
    chessBoard.curPlayer = seq[0] / 10;
    chessBoard.player1Score = 0;
    chessBoard.player2Score = 0;
    int illegal = 0;
    for (int i = 0; i < size; i++) {
        int player = seq[i] / 10;
        int holeNo = seq[i] % 10;
        int err = operate(holeNo, player, &chessBoard);
        if (err != 0) {
            forcedFinish(err, &chessBoard);
            illegal = 1;
            break;
        }
        int winner = checkFinished(&chessBoard);
        if (winner != 0) {
            break;
        }
    }
    for (int i = 0; i <= 5; i++) {
        seq[i] = chessBoard.hole1[i + 1];
    }
    seq[6] = chessBoard.player1Score;
    for (int i = 7; i <= 12; i++) {
        seq[i] = chessBoard.hole2[i - 6];
    }
    seq[13] = chessBoard.player2Score;
    if (!illegal) {
        if (chessBoard.player1Score + chessBoard.player2Score == 48) {
            seq[14] = 200 + chessBoard.player1Score - chessBoard.player2Score;
        } else {
            seq[14] = chessBoard.curPlayer;
        }
    } else {
        if (flag == 1) {
            seq[14] = 200 + 2 * chessBoard.player1Score - 48;
        } else {
            seq[14] = 200 - 2 * chessBoard.player2Score + 48;
        }
    }
    return 0;
} 