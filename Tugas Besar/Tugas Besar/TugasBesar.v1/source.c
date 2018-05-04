#include "header.h"


//Fungsi List
void CreateEmpty(ListParent *L)
{
	(*L).first=NULL;
}

int isEmpty(ListParent L)
{
	if(L.first==NULL)
		return 1;
	else
		return 0;
}

//Fungsi Parent
int isUnique(ListParent L, int nip) //optional
{
	adrParent P = L.first;
	while(P!=NULL)
	{
		if(P->Peg.nip == nip)
		{
			return 0;
		}
		P = P->nextParent;
	}
	return 1;
}

int countPegawai(ListParent L)
{
	adrParent P = L.first;
	int count = 0;
	while(P!=NULL)
	{
		 count++;
		 P = P->nextParent;
	}
	return count;
}

Pegawai konstraktorPegawai(int nip, string nama, string telepon,int total_penjualan)
{
	Pegawai peg;
	peg.nip = nip;
	strcpy(peg.nama, nama);
	strcpy(peg.telepon, telepon);
	peg.total_penjualan = total_penjualan;
	return peg;
}

int HaveChild(adrParent Peg)
{
	if(Peg->firstChild!=NULL)
		return 1;
	else
		return 0;
}

adrParent alokasiPegawai(Pegawai pegawai)
{
	adrParent P;
	P = (adrParent) malloc(sizeof(Parent));
	P->Peg = pegawai; 
	P->nextParent=NULL;
	P->firstChild=NULL;
	return P;
}

adrParent findParent(ListParent L, int nip)
{
	adrParent P = L.first;
	while(P!=NULL && P->Peg.nip!=nip)
	{
		P = P->nextParent;
	}
	return P;
}

void insertFirstParent(ListParent *L, Pegawai pegawai)
{
	adrParent P;
	P = alokasiPegawai(pegawai);
	P->nextParent = (*L).first;
	(*L).first = P;
}

void insertLastParent(ListParent *L, Pegawai pegawai)
{
	adrParent P, last;
	if(isEmpty(*L))
	{
		insertFirstParent(&(*L), pegawai);
	}
	else
	{
		P = alokasiPegawai(pegawai);
		last = (*L).first;
		while(last->nextParent!=NULL)
		{
			last = last->nextParent;
		}
		last->nextParent = P;
	}
}

void deleteFirstParent(ListParent *L)
{
	adrParent del;
	if(isEmpty(*L))
	{
		printf("Tidak ada pegawai");
	}
	else
	{
		del = (*L).first;
		(*L).first = (*L).first->nextParent;
		free(del);
	}
}

void deleteLastParent(ListParent *L)
{
	adrParent del, temp;
	if(isEmpty(*L))
	{
		printf("Tidak ada pegawai");
	}
	else
	{
		if((*L).first->nextParent == NULL)
		{
			deleteFirstParent(&(*L));
		}
		else
		{
			temp = (*L).first;
			while(temp->nextParent->nextParent!=NULL)
			{
				temp = temp->nextParent;
			}
			del = temp->nextParent;
			temp->nextParent = NULL;
			free(del);
		}
	}
}

void deleteAtParent(ListParent *L, int nip)
{
	adrParent P, del;
	int  temp;
	del = findParent((*L), nip);

	if(del == (*L).first)
	{
		deleteFirstParent(&(*L));
	}
	else if(del->nextParent==NULL)
	{
		deleteLastParent(&(*L));
	}
	else
	{
		P = (*L).first;
		while(P->nextParent!=NULL && P->nextParent!=del)
		{
			P = P->nextParent;
		}
		del = P->nextParent;
		P->nextParent = P->nextParent->nextParent;
		free(del);
	}
		
}

void printAll(ListParent L)
{
	adrParent P;
	adrChild C;
	P = L.first;
	while(P!=NULL)
	{
		printf("\n\n\t\t\tSALES");
		printf("\n\t\t\t->NIP\t: %d", P->Peg.nip);
		printf("\n\t\t\t->Nama\t: %s", P->Peg.nama);
		printf("\n\t\t\t->No Telepon\t: %s", P->Peg.telepon);
		printf("\n\t\t\t->Total Penjualan\t: %d", P->Peg.total_penjualan);
		printf("\n\t\t\t\tPROPERTI : ");
		if(HaveChild(P))
		{
			C=P->firstChild;
			printChild(C);
		}
		else
		{
			printf("\n\t\t\t\tBelum punya tanggungan properti");
		}
		P = P->nextParent;
	}
}


//Fungsi Child
int countProperti(ListParent L, int nip)
{
	adrParent P;
	adrChild C;
	int count = 0;
	P = findParent(L, nip);
	C = P->firstChild;
	while(C!=NULL)
	{
		count++;
		C = C->nextChild;
	}
	return count;
}

Properti konstraktorProperti(int nomor_properti, string jenis, string alamat, int harga)
{
	Properti prop; 
	prop.nomor_properti = nomor_properti;
	strcpy(prop.jenis, jenis);
	strcpy(prop.alamat, alamat);
	prop.harga = harga;
	return prop;
}

adrChild alokasiProperti(Properti properti)
{
	adrChild C;
	C = (adrChild) malloc(sizeof(Child));
	C->Prop = properti;
	C->nextChild = NULL;
	return C;
}

adrChild findChild(ListParent L, int nip, int nomor_properti)
{
	adrParent P;
	adrChild C;
	P = findParent(L, nip);
	C = P->firstChild;
	while(C!=NULL && C->Prop.nomor_properti != nomor_properti)
	{
		C = C->nextChild;
	}
	return C;
}

