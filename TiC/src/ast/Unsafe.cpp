#include <tic/ast/Unsafe.hpp>
#include <tic/ast/FunctionParameter.hpp>
#include <tic/ast/UnsafeVariable.hpp>
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <tic/Type.hpp>
#include <tic/ErrorHandler.hpp>
#include <tic/ast/UnsafeVariable.hpp>
#include <tic/Lexer.hpp>

// Taken from tibasic project
// http://tibasic.sourceforge.net/index.php
/// A two byte token (0xBB, 0x7E and SysVar)

/** SysVar **/
#define RADIAN          0x64
#define DEGREE          0x65
#define NORMAL          0x66
#define SCI             0x67
#define ENG             0x68
#define FLOAT           0x69
#define TEST_EQUAL      0x6A
#define TEST_LESSTHAN   0x6B
#define TEST_HIGHTHAN   0x6C
#define TEST_LOREQU     0x6D
#define TEST_GOREQU     0x6E
#define TEST_NOTEQUAL   0x6F
#define ADD             0x70
#define SUBTRACT        0x71
#define ANSWER          0x72
#define FIX             0x73
#define HORIZ           0x74
#define FULL            0x75
#define FUNC            0x76
#define PARAM           0x77
#define POLAR           0x78
#define SEQ             0x79
#define INDPNTAUTO      0x7A
#define INDPNTASK       0x7B
#define DEPENDAUTO      0x7C
#define DEPENDASK       0x7D

/** 7E VARIABLES, ie. graph manipulation **/
#define BOX             0x7F
#define DIVIDE          0x80
#define DOT             0x81
#define MULTIPLY        0x82
#define DIVIDE_SLASH    0x83
#define TRACE           0x84
#define CLRDRAW         0x85
#define ZSTANDARD       0x86
#define ZTRIG           0x87
#define ZBOX            0x88
#define ZOOMIN          0x89
#define ZOOMOUT         0x8A
#define ZSQUARE         0x8B
#define ZINTEGER        0x8C
#define ZPREVIOUS       0x8D
#define ZDECIMAL        0x8E
#define ZOOMSTAT        0x8F
#define ZOOMRCL         0x90
#define PRINTSCREEN     0x91
#define ZOOMSTO         0x92
#define TEXTFUNC        0x93
#define NPR             0x94
#define NCR             0x95
#define FNON            0x96
#define FNOFF           0x97
#define STOREPIC        0x98
#define RECALLPIC       0x99
#define STOREGDB        0x9A
#define RECALLGDB       0x9B
#define LINE            0x9C
#define VERTICAL        0x9D
#define PTON            0x9E
#define PTOFF           0x9F
#define PTCHANGE        0xA0
#define PXLON           0xA1
#define PXLOFF          0xA2
#define PXLCHANGE       0xA3
#define SHADE           0xA4
#define CIRCLE          0xA5
#define HORIZONTAL      0xA6
#define TANGENT         0xA7
#define DRAWINV         0xA8
#define DRAWF           0xA9
#define RAND            0xAB
#define PI              0xAC
#define GETKEY          0xAD
#define APOSTROPHE      0xAE
#define QUESTIONMARK    0xAF

/** SysVar **/
#define NEGATIVE        0xB0
#define CONV_INT        0xB1
#define ABS             0xB2
#define DETERMINANT     0xB3
#define IDENTITY        0xB4
#define DIM             0xB5
#define SUM             0xB6
#define PROD            0xB7
#define NOT             0xB8
#define IPART           0xB9
#define FPART           0xBA

