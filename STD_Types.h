#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char u8;
typedef unsigned short int u16;
typedef float f32;
typedef unsigned int u32;

typedef struct patient{
	u8 name[15];
	u32 age;
	u32 id;
	u8 gender;
	struct patient *next;
}St_Patient; 

typedef struct reservation{
	f32 time;
	u32 id;
	struct reservation *next;
}St_Reservation; 

	

#endif