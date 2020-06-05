/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
/*
x&y提取两数均为为1的位，取反得两数不同或均为0的位；
~x&~y提取两数均为0的位。取反得两数不同或均为1的位，
再将上述两个结果做与运算，得异或。
*/
  return ~(~x&~y)&~(x&y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/*
补码=原码取反+1
最小的数的补码即：符号位1，后面全是0
若int不是32位呢？
*/
  return 1<<31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
/*
最大值为符号位为0，后面全是1。32位的情况下就是0x7FFF FFFF;
最大值有什么特征呢？就是+1会溢出（不考虑符号位）;然后导致符号位改变;
以0x7F为例，x+1==0x80，与x正好每一位都不相同;
因此想到异或：x^(x+1)==0xFF，全是1就好办了。
由于需要返回1，再按位取反~得0x00，再取非!得1；
若x==0xFF，加1得0x00，也会异或得0xFF,因此要排除x=0xFF的情况：即与上!!(x+1),保证x+1≠0
本题主要是要考虑+1会溢出的情况，其他的任何数+1由于符号位不会改变，不会出现异或得0xFF的情况
*/
  return !(~(x^(x+1)))&!!(x+1);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
/*
先或上0x55555555，使得偶数位全为1；若奇数也全为1，则为0xFFFFFFFF
然后就和上题一样操作了按位取反~再逻辑非!
仅允许使用0x00~0xff的数，因此这里可以通过移位得到
*/
  return !(~(x|0x55|0x55<<8|0x55<<16|0x55<<24));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
/*
补码的定义，取反+1
*/
  return ~x+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
/*
考虑和0比较可能会比较好做，x-0x30>=0 && x-0x39<=0
大于小于0可以用符号位判断。
减法用加法代替，参考上题。
注意负数右移会高位补符号位1，所以要用!!转换一下
*/
  return !((x+~0x30+1)>>31)&!!((x+~0x3A+1)>>31);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
  判断x是否为0，0输出z，否则输出y;
  要输出的数应该与上0xFF...,另一个数应与上0x00...，再进行或运算。
  考虑到0xFF+1可得0x00，因此可用 0xFF+!x 来进行选择。
  0xFF... 可由0按位取反得到。
  */
  return ((~0+!x)&y)|((~0+!!x)&z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/*
也是考虑和0比较：y-x>=0,用符号位判断，但发现有溢出的问题
考虑到只有符号位不同时才可能溢出，就可以分为两种情况。也就是 | 的两边
符号相同时就正常作差，然后判断符号位；
符号不同则只看x或者y的符号就可以了，因为另一个已经判断了不同，x为负数则y为正，条件成立；
这里只关注符号位，最后再右移&1即可。isDiffign起到选择的作用。
*/
  int diff = y+~x+1;
  int isDiffSign = x^y;
  return ((~diff & ~isDiffSign) | (isDiffSign&x))>>31&1;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
/*
0的补码和原码是相同的，所以考虑用取反+1的操作。符号位都为0
注意到最小整数0x8000 0000取反+1也是本身。但符号位都为1
其他的数取反+1，符号位会不相同；所以可用符号位判断
只关注符号位，最后把结果右移到第一位上；由于右移高位可能补1，所以还要&1；
所以有真值表：   0 0 1
                0 1 0
                1 0 0
                1 1 0
*/
  return ~(x|(~x+1))>>31&1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
/*
没明白这个题目的意思。。以下是别人的答案;
大体思路就是使用二分法查找最高位的有效位，
*/
  int n = 0;
  x ^= (x<<1);//??
  n += ((!!(x&((~0)<<(n+16)))) << 4);
  n += ((!!(x&((~0)<<(n+8)))) << 3);
  n += ((!!(x&((~0)<<(n+4)))) << 2);
  n += ((!!(x&((~0)<<(n+2)))) << 1);
  n += (!!(x&((~0)<<(n+1))));
  return n+1;//???
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned exp=(uf&0x7F800000)>>23;
  unsigned sign=uf&0x80000000;

  if(exp==0xFF)//NaN or inf
    return uf;

  /*
  非规范化数，左移1位乘2。
  参考深入理解计算机系统（第三版）第二章，IEEE浮点表示的部分：
  非规范化数和规范化数是平滑过渡的，这里左移1位不需要考虑尾数部分溢出了的问题，
  事实证明移到阶码的位是刚刚好的。最后再把符号位补上。
  */
  if(exp==0) return (uf<<1)|sign;
  
  ++exp;//阶码+1==2的指数+1==乘2；
  if(exp==0xFF) return 0x7F800000|sign; //超出表示范围，返回无穷大
  return uf+0x00800000;//一般情况，把阶码加上
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int E=((uf&0x7F800000)>>23)-127; //指数=阶码-(2^(k-1)-1);E=e-bias;
  unsigned sign=uf&0x80000000;
  /*
  提取尾数，并加上缺省的1。相当于得到一个1.xxx的小数左移了23位。
  非规范数不需要+1，但(0,1)转int都为0就不用考虑了。
  所以接下来需要把指数和23比较，大于23的要继续左移，小于23的要右移
  */
  unsigned frac=(uf&0x007FFFFF)|0x00800000;

  if(E>30) return 0x80000000u;  //超出了int表示范围，这里包括了exp==0xFF即inf和NaN的情况；
  if(E<0) return 0x0;           //(0,1)区间的数

  if(E > 23) frac <<= (E-23);
  else frac >>= (23-E);

  if(sign>>31) return ~frac+1;  //负数需要取补码
  else return frac;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
/*
E=e-bias;阶码的范围是0~0xFF
val=(-1)^s*M*2^E, M为1+f，2的指数其实尾数部分f都是0，M==1，把阶码移动到正确位置即可。
*/
  int exp=x+127;
  if(exp<=0) return 0;
  if(exp>=255) return 0x7F800000;
  return exp<<23;
}
