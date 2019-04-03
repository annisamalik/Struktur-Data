#include "variabel.h"

using namespace std;

void buatlist_mhs (List_mhs &M){
    first(M) = NULL;
    last(M) = NULL;
}

void buatlist_mk (List_mk &MK){
    first(MK) = NULL;
}

adr_r find_theR(adr_mhs m, string kode){
    adr_r r = relasi(m);
    while ((r!=NULL) && (info(info(r)).Kode_MK!=kode)) {
        r = next(r);
    }
    return r;
}

adr_r find_thePrec(adr_mhs m, string kode){
    adr_r Prec = relasi(m);
    while ((Prec!=NULL) && (info(info(next(Prec))).Kode_MK!=kode)) {
        Prec = next(Prec);
    }
    return Prec;
}

adr_mk find_theMK(List_mk MK, string KODE){
    adr_mk p = first(MK);
    if (first(MK)!=NULL){
        while(next(p)!=first(MK) && info(p).Kode_MK!=KODE){
            p=next(p);
        }
        if(info(p).Kode_MK!=KODE){
            return NULL;
        } else{
            return p;
        }
    } else
        return NULL;
}

adr_mhs find_theNIM(List_mhs M, string NIM){
    adr_mhs p = first(M);
    while (p!=NULL && info(p).NIM!=NIM){
        p = next(p);
    }
    return p;
}

adr_mk alokasi_mk(string nama, string kode){
    adr_mk p = new kotak_mk;
    info(p).Nama_MK = nama;
    info(p).Kode_MK = kode;
    info(p).sks = atoi(kode.substr(5,1).c_str());
    info(p).jum_mhs = 0;
    info(p).tingkat = atoi(kode.substr(3,1).c_str());
    next(p) = NULL;
    return p;
}

adr_mhs alokasi_mhs(string nama, string nim, float ip){
    adr_mhs p = new kotak_mhs;
    time_t     rawtime;
    struct tm* timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    int bulan = timeinfo->tm_mon;
    int tahun = (timeinfo->tm_year + 1900)-2000 ;
    int z = atoi(nim.substr(4,2).c_str());
    if ( (bulan>6) && (bulan <=12) ){
        info(p).Tingkat = tahun - z + 1 ;
    } else if ( (bulan>=1) && (bulan <=6)) {
        info(p).Tingkat = tahun - z ;
    }
    prev(p) = NULL;
    info(p).Nama = nama;
    info(p).NIM = nim;
    info(p).IP = ip;
    info(p).jum_sks = 0;
    relasi(p) = NULL;
    next(p) = NULL;
    return p;
}

adr_r alokasi_r(adr_mk mk){
    adr_r r = new kotak_relasi;
    info(r) = mk;
    next(r) = NULL;
    return r;
}

void dealokasi_m(adr_mhs &m) {
    delete m;
}

void dealokasi_mk(adr_mk &mk) {
    delete mk;
}

void dealokasi_r(adr_r &r){
    delete r;
}

void tambah_mhs(List_mhs &M, adr_mhs m){
/*IS. Terdapat alamat mahasiswa di m yang akan ditambahkan ke dalam List mahasiswa
FS. Menambahkan info mahasiswa ke List secara terurut */
    if (first(M)==NULL) {
        first(M) = m;
        last(M) = m;
    } else if (info(m).NIM <= info(first(M)).NIM) {
        next(m) = first(M);
        prev(first(M)) = m;
        first(M) = m;
    } else if (info(m).NIM >= info(last(M)).NIM) {
        prev(m) = last(M);
        next(last(M)) = m;
        last(M) = m;
    } else {
        adr_mhs q = first(M);
        while ((q != NULL) && ( info(m).NIM > info(next(q)).NIM ) )  {
            q = next(q);
        }
        prev(m) = q;
        next(m) = next(q);
        prev(next(m)) = m;
        next(q) = m;
    }
}

