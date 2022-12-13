inline CheckerBoard *
redmanmove(int c, CheckerBoard *b, CheckerBoard *m)
{
    switch (c) {
    case 0:
	if (UNOCC(4)) MOVEMAN(R, 0, 4)
	if (UNOCC(5)) MOVEMAN(R, 0, 5)
	break ;
    case 1:
	if (UNOCC(5)) MOVEMAN(R, 1, 5)
	if (UNOCC(6)) MOVEMAN(R, 1, 6)
	break ;
    case 2:
	if (UNOCC(6)) MOVEMAN(R, 2, 6)
	if (UNOCC(7)) MOVEMAN(R, 2, 7)
	break ;
    case 3:
	if (UNOCC(7)) MOVEMAN(R, 3, 7)
	break ;
    case 4:
	if (UNOCC(8)) MOVEMAN(R, 4, 8)
	break ;
    case 5:
	if (UNOCC(8)) MOVEMAN(R, 5, 8)
	if (UNOCC(9)) MOVEMAN(R, 5, 9)
	break ;
    case 6:
	if (UNOCC(9)) MOVEMAN(R, 6, 9)
	if (UNOCC(10)) MOVEMAN(R, 6, 10)
	break ;
    case 7:
	if (UNOCC(10)) MOVEMAN(R, 7, 10)
	if (UNOCC(11)) MOVEMAN(R, 7, 11)
	break ;
    case 8:
	if (UNOCC(12)) MOVEMAN(R, 8, 12)
	if (UNOCC(13)) MOVEMAN(R, 8, 13)
	break ;
    case 9:
	if (UNOCC(13)) MOVEMAN(R, 9, 13)
	if (UNOCC(14)) MOVEMAN(R, 9, 14)
	break ;
    case 10:
	if (UNOCC(14)) MOVEMAN(R, 10, 14)
	if (UNOCC(15)) MOVEMAN(R, 10, 15)
	break ;
    case 11:
	if (UNOCC(15)) MOVEMAN(R, 11, 15)
	break ;
    case 12:
	if (UNOCC(16)) MOVEMAN(R, 12, 16)
	break ;
    case 13:
	if (UNOCC(16)) MOVEMAN(R, 13, 16)
	if (UNOCC(17)) MOVEMAN(R, 13, 17)
	break ;
    case 14:
	if (UNOCC(17)) MOVEMAN(R, 14, 17)
	if (UNOCC(18)) MOVEMAN(R, 14, 18)
	break ;
    case 15:
	if (UNOCC(18)) MOVEMAN(R, 15, 18)
	if (UNOCC(19)) MOVEMAN(R, 15, 19)
	break ;
    case 16:
	if (UNOCC(20)) MOVEMAN(R, 16, 20)
	if (UNOCC(21)) MOVEMAN(R, 16, 21)
	break ;
    case 17:
	if (UNOCC(21)) MOVEMAN(R, 17, 21)
	if (UNOCC(22)) MOVEMAN(R, 17, 22)
	break ;
    case 18:
	if (UNOCC(22)) MOVEMAN(R, 18, 22)
	if (UNOCC(23)) MOVEMAN(R, 18, 23)
	break ;
    case 19:
	if (UNOCC(23)) MOVEMAN(R, 19, 23)
	break ;
    case 20:
	if (UNOCC(24)) MOVEMAN(R, 20, 24)
	break ;
    case 21:
	if (UNOCC(24)) MOVEMAN(R, 21, 24)
	if (UNOCC(25)) MOVEMAN(R, 21, 25)
	break ;
    case 22:
	if (UNOCC(25)) MOVEMAN(R, 22, 25)
	if (UNOCC(26)) MOVEMAN(R, 22, 26)
	break ;
    case 23:
	if (UNOCC(26)) MOVEMAN(R, 23, 26)
	if (UNOCC(27)) MOVEMAN(R, 23, 27)
	break ;
    case 24:
	if (UNOCC(28)) KINGMAN(R, 24, 28)
	if (UNOCC(29)) KINGMAN(R, 24, 29)
	break ;
    case 25:
	if (UNOCC(29)) KINGMAN(R, 25, 29)
	if (UNOCC(30)) KINGMAN(R, 25, 30)
	break ;
    case 26:
	if (UNOCC(30)) KINGMAN(R, 26, 30)
	if (UNOCC(31)) KINGMAN(R, 26, 31)
	break ;
    case 27:
	if (UNOCC(31)) KINGMAN(R, 27, 31)
	break ;
    case 28:
	break ;
    case 29:
	break ;
    case 30:
	break ;
    case 31:
	break ;
    }
    return m ;
}
inline CheckerBoard *
whitemanmove(int c, CheckerBoard *b, CheckerBoard *m)
{
    switch (c) {
    case 0:
	break ;
    case 1:
	break ;
    case 2:
	break ;
    case 3:
	break ;
    case 4:
	if (UNOCC(0)) KINGMAN(W, 4, 0)
	break ;
    case 5:
	if (UNOCC(0)) KINGMAN(W, 5, 0)
	if (UNOCC(1)) KINGMAN(W, 5, 1)
	break ;
    case 6:
	if (UNOCC(1)) KINGMAN(W, 6, 1)
	if (UNOCC(2)) KINGMAN(W, 6, 2)
	break ;
    case 7:
	if (UNOCC(2)) KINGMAN(W, 7, 2)
	if (UNOCC(3)) KINGMAN(W, 7, 3)
	break ;
    case 8:
	if (UNOCC(4)) MOVEMAN(W, 8, 4)
	if (UNOCC(5)) MOVEMAN(W, 8, 5)
	break ;
    case 9:
	if (UNOCC(5)) MOVEMAN(W, 9, 5)
	if (UNOCC(6)) MOVEMAN(W, 9, 6)
	break ;
    case 10:
	if (UNOCC(6)) MOVEMAN(W, 10, 6)
	if (UNOCC(7)) MOVEMAN(W, 10, 7)
	break ;
    case 11:
	if (UNOCC(7)) MOVEMAN(W, 11, 7)
	break ;
    case 12:
	if (UNOCC(8)) MOVEMAN(W, 12, 8)
	break ;
    case 13:
	if (UNOCC(8)) MOVEMAN(W, 13, 8)
	if (UNOCC(9)) MOVEMAN(W, 13, 9)
	break ;
    case 14:
	if (UNOCC(9)) MOVEMAN(W, 14, 9)
	if (UNOCC(10)) MOVEMAN(W, 14, 10)
	break ;
    case 15:
	if (UNOCC(10)) MOVEMAN(W, 15, 10)
	if (UNOCC(11)) MOVEMAN(W, 15, 11)
	break ;
    case 16:
	if (UNOCC(12)) MOVEMAN(W, 16, 12)
	if (UNOCC(13)) MOVEMAN(W, 16, 13)
	break ;
    case 17:
	if (UNOCC(13)) MOVEMAN(W, 17, 13)
	if (UNOCC(14)) MOVEMAN(W, 17, 14)
	break ;
    case 18:
	if (UNOCC(14)) MOVEMAN(W, 18, 14)
	if (UNOCC(15)) MOVEMAN(W, 18, 15)
	break ;
    case 19:
	if (UNOCC(15)) MOVEMAN(W, 19, 15)
	break ;
    case 20:
	if (UNOCC(16)) MOVEMAN(W, 20, 16)
	break ;
    case 21:
	if (UNOCC(16)) MOVEMAN(W, 21, 16)
	if (UNOCC(17)) MOVEMAN(W, 21, 17)
	break ;
    case 22:
	if (UNOCC(17)) MOVEMAN(W, 22, 17)
	if (UNOCC(18)) MOVEMAN(W, 22, 18)
	break ;
    case 23:
	if (UNOCC(18)) MOVEMAN(W, 23, 18)
	if (UNOCC(19)) MOVEMAN(W, 23, 19)
	break ;
    case 24:
	if (UNOCC(20)) MOVEMAN(W, 24, 20)
	if (UNOCC(21)) MOVEMAN(W, 24, 21)
	break ;
    case 25:
	if (UNOCC(21)) MOVEMAN(W, 25, 21)
	if (UNOCC(22)) MOVEMAN(W, 25, 22)
	break ;
    case 26:
	if (UNOCC(22)) MOVEMAN(W, 26, 22)
	if (UNOCC(23)) MOVEMAN(W, 26, 23)
	break ;
    case 27:
	if (UNOCC(23)) MOVEMAN(W, 27, 23)
	break ;
    case 28:
	if (UNOCC(24)) MOVEMAN(W, 28, 24)
	break ;
    case 29:
	if (UNOCC(24)) MOVEMAN(W, 29, 24)
	if (UNOCC(25)) MOVEMAN(W, 29, 25)
	break ;
    case 30:
	if (UNOCC(25)) MOVEMAN(W, 30, 25)
	if (UNOCC(26)) MOVEMAN(W, 30, 26)
	break ;
    case 31:
	if (UNOCC(26)) MOVEMAN(W, 31, 26)
	if (UNOCC(27)) MOVEMAN(W, 31, 27)
	break ;
    }
    return m ;
}
inline CheckerBoard *
redkingmove(int c, CheckerBoard *b, CheckerBoard *m)
{
    switch (c) {
    case 0:
	if (UNOCC(4)) MOVEKING(R, 0, 4)
	if (UNOCC(5)) MOVEKING(R, 0, 5)
	break ;
    case 1:
	if (UNOCC(5)) MOVEKING(R, 1, 5)
	if (UNOCC(6)) MOVEKING(R, 1, 6)
	break ;
    case 2:
	if (UNOCC(6)) MOVEKING(R, 2, 6)
	if (UNOCC(7)) MOVEKING(R, 2, 7)
	break ;
    case 3:
	if (UNOCC(7)) MOVEKING(R, 3, 7)
	break ;
    case 4:
	if (UNOCC(0)) MOVEKING(R, 4, 0)
	if (UNOCC(8)) MOVEKING(R, 4, 8)
	break ;
    case 5:
	if (UNOCC(0)) MOVEKING(R, 5, 0)
	if (UNOCC(1)) MOVEKING(R, 5, 1)
	if (UNOCC(8)) MOVEKING(R, 5, 8)
	if (UNOCC(9)) MOVEKING(R, 5, 9)
	break ;
    case 6:
	if (UNOCC(1)) MOVEKING(R, 6, 1)
	if (UNOCC(2)) MOVEKING(R, 6, 2)
	if (UNOCC(9)) MOVEKING(R, 6, 9)
	if (UNOCC(10)) MOVEKING(R, 6, 10)
	break ;
    case 7:
	if (UNOCC(2)) MOVEKING(R, 7, 2)
	if (UNOCC(3)) MOVEKING(R, 7, 3)
	if (UNOCC(10)) MOVEKING(R, 7, 10)
	if (UNOCC(11)) MOVEKING(R, 7, 11)
	break ;
    case 8:
	if (UNOCC(4)) MOVEKING(R, 8, 4)
	if (UNOCC(5)) MOVEKING(R, 8, 5)
	if (UNOCC(12)) MOVEKING(R, 8, 12)
	if (UNOCC(13)) MOVEKING(R, 8, 13)
	break ;
    case 9:
	if (UNOCC(5)) MOVEKING(R, 9, 5)
	if (UNOCC(6)) MOVEKING(R, 9, 6)
	if (UNOCC(13)) MOVEKING(R, 9, 13)
	if (UNOCC(14)) MOVEKING(R, 9, 14)
	break ;
    case 10:
	if (UNOCC(6)) MOVEKING(R, 10, 6)
	if (UNOCC(7)) MOVEKING(R, 10, 7)
	if (UNOCC(14)) MOVEKING(R, 10, 14)
	if (UNOCC(15)) MOVEKING(R, 10, 15)
	break ;
    case 11:
	if (UNOCC(7)) MOVEKING(R, 11, 7)
	if (UNOCC(15)) MOVEKING(R, 11, 15)
	break ;
    case 12:
	if (UNOCC(8)) MOVEKING(R, 12, 8)
	if (UNOCC(16)) MOVEKING(R, 12, 16)
	break ;
    case 13:
	if (UNOCC(8)) MOVEKING(R, 13, 8)
	if (UNOCC(9)) MOVEKING(R, 13, 9)
	if (UNOCC(16)) MOVEKING(R, 13, 16)
	if (UNOCC(17)) MOVEKING(R, 13, 17)
	break ;
    case 14:
	if (UNOCC(9)) MOVEKING(R, 14, 9)
	if (UNOCC(10)) MOVEKING(R, 14, 10)
	if (UNOCC(17)) MOVEKING(R, 14, 17)
	if (UNOCC(18)) MOVEKING(R, 14, 18)
	break ;
    case 15:
	if (UNOCC(10)) MOVEKING(R, 15, 10)
	if (UNOCC(11)) MOVEKING(R, 15, 11)
	if (UNOCC(18)) MOVEKING(R, 15, 18)
	if (UNOCC(19)) MOVEKING(R, 15, 19)
	break ;
    case 16:
	if (UNOCC(12)) MOVEKING(R, 16, 12)
	if (UNOCC(13)) MOVEKING(R, 16, 13)
	if (UNOCC(20)) MOVEKING(R, 16, 20)
	if (UNOCC(21)) MOVEKING(R, 16, 21)
	break ;
    case 17:
	if (UNOCC(13)) MOVEKING(R, 17, 13)
	if (UNOCC(14)) MOVEKING(R, 17, 14)
	if (UNOCC(21)) MOVEKING(R, 17, 21)
	if (UNOCC(22)) MOVEKING(R, 17, 22)
	break ;
    case 18:
	if (UNOCC(14)) MOVEKING(R, 18, 14)
	if (UNOCC(15)) MOVEKING(R, 18, 15)
	if (UNOCC(22)) MOVEKING(R, 18, 22)
	if (UNOCC(23)) MOVEKING(R, 18, 23)
	break ;
    case 19:
	if (UNOCC(15)) MOVEKING(R, 19, 15)
	if (UNOCC(23)) MOVEKING(R, 19, 23)
	break ;
    case 20:
	if (UNOCC(16)) MOVEKING(R, 20, 16)
	if (UNOCC(24)) MOVEKING(R, 20, 24)
	break ;
    case 21:
	if (UNOCC(16)) MOVEKING(R, 21, 16)
	if (UNOCC(17)) MOVEKING(R, 21, 17)
	if (UNOCC(24)) MOVEKING(R, 21, 24)
	if (UNOCC(25)) MOVEKING(R, 21, 25)
	break ;
    case 22:
	if (UNOCC(17)) MOVEKING(R, 22, 17)
	if (UNOCC(18)) MOVEKING(R, 22, 18)
	if (UNOCC(25)) MOVEKING(R, 22, 25)
	if (UNOCC(26)) MOVEKING(R, 22, 26)
	break ;
    case 23:
	if (UNOCC(18)) MOVEKING(R, 23, 18)
	if (UNOCC(19)) MOVEKING(R, 23, 19)
	if (UNOCC(26)) MOVEKING(R, 23, 26)
	if (UNOCC(27)) MOVEKING(R, 23, 27)
	break ;
    case 24:
	if (UNOCC(20)) MOVEKING(R, 24, 20)
	if (UNOCC(21)) MOVEKING(R, 24, 21)
	if (UNOCC(28)) MOVEKING(R, 24, 28)
	if (UNOCC(29)) MOVEKING(R, 24, 29)
	break ;
    case 25:
	if (UNOCC(21)) MOVEKING(R, 25, 21)
	if (UNOCC(22)) MOVEKING(R, 25, 22)
	if (UNOCC(29)) MOVEKING(R, 25, 29)
	if (UNOCC(30)) MOVEKING(R, 25, 30)
	break ;
    case 26:
	if (UNOCC(22)) MOVEKING(R, 26, 22)
	if (UNOCC(23)) MOVEKING(R, 26, 23)
	if (UNOCC(30)) MOVEKING(R, 26, 30)
	if (UNOCC(31)) MOVEKING(R, 26, 31)
	break ;
    case 27:
	if (UNOCC(23)) MOVEKING(R, 27, 23)
	if (UNOCC(31)) MOVEKING(R, 27, 31)
	break ;
    case 28:
	if (UNOCC(24)) MOVEKING(R, 28, 24)
	break ;
    case 29:
	if (UNOCC(24)) MOVEKING(R, 29, 24)
	if (UNOCC(25)) MOVEKING(R, 29, 25)
	break ;
    case 30:
	if (UNOCC(25)) MOVEKING(R, 30, 25)
	if (UNOCC(26)) MOVEKING(R, 30, 26)
	break ;
    case 31:
	if (UNOCC(26)) MOVEKING(R, 31, 26)
	if (UNOCC(27)) MOVEKING(R, 31, 27)
	break ;
    }
    return m ;
}
inline CheckerBoard *
whitekingmove(int c, CheckerBoard *b, CheckerBoard *m)
{
    switch (c) {
    case 0:
	if (UNOCC(4)) MOVEKING(W, 0, 4)
	if (UNOCC(5)) MOVEKING(W, 0, 5)
	break ;
    case 1:
	if (UNOCC(5)) MOVEKING(W, 1, 5)
	if (UNOCC(6)) MOVEKING(W, 1, 6)
	break ;
    case 2:
	if (UNOCC(6)) MOVEKING(W, 2, 6)
	if (UNOCC(7)) MOVEKING(W, 2, 7)
	break ;
    case 3:
	if (UNOCC(7)) MOVEKING(W, 3, 7)
	break ;
    case 4:
	if (UNOCC(0)) MOVEKING(W, 4, 0)
	if (UNOCC(8)) MOVEKING(W, 4, 8)
	break ;
    case 5:
	if (UNOCC(0)) MOVEKING(W, 5, 0)
	if (UNOCC(1)) MOVEKING(W, 5, 1)
	if (UNOCC(8)) MOVEKING(W, 5, 8)
	if (UNOCC(9)) MOVEKING(W, 5, 9)
	break ;
    case 6:
	if (UNOCC(1)) MOVEKING(W, 6, 1)
	if (UNOCC(2)) MOVEKING(W, 6, 2)
	if (UNOCC(9)) MOVEKING(W, 6, 9)
	if (UNOCC(10)) MOVEKING(W, 6, 10)
	break ;
    case 7:
	if (UNOCC(2)) MOVEKING(W, 7, 2)
	if (UNOCC(3)) MOVEKING(W, 7, 3)
	if (UNOCC(10)) MOVEKING(W, 7, 10)
	if (UNOCC(11)) MOVEKING(W, 7, 11)
	break ;
    case 8:
	if (UNOCC(4)) MOVEKING(W, 8, 4)
	if (UNOCC(5)) MOVEKING(W, 8, 5)
	if (UNOCC(12)) MOVEKING(W, 8, 12)
	if (UNOCC(13)) MOVEKING(W, 8, 13)
	break ;
    case 9:
	if (UNOCC(5)) MOVEKING(W, 9, 5)
	if (UNOCC(6)) MOVEKING(W, 9, 6)
	if (UNOCC(13)) MOVEKING(W, 9, 13)
	if (UNOCC(14)) MOVEKING(W, 9, 14)
	break ;
    case 10:
	if (UNOCC(6)) MOVEKING(W, 10, 6)
	if (UNOCC(7)) MOVEKING(W, 10, 7)
	if (UNOCC(14)) MOVEKING(W, 10, 14)
	if (UNOCC(15)) MOVEKING(W, 10, 15)
	break ;
    case 11:
	if (UNOCC(7)) MOVEKING(W, 11, 7)
	if (UNOCC(15)) MOVEKING(W, 11, 15)
	break ;
    case 12:
	if (UNOCC(8)) MOVEKING(W, 12, 8)
	if (UNOCC(16)) MOVEKING(W, 12, 16)
	break ;
    case 13:
	if (UNOCC(8)) MOVEKING(W, 13, 8)
	if (UNOCC(9)) MOVEKING(W, 13, 9)
	if (UNOCC(16)) MOVEKING(W, 13, 16)
	if (UNOCC(17)) MOVEKING(W, 13, 17)
	break ;
    case 14:
	if (UNOCC(9)) MOVEKING(W, 14, 9)
	if (UNOCC(10)) MOVEKING(W, 14, 10)
	if (UNOCC(17)) MOVEKING(W, 14, 17)
	if (UNOCC(18)) MOVEKING(W, 14, 18)
	break ;
    case 15:
	if (UNOCC(10)) MOVEKING(W, 15, 10)
	if (UNOCC(11)) MOVEKING(W, 15, 11)
	if (UNOCC(18)) MOVEKING(W, 15, 18)
	if (UNOCC(19)) MOVEKING(W, 15, 19)
	break ;
    case 16:
	if (UNOCC(12)) MOVEKING(W, 16, 12)
	if (UNOCC(13)) MOVEKING(W, 16, 13)
	if (UNOCC(20)) MOVEKING(W, 16, 20)
	if (UNOCC(21)) MOVEKING(W, 16, 21)
	break ;
    case 17:
	if (UNOCC(13)) MOVEKING(W, 17, 13)
	if (UNOCC(14)) MOVEKING(W, 17, 14)
	if (UNOCC(21)) MOVEKING(W, 17, 21)
	if (UNOCC(22)) MOVEKING(W, 17, 22)
	break ;
    case 18:
	if (UNOCC(14)) MOVEKING(W, 18, 14)
	if (UNOCC(15)) MOVEKING(W, 18, 15)
	if (UNOCC(22)) MOVEKING(W, 18, 22)
	if (UNOCC(23)) MOVEKING(W, 18, 23)
	break ;
    case 19:
	if (UNOCC(15)) MOVEKING(W, 19, 15)
	if (UNOCC(23)) MOVEKING(W, 19, 23)
	break ;
    case 20:
	if (UNOCC(16)) MOVEKING(W, 20, 16)
	if (UNOCC(24)) MOVEKING(W, 20, 24)
	break ;
    case 21:
	if (UNOCC(16)) MOVEKING(W, 21, 16)
	if (UNOCC(17)) MOVEKING(W, 21, 17)
	if (UNOCC(24)) MOVEKING(W, 21, 24)
	if (UNOCC(25)) MOVEKING(W, 21, 25)
	break ;
    case 22:
	if (UNOCC(17)) MOVEKING(W, 22, 17)
	if (UNOCC(18)) MOVEKING(W, 22, 18)
	if (UNOCC(25)) MOVEKING(W, 22, 25)
	if (UNOCC(26)) MOVEKING(W, 22, 26)
	break ;
    case 23:
	if (UNOCC(18)) MOVEKING(W, 23, 18)
	if (UNOCC(19)) MOVEKING(W, 23, 19)
	if (UNOCC(26)) MOVEKING(W, 23, 26)
	if (UNOCC(27)) MOVEKING(W, 23, 27)
	break ;
    case 24:
	if (UNOCC(20)) MOVEKING(W, 24, 20)
	if (UNOCC(21)) MOVEKING(W, 24, 21)
	if (UNOCC(28)) MOVEKING(W, 24, 28)
	if (UNOCC(29)) MOVEKING(W, 24, 29)
	break ;
    case 25:
	if (UNOCC(21)) MOVEKING(W, 25, 21)
	if (UNOCC(22)) MOVEKING(W, 25, 22)
	if (UNOCC(29)) MOVEKING(W, 25, 29)
	if (UNOCC(30)) MOVEKING(W, 25, 30)
	break ;
    case 26:
	if (UNOCC(22)) MOVEKING(W, 26, 22)
	if (UNOCC(23)) MOVEKING(W, 26, 23)
	if (UNOCC(30)) MOVEKING(W, 26, 30)
	if (UNOCC(31)) MOVEKING(W, 26, 31)
	break ;
    case 27:
	if (UNOCC(23)) MOVEKING(W, 27, 23)
	if (UNOCC(31)) MOVEKING(W, 27, 31)
	break ;
    case 28:
	if (UNOCC(24)) MOVEKING(W, 28, 24)
	break ;
    case 29:
	if (UNOCC(24)) MOVEKING(W, 29, 24)
	if (UNOCC(25)) MOVEKING(W, 29, 25)
	break ;
    case 30:
	if (UNOCC(25)) MOVEKING(W, 30, 25)
	if (UNOCC(26)) MOVEKING(W, 30, 26)
	break ;
    case 31:
	if (UNOCC(26)) MOVEKING(W, 31, 26)
	if (UNOCC(27)) MOVEKING(W, 31, 27)
	break ;
    }
    return m ;
}
inline CheckerBoard *
redmanresolve(int c, CheckerBoard *b, CheckerBoard *m)
{
    CheckerBoard tmp ;
    CheckerBoard *n = m ; /* remember old value */
    switch (c) {
    case 0:
	if (UNOCC(9) && OCC(W, 5)) JUMPMAN(red, R, W, 0, 5, 9)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 1:
	if (UNOCC(8) && OCC(W, 5)) JUMPMAN(red, R, W, 1, 5, 8)
	if (UNOCC(10) && OCC(W, 6)) JUMPMAN(red, R, W, 1, 6, 10)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 2:
	if (UNOCC(9) && OCC(W, 6)) JUMPMAN(red, R, W, 2, 6, 9)
	if (UNOCC(11) && OCC(W, 7)) JUMPMAN(red, R, W, 2, 7, 11)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 3:
	if (UNOCC(10) && OCC(W, 7)) JUMPMAN(red, R, W, 3, 7, 10)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 4:
	if (UNOCC(13) && OCC(W, 8)) JUMPMAN(red, R, W, 4, 8, 13)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 5:
	if (UNOCC(12) && OCC(W, 8)) JUMPMAN(red, R, W, 5, 8, 12)
	if (UNOCC(14) && OCC(W, 9)) JUMPMAN(red, R, W, 5, 9, 14)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 6:
	if (UNOCC(13) && OCC(W, 9)) JUMPMAN(red, R, W, 6, 9, 13)
	if (UNOCC(15) && OCC(W, 10)) JUMPMAN(red, R, W, 6, 10, 15)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 7:
	if (UNOCC(14) && OCC(W, 10)) JUMPMAN(red, R, W, 7, 10, 14)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 8:
	if (UNOCC(17) && OCC(W, 13)) JUMPMAN(red, R, W, 8, 13, 17)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 9:
	if (UNOCC(16) && OCC(W, 13)) JUMPMAN(red, R, W, 9, 13, 16)
	if (UNOCC(18) && OCC(W, 14)) JUMPMAN(red, R, W, 9, 14, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 10:
	if (UNOCC(17) && OCC(W, 14)) JUMPMAN(red, R, W, 10, 14, 17)
	if (UNOCC(19) && OCC(W, 15)) JUMPMAN(red, R, W, 10, 15, 19)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 11:
	if (UNOCC(18) && OCC(W, 15)) JUMPMAN(red, R, W, 11, 15, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 12:
	if (UNOCC(21) && OCC(W, 16)) JUMPMAN(red, R, W, 12, 16, 21)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 13:
	if (UNOCC(20) && OCC(W, 16)) JUMPMAN(red, R, W, 13, 16, 20)
	if (UNOCC(22) && OCC(W, 17)) JUMPMAN(red, R, W, 13, 17, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 14:
	if (UNOCC(21) && OCC(W, 17)) JUMPMAN(red, R, W, 14, 17, 21)
	if (UNOCC(23) && OCC(W, 18)) JUMPMAN(red, R, W, 14, 18, 23)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 15:
	if (UNOCC(22) && OCC(W, 18)) JUMPMAN(red, R, W, 15, 18, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 16:
	if (UNOCC(25) && OCC(W, 21)) JUMPMAN(red, R, W, 16, 21, 25)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 17:
	if (UNOCC(24) && OCC(W, 21)) JUMPMAN(red, R, W, 17, 21, 24)
	if (UNOCC(26) && OCC(W, 22)) JUMPMAN(red, R, W, 17, 22, 26)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 18:
	if (UNOCC(25) && OCC(W, 22)) JUMPMAN(red, R, W, 18, 22, 25)
	if (UNOCC(27) && OCC(W, 23)) JUMPMAN(red, R, W, 18, 23, 27)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 19:
	if (UNOCC(26) && OCC(W, 23)) JUMPMAN(red, R, W, 19, 23, 26)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 20:
	if (UNOCC(29) && OCC(W, 24)) FINISHMAN(red, R, W, 20, 24, 29)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 21:
	if (UNOCC(28) && OCC(W, 24)) FINISHMAN(red, R, W, 21, 24, 28)
	if (UNOCC(30) && OCC(W, 25)) FINISHMAN(red, R, W, 21, 25, 30)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 22:
	if (UNOCC(29) && OCC(W, 25)) FINISHMAN(red, R, W, 22, 25, 29)
	if (UNOCC(31) && OCC(W, 26)) FINISHMAN(red, R, W, 22, 26, 31)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 23:
	if (UNOCC(30) && OCC(W, 26)) FINISHMAN(red, R, W, 23, 26, 30)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 24:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 25:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 26:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 27:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 28:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 29:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 30:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 31:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    }
    return m ;
}
inline CheckerBoard *
redmanjump(int c, CheckerBoard *b, CheckerBoard *m)
{
    CheckerBoard tmp ;
    switch (c) {
    case 0:
	if (UNOCC(9) && OCC(W, 5)) JUMPMAN(red, R, W, 0, 5, 9)
	break ;
    case 1:
	if (UNOCC(8) && OCC(W, 5)) JUMPMAN(red, R, W, 1, 5, 8)
	if (UNOCC(10) && OCC(W, 6)) JUMPMAN(red, R, W, 1, 6, 10)
	break ;
    case 2:
	if (UNOCC(9) && OCC(W, 6)) JUMPMAN(red, R, W, 2, 6, 9)
	if (UNOCC(11) && OCC(W, 7)) JUMPMAN(red, R, W, 2, 7, 11)
	break ;
    case 3:
	if (UNOCC(10) && OCC(W, 7)) JUMPMAN(red, R, W, 3, 7, 10)
	break ;
    case 4:
	if (UNOCC(13) && OCC(W, 8)) JUMPMAN(red, R, W, 4, 8, 13)
	break ;
    case 5:
	if (UNOCC(12) && OCC(W, 8)) JUMPMAN(red, R, W, 5, 8, 12)
	if (UNOCC(14) && OCC(W, 9)) JUMPMAN(red, R, W, 5, 9, 14)
	break ;
    case 6:
	if (UNOCC(13) && OCC(W, 9)) JUMPMAN(red, R, W, 6, 9, 13)
	if (UNOCC(15) && OCC(W, 10)) JUMPMAN(red, R, W, 6, 10, 15)
	break ;
    case 7:
	if (UNOCC(14) && OCC(W, 10)) JUMPMAN(red, R, W, 7, 10, 14)
	break ;
    case 8:
	if (UNOCC(17) && OCC(W, 13)) JUMPMAN(red, R, W, 8, 13, 17)
	break ;
    case 9:
	if (UNOCC(16) && OCC(W, 13)) JUMPMAN(red, R, W, 9, 13, 16)
	if (UNOCC(18) && OCC(W, 14)) JUMPMAN(red, R, W, 9, 14, 18)
	break ;
    case 10:
	if (UNOCC(17) && OCC(W, 14)) JUMPMAN(red, R, W, 10, 14, 17)
	if (UNOCC(19) && OCC(W, 15)) JUMPMAN(red, R, W, 10, 15, 19)
	break ;
    case 11:
	if (UNOCC(18) && OCC(W, 15)) JUMPMAN(red, R, W, 11, 15, 18)
	break ;
    case 12:
	if (UNOCC(21) && OCC(W, 16)) JUMPMAN(red, R, W, 12, 16, 21)
	break ;
    case 13:
	if (UNOCC(20) && OCC(W, 16)) JUMPMAN(red, R, W, 13, 16, 20)
	if (UNOCC(22) && OCC(W, 17)) JUMPMAN(red, R, W, 13, 17, 22)
	break ;
    case 14:
	if (UNOCC(21) && OCC(W, 17)) JUMPMAN(red, R, W, 14, 17, 21)
	if (UNOCC(23) && OCC(W, 18)) JUMPMAN(red, R, W, 14, 18, 23)
	break ;
    case 15:
	if (UNOCC(22) && OCC(W, 18)) JUMPMAN(red, R, W, 15, 18, 22)
	break ;
    case 16:
	if (UNOCC(25) && OCC(W, 21)) JUMPMAN(red, R, W, 16, 21, 25)
	break ;
    case 17:
	if (UNOCC(24) && OCC(W, 21)) JUMPMAN(red, R, W, 17, 21, 24)
	if (UNOCC(26) && OCC(W, 22)) JUMPMAN(red, R, W, 17, 22, 26)
	break ;
    case 18:
	if (UNOCC(25) && OCC(W, 22)) JUMPMAN(red, R, W, 18, 22, 25)
	if (UNOCC(27) && OCC(W, 23)) JUMPMAN(red, R, W, 18, 23, 27)
	break ;
    case 19:
	if (UNOCC(26) && OCC(W, 23)) JUMPMAN(red, R, W, 19, 23, 26)
	break ;
    case 20:
	if (UNOCC(29) && OCC(W, 24)) FINISHMAN(red, R, W, 20, 24, 29)
	break ;
    case 21:
	if (UNOCC(28) && OCC(W, 24)) FINISHMAN(red, R, W, 21, 24, 28)
	if (UNOCC(30) && OCC(W, 25)) FINISHMAN(red, R, W, 21, 25, 30)
	break ;
    case 22:
	if (UNOCC(29) && OCC(W, 25)) FINISHMAN(red, R, W, 22, 25, 29)
	if (UNOCC(31) && OCC(W, 26)) FINISHMAN(red, R, W, 22, 26, 31)
	break ;
    case 23:
	if (UNOCC(30) && OCC(W, 26)) FINISHMAN(red, R, W, 23, 26, 30)
	break ;
    case 24:
	break ;
    case 25:
	break ;
    case 26:
	break ;
    case 27:
	break ;
    case 28:
	break ;
    case 29:
	break ;
    case 30:
	break ;
    case 31:
	break ;
    }
    return m ;
}
inline CheckerBoard *
whitemanresolve(int c, CheckerBoard *b, CheckerBoard *m)
{
    CheckerBoard tmp ;
    CheckerBoard *n = m ; /* remember old value */
    switch (c) {
    case 0:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 1:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 2:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 3:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 4:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 5:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 6:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 7:
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 8:
	if (UNOCC(1) && OCC(R, 5)) FINISHMAN(white, W, R, 8, 5, 1)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 9:
	if (UNOCC(0) && OCC(R, 5)) FINISHMAN(white, W, R, 9, 5, 0)
	if (UNOCC(2) && OCC(R, 6)) FINISHMAN(white, W, R, 9, 6, 2)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 10:
	if (UNOCC(1) && OCC(R, 6)) FINISHMAN(white, W, R, 10, 6, 1)
	if (UNOCC(3) && OCC(R, 7)) FINISHMAN(white, W, R, 10, 7, 3)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 11:
	if (UNOCC(2) && OCC(R, 7)) FINISHMAN(white, W, R, 11, 7, 2)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 12:
	if (UNOCC(5) && OCC(R, 8)) JUMPMAN(white, W, R, 12, 8, 5)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 13:
	if (UNOCC(4) && OCC(R, 8)) JUMPMAN(white, W, R, 13, 8, 4)
	if (UNOCC(6) && OCC(R, 9)) JUMPMAN(white, W, R, 13, 9, 6)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 14:
	if (UNOCC(5) && OCC(R, 9)) JUMPMAN(white, W, R, 14, 9, 5)
	if (UNOCC(7) && OCC(R, 10)) JUMPMAN(white, W, R, 14, 10, 7)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 15:
	if (UNOCC(6) && OCC(R, 10)) JUMPMAN(white, W, R, 15, 10, 6)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 16:
	if (UNOCC(9) && OCC(R, 13)) JUMPMAN(white, W, R, 16, 13, 9)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 17:
	if (UNOCC(8) && OCC(R, 13)) JUMPMAN(white, W, R, 17, 13, 8)
	if (UNOCC(10) && OCC(R, 14)) JUMPMAN(white, W, R, 17, 14, 10)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 18:
	if (UNOCC(9) && OCC(R, 14)) JUMPMAN(white, W, R, 18, 14, 9)
	if (UNOCC(11) && OCC(R, 15)) JUMPMAN(white, W, R, 18, 15, 11)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 19:
	if (UNOCC(10) && OCC(R, 15)) JUMPMAN(white, W, R, 19, 15, 10)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 20:
	if (UNOCC(13) && OCC(R, 16)) JUMPMAN(white, W, R, 20, 16, 13)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 21:
	if (UNOCC(12) && OCC(R, 16)) JUMPMAN(white, W, R, 21, 16, 12)
	if (UNOCC(14) && OCC(R, 17)) JUMPMAN(white, W, R, 21, 17, 14)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 22:
	if (UNOCC(13) && OCC(R, 17)) JUMPMAN(white, W, R, 22, 17, 13)
	if (UNOCC(15) && OCC(R, 18)) JUMPMAN(white, W, R, 22, 18, 15)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 23:
	if (UNOCC(14) && OCC(R, 18)) JUMPMAN(white, W, R, 23, 18, 14)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 24:
	if (UNOCC(17) && OCC(R, 21)) JUMPMAN(white, W, R, 24, 21, 17)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 25:
	if (UNOCC(16) && OCC(R, 21)) JUMPMAN(white, W, R, 25, 21, 16)
	if (UNOCC(18) && OCC(R, 22)) JUMPMAN(white, W, R, 25, 22, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 26:
	if (UNOCC(17) && OCC(R, 22)) JUMPMAN(white, W, R, 26, 22, 17)
	if (UNOCC(19) && OCC(R, 23)) JUMPMAN(white, W, R, 26, 23, 19)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 27:
	if (UNOCC(18) && OCC(R, 23)) JUMPMAN(white, W, R, 27, 23, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 28:
	if (UNOCC(21) && OCC(R, 24)) JUMPMAN(white, W, R, 28, 24, 21)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 29:
	if (UNOCC(20) && OCC(R, 24)) JUMPMAN(white, W, R, 29, 24, 20)
	if (UNOCC(22) && OCC(R, 25)) JUMPMAN(white, W, R, 29, 25, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 30:
	if (UNOCC(21) && OCC(R, 25)) JUMPMAN(white, W, R, 30, 25, 21)
	if (UNOCC(23) && OCC(R, 26)) JUMPMAN(white, W, R, 30, 26, 23)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 31:
	if (UNOCC(22) && OCC(R, 26)) JUMPMAN(white, W, R, 31, 26, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    }
    return m ;
}
inline CheckerBoard *
whitemanjump(int c, CheckerBoard *b, CheckerBoard *m)
{
    CheckerBoard tmp ;
    switch (c) {
    case 0:
	break ;
    case 1:
	break ;
    case 2:
	break ;
    case 3:
	break ;
    case 4:
	break ;
    case 5:
	break ;
    case 6:
	break ;
    case 7:
	break ;
    case 8:
	if (UNOCC(1) && OCC(R, 5)) FINISHMAN(white, W, R, 8, 5, 1)
	break ;
    case 9:
	if (UNOCC(0) && OCC(R, 5)) FINISHMAN(white, W, R, 9, 5, 0)
	if (UNOCC(2) && OCC(R, 6)) FINISHMAN(white, W, R, 9, 6, 2)
	break ;
    case 10:
	if (UNOCC(1) && OCC(R, 6)) FINISHMAN(white, W, R, 10, 6, 1)
	if (UNOCC(3) && OCC(R, 7)) FINISHMAN(white, W, R, 10, 7, 3)
	break ;
    case 11:
	if (UNOCC(2) && OCC(R, 7)) FINISHMAN(white, W, R, 11, 7, 2)
	break ;
    case 12:
	if (UNOCC(5) && OCC(R, 8)) JUMPMAN(white, W, R, 12, 8, 5)
	break ;
    case 13:
	if (UNOCC(4) && OCC(R, 8)) JUMPMAN(white, W, R, 13, 8, 4)
	if (UNOCC(6) && OCC(R, 9)) JUMPMAN(white, W, R, 13, 9, 6)
	break ;
    case 14:
	if (UNOCC(5) && OCC(R, 9)) JUMPMAN(white, W, R, 14, 9, 5)
	if (UNOCC(7) && OCC(R, 10)) JUMPMAN(white, W, R, 14, 10, 7)
	break ;
    case 15:
	if (UNOCC(6) && OCC(R, 10)) JUMPMAN(white, W, R, 15, 10, 6)
	break ;
    case 16:
	if (UNOCC(9) && OCC(R, 13)) JUMPMAN(white, W, R, 16, 13, 9)
	break ;
    case 17:
	if (UNOCC(8) && OCC(R, 13)) JUMPMAN(white, W, R, 17, 13, 8)
	if (UNOCC(10) && OCC(R, 14)) JUMPMAN(white, W, R, 17, 14, 10)
	break ;
    case 18:
	if (UNOCC(9) && OCC(R, 14)) JUMPMAN(white, W, R, 18, 14, 9)
	if (UNOCC(11) && OCC(R, 15)) JUMPMAN(white, W, R, 18, 15, 11)
	break ;
    case 19:
	if (UNOCC(10) && OCC(R, 15)) JUMPMAN(white, W, R, 19, 15, 10)
	break ;
    case 20:
	if (UNOCC(13) && OCC(R, 16)) JUMPMAN(white, W, R, 20, 16, 13)
	break ;
    case 21:
	if (UNOCC(12) && OCC(R, 16)) JUMPMAN(white, W, R, 21, 16, 12)
	if (UNOCC(14) && OCC(R, 17)) JUMPMAN(white, W, R, 21, 17, 14)
	break ;
    case 22:
	if (UNOCC(13) && OCC(R, 17)) JUMPMAN(white, W, R, 22, 17, 13)
	if (UNOCC(15) && OCC(R, 18)) JUMPMAN(white, W, R, 22, 18, 15)
	break ;
    case 23:
	if (UNOCC(14) && OCC(R, 18)) JUMPMAN(white, W, R, 23, 18, 14)
	break ;
    case 24:
	if (UNOCC(17) && OCC(R, 21)) JUMPMAN(white, W, R, 24, 21, 17)
	break ;
    case 25:
	if (UNOCC(16) && OCC(R, 21)) JUMPMAN(white, W, R, 25, 21, 16)
	if (UNOCC(18) && OCC(R, 22)) JUMPMAN(white, W, R, 25, 22, 18)
	break ;
    case 26:
	if (UNOCC(17) && OCC(R, 22)) JUMPMAN(white, W, R, 26, 22, 17)
	if (UNOCC(19) && OCC(R, 23)) JUMPMAN(white, W, R, 26, 23, 19)
	break ;
    case 27:
	if (UNOCC(18) && OCC(R, 23)) JUMPMAN(white, W, R, 27, 23, 18)
	break ;
    case 28:
	if (UNOCC(21) && OCC(R, 24)) JUMPMAN(white, W, R, 28, 24, 21)
	break ;
    case 29:
	if (UNOCC(20) && OCC(R, 24)) JUMPMAN(white, W, R, 29, 24, 20)
	if (UNOCC(22) && OCC(R, 25)) JUMPMAN(white, W, R, 29, 25, 22)
	break ;
    case 30:
	if (UNOCC(21) && OCC(R, 25)) JUMPMAN(white, W, R, 30, 25, 21)
	if (UNOCC(23) && OCC(R, 26)) JUMPMAN(white, W, R, 30, 26, 23)
	break ;
    case 31:
	if (UNOCC(22) && OCC(R, 26)) JUMPMAN(white, W, R, 31, 26, 22)
	break ;
    }
    return m ;
}
inline CheckerBoard *
redkingresolve(int c, CheckerBoard *b, CheckerBoard *m)
{
    CheckerBoard tmp ;
    CheckerBoard *n = m ; /* remember old value */
    switch (c) {
    case 0:
	if (UNOCC(9) && OCC(W, 5)) JUMPKING(red, R, W, 0, 5, 9)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 1:
	if (UNOCC(8) && OCC(W, 5)) JUMPKING(red, R, W, 1, 5, 8)
	if (UNOCC(10) && OCC(W, 6)) JUMPKING(red, R, W, 1, 6, 10)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 2:
	if (UNOCC(9) && OCC(W, 6)) JUMPKING(red, R, W, 2, 6, 9)
	if (UNOCC(11) && OCC(W, 7)) JUMPKING(red, R, W, 2, 7, 11)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 3:
	if (UNOCC(10) && OCC(W, 7)) JUMPKING(red, R, W, 3, 7, 10)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 4:
	if (UNOCC(13) && OCC(W, 8)) JUMPKING(red, R, W, 4, 8, 13)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 5:
	if (UNOCC(12) && OCC(W, 8)) JUMPKING(red, R, W, 5, 8, 12)
	if (UNOCC(14) && OCC(W, 9)) JUMPKING(red, R, W, 5, 9, 14)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 6:
	if (UNOCC(13) && OCC(W, 9)) JUMPKING(red, R, W, 6, 9, 13)
	if (UNOCC(15) && OCC(W, 10)) JUMPKING(red, R, W, 6, 10, 15)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 7:
	if (UNOCC(14) && OCC(W, 10)) JUMPKING(red, R, W, 7, 10, 14)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 8:
	if (UNOCC(1) && OCC(W, 5)) JUMPKING(red, R, W, 8, 5, 1)
	if (UNOCC(17) && OCC(W, 13)) JUMPKING(red, R, W, 8, 13, 17)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 9:
	if (UNOCC(0) && OCC(W, 5)) JUMPKING(red, R, W, 9, 5, 0)
	if (UNOCC(2) && OCC(W, 6)) JUMPKING(red, R, W, 9, 6, 2)
	if (UNOCC(16) && OCC(W, 13)) JUMPKING(red, R, W, 9, 13, 16)
	if (UNOCC(18) && OCC(W, 14)) JUMPKING(red, R, W, 9, 14, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 10:
	if (UNOCC(1) && OCC(W, 6)) JUMPKING(red, R, W, 10, 6, 1)
	if (UNOCC(3) && OCC(W, 7)) JUMPKING(red, R, W, 10, 7, 3)
	if (UNOCC(17) && OCC(W, 14)) JUMPKING(red, R, W, 10, 14, 17)
	if (UNOCC(19) && OCC(W, 15)) JUMPKING(red, R, W, 10, 15, 19)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 11:
	if (UNOCC(2) && OCC(W, 7)) JUMPKING(red, R, W, 11, 7, 2)
	if (UNOCC(18) && OCC(W, 15)) JUMPKING(red, R, W, 11, 15, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 12:
	if (UNOCC(5) && OCC(W, 8)) JUMPKING(red, R, W, 12, 8, 5)
	if (UNOCC(21) && OCC(W, 16)) JUMPKING(red, R, W, 12, 16, 21)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 13:
	if (UNOCC(4) && OCC(W, 8)) JUMPKING(red, R, W, 13, 8, 4)
	if (UNOCC(6) && OCC(W, 9)) JUMPKING(red, R, W, 13, 9, 6)
	if (UNOCC(20) && OCC(W, 16)) JUMPKING(red, R, W, 13, 16, 20)
	if (UNOCC(22) && OCC(W, 17)) JUMPKING(red, R, W, 13, 17, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 14:
	if (UNOCC(5) && OCC(W, 9)) JUMPKING(red, R, W, 14, 9, 5)
	if (UNOCC(7) && OCC(W, 10)) JUMPKING(red, R, W, 14, 10, 7)
	if (UNOCC(21) && OCC(W, 17)) JUMPKING(red, R, W, 14, 17, 21)
	if (UNOCC(23) && OCC(W, 18)) JUMPKING(red, R, W, 14, 18, 23)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 15:
	if (UNOCC(6) && OCC(W, 10)) JUMPKING(red, R, W, 15, 10, 6)
	if (UNOCC(22) && OCC(W, 18)) JUMPKING(red, R, W, 15, 18, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 16:
	if (UNOCC(9) && OCC(W, 13)) JUMPKING(red, R, W, 16, 13, 9)
	if (UNOCC(25) && OCC(W, 21)) JUMPKING(red, R, W, 16, 21, 25)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 17:
	if (UNOCC(8) && OCC(W, 13)) JUMPKING(red, R, W, 17, 13, 8)
	if (UNOCC(10) && OCC(W, 14)) JUMPKING(red, R, W, 17, 14, 10)
	if (UNOCC(24) && OCC(W, 21)) JUMPKING(red, R, W, 17, 21, 24)
	if (UNOCC(26) && OCC(W, 22)) JUMPKING(red, R, W, 17, 22, 26)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 18:
	if (UNOCC(9) && OCC(W, 14)) JUMPKING(red, R, W, 18, 14, 9)
	if (UNOCC(11) && OCC(W, 15)) JUMPKING(red, R, W, 18, 15, 11)
	if (UNOCC(25) && OCC(W, 22)) JUMPKING(red, R, W, 18, 22, 25)
	if (UNOCC(27) && OCC(W, 23)) JUMPKING(red, R, W, 18, 23, 27)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 19:
	if (UNOCC(10) && OCC(W, 15)) JUMPKING(red, R, W, 19, 15, 10)
	if (UNOCC(26) && OCC(W, 23)) JUMPKING(red, R, W, 19, 23, 26)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 20:
	if (UNOCC(13) && OCC(W, 16)) JUMPKING(red, R, W, 20, 16, 13)
	if (UNOCC(29) && OCC(W, 24)) JUMPKING(red, R, W, 20, 24, 29)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 21:
	if (UNOCC(12) && OCC(W, 16)) JUMPKING(red, R, W, 21, 16, 12)
	if (UNOCC(14) && OCC(W, 17)) JUMPKING(red, R, W, 21, 17, 14)
	if (UNOCC(28) && OCC(W, 24)) JUMPKING(red, R, W, 21, 24, 28)
	if (UNOCC(30) && OCC(W, 25)) JUMPKING(red, R, W, 21, 25, 30)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 22:
	if (UNOCC(13) && OCC(W, 17)) JUMPKING(red, R, W, 22, 17, 13)
	if (UNOCC(15) && OCC(W, 18)) JUMPKING(red, R, W, 22, 18, 15)
	if (UNOCC(29) && OCC(W, 25)) JUMPKING(red, R, W, 22, 25, 29)
	if (UNOCC(31) && OCC(W, 26)) JUMPKING(red, R, W, 22, 26, 31)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 23:
	if (UNOCC(14) && OCC(W, 18)) JUMPKING(red, R, W, 23, 18, 14)
	if (UNOCC(30) && OCC(W, 26)) JUMPKING(red, R, W, 23, 26, 30)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 24:
	if (UNOCC(17) && OCC(W, 21)) JUMPKING(red, R, W, 24, 21, 17)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 25:
	if (UNOCC(16) && OCC(W, 21)) JUMPKING(red, R, W, 25, 21, 16)
	if (UNOCC(18) && OCC(W, 22)) JUMPKING(red, R, W, 25, 22, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 26:
	if (UNOCC(17) && OCC(W, 22)) JUMPKING(red, R, W, 26, 22, 17)
	if (UNOCC(19) && OCC(W, 23)) JUMPKING(red, R, W, 26, 23, 19)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 27:
	if (UNOCC(18) && OCC(W, 23)) JUMPKING(red, R, W, 27, 23, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 28:
	if (UNOCC(21) && OCC(W, 24)) JUMPKING(red, R, W, 28, 24, 21)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 29:
	if (UNOCC(20) && OCC(W, 24)) JUMPKING(red, R, W, 29, 24, 20)
	if (UNOCC(22) && OCC(W, 25)) JUMPKING(red, R, W, 29, 25, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 30:
	if (UNOCC(21) && OCC(W, 25)) JUMPKING(red, R, W, 30, 25, 21)
	if (UNOCC(23) && OCC(W, 26)) JUMPKING(red, R, W, 30, 26, 23)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 31:
	if (UNOCC(22) && OCC(W, 26)) JUMPKING(red, R, W, 31, 26, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    }
    return m ;
}
inline CheckerBoard *
redkingjump(int c, CheckerBoard *b, CheckerBoard *m)
{
    CheckerBoard tmp ;
    switch (c) {
    case 0:
	if (UNOCC(9) && OCC(W, 5)) JUMPKING(red, R, W, 0, 5, 9)
	break ;
    case 1:
	if (UNOCC(8) && OCC(W, 5)) JUMPKING(red, R, W, 1, 5, 8)
	if (UNOCC(10) && OCC(W, 6)) JUMPKING(red, R, W, 1, 6, 10)
	break ;
    case 2:
	if (UNOCC(9) && OCC(W, 6)) JUMPKING(red, R, W, 2, 6, 9)
	if (UNOCC(11) && OCC(W, 7)) JUMPKING(red, R, W, 2, 7, 11)
	break ;
    case 3:
	if (UNOCC(10) && OCC(W, 7)) JUMPKING(red, R, W, 3, 7, 10)
	break ;
    case 4:
	if (UNOCC(13) && OCC(W, 8)) JUMPKING(red, R, W, 4, 8, 13)
	break ;
    case 5:
	if (UNOCC(12) && OCC(W, 8)) JUMPKING(red, R, W, 5, 8, 12)
	if (UNOCC(14) && OCC(W, 9)) JUMPKING(red, R, W, 5, 9, 14)
	break ;
    case 6:
	if (UNOCC(13) && OCC(W, 9)) JUMPKING(red, R, W, 6, 9, 13)
	if (UNOCC(15) && OCC(W, 10)) JUMPKING(red, R, W, 6, 10, 15)
	break ;
    case 7:
	if (UNOCC(14) && OCC(W, 10)) JUMPKING(red, R, W, 7, 10, 14)
	break ;
    case 8:
	if (UNOCC(1) && OCC(W, 5)) JUMPKING(red, R, W, 8, 5, 1)
	if (UNOCC(17) && OCC(W, 13)) JUMPKING(red, R, W, 8, 13, 17)
	break ;
    case 9:
	if (UNOCC(0) && OCC(W, 5)) JUMPKING(red, R, W, 9, 5, 0)
	if (UNOCC(2) && OCC(W, 6)) JUMPKING(red, R, W, 9, 6, 2)
	if (UNOCC(16) && OCC(W, 13)) JUMPKING(red, R, W, 9, 13, 16)
	if (UNOCC(18) && OCC(W, 14)) JUMPKING(red, R, W, 9, 14, 18)
	break ;
    case 10:
	if (UNOCC(1) && OCC(W, 6)) JUMPKING(red, R, W, 10, 6, 1)
	if (UNOCC(3) && OCC(W, 7)) JUMPKING(red, R, W, 10, 7, 3)
	if (UNOCC(17) && OCC(W, 14)) JUMPKING(red, R, W, 10, 14, 17)
	if (UNOCC(19) && OCC(W, 15)) JUMPKING(red, R, W, 10, 15, 19)
	break ;
    case 11:
	if (UNOCC(2) && OCC(W, 7)) JUMPKING(red, R, W, 11, 7, 2)
	if (UNOCC(18) && OCC(W, 15)) JUMPKING(red, R, W, 11, 15, 18)
	break ;
    case 12:
	if (UNOCC(5) && OCC(W, 8)) JUMPKING(red, R, W, 12, 8, 5)
	if (UNOCC(21) && OCC(W, 16)) JUMPKING(red, R, W, 12, 16, 21)
	break ;
    case 13:
	if (UNOCC(4) && OCC(W, 8)) JUMPKING(red, R, W, 13, 8, 4)
	if (UNOCC(6) && OCC(W, 9)) JUMPKING(red, R, W, 13, 9, 6)
	if (UNOCC(20) && OCC(W, 16)) JUMPKING(red, R, W, 13, 16, 20)
	if (UNOCC(22) && OCC(W, 17)) JUMPKING(red, R, W, 13, 17, 22)
	break ;
    case 14:
	if (UNOCC(5) && OCC(W, 9)) JUMPKING(red, R, W, 14, 9, 5)
	if (UNOCC(7) && OCC(W, 10)) JUMPKING(red, R, W, 14, 10, 7)
	if (UNOCC(21) && OCC(W, 17)) JUMPKING(red, R, W, 14, 17, 21)
	if (UNOCC(23) && OCC(W, 18)) JUMPKING(red, R, W, 14, 18, 23)
	break ;
    case 15:
	if (UNOCC(6) && OCC(W, 10)) JUMPKING(red, R, W, 15, 10, 6)
	if (UNOCC(22) && OCC(W, 18)) JUMPKING(red, R, W, 15, 18, 22)
	break ;
    case 16:
	if (UNOCC(9) && OCC(W, 13)) JUMPKING(red, R, W, 16, 13, 9)
	if (UNOCC(25) && OCC(W, 21)) JUMPKING(red, R, W, 16, 21, 25)
	break ;
    case 17:
	if (UNOCC(8) && OCC(W, 13)) JUMPKING(red, R, W, 17, 13, 8)
	if (UNOCC(10) && OCC(W, 14)) JUMPKING(red, R, W, 17, 14, 10)
	if (UNOCC(24) && OCC(W, 21)) JUMPKING(red, R, W, 17, 21, 24)
	if (UNOCC(26) && OCC(W, 22)) JUMPKING(red, R, W, 17, 22, 26)
	break ;
    case 18:
	if (UNOCC(9) && OCC(W, 14)) JUMPKING(red, R, W, 18, 14, 9)
	if (UNOCC(11) && OCC(W, 15)) JUMPKING(red, R, W, 18, 15, 11)
	if (UNOCC(25) && OCC(W, 22)) JUMPKING(red, R, W, 18, 22, 25)
	if (UNOCC(27) && OCC(W, 23)) JUMPKING(red, R, W, 18, 23, 27)
	break ;
    case 19:
	if (UNOCC(10) && OCC(W, 15)) JUMPKING(red, R, W, 19, 15, 10)
	if (UNOCC(26) && OCC(W, 23)) JUMPKING(red, R, W, 19, 23, 26)
	break ;
    case 20:
	if (UNOCC(13) && OCC(W, 16)) JUMPKING(red, R, W, 20, 16, 13)
	if (UNOCC(29) && OCC(W, 24)) JUMPKING(red, R, W, 20, 24, 29)
	break ;
    case 21:
	if (UNOCC(12) && OCC(W, 16)) JUMPKING(red, R, W, 21, 16, 12)
	if (UNOCC(14) && OCC(W, 17)) JUMPKING(red, R, W, 21, 17, 14)
	if (UNOCC(28) && OCC(W, 24)) JUMPKING(red, R, W, 21, 24, 28)
	if (UNOCC(30) && OCC(W, 25)) JUMPKING(red, R, W, 21, 25, 30)
	break ;
    case 22:
	if (UNOCC(13) && OCC(W, 17)) JUMPKING(red, R, W, 22, 17, 13)
	if (UNOCC(15) && OCC(W, 18)) JUMPKING(red, R, W, 22, 18, 15)
	if (UNOCC(29) && OCC(W, 25)) JUMPKING(red, R, W, 22, 25, 29)
	if (UNOCC(31) && OCC(W, 26)) JUMPKING(red, R, W, 22, 26, 31)
	break ;
    case 23:
	if (UNOCC(14) && OCC(W, 18)) JUMPKING(red, R, W, 23, 18, 14)
	if (UNOCC(30) && OCC(W, 26)) JUMPKING(red, R, W, 23, 26, 30)
	break ;
    case 24:
	if (UNOCC(17) && OCC(W, 21)) JUMPKING(red, R, W, 24, 21, 17)
	break ;
    case 25:
	if (UNOCC(16) && OCC(W, 21)) JUMPKING(red, R, W, 25, 21, 16)
	if (UNOCC(18) && OCC(W, 22)) JUMPKING(red, R, W, 25, 22, 18)
	break ;
    case 26:
	if (UNOCC(17) && OCC(W, 22)) JUMPKING(red, R, W, 26, 22, 17)
	if (UNOCC(19) && OCC(W, 23)) JUMPKING(red, R, W, 26, 23, 19)
	break ;
    case 27:
	if (UNOCC(18) && OCC(W, 23)) JUMPKING(red, R, W, 27, 23, 18)
	break ;
    case 28:
	if (UNOCC(21) && OCC(W, 24)) JUMPKING(red, R, W, 28, 24, 21)
	break ;
    case 29:
	if (UNOCC(20) && OCC(W, 24)) JUMPKING(red, R, W, 29, 24, 20)
	if (UNOCC(22) && OCC(W, 25)) JUMPKING(red, R, W, 29, 25, 22)
	break ;
    case 30:
	if (UNOCC(21) && OCC(W, 25)) JUMPKING(red, R, W, 30, 25, 21)
	if (UNOCC(23) && OCC(W, 26)) JUMPKING(red, R, W, 30, 26, 23)
	break ;
    case 31:
	if (UNOCC(22) && OCC(W, 26)) JUMPKING(red, R, W, 31, 26, 22)
	break ;
    }
    return m ;
}
inline CheckerBoard *
whitekingresolve(int c, CheckerBoard *b, CheckerBoard *m)
{
    CheckerBoard tmp ;
    CheckerBoard *n = m ; /* remember old value */
    switch (c) {
    case 0:
	if (UNOCC(9) && OCC(R, 5)) JUMPKING(white, W, R, 0, 5, 9)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 1:
	if (UNOCC(8) && OCC(R, 5)) JUMPKING(white, W, R, 1, 5, 8)
	if (UNOCC(10) && OCC(R, 6)) JUMPKING(white, W, R, 1, 6, 10)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 2:
	if (UNOCC(9) && OCC(R, 6)) JUMPKING(white, W, R, 2, 6, 9)
	if (UNOCC(11) && OCC(R, 7)) JUMPKING(white, W, R, 2, 7, 11)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 3:
	if (UNOCC(10) && OCC(R, 7)) JUMPKING(white, W, R, 3, 7, 10)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 4:
	if (UNOCC(13) && OCC(R, 8)) JUMPKING(white, W, R, 4, 8, 13)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 5:
	if (UNOCC(12) && OCC(R, 8)) JUMPKING(white, W, R, 5, 8, 12)
	if (UNOCC(14) && OCC(R, 9)) JUMPKING(white, W, R, 5, 9, 14)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 6:
	if (UNOCC(13) && OCC(R, 9)) JUMPKING(white, W, R, 6, 9, 13)
	if (UNOCC(15) && OCC(R, 10)) JUMPKING(white, W, R, 6, 10, 15)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 7:
	if (UNOCC(14) && OCC(R, 10)) JUMPKING(white, W, R, 7, 10, 14)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 8:
	if (UNOCC(1) && OCC(R, 5)) JUMPKING(white, W, R, 8, 5, 1)
	if (UNOCC(17) && OCC(R, 13)) JUMPKING(white, W, R, 8, 13, 17)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 9:
	if (UNOCC(0) && OCC(R, 5)) JUMPKING(white, W, R, 9, 5, 0)
	if (UNOCC(2) && OCC(R, 6)) JUMPKING(white, W, R, 9, 6, 2)
	if (UNOCC(16) && OCC(R, 13)) JUMPKING(white, W, R, 9, 13, 16)
	if (UNOCC(18) && OCC(R, 14)) JUMPKING(white, W, R, 9, 14, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 10:
	if (UNOCC(1) && OCC(R, 6)) JUMPKING(white, W, R, 10, 6, 1)
	if (UNOCC(3) && OCC(R, 7)) JUMPKING(white, W, R, 10, 7, 3)
	if (UNOCC(17) && OCC(R, 14)) JUMPKING(white, W, R, 10, 14, 17)
	if (UNOCC(19) && OCC(R, 15)) JUMPKING(white, W, R, 10, 15, 19)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 11:
	if (UNOCC(2) && OCC(R, 7)) JUMPKING(white, W, R, 11, 7, 2)
	if (UNOCC(18) && OCC(R, 15)) JUMPKING(white, W, R, 11, 15, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 12:
	if (UNOCC(5) && OCC(R, 8)) JUMPKING(white, W, R, 12, 8, 5)
	if (UNOCC(21) && OCC(R, 16)) JUMPKING(white, W, R, 12, 16, 21)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 13:
	if (UNOCC(4) && OCC(R, 8)) JUMPKING(white, W, R, 13, 8, 4)
	if (UNOCC(6) && OCC(R, 9)) JUMPKING(white, W, R, 13, 9, 6)
	if (UNOCC(20) && OCC(R, 16)) JUMPKING(white, W, R, 13, 16, 20)
	if (UNOCC(22) && OCC(R, 17)) JUMPKING(white, W, R, 13, 17, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 14:
	if (UNOCC(5) && OCC(R, 9)) JUMPKING(white, W, R, 14, 9, 5)
	if (UNOCC(7) && OCC(R, 10)) JUMPKING(white, W, R, 14, 10, 7)
	if (UNOCC(21) && OCC(R, 17)) JUMPKING(white, W, R, 14, 17, 21)
	if (UNOCC(23) && OCC(R, 18)) JUMPKING(white, W, R, 14, 18, 23)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 15:
	if (UNOCC(6) && OCC(R, 10)) JUMPKING(white, W, R, 15, 10, 6)
	if (UNOCC(22) && OCC(R, 18)) JUMPKING(white, W, R, 15, 18, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 16:
	if (UNOCC(9) && OCC(R, 13)) JUMPKING(white, W, R, 16, 13, 9)
	if (UNOCC(25) && OCC(R, 21)) JUMPKING(white, W, R, 16, 21, 25)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 17:
	if (UNOCC(8) && OCC(R, 13)) JUMPKING(white, W, R, 17, 13, 8)
	if (UNOCC(10) && OCC(R, 14)) JUMPKING(white, W, R, 17, 14, 10)
	if (UNOCC(24) && OCC(R, 21)) JUMPKING(white, W, R, 17, 21, 24)
	if (UNOCC(26) && OCC(R, 22)) JUMPKING(white, W, R, 17, 22, 26)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 18:
	if (UNOCC(9) && OCC(R, 14)) JUMPKING(white, W, R, 18, 14, 9)
	if (UNOCC(11) && OCC(R, 15)) JUMPKING(white, W, R, 18, 15, 11)
	if (UNOCC(25) && OCC(R, 22)) JUMPKING(white, W, R, 18, 22, 25)
	if (UNOCC(27) && OCC(R, 23)) JUMPKING(white, W, R, 18, 23, 27)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 19:
	if (UNOCC(10) && OCC(R, 15)) JUMPKING(white, W, R, 19, 15, 10)
	if (UNOCC(26) && OCC(R, 23)) JUMPKING(white, W, R, 19, 23, 26)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 20:
	if (UNOCC(13) && OCC(R, 16)) JUMPKING(white, W, R, 20, 16, 13)
	if (UNOCC(29) && OCC(R, 24)) JUMPKING(white, W, R, 20, 24, 29)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 21:
	if (UNOCC(12) && OCC(R, 16)) JUMPKING(white, W, R, 21, 16, 12)
	if (UNOCC(14) && OCC(R, 17)) JUMPKING(white, W, R, 21, 17, 14)
	if (UNOCC(28) && OCC(R, 24)) JUMPKING(white, W, R, 21, 24, 28)
	if (UNOCC(30) && OCC(R, 25)) JUMPKING(white, W, R, 21, 25, 30)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 22:
	if (UNOCC(13) && OCC(R, 17)) JUMPKING(white, W, R, 22, 17, 13)
	if (UNOCC(15) && OCC(R, 18)) JUMPKING(white, W, R, 22, 18, 15)
	if (UNOCC(29) && OCC(R, 25)) JUMPKING(white, W, R, 22, 25, 29)
	if (UNOCC(31) && OCC(R, 26)) JUMPKING(white, W, R, 22, 26, 31)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 23:
	if (UNOCC(14) && OCC(R, 18)) JUMPKING(white, W, R, 23, 18, 14)
	if (UNOCC(30) && OCC(R, 26)) JUMPKING(white, W, R, 23, 26, 30)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 24:
	if (UNOCC(17) && OCC(R, 21)) JUMPKING(white, W, R, 24, 21, 17)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 25:
	if (UNOCC(16) && OCC(R, 21)) JUMPKING(white, W, R, 25, 21, 16)
	if (UNOCC(18) && OCC(R, 22)) JUMPKING(white, W, R, 25, 22, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 26:
	if (UNOCC(17) && OCC(R, 22)) JUMPKING(white, W, R, 26, 22, 17)
	if (UNOCC(19) && OCC(R, 23)) JUMPKING(white, W, R, 26, 23, 19)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 27:
	if (UNOCC(18) && OCC(R, 23)) JUMPKING(white, W, R, 27, 23, 18)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 28:
	if (UNOCC(21) && OCC(R, 24)) JUMPKING(white, W, R, 28, 24, 21)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 29:
	if (UNOCC(20) && OCC(R, 24)) JUMPKING(white, W, R, 29, 24, 20)
	if (UNOCC(22) && OCC(R, 25)) JUMPKING(white, W, R, 29, 25, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 30:
	if (UNOCC(21) && OCC(R, 25)) JUMPKING(white, W, R, 30, 25, 21)
	if (UNOCC(23) && OCC(R, 26)) JUMPKING(white, W, R, 30, 26, 23)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    case 31:
	if (UNOCC(22) && OCC(R, 26)) JUMPKING(white, W, R, 31, 26, 22)
	if (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}
	break ;
    }
    return m ;
}
inline CheckerBoard *
whitekingjump(int c, CheckerBoard *b, CheckerBoard *m)
{
    CheckerBoard tmp ;
    switch (c) {
    case 0:
	if (UNOCC(9) && OCC(R, 5)) JUMPKING(white, W, R, 0, 5, 9)
	break ;
    case 1:
	if (UNOCC(8) && OCC(R, 5)) JUMPKING(white, W, R, 1, 5, 8)
	if (UNOCC(10) && OCC(R, 6)) JUMPKING(white, W, R, 1, 6, 10)
	break ;
    case 2:
	if (UNOCC(9) && OCC(R, 6)) JUMPKING(white, W, R, 2, 6, 9)
	if (UNOCC(11) && OCC(R, 7)) JUMPKING(white, W, R, 2, 7, 11)
	break ;
    case 3:
	if (UNOCC(10) && OCC(R, 7)) JUMPKING(white, W, R, 3, 7, 10)
	break ;
    case 4:
	if (UNOCC(13) && OCC(R, 8)) JUMPKING(white, W, R, 4, 8, 13)
	break ;
    case 5:
	if (UNOCC(12) && OCC(R, 8)) JUMPKING(white, W, R, 5, 8, 12)
	if (UNOCC(14) && OCC(R, 9)) JUMPKING(white, W, R, 5, 9, 14)
	break ;
    case 6:
	if (UNOCC(13) && OCC(R, 9)) JUMPKING(white, W, R, 6, 9, 13)
	if (UNOCC(15) && OCC(R, 10)) JUMPKING(white, W, R, 6, 10, 15)
	break ;
    case 7:
	if (UNOCC(14) && OCC(R, 10)) JUMPKING(white, W, R, 7, 10, 14)
	break ;
    case 8:
	if (UNOCC(1) && OCC(R, 5)) JUMPKING(white, W, R, 8, 5, 1)
	if (UNOCC(17) && OCC(R, 13)) JUMPKING(white, W, R, 8, 13, 17)
	break ;
    case 9:
	if (UNOCC(0) && OCC(R, 5)) JUMPKING(white, W, R, 9, 5, 0)
	if (UNOCC(2) && OCC(R, 6)) JUMPKING(white, W, R, 9, 6, 2)
	if (UNOCC(16) && OCC(R, 13)) JUMPKING(white, W, R, 9, 13, 16)
	if (UNOCC(18) && OCC(R, 14)) JUMPKING(white, W, R, 9, 14, 18)
	break ;
    case 10:
	if (UNOCC(1) && OCC(R, 6)) JUMPKING(white, W, R, 10, 6, 1)
	if (UNOCC(3) && OCC(R, 7)) JUMPKING(white, W, R, 10, 7, 3)
	if (UNOCC(17) && OCC(R, 14)) JUMPKING(white, W, R, 10, 14, 17)
	if (UNOCC(19) && OCC(R, 15)) JUMPKING(white, W, R, 10, 15, 19)
	break ;
    case 11:
	if (UNOCC(2) && OCC(R, 7)) JUMPKING(white, W, R, 11, 7, 2)
	if (UNOCC(18) && OCC(R, 15)) JUMPKING(white, W, R, 11, 15, 18)
	break ;
    case 12:
	if (UNOCC(5) && OCC(R, 8)) JUMPKING(white, W, R, 12, 8, 5)
	if (UNOCC(21) && OCC(R, 16)) JUMPKING(white, W, R, 12, 16, 21)
	break ;
    case 13:
	if (UNOCC(4) && OCC(R, 8)) JUMPKING(white, W, R, 13, 8, 4)
	if (UNOCC(6) && OCC(R, 9)) JUMPKING(white, W, R, 13, 9, 6)
	if (UNOCC(20) && OCC(R, 16)) JUMPKING(white, W, R, 13, 16, 20)
	if (UNOCC(22) && OCC(R, 17)) JUMPKING(white, W, R, 13, 17, 22)
	break ;
    case 14:
	if (UNOCC(5) && OCC(R, 9)) JUMPKING(white, W, R, 14, 9, 5)
	if (UNOCC(7) && OCC(R, 10)) JUMPKING(white, W, R, 14, 10, 7)
	if (UNOCC(21) && OCC(R, 17)) JUMPKING(white, W, R, 14, 17, 21)
	if (UNOCC(23) && OCC(R, 18)) JUMPKING(white, W, R, 14, 18, 23)
	break ;
    case 15:
	if (UNOCC(6) && OCC(R, 10)) JUMPKING(white, W, R, 15, 10, 6)
	if (UNOCC(22) && OCC(R, 18)) JUMPKING(white, W, R, 15, 18, 22)
	break ;
    case 16:
	if (UNOCC(9) && OCC(R, 13)) JUMPKING(white, W, R, 16, 13, 9)
	if (UNOCC(25) && OCC(R, 21)) JUMPKING(white, W, R, 16, 21, 25)
	break ;
    case 17:
	if (UNOCC(8) && OCC(R, 13)) JUMPKING(white, W, R, 17, 13, 8)
	if (UNOCC(10) && OCC(R, 14)) JUMPKING(white, W, R, 17, 14, 10)
	if (UNOCC(24) && OCC(R, 21)) JUMPKING(white, W, R, 17, 21, 24)
	if (UNOCC(26) && OCC(R, 22)) JUMPKING(white, W, R, 17, 22, 26)
	break ;
    case 18:
	if (UNOCC(9) && OCC(R, 14)) JUMPKING(white, W, R, 18, 14, 9)
	if (UNOCC(11) && OCC(R, 15)) JUMPKING(white, W, R, 18, 15, 11)
	if (UNOCC(25) && OCC(R, 22)) JUMPKING(white, W, R, 18, 22, 25)
	if (UNOCC(27) && OCC(R, 23)) JUMPKING(white, W, R, 18, 23, 27)
	break ;
    case 19:
	if (UNOCC(10) && OCC(R, 15)) JUMPKING(white, W, R, 19, 15, 10)
	if (UNOCC(26) && OCC(R, 23)) JUMPKING(white, W, R, 19, 23, 26)
	break ;
    case 20:
	if (UNOCC(13) && OCC(R, 16)) JUMPKING(white, W, R, 20, 16, 13)
	if (UNOCC(29) && OCC(R, 24)) JUMPKING(white, W, R, 20, 24, 29)
	break ;
    case 21:
	if (UNOCC(12) && OCC(R, 16)) JUMPKING(white, W, R, 21, 16, 12)
	if (UNOCC(14) && OCC(R, 17)) JUMPKING(white, W, R, 21, 17, 14)
	if (UNOCC(28) && OCC(R, 24)) JUMPKING(white, W, R, 21, 24, 28)
	if (UNOCC(30) && OCC(R, 25)) JUMPKING(white, W, R, 21, 25, 30)
	break ;
    case 22:
	if (UNOCC(13) && OCC(R, 17)) JUMPKING(white, W, R, 22, 17, 13)
	if (UNOCC(15) && OCC(R, 18)) JUMPKING(white, W, R, 22, 18, 15)
	if (UNOCC(29) && OCC(R, 25)) JUMPKING(white, W, R, 22, 25, 29)
	if (UNOCC(31) && OCC(R, 26)) JUMPKING(white, W, R, 22, 26, 31)
	break ;
    case 23:
	if (UNOCC(14) && OCC(R, 18)) JUMPKING(white, W, R, 23, 18, 14)
	if (UNOCC(30) && OCC(R, 26)) JUMPKING(white, W, R, 23, 26, 30)
	break ;
    case 24:
	if (UNOCC(17) && OCC(R, 21)) JUMPKING(white, W, R, 24, 21, 17)
	break ;
    case 25:
	if (UNOCC(16) && OCC(R, 21)) JUMPKING(white, W, R, 25, 21, 16)
	if (UNOCC(18) && OCC(R, 22)) JUMPKING(white, W, R, 25, 22, 18)
	break ;
    case 26:
	if (UNOCC(17) && OCC(R, 22)) JUMPKING(white, W, R, 26, 22, 17)
	if (UNOCC(19) && OCC(R, 23)) JUMPKING(white, W, R, 26, 23, 19)
	break ;
    case 27:
	if (UNOCC(18) && OCC(R, 23)) JUMPKING(white, W, R, 27, 23, 18)
	break ;
    case 28:
	if (UNOCC(21) && OCC(R, 24)) JUMPKING(white, W, R, 28, 24, 21)
	break ;
    case 29:
	if (UNOCC(20) && OCC(R, 24)) JUMPKING(white, W, R, 29, 24, 20)
	if (UNOCC(22) && OCC(R, 25)) JUMPKING(white, W, R, 29, 25, 22)
	break ;
    case 30:
	if (UNOCC(21) && OCC(R, 25)) JUMPKING(white, W, R, 30, 25, 21)
	if (UNOCC(23) && OCC(R, 26)) JUMPKING(white, W, R, 30, 26, 23)
	break ;
    case 31:
	if (UNOCC(22) && OCC(R, 26)) JUMPKING(white, W, R, 31, 26, 22)
	break ;
    }
    return m ;
}
