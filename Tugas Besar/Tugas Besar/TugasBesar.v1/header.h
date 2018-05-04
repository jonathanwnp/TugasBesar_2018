#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <string.h>

typedef char string[20];

typedef struct tChild* adrChild;
typedef struct tParent* adrParent;

typedef struct
{
	int nomor_properti;
	string jenis;
	string alamat;
	int harga;
}Properti;

typedef struct
{
	int nip;
	string nama;
	string telepon;
	int total_penjualan;
}Pegawai;

typedef struct tChild
{
	Properti Prop;
	adrChild nextChild;
}Child;

typedef struct tParent 
{
	Pegawai Peg;
	adrParent nextParent;
	adrChild firstChild;
}Parent;

typedef struct
{
	adrParent first;
}ListParent;


//Fungsi List
void CreateEmpty(ListParent *L);
int isEmpty(ListParent L);

//Fungsi Parent
int isUnique(ListParent L, int nip); //optional
int countPegawai(ListParent L);
Pegawai konstraktorPegawai(int nip, string nama, string telepon,int total_penjualan);
int HaveChild(adrParent Peg);
adrParent alokasiPegawai(Pegawai pegawai);
adrParent findParent(ListParent L, int nip);
void insertFirstParent(ListParent *L, Pegawai pegawai);
void insertLastParent(ListParent *L, Pegawai pegawai);
void deleteFirstParent(ListParent *L);
void deleteLastParent(ListParent *L);
void deleteAtParent(ListParent *L, int nip);
void printAll(ListParent L);


//Fungsi Child
int countProperti(ListParent L, int nip);
Properti konstraktorProperti(int nomor_properti, string jenis, string alamat, int harga);
adrChild alokasiProperti(Properti properti);
adrChild findChild(ListParent L, int nip, int nomor_properti);
void insertFirstChild(ListParent *L, int nip, Properti properti);
void insertLastChild(ListParent *L, int nip, Properti properti);
void deleteFirstChild(ListParent *L, int nip);
void deleteLastChild(ListParent *L, int nip);
void deleteAtChild(ListParent *L, int nip, int nomor_properti);
void printChild(adrChild Prop);
void penjualanProperti(ListParent *L, int nip, int nomor_properti);
void pindahProperti(ListParent *L, int nip, int nip_pindah);
void printPropertiBelumTerjual(ListParent L);
void printProperti(ListParent L);


//fungsi file handling
void save(ListParent *L);
void load(ListParent *L);