void tambah_mk(List_mk &MK, adr_mk mk){
//Insert last circular list
    adr_mk p;
    if (first(MK)==NULL){
        first(MK) = mk;
        next(mk) = mk;
    } else {
        p = first(MK);
        while (next(p)!=first(MK)){
            p = next(p);
        }
        next(mk) = first(MK);
        next(p) = mk;
    }
}

void tambah_sks(List_mhs &M, List_mk &MK, adr_mhs &m, adr_mk mk){
/* IS. Diketahui alamat mahasiswa yang akan menginput mata kuliah.
FS. Menambah mata kuliah dalam jadwal mahasiswa (insert first), merubah jumlah sks yang diambil dan jumlah mahasiswa pada elemen mata kuliah.
*/
    adr_r r = find_theR(m, info(mk).Kode_MK);
    if (r==NULL){
        if ( (info(m).IP >= 3 && info(m).IP <= 4 && (info(m).jum_sks+info(mk).sks) <= 24) || (info(m).IP < 3 && info(m).IP >= 0 && (info(m).jum_sks+info(mk).sks) <= 20)){
            r = alokasi_r(mk);
            info(m).jum_sks = info(m).jum_sks + info(mk).sks;
            info(mk).jum_mhs = info(mk).jum_mhs + 1;
            next(r) = relasi(m);
            relasi(m) = r;
        } else {
            cout<<"   Maaf anda hanya bisa mengambil ";
            if (info(m).IP >= 3) {
                cout<<endl<<"24 sks. Jumlah sks yang telah anda ambil adalah "<<info(m).jum_sks;
            } else {
                cout<<endl<<"20 sks. Jumlah sks yang telah anda ambil adalah "<<info(m).jum_sks;
            }
        }
    } else {
        cout<<endl<<"   Maaf anda sudah mengambil mata kuliah tersebut."<<endl;
    }
}

void lepas_mk(List_mhs &M, List_mk &MK, adr_mk mk, adr_mhs m){
    adr_r r, Prec;
    if (info(relasi(m))==mk) {
        r = relasi(m);
        relasi(m) = next(relasi(m));
    } else {
        r = find_theR(m, info(mk).Kode_MK);
        Prec = find_thePrec(m, info(mk).Kode_MK);
        next(Prec) = next(r);
        next(r) = NULL;
    }
    info(m).jum_sks = info(m).jum_sks - info(mk).sks;
    info(mk).jum_mhs = info(mk).jum_mhs - 1;
}

void hapus_mhs(List_mhs &M, adr_mhs &m, List_mk &MK){
    adr_r r, c;
    r = relasi(m);
    while (r!=NULL){
        c = r;
        lepas_mk(M, MK, info(c), m);
        r = next(r);
        dealokasi_r(c);
    }
    if (m==first(M) && m==last(M)){
        first(M)= NULL;
        last(M)= NULL;
    }else if (m==first(M)){
        first(M) = next(m);
        prev(next(m)) = NULL;
        next(m) = NULL;
    } else if (m==last(M)){
        last(M) = prev(m);
        next(prev(m)) = NULL;
        prev(m) = NULL;
    } else {
        next(prev(m)) = next(m);
        prev(next(m)) = prev(m);
        next(m) = NULL;
        prev(m) = NULL;
    }
}

void hapus_mk(List_mk &MK, adr_mk &mk, List_mhs &M){
/* IS. diketahui alamat mata kuliah yang akan di hapus.
FS. Semua relasi yang berhubungan dengan mata kuliah tersebut di hapus, dan di keluarkan alamat mata kuliah yang di hapus.
*/
    adr_mhs m = first(M);
    adr_mk p;
    while (m!=NULL){
        adr_r r, c;
        r = relasi(m);
        while(r!=NULL){
            if (info(r)==mk){
                c = r;
                lepas_mk(M, MK, mk, m);
                r = next(r);
                dealokasi_r(c);
            } else
                r = next(r);
        }
        m = next(m);
    }if (next(mk)==mk){
        first(MK) = NULL;
        next(mk) = NULL;
    } else if (mk==first(MK)){
        p = first(MK);
        while (next(p)!=first(MK)){
            p =next(p);
        }
        first(MK) = next(mk);
        next(p) = first(MK);
        next(mk) = NULL;
    } else {
        p = first(MK);
        while (next(p)!=mk) {
            p = next(p);
        }
        next(p) = next(mk);
        next(mk) = NULL;
    }
}