/** BB tokens **/
#define SQR_ROOT        0xBC
#define CUBE_ROOT       0xBD
#define NATLOG          0xBE
#define ETOPOWER        0xBF
#define LOGARITHM       0xC0
#define POWER10         0xC1
#define SINE            0xC2
#define INVSIN          0xC3
#define COSINE          0xC4
#define INVCOSINE       0xC5
#define TANGENT_TRIG    0xC6
#define INVTANGENT      0xC7
#define HYP_SINE        0xC8
#define HYP_ISINE       0xC9
#define HYP_COSINE      0xCA
#define HYP_ICOSINE     0xCB
#define HYP_TANGENT     0xCC
#define HYP_ITANGENT    0xCD
#define LOGIC_IF        0xCE
#define LOGIC_THEN      0xCF
#define LOGIC_ELSE      0xD0
#define CTL_WHILE       0xD1
#define CTL_REPEAT      0xD2
#define CTL_FOR         0xD3
#define CTL_END         0xD4
#define CTL_RETURN      0xD5
#define LABEL           0xD6
#define CTL_GOTO        0xD7
#define CTL_PAUSE       0xD8
#define CTL_STOP        0xD9
#define INCSKIPIFHIGH   0xDA
#define DECSKIPIFLOW    0xDB
#define INPUT           0xDC
#define PROMPT          0xDD
#define DISP            0xDE
#define DISPGRAPH       0xDF
#define OUTPUT          0xE0
#define CLRHOME         0xE1
#define FILL            0xE2
#define SORTA           0xE3
#define SORTD           0xE4
#define DISPTABLE       0xE5
#define MENU            0xE6
#define SEND            0xE7
#define GET             0xE8
#define PLOTSON         0xE9
#define PLOTSOFF        0xEA
#define PLOT1           0xEC
#define PLOT2           0xED
#define PLOT3           0xEE
#define POWEROF         0xF0
#define XTHROOT         0xF1
#define VARSTATS_1      0xF2
#define VARSTATS_2      0xF3
#define LINREG1         0xF4
#define EXPREG          0xF5
#define LNREG           0xF6
#define PWRREG          0xF7
#define MEDMED          0xF8
#define QUADREG         0xF9
#define CLRLIST         0xFA
#define CLRTABLE        0xFB
#define HISTOGRAM       0xFC
#define XYLINE          0xFD
#define SCATTER         0xFE
#define LINREG2         0xFF

/** SYSTEM VARIABLES **/

// Matrices
#define MAT_A           0x005C
#define MAT_B           0x015C
#define MAT_C           0x025C
#define MAT_D           0x035C
#define MAT_E           0x045C
#define MAT_F           0x055C
#define MAT_G           0x065C
#define MAT_H           0x075C
#define MAT_I           0x085C
#define MAT_J           0x095C

// Lists
#define L1              0x005D
#define L2              0x015D
#define L3              0x025D
#define L4              0x035D
#define L5              0x045D
#define L6              0x055D
#define L7              0x065D
#define L8              0x075D
#define L9              0x085D
#define L0              0x095D

// Graph (function)
#define Y1              0x105E
#define Y2              0x115E
#define Y3              0x125E
#define Y4              0x135E
#define Y5              0x145E
#define Y6              0x155E
#define Y7              0x165E
#define Y8              0x175E
#define Y9              0x185E
#define Y0              0x195E

// Graph (parametric)
#define X1T             0x205E
#define Y1T             0x215E
#define X2T             0x225E
#define Y2T             0x235E
#define X3T             0x245E
#define Y3T             0x255E
#define X4T             0x265E
#define Y4T             0x275E
#define X5T             0x285E
#define Y5T             0x295E
#define X6T             0x2A5E
#define Y6T             0x2B5E

// Graph (polar)
#define R1              0x405E
#define R2              0x415E
#define R3              0x425E
#define R4              0x435E
#define R5              0x445E
#define R6              0x455E
#define SYSVAR_U        0x805E
#define SYSVAR_V        0x815E

// Pictures
#define PIC1            0x0060
#define PIC2            0x0160
#define PIC3            0x0260
#define PIC4            0x0360
#define PIC5            0x0460
#define PIC6            0x0560
#define PIC7            0x0660
#define PIC8            0x0760
#define PIC9            0x0860
#define PIC0            0x0960

// Graph databases
#define GDB1            0x0061
#define GDB2            0x0161
#define GDB3            0x0261
#define GDB4            0x0361
#define GDB5            0x0461
#define GDB6            0x0561
#define GDB7            0x0661
#define GDB8            0x0761
#define GDB9            0x0861
#define GDB0            0x0961

