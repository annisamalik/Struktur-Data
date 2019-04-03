#include "variabel.h"

//Data registrasi mahasiswa
/*
Implementasikan multi linked-list yang memodelkan data mahasiswa dan data matakuliah yang diambilnya pada semester tertentu
Seorang mahasiswa bisa mengambil banyak matakuliah berdasarkan banyak (1-24 sks) dan tingkat matakuliah (tingkat 1 hingga 4) tersebut ditawarkan.
Sedangkan suatu matakuliah bisa diambil oleh  banyak mahasiswa.

Fungsionalitas:
a. Penambahan data mahasiswa. [[done]]
b. Penambahan data matakuliah. [[done]]
c. Penentuan relasi antara mahasiswa dan matakuliah dan sebaliknya.
d. Menghapus data matakuliah tertentu.
e. Menghapus data mahasiswa tertentu.
f. Menampilkan data keseluruhan mahasiswa beserta data mata kuliah yang diambilnya. [[done]]
g. Menampilkan data mahasiswa yang mengambil matakuliah tertentu. [[almost]]
h. Menampilkan data matakuliah yang diambil mahasiswa tertentu. [[almost]]
i. Menampilkan data matakuliah yang memiliki jumlah peminat paling banyak dan paling sedikit. [[hmm]]
*/

