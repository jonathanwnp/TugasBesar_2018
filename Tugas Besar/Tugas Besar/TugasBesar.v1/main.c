#include "header.h"

void main()
{
	ListParent L; 
	Pegawai Peg;
	Properti Prop;
	adrParent P;
	adrChild C;
	int menu, submenu, nip = 0, noproperti = 0, carinip, harga, carinoproperti, delnip;
	string nama, notelepon, jenis, alamat;
	
	CreateEmpty(&L);
	
	do
	{
		system("cls");
		printf("\n\n\t\t\t\tREAL ESTATE XYZ");
		printf("\n\n\t\t1. INPUT SALES");
		printf("\n\t\t2. INPUT PROPERTI");
		printf("\n\t\t3. JUAL PROPERTI");
		printf("\n\t\t4. PENGUNDURUAN SALES");
		printf("\n\t\t5. TAMPIL LAPORAN");
		printf("\n\t\tMasukkan menu pilihan anda : ");scanf("%d", &menu);
		switch(menu)
		{
			case 1:
				system("cls");
				printf("\n\n\t\t\t\tREAL ESTATE XYZ");
				printf("\n\n\t\t\t==========INPUT SALES==========");
				printf("\n\n\t\tSilakan masukkan data sales : ");
				if(!isEmpty(L))
				{
					nip = countPegawai(L) + 1;
				}
				else
				{
					nip++;
				}
				printf("\n\t\t\tNIP\t: %d", nip);
				printf("\n\t\t\tNama\t: ");fflush(stdin);gets(nama);
				printf("\t\t\tNo Telepon\t: ");fflush(stdin);gets(notelepon);
				Peg = konstraktorPegawai(nip, nama, notelepon,0);
				insertLastParent(&L, Peg);
				
				break;
			case 2: 
				system("cls");
				printf("\n\n\t\t\t\tREAL ESTATE XYZ");
				printf("\n\n\t\t\t==========INPUT PROPERTI==========");
				if(!isEmpty(L))
				{
					do
					{
						printf("\n\n\t\tPilih sales yang ingin diberi tanggungan properti berdasar nip : ");scanf("%d", &carinip);
						P = findParent(L, carinip);
						if(P==NULL)
						{
							printf("\n\t\tPegawai yang anda cari tidak terdaftar. Silakan coba lagi");
						}
					}while(P==NULL);
					
					printf("\n\n\t\tSilakan masukkan data sales : ");
					if(!HaveChild(P))
					{
						noproperti++;
					}
					else 
					{
						noproperti = countProperti(L, carinip) + 1;
					}
					printf("\n\t\t\tNomor Properti\t: %d", noproperti);
					do
					{
						printf("\n\t\t\tJenis\t: ");fflush(stdin);gets(jenis);
						if(strcmpi(jenis,"Tanah")==0 && strcmpi(jenis,"Rumah")==0)
						{
								printf("\n\t\t\tSilakan masukkan Tanah atau Rumah");
						}
					}while(strcmpi(jenis,"Tanah")==0 && strcmpi(jenis,"Rumah")==0);
					printf("\t\t\tAlamat\t: ");fflush(stdin);gets(alamat);
					printf("\t\t\tHarga\t: ");scanf("%d", &harga);
					Prop = konstraktorProperti(noproperti, jenis, alamat, harga);
					insertLastChild(&L, carinip, Prop);
				}
				else
				{
					printf("\n\n\t\tInputkan sales terlebih dahulu");
				}
				break;
			case 3: 
				system("cls");
				printf("\n\n\t\t\t\tREAL ESTATE XYZ");
				printf("\n\n\t\t\t==========PENJUALAN==========");
				do
				{
					printf("\n\n\t\tPilih sales : ");scanf("%d", &carinip);
					P = findParent(L, carinip);
					if(P==NULL)
					{
						printf("\n\t\tPegawai yang anda cari tidak terdaftar. Silakan coba lagi");
					}
				}while(P==NULL);
				do
				{
					printf("\n\n\t\tPilih properti : ");scanf("%d", &carinoproperti);
					C = findChild(L, carinip, carinoproperti);
					if(C==NULL)
					{
						printf("\n\t\tProperti yang anda cari tidak terdaftar. Silakan coba lagi");
					}
				}while(C==NULL);
				penjualanProperti(&L, carinip, carinoproperti);
				break;
			case 4: 
				system("cls");
				printf("\n\n\t\t\t\tREAL ESTATE XYZ");
				printf("\n\n\t\t\t==========PENGUNDURAN DIRI==========");
				if(L.first->nextParent == NULL)
				{
					printf("\n\t\tHanya ada 1 pegawai.");
				}
				else
				{
					do
					{
						printf("\n\n\t\tPilih sales yang akan keluar: ");scanf("%d", &delnip);
						P = findParent(L, delnip);
						if(P==NULL)
						{
							printf("\n\t\tPegawai yang anda cari tidak terdaftar. Silakan coba lagi");
						}
					}while(P==NULL);
					do
					{
						printf("\n\n\t\tPilih sales yang akan diberi tanggungan : ");scanf("%d", &carinip);
						P = findParent(L, carinip);
						if(P==NULL)
						{
							printf("\n\t\tPegawai yang anda cari tidak terdaftar. Silakan coba lagi");
						}
					}while(P==NULL);
					pindahProperti(&L, delnip, carinip);
				}
				break;
			case 5: 
				system("cls");
				printf("\n\n\t\t\t\tREAL ESTATE XYZ");
				printf("\n\n\t\t\t==========TAMPIL LAPORAN==========");
				printf("\n\n\t\t1. DAFTAR SALES");
				printf("\n\t\t2. DAFTAR PROPERTI YANG BELUM TERJUAL");
				printf("\n\t\t3. JUMLAH PROPERTI ");
				printf("\n\n\t\tSilakan pilih data laporan apa yang ingin ditampilkan : ");scanf("%d", &submenu);
				switch(submenu)
				{
					case 1 : 
						printAll(L);
						break;
					case 2 : 
						printPropertiBelumTerjual(L);
						break;
					case 3 : 
						printProperti(L);
						break;
				}
				
				break;
		}getch();
	}while(menu!=0);
}