// Stat data
#define REGEQ           0x0162
#define STAT_N          0x0262
#define MEANX           0x0362
#define SUMX            0x0462
#define SUMXSQUARED     0x0562
#define SX              0x0662
#define SIGMAX          0x0762
#define MINX            0x0862
#define MAXX            0x0962
#define MINY            0x0A62
#define MAXY            0x0B02
#define MEANY           0x0C62
#define SUMY            0x0D62
#define SUMYSQUARED     0x0E62
#define SY              0x0F62
#define SIGMAY          0x1062
#define SUMXY           0x1162
#define SYSVAR_R        0x1262
#define MED             0x1362
#define Q1              0x1462
#define Q3              0x1562
#define SYSVAR_A        0x1662
#define SYSVAR_B        0x1762
#define SYSVAR_C        0x1862
#define SYSVAR_D        0x1962
#define SYSVAR_E        0x1A62
#define X1              0x1B62
#define X2              0x1C62
#define X3              0x1D62
#define Y1_1            0x1E62
#define Y2_1            0x1F62
#define Y3_1            0x2062
#define SYSVAR_N        0x2162
#define SYSVAR_P        0x2262
#define SYSVAR_Z        0x2362
#define SYSVAR_T        0x2462
#define CHISQUARED      0x2562
#define FIN             0x2662
#define DF              0x2762
#define PHAT            0x2862
#define PHAT1           0x2962
#define PHAT2           0x2A62
#define MEANX1          0x2B62
#define SX1             0x2C62
#define N1              0x2D62
#define MEANX2          0x2E62
#define SX2             0x2F62
#define N2              0x3062
#define SXP             0x3162
#define LOWER           0x3262
#define UPPER           0x3362
#define SYSVAR_S        0x3462
#define RSQUARED        0x3562
#define CAPRSQUARED     0x3662
#define DF2             0x3762 // not sure about this one
#define SS              0x3862
#define MS              0x3962
#define DF3             0x3A62 // again here?
#define SS1             0x3B62 // another double
#define MS1             0x3C62 //   "       "

// Graph data
#define ZXSCL           0x0063
#define ZYSCL           0x0163
#define XSCL            0x0263
#define YSCL            0x0363
#define UNSTART         0x0463
#define VNSTART         0x0563
#define UNINVERSE       0x0663
#define VNINVERSE       0x0763
#define ZUNSTART        0x0863
#define ZVNSTART        0x0963
#define XMIN            0x0A63
#define XMAX            0x0B63
#define YMIN            0x0C63
#define YMAX            0x0D63
#define TMIN            0x0E63
#define TMAX            0x0F63
#define THETAMIN        0x1063
#define THETAMAX        0x1163
#define ZXMIN           0x1263
#define ZXMAX           0x1363
#define ZYMIN           0x1463
#define ZYMAX           0x1563
#define ZTHETAMIN       0x1663
#define ZTHETAMAX       0x1763
#define ZTMIN           0x1863
#define ZTMAX           0x1963
#define TBLMIN          0x1A63
#define NMIN            0x1B63
#define ZNMIN           0x1C63
#define NMAX            0x1D63
#define ZNMAX           0x1E63
#define NSTART          0x1F63
#define ZNSTART         0x2063
#define DELTATABLE      0x2163
#define TSTEP           0x2263
#define THETASTEP       0x2363
#define ZTSTEP          0x2463
#define ZTHETASTEP      0x2563
#define DELTAX          0x2663
#define DELTAY          0x2763
#define XFACT           0x2863
#define YFACT           0x2963
#define TBLINPUT        0x2A63
#define SYSVAR_CAPN     0x2B63
#define IPERCENT        0x2C63
#define PV              0x2D63
#define PMT             0x2E63
#define FV              0x2F63
#define XRES            0x3063
#define ZXRES           0x3163

// Strings
#define STR1            0x00AA
#define STR2            0x01AA
#define STR3            0x02AA
#define STR4            0x03AA
#define STR5            0x04AA
#define STR6            0x05AA
#define STR7            0x06AA
#define STR8            0x07AA
#define STR9            0x08AA
#define STR0            0x09AA

/** 7E VARIABLES **/
#define SEQUENTIAL_7E   0x007E
#define SIMUL           0x017E
#define POLARGC         0x027E
#define RECTGC          0x037E
#define COORDON         0x047E
#define COORDOFF        0x057E
#define CONNECTED       0x067E
#define DOT_7E          0x077E
#define AXESON          0x087E
#define AXESOFF         0x097E
#define GRIDON          0x0A7E
#define GRIDOFF         0x0B7E
#define LABELON         0x0C7E
#define LABELOFF        0x0D7E
#define WEB             0x0E7E
#define TIME            0x0F7E
#define UVAXES          0x107E
#define VWAXES          0x117E
#define UWAXES          0x127E