int main()
{
    List_mhs M; List_mk MK;
    buatlist_mhs(M); buatlist_mk(MK);
    string yourName, yourNIM, KodeMK, NamaMK;
    float yourIP;
    adr_mk mk;
    tambah_mhs(M, alokasi_mhs("Annisa Aisyha Malik", "1301170031", 3.0));
    tambah_mk(MK, alokasi_mk("Struktur Data", "CCH1D4"));
    tambah_mk(MK, alokasi_mk("Kalkulus IIB", "MUH1E3"));
    tambah_mk(MK, alokasi_mk("Bahasa Indonesia", "LUH1A2"));
    tambah_mk(MK, alokasi_mk("MATRIKS DAN RUANG VEKTOR", "MUH1G3"));
    tambah_mk(MK, alokasi_mk("PANCASILA DAN KEWARGANEGARAAN", "HUH1G3"));
    tambah_mk(MK, alokasi_mk("PENDIDIKAN AGAMA ISLAM DAN ETIKA", "HUH1A2"));
    tambah_mk(MK, alokasi_mk("MODEL BISNIS DIGITAL", "CSH2H3"));
    tambah_mk(MK, alokasi_mk("MATEMATIKA DISKRIT A", "MSH2A3"));
    tambah_mk(MK, alokasi_mk("DASAR ALGORITMA DAN PEMROGRAMAN", "CCH1A4"));
    tambah_mk(MK, alokasi_mk("LOGIKA MATEMATIKA A", "MSH1B3"));
    tambah_mk(MK, alokasi_mk("KALKULUS IB", "MUH1B3"));
    tambah_mk(MK, alokasi_mk("BAHASA INGGRIS I", "LUH1B2"));
    tambah_mk(MK, alokasi_mk("FISIKA DASAR", "FUH1G3"));
    tambah_mk(MK, alokasi_mk("PENGANTAR TEKNIK INFORMATIKA", "CSH1F2"));
    char jawab = '0';
    while (jawab=='0' || jawab=='T' || jawab=='t') {
        system ("CLS");
        cout<<"   -------------------------------------------------------------------"<<endl;
        cout<<"                         Data registrasi Mahasiswa" << endl;
        cout<<"   -------------------------------------------------------------------"<<endl<<endl;
        cout<<"   Apa yang ingin anda lakukan?"<<endl;
        cout<<"   a. Tambah data Mahasiswa"<<endl;
        cout<<"   b. Tambah data Matakuliah"<<endl;
        cout<<"   c. Input matakuliah"<<endl;
        cout<<"   d. Lepas matakuliah"<<endl;
        cout<<"   e. Hapus data mata kuliah"<<endl;
        cout<<"   f. Hapus data mahasiswa"<<endl;
        cout<<"   g. Tampilkan data mahasiswa dan mata kuliah yang diambilnya"<<endl;
        cout<<"   h. Tampilkan data mahasiswa yang mengambil mata kuliah tertentu."<<endl;
        cout<<"   i. Tampilkan data mahasiswa tertentu"<<endl;
        cout<<"   j. Tampilkan statistik peminatan mata kuliah"<<endl;
        cout<<"   ___________________________________________________________________"<<endl<<endl<<"   ";
        cin>>jawab;

        if (jawab=='a'){
            do {
                adr_mhs ada = NULL;
                do {
                    do {
                        system ("CLS");
                        cout<<endl<<"   Anda akan menambahkan data mahasiswa ke dalam sistem, silahkan masukan data berikut."<<endl<<endl;
                        cout<<"   NIM  : "; cin>>yourNIM;
                    } while (yourNIM.length() != 10);
                    ada = find_theNIM(M, yourNIM);
                    if (ada!=NULL) {
                        cout<<endl<<"   Maaf NIM yang anda masukkan telah terdaftar silahkan masukan NIM lain."<<endl;
                        cout<<"   Apakah anda ingin memasukan NIM lain? [Y/T]"<<endl<<"   ";
                        cin>>jawab;

                    }
                } while (ada!=NULL && (jawab=='y' || jawab=='Y'));
                if (ada==NULL){
                    cout<<"   Nama : ";
                    cin.ignore(); getline(cin, yourName);
                    do {
                            cout<<"   IP   : ";
                            cin>>yourIP;
                            if (yourIP<0 || yourIP>4){
                                cout<<"   IP anda tidak mungkin kurang dari nol atau lebih dari 4."<<endl;
                            }
                    } while (yourIP<0 || yourIP>4);
                    adr_mhs m = alokasi_mhs(yourName, yourNIM, yourIP);
                    tambah_mhs(M, m);
                    cout<<endl;
                    cout<<"   Apakah anda ingin menambahkan data mahasiswa lagi? [Y/T]"<<endl<<"   ";
                    cin>>jawab;
                }
            } while (jawab=='Y' || jawab=='y');


        } else if (jawab=='b'){
            adr_mk mk;
            do {
                do {
                    do {
                        system ("CLS");
                        cout<<endl<<"   Anda akan menambahkan data mata kuliah ke dalam sistem, silahkan masukan data berikut."<<endl<<endl;
                        cout<<"   Kode Mata Kuliah  : "; cin>>KodeMK;
                    } while (KodeMK.length() != 6 || (not isdigit(KodeMK[5])) || (not isdigit(KodeMK[3]))) ;
                    mk = find_theMK(MK, KodeMK);
                    if (mk!=NULL) {
                        cout<<endl<<"   Maaf mata kuliah yang anda masukkan telah terdaftar silahkan masukan kode lain."<<endl;
                        cout<<"   Apakah anda ingin memasukan mata kuliah lain? [Y/T]"<<endl<<"   ";
                        cin>>jawab;
                    }
                } while (mk!=NULL && (jawab=='y' || jawab=='Y'));
                if (mk==NULL){
                    cout<<"   Nama Mata Kuliah : "; cin.ignore(); getline(cin, NamaMK);
                    mk = alokasi_mk(NamaMK, KodeMK);
                    tambah_mk(MK, mk);
                    cout<<endl;
                    cout<<"   Apakah anda ingin menambahkan data mata kuliah lagi? [Y/T]"<<endl<<"   ";
                    cin>>jawab;
                }
            } while (jawab=='Y' || jawab=='y');


        } else if (jawab=='c'){
            adr_mhs m = NULL;
            do {
                do {
                    system ("CLS");
                    cout<<endl<<"   Anda akan menambahkan mata kuliah ke dalam jadwal anda, silahkan masukan NIM anda."<<endl<<endl;
                    cout<<"   NIM  : "; cin>>yourNIM;
                } while (yourNIM.length() != 10);
                m = find_theNIM(M, yourNIM);
                cout<<endl;
                if (m==NULL) {
                    cout<<endl<<"   Maaf NIM yang anda masukkan belum terdaftar."<<endl;
                    cout<<"   Jika anda belum menambahkan NIM anda dalam sistem silahkan masukan melalui menu utama."<<endl;
                    cout<<"   Apakah anda ingin memasukan NIM lain? [Y/T]"<<endl;
                    cin>>jawab;
                }
            } while (m==NULL && (jawab=='Y' || jawab=='y'));
            if (m!=NULL){
                do {
                    //system ("CLS");
                    //how to clear screen based on the option before but not clear everything
                    cout<<"   Berikut adalah daftar mata kuliah yang bisa anda ambil"<<endl;
                    if (first(MK)!=NULL){
                        tampil_mk_hijau(m, MK);
                        cout<<endl<<"   Silahkan masukan kode mata kuliah yang ingin anda ambil"<<endl<<"   ";
                        cin>>KodeMK;
                        adr_mk mk = find_theMK(MK, KodeMK);
                        if (mk==NULL) {
                            cout<<endl<<"   Maaf mata kuliah dengan kode "<<KodeMK<<" tidak tersedia."<<endl;
                        } else {
                            if (info(m).Tingkat==info(mk).tingkat)
                                tambah_sks(M, MK, m, mk);
                            else
                                cout<<endl<<"   Maaf anda tidak bisa mengambil mata kuliah tingkat atas.";
                        }
                        cout<<endl<<"   Apakah anda, "<<info(m).Nama<<" akan menambah mata kuliah lagi?[Y/T]"<<endl<<"   ";
                        cin>>jawab;
                    } else {
                        cout<<"   Maaf tidak ada mata kuliah yang terdaftar dalam sistem."<<endl;
                        jawab = '0';
                    }
                } while(jawab=='Y' || jawab=='y');
            }


        } else if (jawab=='d'){
            adr_mhs m = NULL;
            do {
                do {
                    system ("CLS");
                    cout<<endl<<"   Anda akan menghapus mata kuliah dari jadwal anda, silahkan masukan NIM anda."<<endl<<endl;
                    cout<<"   NIM  : "; cin>>yourNIM;
                } while (yourNIM.length() != 10);
                m = find_theNIM(M, yourNIM);
                cout<<endl;
                if (m==NULL) {
                    cout<<"   Maaf NIM yang anda masukkan belum terdaftar."<<endl;
                    cout<<"   Jika anda belum menambahkan NIM anda dalam sistem silahkan masukan melalui menu utama."<<endl;
                    cout<<"   Apakah anda ingin memasukan NIM lain? [Y/T]"<<endl;
                    cin>>jawab;
                }
            } while (m==NULL && (jawab=='Y' || jawab=='y'));
            do {
                if (m!=NULL){
                    if (first(MK)!=NULL && relasi(m)!=NULL) {
                        cout<<"   Berikut adalah daftar mata kuliah yang anda pilih."<<endl;
                        tampil_mk(M, m);
                        cout<<endl<<"   Silahkan masukan kode mata kuliah yang anda ingin hapus."<<endl<<"   ";
                        cin>>KodeMK;
                        adr_mk mk = find_theMK(MK, KodeMK);
                        if (mk==NULL) {
                            cout<<"   Maaf mata kuliah dengan kode "<<KodeMK<<" tidak tersedia."<<endl;
                        } else {
                            lepas_mk(M, MK, mk, m);
                            cout<<"   Mata kuliah "<<info(mk).Kode_MK<<" - "<<info(mk).Nama_MK<<" telah dihapus dari jadwal."<<endl;
                            cout<<endl;
                        }
                        cout<<"   Apakah anda ingin menghapus mata kuliah lain dari jadwal? [Y/T]"<<endl<<"   ";
                        cin>>jawab;
                    } else {
                        cout<<"   Tidak ada mata kuliah yang dapat di hapus."<<endl<<endl;
                        jawab = '0';cout<<"   ";system("pause");
                    }

                }
            } while (jawab=='Y' || jawab=='y');


        } else if (jawab=='e'){
            do {
                system ("CLS");
                cout<<endl<<"   Anda akan menghapus data mata kuliah, silahkan masukan kode mata kuliah yang ingin dihapus."<<endl<<endl;
                adr_mk mk;
                tampil_daftar_mk(MK);
                do {
                    do{
                        cout<<"   Kode MK : ";
                        cin>>KodeMK;
                    } while (KodeMK.length() != 6);
                    mk = find_theMK(MK, KodeMK);
                    if (mk==NULL){
                        cout<<endl<<"   Maaf mata kuliah dengan kode "<<KodeMK<<" tidak terdaftar."<<endl;
                        cout<<"   Apakah anda ingin memasukan kode lain? [Y/T]"<<endl<<"   ";
                        cin>>jawab;
                    }
                } while (mk==NULL && (jawab=='Y' || jawab=='y'));

                if (mk!=NULL){
                    cout<<endl<<"   Apakah anda yakin akan menghapus mata kuliah "<<info(mk).Kode_MK<<" - "<<info(mk).Nama_MK<<"?"<<endl;
                    cout<<"   Menghapus mata kuliah ini, akan menghapus mata kuliah ini dari jadwal mahasiswa yang mengambil mata kuliah ini."<<endl;
                    cout<<"   Yakin? [Y/T]"<<endl<<"   ";
                    cin>>jawab;
                    if (jawab=='Y' || jawab=='y'){
                        hapus_mk(MK, mk, M);
                        dealokasi_mk(mk);
                        cout<<endl<<"   Data mata kuliah dengan kode "<<KodeMK<<" telah dihapus."<<endl;
                        cout<<"   Apakah anda ingin menghapus data mata kuliah lain?[Y/T]"<<endl<<"   ";
                        cin>>jawab;
                    }
                }
            } while (jawab=='Y' || jawab=='y');


        } else if (jawab=='f'){
            do {
                adr_mhs m = NULL;
                do {
                    do {
                        system ("CLS");
                        cout<<endl<<"   Anda akan menghapus data mahasiswa, silahkan masukkan NIM mahasiswa yang ingin dihapus."<<endl<<endl;
                        tampil_daftar_mhs(M);
                        cout<<"   NIM  : "; cin>>yourNIM;
                    } while (yourNIM.length() != 10);
                    m = find_theNIM(M, yourNIM);
                    cout<<endl;
                    if (m==NULL) {
                        cout<<"   Maaf NIM yang anda masukkan tidak terdaftar silahkan masukan NIM lain."<<endl;
                    }
                } while (m==NULL);

                if (m!=NULL){
                    cout<<"   Apakah anda yakin akan menghapus data mahasiswa "<<info(m).NIM<<" - "<<info(m).Nama<<"?"<<endl;
                    cout<<"   Yakin? [Y/T]"<<endl<<"   ";
                    cin>>jawab;
                    if (jawab=='Y' || jawab=='y'){
                        hapus_mhs(M, m, MK);
                        dealokasi_m(m);
                        cout<<"   Data mahasiswa dengan NIM "<<yourNIM<<" telah dihapus."<<endl;
                        cout<<"   Apakah anda ingin menghapus data mahasiswa lain? [Y/T]"<<endl;
                        cin>>jawab;
                    }
                }
            } while (jawab=='Y' || jawab=='y');


        } else if (jawab=='g'){
            system ("CLS");
            cout<<endl<<"   Berikut adalah data mahasiswa dan mata kuliah yang diambilnya"<<endl<<endl;
            tampil_semua(M);
            jawab = '0';
            cout<<endl<<"   ";system("pause");


        } else if (jawab=='h'){
            do {
                do{
                    system ("CLS");
                    cout<<endl<<"   Masukan kode mata kuliah."<<endl<<endl;
                    cout<<"   Kode MK : ";
                    cin>>KodeMK;
                } while (KodeMK.length() != 6);

                mk = find_theMK(MK, KodeMK);

                if (mk==NULL){
                    cout<<endl<<"   Maaf mata kuliah dengan kode "<<KodeMK<<" tidak terdaftar."<<endl;
                    cout<<"   Apakah anda ingin memasukan kode lain? [Y/T]"<<endl<<"   ";
                    cin>>jawab;
                }
            } while (mk==NULL && (jawab=='Y' || jawab=='y'));

            if (mk!=NULL) {
                cout<<endl<<"   Berikut adalah daftar mahasiswa yang mengambil matakuliah "<<KodeMK<<endl;
                tampil_mhs(M, KodeMK);
                jawab = '0';
                cout<<endl;
            }

            cout<<endl<<"   ";system("pause");


        } else if (jawab=='i'){
            system ("CLS");
            cout<<endl<<"   Masukkan NIM mahasiswa."<<endl<<"   ";
            cin>>yourNIM;
            adr_mhs m = find_theNIM(M, yourNIM);
            if (m!=NULL) {
                tampil_mk(M, m);
            } else {
                cout<<"   Mahasiswa dengan NIM "<<yourNIM<<" tidak terdaftar."<<endl;
            }
            jawab = '0';
            cout<<endl<<"   ";system("pause");


        } else if (jawab=='j'){
            system ("CLS");
            statistik_mk(MK);
            jawab = '0';
            cout<<endl<<"   ";system("pause");
        }
    }
    return 0;
}
