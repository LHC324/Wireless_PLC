#include "Chinese_code.h"


unsigned char code ChineseTable[][2]=
{
	"标","定","开","关","参","数","配","置","时","间","行",
	"模","拟","请","输","入","密","码","新","确","认","修",
	"改","成","功","失","败","主","界","面","本","地","连",
	"接","远","程","通","信","方","式","启","停","波","特",
	"率","设","串","口","恢","复","出","厂","是","否","等",
};

unsigned char code Chinese_code_12x12[]= 
{
0x88,0x68,0xFF,0x48,0x10,0x92,0x12,0xF2,0x12,0x92,0x10,0x00,0x00,0x00,0x0F,0x00,0x02,0x01,0x08,0x0F,0x00,0x00,0x03,0x00,/*"标",0*/

0x2C,0x24,0xA4,0x24,0x25,0xE6,0x24,0x24,0x24,0x24,0x2C,0x00,0x08,0x04,0x03,0x04,0x08,0x0F,0x09,0x09,0x09,0x09,0x08,0x00,/*"定",1*/

0x40,0x42,0x42,0xFE,0x42,0x42,0x42,0xFE,0x42,0x42,0x40,0x00,0x00,0x08,0x06,0x01,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,/*"开",2*/

0x40,0x48,0x49,0x4A,0x48,0xF8,0x48,0x4A,0x49,0x48,0x40,0x00,0x08,0x08,0x04,0x02,0x01,0x00,0x01,0x02,0x04,0x08,0x08,0x00,/*"关",3*/

0x90,0x54,0xB6,0x95,0x5C,0x54,0x34,0x94,0x36,0x54,0x90,0x00,0x00,0x0A,0x0A,0x0A,0x0A,0x09,0x05,0x04,0x04,0x02,0x00,0x00,/*"参",4*/

0x48,0x2A,0x98,0x7F,0x28,0x4A,0x10,0xEF,0x08,0xF8,0x08,0x00,0x09,0x0B,0x05,0x05,0x0B,0x00,0x08,0x05,0x02,0x05,0x08,0x00,/*"数",5*/

0xFA,0x4A,0x3E,0x0A,0x3E,0x4A,0xFA,0x00,0xE2,0x22,0x3E,0x00,0x0F,0x05,0x05,0x05,0x05,0x05,0x0F,0x00,0x07,0x08,0x0E,0x00,/*"配",6*/

0x10,0x17,0xD5,0x55,0x57,0x7D,0x57,0x55,0xD5,0x17,0x10,0x00,0x08,0x08,0x0F,0x08,0x08,0x0E,0x08,0x08,0x0F,0x08,0x08,0x00,/*"置",7*/

0xFE,0x22,0x22,0xFE,0x00,0x08,0x48,0x88,0x08,0xFF,0x08,0x00,0x07,0x02,0x02,0x07,0x00,0x00,0x00,0x09,0x08,0x0F,0x00,0x00,/*"时",8*/

0x00,0xF9,0x02,0xF8,0x49,0x49,0x49,0x49,0xF9,0x01,0xFF,0x00,0x00,0x0F,0x00,0x03,0x02,0x02,0x02,0x02,0x0B,0x08,0x0F,0x00,/*"间",9*/

0x48,0x24,0xF2,0x09,0x10,0x12,0x12,0x12,0xF2,0x12,0x10,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x08,0x08,0x0F,0x00,0x00,0x00,/*"行",10*/

0x88,0x68,0xFF,0x48,0x02,0xFA,0xAF,0xAA,0xAF,0xFA,0x02,0x00,0x00,0x00,0x0F,0x00,0x0A,0x0A,0x06,0x03,0x06,0x0A,0x0A,0x00,/*"模",11*/

0x88,0xFF,0x48,0x00,0xFE,0x00,0x82,0x0C,0xE0,0x1F,0x00,0x00,0x08,0x0F,0x00,0x00,0x03,0x09,0x04,0x03,0x00,0x03,0x0C,0x00,/*"拟",12*/

0x11,0xF2,0x00,0x22,0xEA,0xAA,0xBF,0xAA,0xAA,0xEA,0x22,0x00,0x00,0x0F,0x04,0x00,0x0F,0x02,0x02,0x02,0x0A,0x0F,0x00,0x00,/*"请",13*/

0x34,0x2C,0xF7,0xA4,0xE8,0xA4,0xEA,0x09,0xCA,0x04,0xE8,0x00,0x01,0x01,0x0F,0x00,0x0F,0x02,0x0F,0x00,0x03,0x08,0x0F,0x00,/*"输",14*/

0x00,0x00,0x01,0x81,0x72,0x0C,0x70,0x80,0x00,0x00,0x00,0x00,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x00,/*"入",15*/

0x46,0x32,0x82,0xB2,0x46,0x6B,0x52,0x4A,0x62,0x12,0x66,0x00,0x00,0x0E,0x08,0x08,0x08,0x0F,0x08,0x08,0x08,0x0E,0x00,0x00,/*"密",16*/

0x42,0xF2,0x2E,0xE2,0x01,0x3D,0x21,0x21,0x21,0x3F,0xE0,0x00,0x00,0x07,0x02,0x07,0x01,0x01,0x01,0x01,0x09,0x08,0x07,0x00,/*"码",17*/

0x20,0xAA,0xB2,0xE3,0xB2,0xAA,0x00,0xFE,0x12,0xF2,0x11,0x00,0x04,0x02,0x08,0x0F,0x00,0x0A,0x04,0x03,0x00,0x0F,0x00,0x00,/*"新",18*/

0x42,0xF2,0x2E,0xE2,0x00,0xF4,0x53,0xF2,0x5A,0x56,0xF0,0x00,0x00,0x07,0x02,0x07,0x08,0x07,0x01,0x07,0x01,0x09,0x0F,0x00,/*"确",19*/

0x10,0x11,0xF2,0x00,0x00,0x00,0xC0,0x3F,0xC0,0x00,0x00,0x00,0x00,0x00,0x07,0x02,0x09,0x06,0x01,0x00,0x01,0x06,0x08,0x00,/*"认",20*/

0x10,0xFC,0x03,0xF8,0x10,0x94,0x8B,0x4A,0x2A,0x96,0x10,0x00,0x00,0x0F,0x00,0x03,0x08,0x0A,0x0A,0x09,0x05,0x04,0x02,0x00,/*"修",21*/

0xE2,0x22,0x22,0x3E,0x20,0x10,0xEF,0x08,0x88,0x78,0x08,0x00,0x0F,0x04,0x02,0x01,0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00,/*"改",22*/

0x00,0xFC,0x24,0x24,0xE4,0x04,0xFF,0x04,0x85,0x66,0x04,0x00,0x08,0x07,0x00,0x02,0x0B,0x04,0x02,0x01,0x02,0x04,0x0F,0x00,/*"成",23*/

0x04,0x04,0xFC,0x04,0x04,0x08,0xFF,0x08,0x08,0x08,0xF8,0x00,0x02,0x02,0x01,0x09,0x05,0x03,0x00,0x00,0x08,0x08,0x07,0x00,/*"功",24*/

0xA0,0x90,0x8E,0x88,0x88,0xFF,0x88,0x88,0x88,0x80,0x80,0x00,0x08,0x08,0x04,0x02,0x01,0x00,0x01,0x02,0x04,0x08,0x08,0x00,/*"失",25*/

0xFE,0x02,0xFA,0x02,0xFE,0x10,0xEC,0x0B,0x08,0xF8,0x08,0x00,0x09,0x04,0x03,0x04,0x09,0x08,0x05,0x02,0x05,0x08,0x08,0x00,/*"败",26*/

0x00,0x88,0x88,0x88,0x89,0xFA,0x88,0x88,0x88,0x88,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x0F,0x08,0x08,0x08,0x08,0x08,0x00,/*"主",27*/

0x80,0x9F,0x95,0x55,0x55,0x3F,0x55,0x55,0x95,0x9F,0x80,0x00,0x00,0x08,0x04,0x03,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,/*"界",28*/

0x02,0xF2,0x12,0x12,0xFA,0x56,0x52,0xF2,0x12,0x12,0xF2,0x00,0x00,0x0F,0x04,0x04,0x07,0x05,0x05,0x07,0x04,0x04,0x0F,0x00,/*"面",29*/

0x04,0x04,0x84,0x64,0x14,0xFF,0x14,0x64,0x84,0x04,0x04,0x00,0x02,0x01,0x02,0x02,0x02,0x0F,0x02,0x02,0x02,0x01,0x02,0x00,/*"本",30*/

0x10,0x10,0xFF,0x10,0x20,0xFC,0x10,0xFF,0x08,0x84,0xFC,0x00,0x04,0x04,0x03,0x02,0x00,0x07,0x08,0x09,0x08,0x08,0x0E,0x00,/*"地",31*/

0x21,0xE2,0x00,0x04,0x34,0x2C,0x27,0xF4,0x24,0x24,0x04,0x00,0x08,0x07,0x08,0x09,0x09,0x09,0x09,0x0F,0x09,0x09,0x09,0x00,/*"连",32*/

0x88,0x88,0xFF,0x48,0xA4,0xAC,0xB5,0xE6,0xB4,0xAC,0xA4,0x00,0x00,0x08,0x0F,0x00,0x08,0x0A,0x0B,0x04,0x04,0x0B,0x08,0x00,/*"接",33*/

0x21,0xE2,0x00,0x10,0x12,0xF2,0x12,0x12,0xF2,0x12,0x10,0x00,0x08,0x07,0x08,0x0A,0x09,0x08,0x08,0x08,0x09,0x0A,0x0B,0x00,/*"远",34*/

0x12,0xD2,0xFE,0x51,0x80,0x2F,0x29,0xE9,0x29,0x2F,0x00,0x00,0x01,0x00,0x0F,0x00,0x08,0x09,0x09,0x0F,0x09,0x09,0x08,0x00,/*"程",35*/

0x11,0xF2,0x00,0xF9,0xA9,0xAB,0xFD,0xAD,0xAB,0xF8,0x00,0x00,0x08,0x07,0x08,0x0B,0x08,0x08,0x0B,0x08,0x0A,0x0B,0x08,0x00,/*"通",36*/

0x10,0xFC,0x03,0x04,0x54,0x54,0x55,0x56,0x54,0x54,0x04,0x00,0x00,0x0F,0x00,0x00,0x0F,0x05,0x05,0x05,0x05,0x0F,0x00,0x00,/*"信",37*/

0x04,0x04,0x04,0xFC,0x25,0x26,0x24,0x24,0x24,0xE4,0x04,0x00,0x08,0x04,0x03,0x00,0x00,0x00,0x08,0x08,0x08,0x07,0x00,0x00,/*"方",38*/

0x08,0x48,0x48,0xC8,0x48,0x48,0x08,0xFF,0x08,0x09,0x0A,0x00,0x08,0x08,0x08,0x07,0x04,0x04,0x04,0x00,0x03,0x04,0x0E,0x00,/*"式",39*/

0x00,0x00,0xFC,0xA4,0xA4,0xA5,0xA6,0xA4,0xA4,0xA4,0xBC,0x00,0x08,0x06,0x01,0x0F,0x04,0x04,0x04,0x04,0x04,0x04,0x0F,0x00,/*"启",40*/

0x20,0x10,0xFC,0x03,0x82,0xBA,0xAA,0xAB,0xAA,0xBA,0x82,0x00,0x00,0x00,0x0F,0x00,0x01,0x02,0x0A,0x0E,0x02,0x02,0x01,0x00,/*"停",41*/

0x22,0x44,0x00,0xFC,0x24,0xE4,0x24,0x3F,0x24,0xE4,0x0C,0x00,0x04,0x02,0x08,0x07,0x08,0x08,0x05,0x02,0x05,0x08,0x08,0x00,/*"波",42*/

0x9C,0x88,0xFF,0x48,0x10,0x54,0x54,0x5F,0xF4,0x54,0x50,0x00,0x00,0x00,0x0F,0x00,0x00,0x01,0x0A,0x08,0x0F,0x00,0x00,0x00,/*"特",43*/

0x02,0x8A,0x52,0x9A,0xD6,0xB3,0xD2,0x8A,0x52,0x8A,0x02,0x00,0x02,0x02,0x02,0x02,0x02,0x0F,0x02,0x02,0x02,0x02,0x02,0x00,/*"率",44*/

0x10,0x11,0xF2,0x00,0x50,0xCF,0x41,0x41,0x4F,0xD0,0x10,0x00,0x00,0x00,0x07,0x02,0x08,0x08,0x05,0x02,0x05,0x08,0x08,0x00,/*"设",45*/

0xC0,0x5E,0x52,0x52,0x52,0xFF,0x52,0x52,0x52,0x5E,0xC0,0x00,0x07,0x02,0x02,0x02,0x02,0x0F,0x02,0x02,0x02,0x02,0x07,0x00,/*"串",46*/

0x00,0xFE,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x07,0x00,0x00,/*"口",47*/

0x78,0x00,0xFF,0x08,0xC4,0x3F,0xC4,0x04,0xF4,0x44,0x24,0x00,0x00,0x00,0x0F,0x04,0x03,0x08,0x04,0x02,0x01,0x06,0x08,0x00,/*"恢",48*/

0x04,0x02,0x7D,0xD5,0x55,0x55,0x55,0x55,0x55,0x7D,0x01,0x00,0x00,0x0A,0x09,0x0B,0x05,0x05,0x05,0x05,0x0B,0x09,0x08,0x00,/*"复",49*/

0x80,0x1E,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x1E,0x80,0x00,0x07,0x04,0x04,0x04,0x04,0x07,0x04,0x04,0x04,0x04,0x0F,0x00,/*"出",50*/

0x00,0xFE,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x08,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"厂",51*/

0x40,0x40,0x5F,0x55,0x55,0xD5,0x55,0x55,0x5F,0x40,0x40,0x00,0x08,0x04,0x03,0x04,0x08,0x0F,0x09,0x09,0x09,0x09,0x08,0x00,/*"是",52*/

0x11,0x91,0x89,0x89,0x85,0xBF,0x81,0x85,0x85,0x89,0x11,0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x0F,0x00,0x00,/*"否",53*/

0x44,0x53,0x52,0x56,0x52,0x7C,0x53,0xD2,0x56,0x52,0x42,0x00,0x01,0x01,0x03,0x05,0x01,0x09,0x09,0x0F,0x01,0x01,0x01,0x00,/*"等",54*/

}; 