/** BB VARIABLES **/
#define NPV             0x00BB
#define IRR             0x01BB
#define BAL             0x02BB
#define SUMPRN          0x03BB
#define SUMINT          0x04BB
#define TONOM           0x05BB
#define TOEFF           0x06BB
#define DBD             0x07BB
#define LCM             0x08BB
#define GCD             0x09BB
#define RANDINT         0x0ABB
#define RANDBIN         0x0BBB
#define SUB             0x0CBB
#define STDDEV          0x0DBB
#define VARIANCE        0x0EBB
#define INSTRING        0x0FBB
#define NORMALCDF       0x10BB
#define INVNORM         0x11BB
#define TCDF            0x12BB
#define XSQUCDF         0x13BB
#define FCDF            0x14BB
#define BINOMPDF        0x15BB
#define BINOMCDF        0x16BB
#define POISSONPDF      0x17BB
#define POISSONCDF      0x18BB
#define GEOMETPDF       0x19BB
#define GEOMETCDF       0x1ABB
#define NORMALPDF       0x1BBB
#define TPDF            0x1CBB
#define XSQUPDF         0x1DBB
#define FPDF            0x1EBB
#define RANDNORM        0x1FBB
#define TVM_PMT         0x20BB
#define TVM_I_PERCENT   0x21BB
#define TVM_PV          0x22BB
#define TVM_N           0x23BB
#define TVM_FV          0x24BB
#define CONJ            0x25BB
#define REAL            0x26BB
#define IMAG            0x27BB
#define ANGLE           0x28BB
#define CUMSUM          0x29BB
#define EXPR            0x2ABB
#define LENGTH          0x2BBB
#define DELTA_LIST      0x2CBB
#define REF             0x2DBB
#define RREF            0x2EBB
#define TORECT          0x2FBB
#define TOPOLAR         0x30BB
#define VAR_E           0x31BB
#define SINREG          0x32BB
#define LOGISTIC        0x33BB
#define LINREGTTEST     0x34BB
#define SHADENORM       0x35BB
#define SHADE_T         0x36BB
#define SHADEXSQU       0x37BB
#define SHADEF          0x38BB
#define MATRTOLIST      0x39BB
#define LISTTOMATR      0x3ABB
#define ZTEST           0x3BBB
#define TTEST           0x3CBB
#define TWO_SAMPZTEST   0x3DBB
#define ONE_PROPZTEST   0x3EBB
#define TWO_PROPZTEST   0x3FBB
#define XSQUTEST        0x40BB
#define ZINTERVAL       0x41BB
#define TWO_SAMPZINT    0x42BB
#define ONE_PROPZINT    0x43BB
#define TWO_PROPZINT    0x44BB
#define GRAPHSTYLE      0x45BB
#define TWO_SAMPTTEST   0x46BB
#define TWO_SAMPFTEST   0x47BB
#define TINTERVAL       0x48BB
#define TWO_SAMPTINT    0x49BB
#define SETUPEDITOR     0x4ABB
#define PMT_END         0x4BBB
#define PMT_BGN         0x4CBB
#define REAL_BB         0x4DBB
#define REPOWTHETAI     0x4EBB
#define APLUSBI         0x4FBB
#define EXPRON          0x50BB
#define EXPROFF         0x51BB
#define CLRALLLISTS     0x52BB
#define GETCALC         0x53BB
#define DELVAR          0x54BB
#define EQUTOSTRING     0x55BB
#define STRINGTOEQU     0x56BB
#define CLEARENTRIES    0x57BB
#define SELECT          0x58BB
#define ANOVA           0x59BB
#define MODBOXPLOT      0x5ABB
#define NORMPROBPLOT    0x5BBB

struct TwoByte {
    unsigned short data;
    const char* text;
};

struct TwoByte CalcVars[] = {
    // AsmPrgm (uncompiled)
    { 0x6CBB,           "AsmPrgm"   },
    { 0x6DBB,           "AsmPrgm"   }, // this means decompilation works, but compilation won't hit this

