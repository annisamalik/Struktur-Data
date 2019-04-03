#ifndef VARIABEL_H_INCLUDED
#define VARIABEL_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include<ctime>
#define next(p) (p)->next
#define info(p) (p)->info
#define prev(p) (p)->prev
#define relasi(p) (p)->relasi
#define first(L) ((L).first)
#define last(L) ((L).last)
#include <ctype.h>

using namespace std;

struct mhs {
    string Nama;
    string NIM;
    int Tingkat;
    float IP;
    int jum_sks;
};

struct mk {
    string Nama_MK;
    string Kode_MK;
    int tingkat;
    int sks;
    int jum_mhs;
};

typedef struct kotak_mhs *adr_mhs;
typedef struct kotak_mk *adr_mk;
typedef struct kotak_relasi *adr_r;

struct kotak_mhs {
    adr_mhs prev;
    mhs info;
    adr_r relasi;
    adr_mhs next;
};

struct kotak_mk {
    mk info;
    adr_mk next;
};

struct kotak_relasi {
    adr_mk info;
    adr_r next;
};

struct List_mhs {
    adr_mhs first;
    adr_mhs last;
};

struct List_mk {
    adr_mk first;
};

void buatlist_mhs(List_mhs &M);
void buatlist_mk (List_mk &MK);

adr_r find_thePrec(adr_mhs m, string kode);
adr_r find_theR(adr_mhs m, string kode);
adr_mk find_theMK(List_mk MK, string KODE);
adr_mhs find_theNIM(List_mhs M, string NIM);

adr_mk alokasi_mk(string nama, string kode);
adr_mhs alokasi_mhs(string nama, string nim, float ip);
adr_r alokasi_r(adr_mk mk);

void dealokasi_m(adr_mhs &m);
void dealokasi_mk(adr_mk &mk);
void dealokasi_r(adr_r &r);

void tambah_mhs(List_mhs &M, adr_mhs m);
void tambah_mk(List_mk &MK, adr_mk mk);

void tambah_sks(List_mhs &M, List_mk &MK, adr_mhs &m, adr_mk mk);
void lepas_mk(List_mhs &M, List_mk &MK, adr_mk mk, adr_mhs m);

void hapus_mhs(List_mhs &M, adr_mhs &m, List_mk &MK);
void hapus_mk(List_mk &MK, adr_mk &mk, List_mhs &M);

void tampil_semua(List_mhs M);
void tampil_mk_hijau(adr_mhs m, List_mk MK);
void tampil_mhs(List_mhs M, string Kode);
void tampil_mk(List_mhs M, adr_mhs m);
void statistik_mk(List_mk MK);

void tampil_daftar_mhs(List_mhs M);
void tampil_daftar_mk(List_mk MK);


#endif // VARIABEL_H_INCLUDED