//纵向取模，字节倒叙 
unsigned char code Ascii_table_5x8[95][5]={
/*全体ASCII 列表:5x8点阵*/
0x00,0x00,0x00,0x00,0x00,//- -   //space
0x00,0x00,0x4f,0x00,0x00,//-!-
0x00,0x07,0x00,0x07,0x00,//-"-
0x14,0x7f,0x14,0x7f,0x14,//-#-
0x24,0x2a,0x7f,0x2a,0x12,//-$-
0x23,0x13,0x08,0x64,0x62,//-%-
0x36,0x49,0x55,0x22,0x50,//-&-
0x00,0x05,0x07,0x00,0x00,//-'-
0x00,0x1c,0x22,0x41,0x00,//-(-
0x00,0x41,0x22,0x1c,0x00,//-)-
0x14,0x08,0x3e,0x08,0x14,//-*-
0x08,0x08,0x3e,0x08,0x08,//-+-
0x00,0x50,0x30,0x00,0x00,//-,-
0x08,0x08,0x08,0x08,0x08,//---
0x00,0x60,0x60,0x00,0x00,//-.-
0x20,0x10,0x08,0x04,0x02,//-/-
0x3e,0x51,0x49,0x45,0x3e,//-0-
0x00,0x42,0x7f,0x40,0x00,//-1-
0x42,0x61,0x51,0x49,0x46,//-2-
0x21,0x41,0x45,0x4b,0x31,//-3-	   
0x18,0x14,0x12,0x7f,0x10,//-4-
0x27,0x45,0x45,0x45,0x39,//-5-
0x3c,0x4a,0x49,0x49,0x30,//-6-
0x01,0x71,0x09,0x05,0x03,//-7-
0x36,0x49,0x49,0x49,0x36,//-8-
0x06,0x49,0x49,0x29,0x1e,//-9-
0x00,0x36,0x36,0x00,0x00,//-:-
0x00,0x56,0x36,0x00,0x00,//-;-
0x08,0x14,0x22,0x41,0x00,//-<-
0x14,0x14,0x14,0x14,0x14,//-=-
0x00,0x41,0x22,0x14,0x08,//->-
0x02,0x01,0x51,0x09,0x06,//-?-
0x32,0x49,0x79,0x41,0x3e,//-@-
0x7e,0x11,0x11,0x11,0x7e,//-A-
0x7f,0x49,0x49,0x49,0x36,//-B-
0x3e,0x41,0x41,0x41,0x22,//-C-
0x7f,0x41,0x41,0x22,0x1c,//-D-
0x7f,0x49,0x49,0x49,0x41,//-E-
0x7f,0x09,0x09,0x09,0x01,//-F-
0x3e,0x41,0x49,0x49,0x7a,//-G-
0x7f,0x08,0x08,0x08,0x7f,//-H-
0x00,0x41,0x7f,0x41,0x00,//-I-
0x20,0x40,0x41,0x3f,0x01,//-J-
0x7f,0x08,0x14,0x22,0x41,//-K-
0x7f,0x40,0x40,0x40,0x40,//-L-
0x7f,0x02,0x0c,0x02,0x7f,//-M-
0x7f,0x04,0x08,0x10,0x7f,//-N-
0x3e,0x41,0x41,0x41,0x3e,//-O-
0x7f,0x09,0x09,0x09,0x06,//-P-
0x3e,0x41,0x51,0x21,0x5e,//-Q-
0x7f,0x09,0x19,0x29,0x46,//-R-
0x46,0x49,0x49,0x49,0x31,//-S-
0x01,0x01,0x7f,0x01,0x01,//-T-
0x3f,0x40,0x40,0x40,0x3f,//-U-
0x1f,0x20,0x40,0x20,0x1f,//-V-
0x3f,0x40,0x38,0x40,0x3f,//-W-
0x63,0x14,0x08,0x14,0x63,//-X-
0x07,0x08,0x70,0x08,0x07,//-Y-
0x61,0x51,0x49,0x45,0x43,//-Z-
0x00,0x7f,0x41,0x41,0x00,//-[-
0x02,0x04,0x08,0x10,0x20,//-\-
0x00,0x41,0x41,0x7f,0x00,//-]-
0x04,0x02,0x01,0x02,0x04,//-^-
0x40,0x40,0x40,0x40,0x40,//-_-
0x01,0x02,0x04,0x00,0x00,//-`-
0x20,0x54,0x54,0x54,0x78,//-a-
0x7f,0x48,0x48,0x48,0x30,//-b-
0x38,0x44,0x44,0x44,0x44,//-c-
0x30,0x48,0x48,0x48,0x7f,//-d-
0x38,0x54,0x54,0x54,0x58,//-e-
0x00,0x08,0x7e,0x09,0x02,//-f-
0x48,0x54,0x54,0x54,0x3c,//-g-
0x7f,0x08,0x08,0x08,0x70,//-h-
0x00,0x00,0x7a,0x00,0x00,//-i-
0x20,0x40,0x40,0x3d,0x00,//-j-
0x7f,0x20,0x28,0x44,0x00,//-k-
0x00,0x41,0x7f,0x40,0x00,//-l-
0x7c,0x04,0x38,0x04,0x7c,//-m-
0x7c,0x08,0x04,0x04,0x78,//-n-
0x38,0x44,0x44,0x44,0x38,//-o-
0x7c,0x14,0x14,0x14,0x08,//-p-
0x08,0x14,0x14,0x14,0x7c,//-q-
0x7c,0x08,0x04,0x04,0x08,//-r-
0x48,0x54,0x54,0x54,0x24,//-s-
0x04,0x04,0x3f,0x44,0x24,//-t-
0x3c,0x40,0x40,0x40,0x3c,//-u-
0x1c,0x20,0x40,0x20,0x1c,//-v-
0x3c,0x40,0x30,0x40,0x3c,//-w-
0x44,0x28,0x10,0x28,0x44,//-x-
0x04,0x48,0x30,0x08,0x04,//-y-
0x44,0x64,0x54,0x4c,0x44,//-z-
0x08,0x36,0x41,0x41,0x00,//-{-
0x00,0x00,0x77,0x00,0x00,//-|-
0x00,0x41,0x41,0x36,0x08,//-}-
0x04,0x02,0x02,0x02,0x01,//-~-
};