    // SysVar
    { MAT_A,            "[A]"       },
    { MAT_B,            "[B]"       },
    { MAT_C,            "[C]"       },
    { MAT_D,            "[D]"       },
    { MAT_E,            "[E]"       },
    { MAT_F,            "[F]"       },
    { MAT_G,            "[G]"       },
    { MAT_H,            "[H]"       },
    { MAT_I,            "[I]"       },
    { MAT_J,            "[J]"       },
    { L1,               "L1"        },
    { L2,               "L2"        },
    { L3,               "L3"        },
    { L4,               "L4"        },
    { L5,               "L5"        },
    { L6,               "L6"        },
    { L7,               "L7"        },
    { L8,               "L8"        },
    { L9,               "L9"        },
    { L0,               "L0"        },
    { Y1,               "Y1"        },
    { Y2,               "Y2"        },
    { Y3,               "Y3"        },
    { Y4,               "Y4"        },
    { Y5,               "Y5"        },
    { Y6,               "Y6"        },
    { Y7,               "Y7"        },
    { Y8,               "Y8"        },
    { Y9,               "Y9"        },
    { Y0,               "Y0"        },
    { X1T,              "X1T"       },
    { Y1T,              "Y1T"       },
    { X2T,              "X2T"       },
    { Y2T,              "Y2T"       },
    { X3T,              "X3T"       },
    { Y3T,              "Y3T"       },
    { X4T,              "X4T"       },
    { Y4T,              "Y4T"       },
    { X5T,              "X5T"       },
    { Y5T,              "Y5T"       },
    { X6T,              "X6T"       },
    { Y6T,              "Y6T"       },
    { R1,               "R1"        },
    { R2,               "R2"        },
    { R3,               "R3"        },
    { R4,               "R4"        },
    { R5,               "R5"        },
    { R6,               "R6"        },
    { SYSVAR_U,         "[u]"       },
    { SYSVAR_V,         "[v]"       },
    { PIC1,             "PIC1"      },
    { PIC2,             "PIC2"      },
    { PIC3,             "PIC3"      },
    { PIC4,             "PIC4"      },
    { PIC5,             "PIC5"      },
    { PIC6,             "PIC6"      },
    { PIC7,             "PIC7"      },
    { PIC8,             "PIC8"      },
    { PIC9,             "PIC9"      },
    { PIC0,             "PIC0"      },
    { GDB1,             "GDB1"      },
    { GDB2,             "GDB2"      },
    { GDB3,             "GDB3"      },
    { GDB4,             "GDB4"      },
    { GDB5,             "GDB5"      },
    { GDB6,             "GDB6"      },
    { GDB7,             "GDB7"      },
    { GDB8,             "GDB8"      },
    { GDB9,             "GDB9"      },
    { GDB0,             "GDB0"      },
    // finally, StatVars
    { SX1,              "Sx1"       },
    { SX2,              "Sx2"       },
    { SXP,              "Sxp"       },
    { REGEQ,            "RegEq"     },
    { STAT_N,           "[n]"       },
    { MEANX,            "mean(x)"   },
    { SUMXSQUARED,      "sum(x)^2"  },
    { SUMX,             "sum(x)"    },
    { SX,               "Sx"        },
    { SIGMAX,           "[sigma]x"  },
    { MINX,             "minX"      },
    { MAXX,             "maxX"      },
    { MINY,             "minY"      },
    { MAXY,             "maxY"      },
    { MEANY,            "mean(y)"   },
    { SUMYSQUARED,      "sum(y)^2"  },
    { SUMY,             "sum(y)"    },
    { SY,               "Sy"        },
    { SIGMAY,           "[sigma]y"  },
    { SUMXY,            "sum(xy)"   },
    { SYSVAR_R,         "[r]"       },
    { MED,              "Med"       },
    { Q1,               "Q1"        },
    { Q3,               "Q3"        },
    { SYSVAR_A,         "[a]"       },
    { SYSVAR_B,         "[b]"       },
    { SYSVAR_C,         "[c]"       },
    { SYSVAR_D,         "[d]"       },
    { SYSVAR_E,         "[stat_e]"  }, // because '[e]' refers to the constant e
    { X1,               "x1"        },
    { X2,               "x2"        },
    { X3,               "x3"        },
    { Y1_1,             "y1"        },
    { Y2_1,             "y2"        },
    { Y3_1,             "y3"        },
    { SYSVAR_N,         "[n]"       }, // somebody please tell me why there are so many variations on n
    { SYSVAR_P,         "[p]"       },
    { SYSVAR_Z,         "[z]"       },
    { SYSVAR_T,         "[t]"       },
    { CHISQUARED,       "[chi]^2"   },
    { FIN,              "[fin]"     },
    { DF,               "[df]"      },
    { PHAT,             "[p^]"      },
    { PHAT1,            "[p^1]"     },
    { PHAT2,            "[p^2]"     },
    { MEANX1,           "mean(x1)"  },
    { N1,               "[n1]"      },
    { MEANX2,           "mean(x2)"  },
    { N2,               "[n2]"      },
    { LOWER,            "[lower]"   },
    { UPPER,            "[upper]"   },
    { SYSVAR_S,         "[s]"       },
    { RSQUARED,         "r^2"       },
    { CAPRSQUARED,      "R^2"       },
    { DF2,              "[df]"      }, // somebody was high when they invented the token tables
    { SS,               "SS"        },
    { DF3,              "[df]"      }, // see previous comment
    { SS1,              "SS"        }, // again...
    { MS1,              "MS"        }, // and again!
    // graph data
    { ZXSCL,            "ZXscl"     },
    { ZYSCL,            "ZYscl"     },
    { XSCL,             "Xscl"      },
    { YSCL,             "Yscl"      },
    { ZUNSTART,         "ZUnStart"  },
    { ZVNSTART,         "ZVnStart"  },
    { UNSTART,          "UnStart"   },
    { VNSTART,          "VnStart"   },
    { UNINVERSE,        "Un-1"      }, // i read a ^-1, but it's actually a -1...
    { VNINVERSE,        "Vn-1"      }, // same as above
    { ZXMIN,            "ZXmin"     },
    { ZXMAX,            "ZXmax"     },
    { ZYMIN,            "ZYmin"     },
    { ZYMAX,            "ZYmax"     },
    { ZTHETAMIN,        "Ztheta_min"},
    { ZTHETAMAX,        "Ztheta_max"},
    { ZTMIN,            "ZTmin"     },
    { ZTMAX,            "ZTmax"     },
    { XMIN,             "Xmin"      },
    { XMAX,             "Xmax"      },
    { YMIN,             "Ymin"      },
    { YMAX,             "Ymax"      },
    { TMIN,             "Tmin"      },
    { TMAX,             "Tmax"      },
    { THETAMIN,         "theta_min" },
    { THETAMAX,         "theta_max" },
    { TBLMIN,           "TblMin"    },
    { ZNMIN,            "ZnMin"     },
    { NMIN,             "nMin"      },
    { ZNMAX,            "ZnMax"     },
    { NMAX,             "nMax"      },
    { ZNSTART,          "ZnStart"   },
    { NSTART,           "nStart"    },
    { DELTATABLE,       "delta_Tbl" },
    { ZTSTEP,           "ZTstep"    },
    { ZTHETASTEP,       "Ztheta_step"},
    { TSTEP,            "Tstep"     },
    { THETASTEP,        "theta_step"},
    { DELTAX,           "delta_X"   },
    { DELTAY,           "delta_Y"   },
    { XFACT,            "XFact"     },
    { YFACT,            "YFact"     },
    { TBLINPUT,         "TblInput"  },
    // finance app
    { SYSVAR_CAPN,      "[N]"       }, // this is the N in the Finance app
    { IPERCENT,         "I%"        },
    { PV,               "PV"        },
    { PMT,              "PMT"       },
    { FV,               "FV"        },
    { ZXRES,            "ZXres"     },
    { XRES,             "Xres"      },
    // strings
    { STR1,             "STR1"      },
    { STR2,             "STR2"      },
    { STR3,             "STR3"      },
    { STR4,             "STR4"      },
    { STR5,             "STR5"      },
    { STR6,             "STR6"      },
    { STR7,             "STR7"      },
    { STR8,             "STR8"      },
    { STR9,             "STR9"      },
    { STR0,             "STR0"      },
    // 7E Variables
    { SEQ,              "Sequential"    },
    { SIMUL,            "Simul"         },
    { POLARGC,          "PolarGC"       },
    { RECTGC,           "RectGC"        },
    { COORDON,          "CoordOn"       },
    { COORDOFF,         "CoordOff"      },
    { CONNECTED,        "Connected"     },
    { DOT_7E,           "Dot"           },
    { AXESON,           "AxesOn"        },
    { AXESOFF,          "AxesOff"       },
    { GRIDON,           "GridOn"        },
    { GRIDOFF,          "GridOff"       },
    { LABELON,          "LabelOn"       },
    { LABELOFF,         "LabelOff"      },
    { WEB,              "Web"           },
    { TIME,             "Time"          },
    { UVAXES,           "uvAxes"        },
    { VWAXES,           "vwAxes"        },
    { UWAXES,           "uwAxes"        },
    // BB Variables
    { NPV,              "npv("          },
    { IRR,              "irr("          },
    { BAL,              "bal("          },
    { SUMPRN,           "sum_prn("      },
    { SUMINT,           "sum_int("      },
    { TONOM,            "->Nom"         },
    { TOEFF,            "->Eff"         },
    { DBD,              "dbd("          },
    { LCM,              "lcm("          },
    { GCD,              "gcd("          },
    { RANDINT,          "RandInt("      },
    { RANDBIN,          "RandBin("      },
    { SUB,              "sub("          },
    { STDDEV,           "StdDev("       },
    { VARIANCE,         "variance("     },
    { INSTRING,         "inString("     },
    { NORMALCDF,        "normalcdf("    },
    { INVNORM,          "invNorm("      },
    { TCDF,             "tcdf("         },
    { XSQUCDF,          "x^2cdf("       },
    { FCDF,             "fcdf("         },
    { BINOMPDF,         "binompdf("     },
    { BINOMCDF,         "binomcdf("     },
    { POISSONPDF,       "poissonpdf("   },
    { POISSONCDF,       "poissoncdf("   },
    { GEOMETPDF,        "geometpdf("    },
    { GEOMETCDF,        "geometcdf("    },
    { NORMALPDF,        "normalpdf("    },
    { TPDF,             "tpdf("         },
    { XSQUPDF,          "x^2pdf("       },
    { FPDF,             "fpdf("         },
    { RANDNORM,         "RandNorm("     },
    { TVM_PMT,          "tvm_pmt"       },
    { TVM_I_PERCENT,    "tvm_i%"        },
    { TVM_PV,           "tvm_PV"        },
    { TVM_N,            "tvm_N"         },
    { TVM_FV,           "tvm_FV"        },
    { CONJ,             "conj("         },
    { REAL,             "real("         },
    { IMAG,             "imag("         },
    { ANGLE,            "angle("        },
    { CUMSUM,           "cumSum("       },
    { EXPR,             "expr("         },
    { LENGTH,           "length("       },
    { DELTA_LIST,       "delta_List("   },
    { REF,              "ref("          },
    { RREF,             "rref("         },
    { TORECT,           "->Rect"        },
    { TOPOLAR,          "->Polar"       },
    { VAR_E,            "[e]"           }, // e by itself is impossible, and dangerous (imagine Disp "Hello"!)
    { SINREG,           "SinReg "       },
    { LOGISTIC,         "Logistic "     },
    { LINREGTTEST,      "LinRegTTest "  },
    { SHADENORM,        "ShadeNorm("    },
    { SHADE_T,          "Shade_t("      },
    { SHADEXSQU,        "Shade_x^2("    },
    { SHADEF,           "ShadeF("       },
    { MATRTOLIST,       "Matr->list"    },
    { LISTTOMATR,       "List->matr"    },
    { ZTEST,            "Z-Test("       },
    { TTEST,            "T-Test "       },
    { TWO_SAMPZTEST,    "2-SampZTest("  },
    { ONE_PROPZTEST,    "1-PropZTest("  },
    { TWO_PROPZTEST,    "2-PropZTest("  },
    { XSQUTEST,         "x^2_test("     },
    { ZINTERVAL,        "ZInterval"     },
    { TWO_SAMPZINT,     "2-SampZInt("   },
    { ONE_PROPZINT,     "1-PropZInt("   },
    { TWO_PROPZINT,     "2-PropZInt("   },
    { GRAPHSTYLE,       "GraphStyle("   },
    { TWO_SAMPTTEST,    "2-SampTTest "  },
    { TWO_SAMPFTEST,    "2-SampFTest_"  },
    { TINTERVAL,        "TInterval "    },
    { TWO_SAMPTINT,     "2-SampTInt "   },
    { SETUPEDITOR,      "SetUpEditor "  },
    { PMT_END,          "PMT_End"       },
    { PMT_BGN,          "PMT_Bgn"       },
    { REAL_BB,          "Real"          },
    { REPOWTHETAI,      "re^[theta]i"   },
    { APLUSBI,          "a+bi"          },
    { EXPRON,           "ExprOn"        },
    { EXPROFF,          "ExprOff"       },
    { CLRALLLISTS,      "ClrAllLists"   },
    { GETCALC,          "GetCalc("      },
    { DELVAR,           "DelVar "       },
    { EQUTOSTRING,      "Equ->String("  },
    { STRINGTOEQU,      "String->Equ("  },
    { CLEARENTRIES,     "Clear Entries" },
    { SELECT,           "Select("       },
    { ANOVA,            "ANOVA("        },
    { MODBOXPLOT,       "ModBoxPlot"    },
    { NORMPROBPLOT,     "NormProbPlot"  },
};