void insertFirstChild(ListParent *L, int nip, Properti properti)
{
	adrParent P; 
	adrChild C;
	P = findParent((*L), nip);
	C = alokasiProperti(properti);
	C->nextChild = P->firstChild;
	P->firstChild = C;
}

void insertLastChild(ListParent *L, int nip, Properti properti)
{
	adrParent P;
	adrChild C, last;
	P = findParent((*L), nip);
	if(!HaveChild(P))
	{
		insertFirstChild(&(*L), nip, properti);
	}
	else
	{
		C = alokasiProperti(properti);
		last = P->firstChild;
		while(last->nextChild!=NULL)
		{
			last = last->nextChild;
		}
		last->nextChild = C;
	}
}

void deleteFirstChild(ListParent *L, int nip)
{
	adrParent P;
	adrChild del;
	P = findParent((*L), nip);
	del = P->firstChild;
	P->firstChild=P->firstChild->nextChild;
	free(del);
}

void deleteLastChild(ListParent *L, int nip)
{
	adrParent P;
	adrChild del, temp;
	P = findParent((*L), nip);
	if(P->firstChild->nextChild == NULL)
	{
		deleteFirstChild(&(*L), nip);
	}
	else
	{
		temp = P->firstChild;
		while(temp->nextChild->nextChild!=NULL)
		{
			temp = temp->nextChild;
		}
		del = temp->nextChild;
		temp->nextChild = temp->nextChild->nextChild;
		free(del);
	}
}

void deleteAtChild(ListParent *L, int nip, int nomor_properti)
{
	adrParent P;
	adrChild del, C;
	P = findParent((*L), nip);
	del = findChild((*L), nip, nomor_properti);
	if(del == P->firstChild)
	{
		deleteFirstChild(&(*L), nip);
	}
	else if(del->nextChild == NULL)
	{
		deleteLastChild(&(*L),nip);
	}
	else
	{
		C = P->firstChild;
		while(C->nextChild!=NULL && C->nextChild != del)
		{
			C = C->nextChild;
		}
		del = C->nextChild;
		C->nextChild = C->nextChild->nextChild;
		free(del);
	}
}

void printChild(adrChild Prop)
{
	if(Prop!=NULL)
	{
		while(Prop!=NULL)
		{
			printf("\n");
			printf("\n\t\t\t\t\t->Nomor Properti\t: %d", Prop->Prop.nomor_properti);
			printf("\n\t\t\t\t\t->Jenis\t\t: %s", Prop->Prop.jenis);
			printf("\n\t\t\t\t\t->Alamat\t\t: %s", Prop->Prop.alamat);
			printf("\n\t\t\t\t\t->Harga\t\t: %d", Prop->Prop.harga);
			
			Prop = Prop->nextChild;
		}
	}
}

void penjualanProperti(ListParent *L, int nip, int nomor_properti)
{
	adrParent P;
	adrChild C;
	int tampung;
	P = findParent((*L), nip);
	C = findChild((*L), nip, nomor_properti);
	tampung = C->Prop.harga;
	P->Peg.total_penjualan = P->Peg.total_penjualan + tampung;
	deleteAtChild(&(*L), nip, nomor_properti);
}

void pindahProperti(ListParent *L, int nip, int nip_pindah)
{
	adrParent P;
	adrChild C, pindah;
	Properti prop;
	P = findParent((*L), nip);
	//C = findChild((*L), nip, nomor_properti);
	C = P->firstChild;
	while(C!=NULL)
	{
		prop = konstraktorProperti(C->Prop.nomor_properti, C->Prop.jenis, C->Prop.alamat, C->Prop.harga); 
		pindah = alokasiProperti(prop);
		insertFirstChild(&(*L), nip_pindah, prop);
		C = C->nextChild;
	}
	
	P = findParent((*L), nip);
	C = P->firstChild;
	while(C!=NULL)
	{
		deleteFirstChild(&(*L), nip);
		C = C->nextChild;
	}
	deleteAtParent(&(*L), nip);
}

void printPropertiBelumTerjual(ListParent L)
{
	adrParent P;
	adrChild C;
	int nip;
	printf("\n\n\t\tMasukkan NIP sales yang ingin dilihat : ");scanf("%d",&nip);
	P = findParent(L, nip);
	printf("\n\n\t\t\tSALES");
	printf("\n\t\t\t->NIP\t: %d", P->Peg.nip);
	printf("\n\t\t\t->Nama\t: %s", P->Peg.nama);
	printf("\n\t\t\t\tPROPERTI : ");
	if(HaveChild(P))
	{
		C=P->firstChild;
		printChild(C);
	}
	else 
	{
		if(P->Peg.total_penjualan > 0)
		{
			printf("\n\t\t\t\tSemua properti sudah terjual");
		}
		else
		{
			printf("\n\t\t\t\tbelum ada tanggungan properti");
		}
	}
}

void printProperti(ListParent L)
{
	adrParent P;
	adrChild C;
	int tanah = 0 , rumah = 0;
	P = L.first;
	while(P!=NULL)
	{
		if(HaveChild(P))
		{
			C = P->firstChild;
			while(C!=NULL)
			{
				if(strcmpi(C->Prop.jenis, "tanah")==0)
				{
					tanah++;
				}
				else if(strcmpi(C->Prop.jenis, "rumah")==0)
				{
					rumah++;
				}
				C = C->nextChild;
			}
		}
		P = P->nextParent;
	}
	printf("\n\t\t\t\tJumlah properti yang belum terjual");
	printf("\n\t\t\t\t\tRumah\t=\t%d",rumah);
	printf("\n\t\t\t\t\tTanah\t=\t%d",tanah);
}


//fungsi file handling
void save(ListParent *L);
void load(ListParent *L);



//fungsi tampil

void tampilError(int code);

