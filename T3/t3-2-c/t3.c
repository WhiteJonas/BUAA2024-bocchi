typedef struct CHESSBOARD {
    int hole1[7];
    int player1Score;
    int player2Score;
    int hole2[7];
    int curPlayer;
}ChessBoard;

void copy(ChessBoard *dst, ChessBoard *src) {
    for (int i = 0; i <= 6; i++) {
        dst->hole1[i] = src->hole1[i];
        dst->hole2[i] = src->hole2[i];
    }
    dst->player1Score = src->player1Score;
    dst->player2Score = src->player2Score;
    dst->curPlayer = src->curPlayer;
}
ChessBoard chessBoard;
/*
    ret < 0 操作异常
    ret = 0 换下一个操作，无得分
    ret = 1 换下一个操作，有得分
    ret = 2 获得额外操作机会
    ret = 3 顺走对面的球
*/
int operate(int holeNo, ChessBoard *cb) {
    int player = cb->curPlayer;
    int ret = 0;
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
                ret = 1;
            } else {
                cb->hole2[target - 7]++;
            }
        }
        //??????????
        if (target != 7) {
            cb->curPlayer = 2;
        } else {
            ret = 2;
        }
        if (target < 7 && cb->hole1[target] == 1 && cb->hole2[7 - target] > 0) {
            cb->player1Score += cb->hole1[target] + cb->hole2[7 - target];
            cb->hole1[target] = 0;
            cb->hole2[7 - target] = 0;
            ret = 3;
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
                ret = 1;
            } else {
                cb->hole1[target - 7]++;
            }
        }
        //??????????
        if (target != 7) {
            cb->curPlayer = 1;
        } else {
            ret = 2;
        }
        if (target < 7 && cb->hole2[target] == 1 && cb->hole1[7 - target] > 0) {
            cb->player2Score += cb->hole2[target] + cb->hole1[7 - target];
            cb->hole2[target] = 0;
            cb->hole1[7 - target] = 0;
            ret = 3;
        }
    }
    return ret;
}

int monitor(int holeNo, ChessBoard *cb) {
    ChessBoard newCb, newnewCb;
    int player = cb->curPlayer;
    copy(&newCb, cb);
    int result = operate(holeNo, &newCb);
    if (result < 0 ) {
        return -1;
    }
    int rank = result * 5 + 100;
    //如果交给对手，判断是否可能让对方连吃
    if (newCb.curPlayer != player) {
        for (int i = 1; i <= 6; i++) {
            copy(&newnewCb, &newCb);
            if (operate(i, &newnewCb) == 2) {
                rank -= 5;
            }
        }
    }
    //最好让最右侧清空
    if (player == 1 && newCb.hole1[6] == 0 || player == 2 && newCb.hole2[6] == 0) {
        rank += 3;
    }
    return rank;
}
//?????,??0,????????
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


int getWonScore(int player, ChessBoard *cb) {
    if (player == 1) {
        return cb->player1Score - cb->player2Score;
    } else {
        return -cb->player1Score + cb->player2Score;
    }
}

int mancalaOperator(int flag, int seq[]) {
    for (int i = 1; i <= 6; i++) {
        chessBoard.hole1[i] = seq[i-1];
        chessBoard.hole2[i] = seq[i+6];
    }
    chessBoard.curPlayer = flag;
    chessBoard.player1Score = seq[6];
    chessBoard.player2Score = seq[13];
    ChessBoard *cb = &chessBoard;

    int bestStep, maxRank = -1;
    for (int i = 1; i <= 6; i++) {
        int rank = monitor(i, cb);
        if (rank > 0 && rank > maxRank) {
            maxRank = rank;
            bestStep = i;
        }
    }

    return bestStep + flag * 10;;
} 