using std::cout;
using std::endl;

namespace tic
{
namespace ast 
{
Unsafe::Unsafe(const std::string &name)
    : Function(name, "Unsafe", NodeType::Unsafe)
{

}
Unsafe::~Unsafe()
{
    
}
void Unsafe::appendContent(const std::string &content)
{
    using namespace boost;
    
    typedef tokenizer<char_separator<char>> tokenizer;
    char_separator<char> sep("\t", "+-*/,=:;)({}\n\" ><");
    tokenizer tok(content, sep);
    
    Type::TypeEnum type = Type::NO_TYPE;
    
    for(auto token = tok.begin(); token != tok.end(); ++token)
    {
        // Detect if this can possibly be a variable.
        if(Lexer::isValidVarName(*token, true))
        {
            type = isUnsafeVariable(*token);
            if(type == Type::NO_TYPE) {
                // This is an error!
                errorHandler->handleError(Error("The variable \"" + *token + "\" in the unsafe block \"" + functionName() + "\" is no valid tibasic variable!", debugInfo()));
            } else {
                if(!variableAlreadyDefined(*token)) {
                    auto var = std::make_unique<UnsafeVariable>(type, *token);
                    var->setDebugInfo(m_debugInfo);
                    push_back(std::move(var));
                }
            }
        }
    }
    
    m_content.append(content);
}
void Unsafe::setContent(const std::string &content)
{
    m_content.clear();
    appendContent(content);
}
Type::TypeEnum Unsafe::isUnsafeVariable(const std::string &str)
{
    if(str.length() == 1)       // Register
    {
        if(std::isalpha(str[0])) {
            if(std::isupper(str[0])) {
                return Type::NUMBER;
            }
        }
    } 
    if(str.length() == 3) {     // Matrix
        if(str == "[A]"
            || str == "[B]"
            || str == "[C]"
            || str == "[D]"
            || str == "[E]"
            || str == "[F]"
            || str == "[G]"
            || str == "[H]"
            || str == "[I]"
            || str == "[J]"
        ) {
            return Type::MATRIX;
        }
    }
    if(str.length() == 2) {     // List
        if(str == "L1"
            || str == "L2"
            || str == "L3"
            || str == "L4"
            || str == "L5"
            || str == "L6"
        ) {
            return Type::LIST;
        }
    }
    if(str.length() == 4) {     // String
        if(str == "STR0"
            || str == "STR1"
            || str == "STR2"
            || str == "STR3"
            || str == "STR4"
            || str == "STR5"
            || str == "STR6"
            || str == "STR7"
            || str == "STR8"
            || str == "STR9"
        ) {
            return Type::STRING;
        }
    }
    // Check if the given variable is the same as any other variable of the list above. 
    for(std::size_t i = 0; i < 302; ++i) 
    {
        if(CalcVars[i].text == str) {
            return Type::UNKNOWN;
        }
    }
    // Could not find any variable like the one specified. 
    return Type::NO_TYPE;
}
bool Unsafe::variableAlreadyDefined(const std::string &str)
{
    for(auto var : *this)
    {
        if(boost::static_pointer_cast<UnsafeVariable>(var)->variable() == str) {
            return true;
        }
    }
    return false;
}
void Unsafe::loadContentFromFile(const std::string &path)
{
    using namespace std;
    cout << "Trying to load \"" << path << "\" as a tibasic unsafe file." << endl;
    ifstream file(path);
    
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) 
        {
            appendContent(line);
        }
    } else {
        cout << "Loading of \"" << path << "\" failed!" << endl;
    }
}
void Unsafe::loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current, ast::List &rootList)
{
    bool end = false;
    
    // Parsing flags. 
    bool unsafeHead = true;
    bool parameterList = true;
    bool varAssign = false;
    
    for(auto it = current; it != tokens.end() && !end; ++it)
    {
        switch(it->first)
        {
            case TokenType::PARAM_LIST_BEGIN:
                if(unsafeHead) {
                    parameterList = true;
                }
                break;
            case TokenType::PARAM_LIST_END:
                parameterList = false;
                break;
            case TokenType::TYPE:
            {
                if(parameterList) {
                    auto param = std::make_unique<FunctionParameter>(it->second, "");
                    param->setDebugInfo(it->toDebugInfo());
                    m_parameters.push_back(std::move(param));
                }
                break;
            }
            case TokenType::VAR_NAME:
            {
                if(parameterList) {
                    if(varAssign) {
                        boost::static_pointer_cast<FunctionParameter>(m_parameters.back())->setAssignedVarName(it->second);
                        varAssign = false;
                    } else {
                        boost::static_pointer_cast<FunctionParameter>(m_parameters.back())->setVarName(it->second);
                    }
                } 
                break;
            }
            case TokenType::PARAM_ITEM_ASSIGN:
            {
                varAssign = true;
                break;
            }
            case TokenType::STRING_LITERAL:
            {
                if(!parameterList) {
                    // Because the string literal is outside of the parameter list, a file has to be loaded. 
                }
            }
            case TokenType::UNSAFE_CONTENT:
            {
                appendContent(it->second);
                break;
            }
            case TokenType::UNSAFE_SCOPE_END:
            {
                end = true;
                break;
            }
        }
    }
}
const std::string& Unsafe::content()
{
    return m_content;
}
}
}