void tampil_semua(List_mhs M){
    adr_r q;
    adr_mhs p = first(M);
    if (p!=NULL) {
        while (p!=NULL) {
            cout<<"   Nama : "<<info(p).Nama<<endl;
            cout<<"   NIM : "<<info(p).NIM<<endl;
            cout<<"   Tingkat : "<<info(p).Tingkat<<endl;
            cout<<"   IP : "<<info(p).IP<<endl;
            q = relasi(p);
            if (q!=NULL){
                cout<<"   Matakuliah yang diambil"<<endl;
                while (q!=NULL){
                    cout<<"   "<<info(info(q)).Kode_MK<<" - "<<info(info(q)).Nama_MK<<"( "<<info(info(q)).sks<<" sks )"<<endl;
                    q = next(q);
                }
                cout<<endl;
            } else {
                cout<<"   Mahasiswa belum memilih mata kuliah."<<endl<<endl;
            }
            p = next(p);
        }
    } else {
        cout<<"   Maaf tidak ada daftar mahasiswa dalam sistem."<<endl;
    }
}

void tampil_mhs(List_mhs M, string Kode){
    adr_r q; adr_mhs p = first(M);
    bool ada = false;
    if (first(M)!=NULL){
        while (p!=NULL) {
            q = relasi(p);
            while (q!=NULL && info(info(q)).Kode_MK!=Kode){
                q = next(q);
            }
            if (q!=NULL){
                cout<<"   "<<info(p).NIM<<" - "<<info(p).Nama<<endl;
                ada = true;
            }
            p = next(p);
        }
        if (not ada)
            cout<<"   Belum ada mahasiswa yang mendaftar mata kuliah ini."<<endl;
    } else
        cout<<"   Belum ada mahasiswa yang terdaftar dalam sistem."<<endl;
}

void tampil_mk(List_mhs M, adr_mhs m){
/* IS. telah diketahui alamat dari mahasiswa
FS. menampilkan mata kuliah apa saja yang telah dipilih oleh mahasiswa tersebut.
*/
    adr_r r = relasi(m);
    if (r!=NULL) {
        cout<<endl<<"   Berikut adalah daftar mata kuliah yang diambil mahasiswa dengan NIM "<<info(m).NIM<<endl;
        while (r!=NULL){
            cout<<"   "<<info(info(r)).Kode_MK<<" - "<<info(info(r)).Nama_MK<<" ( "<<info(info(r)).sks<<" sks )"<<endl;
            r = next(r);
        }
    } else
        cout<<endl<<"   Mahasiswa dengan NIM "<<info(m).NIM<<" belum memilih mata kuliah."<<endl;

}

void tampil_mk_hijau(adr_mhs m, List_mk MK){
    adr_mk mk = first(MK);
    adr_r r;
    if (first(MK)!=NULL){
        while (next(mk)!=first(MK)){
            r = find_theR(m, info(mk).Kode_MK);
            if ((info(mk).tingkat == info(m).Tingkat) && (r==NULL)){
                cout<<"   "<<info(mk).Kode_MK<<" - "<<info(mk).Nama_MK<<" ( "<<info(mk).sks<<" sks )"<<endl;
            }
            mk = next(mk);
        }
        r = find_theR(m, info(mk).Kode_MK);
        if ((info(mk).tingkat == info(m).Tingkat) && (r==NULL)){
            cout<<"   "<<info(mk).Kode_MK<<" - "<<info(mk).Nama_MK<<" ( "<<info(mk).sks<<" sks )"<<endl;
        }
    } else
        cout<<"Belum ada mata kuliah yang terdaftar di dalam sistem."<<endl;
}