//手指箭头图标  16*12
unsigned char finger[]=
{
		0xF8,0xF8,0x10,0x10,0x08,0x04,0x04,0x02,0x4A,0xC9,0x4D,0x4A,0x48,0x48,0x68,0x30,0x03,0x03,0x01,0x01,0x01,0x01,0x01,0x01,
		0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"手指箭头",0*/
};

//圆点图标	16*12
unsigned char dot[] = 
{	  
		0x00,0x00,0x00,0x00,0xF0,0xF8,0xFC,0xFC,0xFC,0xFC,0xF8,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,
		0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,/*"圆点",0*/
};

//左小旗图标 5*8
unsigned char Iconleft[] = 
{
		0x08,0x1C,0x3E,0x7F,0x00,/*"左小旗",0*/
};

//右小旗图标 5*8
unsigned char IconRight[] = 
{
		0x00,0x7F,0x3E,0x1C,0x08,/*"右小旗",0*/
};

unsigned char WhiteIcon[] = 
{
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char BlackIcon[] = 
{
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

//公司Logo 81*50
unsigned char Logo[] = 
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF0,0xF8,0xF8,0xF8,0xF8,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFE,
0xFE,0xFE,0xFC,0xFC,0xFC,0xFC,0xFC,0xF8,0xF8,0xF8,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xE0,
0xE0,0xF0,0xF0,0xF8,0xFC,0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0x3F,0x3F,0x3F,0x3F,0x1F,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3C,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x20,0x20,0x30,
0x18,0x18,0x0C,0x0E,0x0F,0x0F,0x07,0x07,0x07,0x03,0x03,0x03,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,
0xF0,0xF0,0xF0,0xF8,0xF8,0xF8,0xF8,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xF8,0xF8,0xF8,0xF0,0xF0,0xE0,0x00,
0x00,0x00,0x00,0x00,0x01,0x07,0x1F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,
0xC0,0x00,0x00,0x04,0x3F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,
0x7F,0x3F,0x3F,0x3F,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0xC0,0xC0,0xC0,
0xC0,0xE0,0xE0,0x70,0x30,0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC,0xFC,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,
0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFF,0xFF,
0x7F,0x3F,0x3F,0x1F,0x1F,0x0F,0x07,0x07,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x0F,0x1F,0x3F,0x3F,0x3F,0x7F,
0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F,0x3F,0x3F,0x3F,0x1F,0x1F,0x1F,0x0F,0x0F,0x07,
0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\logologo.bmp",0*/
};


//100*56
unsigned char PlcRun[] =
{
0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xE0,0xE0,0x20,0x20,
0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x7E,0xE6,0xC3,0x83,0x83,0xC3,0xEE,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x07,0x07,0x0F,0x0F,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x03,0x03,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0x07,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x07,
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\???.bmp",0*/
};

unsigned char PlcStop[] = 
{
	0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xC0,0xC0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x60,0x60,0x60,
0x60,0x60,0x60,0x60,0x60,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x60,0x60,0xE0,0xC0,0xC0,0xC0,0xC0,0x80,0x80,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x3F,0x71,0x61,0xC1,0xC1,0x61,0x77,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x03,0x03,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0F,0x0F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0x07,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x07,
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\???.bmp",0*/

};

/*南方电网logo*/
const unsigned char PowerGrid_Image[] = { /* 0X00,0X01,0X80,0X00,0X20,0X00, */
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFE,0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,
0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xC1,0xC1,0x81,0x83,0x83,0x07,0x07,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xFF,
0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0xFF,0xFF,
0xFF,0x07,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0x07,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0xFF,0xFF,
0xFF,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x00,0x00,0x00,0xF0,0xF0,0xF0,
0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
0xF0,0xF0,0x00,0x00,0x00,0x00,0xF8,0xF8,0x78,0x78,0x78,0x78,0x78,0xFF,0xFF,0xFF,
0x78,0x78,0x78,0x78,0xF8,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0x1F,0x1F,0x1F,0xDF,0xDF,0xDF,0x1F,0x1F,0x1F,0xDF,0xDF,0xDF,0x1F,0xFF,0xFF,0xFF,
0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,
0x1F,0x3F,0x3F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,
0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0xFF,
0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,
0xFF,0x00,0x03,0xE3,0xE3,0xE3,0xE3,0xFF,0xFF,0xFF,0xE3,0xE3,0xE3,0xE3,0x00,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0xFE,0xFE,0xFE,0x1E,0x1E,0x1E,0xFE,0xFE,0xFF,0x1F,
0x1F,0xFE,0xFE,0xFE,0x1E,0x1E,0xFE,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x78,0x78,0x78,0x78,0x78,0xFF,0xFF,0xFF,
0x78,0x78,0x78,0x78,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0x0E,0x1E,0xFE,0xFF,0xFF,0x1F,0x0C,0x3C,0xFC,0xFF,0xFF,0x07,0x00,0xFF,0xFF,0xFF,
0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xE0,0xE0,0xC0,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,
0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0xFF,
0xFF,0xFF,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0xFF,0xFF,
0xFF,0xC0,0xC0,0xC1,0xC1,0xC1,0xC1,0xFF,0xFF,0xFF,0xC1,0xF9,0xF9,0xF9,0xC0,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0xCF,0xCF,0xCF,0xCF,0xFF,0xFF,
0xFF,0xFF,0xCF,0xCF,0xCF,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0xF8,0xFF,0xFF,0x0F,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF,0xFF,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x78,0x78,0x78,0x78,0x78,0xFF,0xFF,0xFF,
0x78,0x78,0x78,0x78,0x7F,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0xF0,0xF8,0xFF,0x3F,0x3F,0x3F,0xF8,0xF8,0xFF,0x3F,0x7F,0xFE,0xF0,0xFF,0xFF,0xFF,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x03,0x03,
0x07,0x07,0x07,0x07,0x0F,0x0F,0x1F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,
0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
0xFF,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x03,0x03,0x03,0x03,0xFF,0xFF,
0xFF,0x03,0x03,0x03,0xF3,0xF0,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,
0xFC,0x3F,0x1F,0x0F,0x03,0x00,0x00,0x00,0x70,0x70,0x70,0x70,0x7F,0x7F,0x7F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xFC,0xFC,0xFC,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x00,0x00,0xF0,0xF0,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,
0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0x80,0x00,0x00,0x80,0x01,
0x01,0x81,0x00,0x00,0x80,0x00,0x80,0x80,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x80,0xC0,0xC0,0x80,
0x00,0x00,0xC0,0x00,0x00,0xC0,0xC0,0x00,0xC0,0xC0,0xC0,0xC0,0x00,0x80,0x80,0x00,
0x00,0x80,0x00,0x00,0xC1,0xC1,0xC1,0xC0,0x00,0x00,0xC0,0xC0,0xC0,0x80,0x00,0x00,
0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0x80,0x00,0x00,0x80,
0xC0,0xC0,0x80,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0xC1,0xC1,0xC1,
0xC1,0x01,0x01,0xC1,0xC1,0xC1,0x81,0x01,0x01,0x00,0x00,0x00,0x80,0xC0,0xC0,0x80,
0x00,0x00,0x80,0xC0,0xC0,0xC0,0x80,0x00,0x80,0x80,0x00,0xC0,0xC0,0xC0,0xC0,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xC0,0xC0,0x61,0x00,0x00,0xFF,0x04,
0x04,0xFF,0x00,0x00,0xFF,0x00,0xFF,0x0F,0x0E,0x78,0xFF,0x00,0xE0,0x7E,0x67,0x67,
0x7C,0xE0,0x00,0x00,0x00,0x63,0xC7,0xCC,0xFD,0x71,0x00,0x3F,0xE1,0xC0,0xC0,0x7F,
0x1E,0x00,0x7F,0xC0,0xC0,0xFF,0x3F,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x0C,
0x0C,0xFF,0x00,0x00,0xFF,0xCC,0xCC,0xCC,0x00,0x7F,0xFF,0x18,0x1C,0xFF,0xC0,0x00,
0xFF,0x07,0x1C,0xF8,0xFF,0x00,0x00,0x00,0xFF,0xFF,0x18,0x0F,0x07,0x00,0x3E,0xF3,
0xE1,0xE1,0xF3,0x3F,0x07,0xFE,0xF8,0x07,0x07,0xFC,0xFE,0x03,0x00,0xFF,0xCC,0xCC,
0xCC,0x00,0x00,0xFF,0x18,0x1C,0xFF,0xC0,0x00,0x00,0x00,0x3F,0xFF,0xC0,0xC8,0xF9,
0x30,0x00,0xFF,0x0C,0x0C,0x3C,0xE7,0x00,0xFF,0xFF,0x00,0xFF,0xC0,0xC0,0xF3,0x7F
};

