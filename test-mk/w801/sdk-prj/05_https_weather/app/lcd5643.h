#ifndef LCD5643_H
#define LCD5643_H


#define OUT_SEC_IND 0
#define OUT_SIG_1   1
#define OUT_DIG_1   1
#define OUT_DIG_2   2
#define OUT_DIG_3   3
#define OUT_DIG_4   4
#define OUT_C_4     4


void lcd5643printDigit(u8 i_pos,u8 i_num,u8 iMode);



#endif /* LCD5643 */