void statistik_mk(List_mk MK){
    adr_mk Nmin, Nmax, p;
    Nmin = first(MK); Nmax = first(MK); p = first(MK);
    if (first(MK)!=NULL){
        while (next(p)!=first(MK)) {
            if (info(p).jum_mhs > info(Nmax).jum_mhs){
                Nmax = p;
            } else
                Nmin = p;
            p = next(p);
        }
        if (info(p).jum_mhs > info(Nmax).jum_mhs){
            Nmax = p;
        } else
            Nmin = p;
        cout<<endl;
        if (info(Nmax).jum_mhs!=0){
            cout<<endl<<"   Berikut adalah daftar jumlah peminat setiap mata kuliah."<<endl;
            cout<<"   Matakuliah yang memiliki jumlah peminat paling banyak adalah "<<endl;
            p = first(MK);
            while (next(p)!=first(MK)) {
                if (info(p).jum_mhs == info(Nmax).jum_mhs){
                    cout<<"   "<<info(p).Kode_MK<<" - "<<info(p).Nama_MK<<" "<<info(p).sks<<" sks Jumlah Mahasiswa: "<<info(p).jum_mhs<<endl;
                }
                p = next(p);
            }
            if (info(p).jum_mhs == info(Nmax).jum_mhs){
                cout<<"   "<<info(p).Kode_MK<<" - "<<info(p).Nama_MK<<" "<<info(p).sks<<" sks Jumlah Mahasiswa: "<<info(p).jum_mhs<<endl;
            }

            cout<<endl<<endl<<"   Matakuliah yang memiliki jumlah peminat paling sedikit adalah "<<endl;
            p = first(MK);
            while (next(p)!=first(MK)) {
                if (info(p).jum_mhs == info(Nmin).jum_mhs){
                        cout<<"   "<<info(p).Kode_MK<<" - "<<info(p).Nama_MK<<" "<<info(p).sks<<" sks Jumlah Mahasiswa: "<<info(p).jum_mhs<<endl;
                    }
                    p = next(p);
            }
            if (info(p).jum_mhs == info(Nmin).jum_mhs){
                cout<<"   "<<info(p).Kode_MK<<" - "<<info(p).Nama_MK<<" "<<info(p).sks<<" sks Jumlah Mahasiswa: "<<info(p).jum_mhs<<endl;
            }
        } else {
                cout<<"   Belum ada mahasiswa yang memilih matakuliah."<<endl;
        }
    } else
        cout<<"   Tidak ada daftar mata kuliah dalam sistem."<<endl;
}

void tampil_daftar_mk(List_mk MK){
    adr_mk mk = first(MK);
    if (first(MK)!=NULL){
        while (next(mk)!=first(MK)){
            cout<<"   "<<info(mk).Kode_MK<<" - "<<info(mk).Nama_MK<<" "<<info(mk).sks<<" sks"<<endl;
            mk = next(mk);
        }
        cout<<"   "<<info(mk).Kode_MK<<" - "<<info(mk).Nama_MK<<" "<<info(mk).sks<<" sks"<<endl;
    } else {
        cout<<"   Belum ada mata kuliah yang terdaftar di dalam sistem."<<endl;
    }
}

void tampil_daftar_mhs(List_mhs M){
    adr_mhs m = first(M);
    if (first(M)!=NULL){
        while (m!=NULL){
            cout<<"   "<<info(m).NIM<<" - "<<info(m).Nama<<" Tingkat: "<<info(m).Tingkat<<" IP: "<<info(m).IP<<" Jumlah sks: "<<info(m).jum_sks<<" sks"<<endl;
            m = next(m);
        }
    } else {
        cout<<"   Belum ada mahasiswa yang terdaftar di dalam sistem."<<endl;
    }
}
