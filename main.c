
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX_PRODUK 50
#define PANJANG_NAMA 50

// ==========================================
// DEKLARASI ARRAY DAN VARIABEL GLOBAL
// ==========================================

// Array karakter dua dimensi untuk nama produk
char namaProduk[MAX_PRODUK][PANJANG_NAMA];

// Array satu dimensi
long long harga[MAX_PRODUK];
int stok[MAX_PRODUK];
int jumlahTerjual[MAX_PRODUK];

// Variabel untuk jumlah produk aktif
int jumlahProduk = 5;

// Total pendapatan dari transaksi yang berhasil
long long totalPendapatan = 0;

// ==========================================
// FUNGSI INPUT DAN VALIDASI
// ==========================================

void bacaBaris(char teks[], int ukuran) {
    if (fgets(teks, ukuran, stdin) == NULL) {
        printf("\nInput tidak tersedia. Program dihentikan.\n");
        exit(0);
    }

    teks[strcspn(teks, "\n")] = '\0';
}

long long inputAngka(const char *pesan) {
    char buffer[100];
    char *akhir;
    long long angka;

    while (1) {
        printf("%s", pesan);
        bacaBaris(buffer, sizeof(buffer));

        angka = strtoll(buffer, &akhir, 10);

        while (isspace((unsigned char)*akhir)) {
            akhir++;
        }

        if (akhir != buffer && *akhir == '\0') {
            return angka;
        }

        printf("Input harus berupa angka!\n");
    }
}

int inputPilihan(const char *pesan, int minimum, int maksimum) {
    long long angka;

    while (1) {
        angka = inputAngka(pesan);

        if (angka >= minimum && angka <= maksimum) {
            return (int)angka;
        }

        printf("Pilihan harus antara %d sampai %d!\n",
               minimum, maksimum);
    }
}

// ==========================================
// FUNGSI PENCARIAN NAMA PRODUK
// ==========================================

int cariProduk(const char nama[]) {
    char nama1[PANJANG_NAMA];
    char nama2[PANJANG_NAMA];

    for (int i = 0; i < jumlahProduk; i++) {
        strcpy(nama1, namaProduk[i]);
        strcpy(nama2, nama);

        for (int j = 0; nama1[j] != '\0'; j++) {
            nama1[j] = (char)tolower((unsigned char)nama1[j]);
        }

        for (int j = 0; nama2[j] != '\0'; j++) {
            nama2[j] = (char)tolower((unsigned char)nama2[j]);
        }

        if (strstr(nama1, nama2) != NULL) {
            return i;
        }
    }

    return -1;
}

// ==========================================
// FUNGSI DATA AWAL PRODUK
// ==========================================

void dataAwal() {
    strcpy(namaProduk[0], "Nasi Goreng");
    harga[0] = 12000;
    stok[0] = 20;
    jumlahTerjual[0] = 0;

    strcpy(namaProduk[1], "Mie Goreng");
    harga[1] = 10000;
    stok[1] = 15;
    jumlahTerjual[1] = 0;

    strcpy(namaProduk[2], "Es Teh");
    harga[2] = 5000;
    stok[2] = 30;
    jumlahTerjual[2] = 0;

    strcpy(namaProduk[3], "Air Mineral");
    harga[3] = 4000;
    stok[3] = 25;
    jumlahTerjual[3] = 0;

    strcpy(namaProduk[4], "Roti Bakar");
    harga[4] = 8000;
    stok[4] = 10;
    jumlahTerjual[4] = 0;
}

// ==========================================
// FUNGSI MENAMPILKAN DAFTAR PRODUK
// ==========================================

void tampilkanProduk() {
    printf("\n");
    printf("===============================================================\n");
    printf("                    DAFTAR PRODUK KANTIN\n");
    printf("===============================================================\n");

    if (jumlahProduk == 0) {
        printf("Belum ada produk tersedia.\n");
        return;
    }

    printf("%-5s %-20s %-15s %-10s %-10s\n",
           "No", "Nama Produk", "Harga", "Stok", "Terjual");

    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < jumlahProduk; i++) {
        printf("%-5d %-20s Rp%-13lld %-10d %-10d\n",
               i + 1,
               namaProduk[i],
               harga[i],
               stok[i],
               jumlahTerjual[i]);
    }

    printf("===============================================================\n");
}

// ==========================================
// FUNGSI MENAMBAHKAN PRODUK
// ==========================================

void tambahProduk() {
    char nama[PANJANG_NAMA];

    printf("\n========== TAMBAH PRODUK BARU ==========\n");

    if (jumlahProduk >= MAX_PRODUK) {
        printf("Kapasitas produk sudah mencapai 50!\n");
        return;
    }

    while (1) {
        printf("Masukkan nama produk: ");
        bacaBaris(nama, sizeof(nama));

        if (strlen(nama) == 0) {
            printf("Nama produk tidak boleh kosong!\n");
            continue;
        }

        if (cariProduk(nama) != -1) {
            printf("Produk dengan nama tersebut sudah ada!\n");
            continue;
        }

        break;
    }

    long long hargaBaru;

    do {
        hargaBaru = inputAngka("Masukkan harga produk: Rp");

        if (hargaBaru < 0) {
            printf("Harga tidak boleh negatif!\n");
        }
    } while (hargaBaru < 0);

    int stokBaru;

    do {
        stokBaru = (int)inputAngka("Masukkan jumlah stok: ");

        if (stokBaru < 0) {
            printf("Stok tidak boleh negatif!\n");
        } else if (stokBaru > INT_MAX) {
            printf("Jumlah stok terlalu besar!\n");
            stokBaru = -1;
        }
    } while (stokBaru < 0);

    strcpy(namaProduk[jumlahProduk], nama);
    harga[jumlahProduk] = hargaBaru;
    stok[jumlahProduk] = stokBaru;
    jumlahTerjual[jumlahProduk] = 0;

    jumlahProduk++;

    printf("\nProduk berhasil ditambahkan!\n");
}

// ==========================================
// FUNGSI MENGUBAH PRODUK
// ==========================================

void ubahProduk() {
    printf("\n========== UBAH DATA PRODUK ==========\n");

    tampilkanProduk();

    if (jumlahProduk == 0) return;

    int nomor = inputPilihan(
        "Masukkan nomor produk yang ingin diubah: ",
        1, jumlahProduk
    );

    int index = nomor - 1;

    printf("\nProduk: %s\n", namaProduk[index]);

    long long hargaBaru = inputAngka(
        "Masukkan harga baru: Rp"
    );

    if (hargaBaru < 0) {
        printf("Harga tidak boleh negatif!\n");
        return;
    }

    long long stokBaru = inputAngka(
        "Masukkan stok baru: "
    );

    if (stokBaru < 0 || stokBaru > INT_MAX) {
        printf("Stok tidak valid!\n");
        return;
    }

    harga[index] = hargaBaru;
    stok[index] = (int)stokBaru;

    printf("Data produk berhasil diperbarui!\n");
}

// ==========================================
// FUNGSI TRANSAKSI PENJUALAN
// ==========================================

void transaksiPenjualan() {
    int keranjang[MAX_PRODUK] = {0};
    int nomor, jumlah;
    long long subtotal, total = 0;

    printf("\n");
    printf("============================================\n");
    printf("             TRANSAKSI PENJUALAN\n");
    printf("============================================\n");

    if (jumlahProduk == 0) {
        printf("Belum ada produk untuk dijual!\n");
        return;
    }

    tampilkanProduk();

    printf("\nMasukkan nomor produk dan jumlah pembelian.\n");
    printf("Masukkan nomor 0 jika transaksi selesai.\n");

    while (1) {
        nomor = inputPilihan(
            "\nNomor produk (0 untuk selesai): ",
            0, jumlahProduk
        );

        if (nomor == 0) {
            break;
        }

        int index = nomor - 1;

        jumlah = inputPilihan(
            "Jumlah pembelian: ",
            1, INT_MAX
        );

        // Validasi stok termasuk produk yang sudah
        // dimasukkan sebelumnya ke keranjang.

        if (jumlah > stok[index] - keranjang[index]) {
            printf("Stok tidak mencukupi!\n");
            printf("Stok tersedia: %d\n",
                   stok[index] - keranjang[index]);

            printf("Transaksi dibatalkan.\n");
            return;
        }

        keranjang[index] += jumlah;

        printf("Produk berhasil dimasukkan ke keranjang.\n");
    }

    // Menghitung total transaksi
    printf("\n");
    printf("============= RINCIAN TRANSAKSI =============\n");

    for (int i = 0; i < jumlahProduk; i++) {
        if (keranjang[i] > 0) {
            subtotal = harga[i] * keranjang[i];
            total += subtotal;

            printf("%-20s x %-5d = Rp%lld\n",
                   namaProduk[i],
                   keranjang[i],
                   subtotal);
        }
    }

    if (total == 0) {
        printf("Tidak ada produk yang dibeli.\n");
        return;
    }

    printf("---------------------------------------------\n");
    printf("TOTAL PEMBAYARAN : Rp%lld\n", total);

    // Konfirmasi transaksi
    int konfirmasi = inputPilihan(
        "Konfirmasi pembayaran? (1=Ya, 0=Tidak): ",
        0, 1
    );

    if (konfirmasi == 0) {
        printf("Transaksi dibatalkan. Stok tidak berubah.\n");
        return;
    }

    // Memperbarui stok dan jumlah produk terjual
    for (int i = 0; i < jumlahProduk; i++) {
        if (keranjang[i] > 0) {
            stok[i] -= keranjang[i];
            jumlahTerjual[i] += keranjang[i];
        }
    }

    totalPendapatan += total;

    printf("\nTRANSAKSI BERHASIL!\n");
    printf("Total pembayaran: Rp%lld\n", total);
    printf("Stok produk telah diperbarui.\n");
}

// ==========================================
// FUNGSI MENAMBAH STOK
// ==========================================

void tambahStok() {
    printf("\n========== TAMBAH STOK PRODUK ==========\n");

    tampilkanProduk();

    if (jumlahProduk == 0) return;

    int nomor = inputPilihan(
        "Pilih nomor produk: ",
        1, jumlahProduk
    );

    int index = nomor - 1;

    long long tambahan = inputAngka(
        "Masukkan jumlah stok tambahan: "
    );

    if (tambahan <= 0) {
        printf("Penambahan stok harus lebih dari 0!\n");
        return;
    }

    if (tambahan > INT_MAX - (long long)stok[index]) {
        printf("Jumlah stok melebihi batas!\n");
        return;
    }

    stok[index] += (int)tambahan;

    printf("Stok berhasil ditambahkan!\n");
    printf("Nama produk : %s\n", namaProduk[index]);
    printf("Stok sekarang: %d\n", stok[index]);
}

// ==========================================
// FUNGSI PENCARIAN PRODUK
// ==========================================

void pencarianProduk() {
    char nama[PANJANG_NAMA];

    printf("\n========== PENCARIAN PRODUK ==========\n");

    if (jumlahProduk == 0) {
        printf("Belum ada produk tersedia.\n");
        return;
    }

    printf("Masukkan nama produk yang dicari: ");
    bacaBaris(nama, sizeof(nama));

    if (strlen(nama) == 0) {
        printf("Nama pencarian tidak boleh kosong!\n");
        return;
    }

    int ditemukan = 0;

    for (int i = 0; i < jumlahProduk; i++) {
        char nama1[PANJANG_NAMA];
        char nama2[PANJANG_NAMA];

        strcpy(nama1, namaProduk[i]);
        strcpy(nama2, nama);

        for (int j = 0; nama1[j] != '\0'; j++)
            nama1[j] = (char)tolower((unsigned char)nama1[j]);

        for (int j = 0; nama2[j] != '\0'; j++)
            nama2[j] = (char)tolower((unsigned char)nama2[j]);

        if (strstr(nama1, nama2) != NULL) {
            printf("\nProduk ditemukan!\n");
            printf("Nama   : %s\n", namaProduk[i]);
            printf("Harga  : Rp%lld\n", harga[i]);
            printf("Stok   : %d\n", stok[i]);
            printf("Terjual: %d\n", jumlahTerjual[i]);

            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Produk tidak ditemukan!\n");
    }
}

// ==========================================
// FUNGSI MENUKAR DATA PRODUK
// ==========================================

void tukarProduk(int a, int b) {
    char namaSementara[PANJANG_NAMA];
    long long hargaSementara;
    int stokSementara;
    int terjualSementara;

    strcpy(namaSementara, namaProduk[a]);
    strcpy(namaProduk[a], namaProduk[b]);
    strcpy(namaProduk[b], namaSementara);

    hargaSementara = harga[a];
    harga[a] = harga[b];
    harga[b] = hargaSementara;

    stokSementara = stok[a];
    stok[a] = stok[b];
    stok[b] = stokSementara;

    terjualSementara = jumlahTerjual[a];
    jumlahTerjual[a] = jumlahTerjual[b];
    jumlahTerjual[b] = terjualSementara;
}

// ==========================================
// FUNGSI PENGURUTAN PRODUK
// ==========================================

void urutkanProduk() {
    int pilihan;

    printf("\n========== PENGURUTAN PRODUK ==========\n");
    printf("1. Harga termurah ke termahal\n");
    printf("2. Jumlah terjual terbanyak\n");

    pilihan = inputPilihan("Pilih pengurutan: ", 1, 2);

    if (pilihan == 1) {
        // Bubble Sort berdasarkan harga
        for (int i = 0; i < jumlahProduk - 1; i++) {
            for (int j = 0; j < jumlahProduk - i - 1; j++) {
                if (harga[j] > harga[j + 1]) {
                    tukarProduk(j, j + 1);
                }
            }
        }

        printf("\nProduk berhasil diurutkan berdasarkan harga!\n");
    } else {
        // Bubble Sort berdasarkan jumlah terjual
        for (int i = 0; i < jumlahProduk - 1; i++) {
            for (int j = 0; j < jumlahProduk - i - 1; j++) {
                if (jumlahTerjual[j] < jumlahTerjual[j + 1]) {
                    tukarProduk(j, j + 1);
                }
            }
        }

        printf("\nProduk berhasil diurutkan berdasarkan penjualan!\n");
    }

    tampilkanProduk();
}

// ==========================================
// FUNGSI LAPORAN PENJUALAN
// ==========================================

void laporanPenjualan() {
    int totalUnit = 0;
    int indexTerlaris = -1;

    printf("\n");
    printf("=================================================\n");
    printf("               LAPORAN PENJUALAN\n");
    printf("=================================================\n");

    printf("%-5s %-20s %-15s\n",
           "No", "Nama Produk", "Jumlah Terjual");

    printf("-------------------------------------------------\n");

    for (int i = 0; i < jumlahProduk; i++) {
        printf("%-5d %-20s %-15d\n",
               i + 1,
               namaProduk[i],
               jumlahTerjual[i]);

        totalUnit += jumlahTerjual[i];

        if (indexTerlaris == -1 ||
            jumlahTerjual[i] > jumlahTerjual[indexTerlaris]) {
            indexTerlaris = i;
        }
    }

    printf("-------------------------------------------------\n");

    printf("Total unit terjual : %d\n", totalUnit);
    printf("Total pendapatan   : Rp%lld\n", totalPendapatan);

    if (totalUnit == 0) {
        printf("Produk terlaris    : Belum ada penjualan\n");
    } else {
        printf("Produk terlaris    : %s\n",
               namaProduk[indexTerlaris]);

        printf("Jumlah terjual     : %d unit\n",
               jumlahTerjual[indexTerlaris]);
    }

    printf("=================================================\n");
}

// ==========================================
// FUNGSI CEK STOK MENIPIS
// ==========================================

void cekStokMenipis() {
    int ditemukan = 0;

    printf("\n========== PERINGATAN STOK MENIPIS ==========\n");

    for (int i = 0; i < jumlahProduk; i++) {
        if (stok[i] < 5) {
            printf("Nama produk: %-20s Stok: %d\n",
                   namaProduk[i], stok[i]);

            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Semua stok produk masih mencukupi.\n");
    }
}

// ==========================================
// FUNGSI MENU UTAMA
// ==========================================

void menuUtama() {
    printf("\n");
    printf("=================================================\n");
    printf("       SISTEM MONITORING STOK DAN PENJUALAN\n");
    printf("                  KANTIN KAMPUS\n");
    printf("=================================================\n");

    printf("1. Lihat Daftar Produk\n");
    printf("2. Tambah Produk\n");
    printf("3. Ubah Produk\n");
    printf("4. Transaksi Penjualan\n");
    printf("5. Tambah Stok\n");
    printf("6. Cari Produk\n");
    printf("7. Urutkan Produk\n");
    printf("8. Laporan Penjualan\n");
    printf("9. Cek Stok Menipis\n");
    printf("0. Keluar\n");

    printf("=================================================\n");
}

// ==========================================
// PROGRAM UTAMA
// ==========================================

int main() {
    int pilihan;

    dataAwal();

    do {
        menuUtama();

        pilihan = inputPilihan("Masukkan pilihan menu: ", 0, 9);

        switch (pilihan) {
            case 1:
                tampilkanProduk();
                break;

            case 2:
                tambahProduk();
                break;

            case 3:
                ubahProduk();
                break;

            case 4:
                transaksiPenjualan();
                break;

            case 5:
                tambahStok();
                break;

            case 6:
                pencarianProduk();
                break;

            case 7:
                urutkanProduk();
                break;

            case 8:
                laporanPenjualan();
                break;

            case 9:
                cekStokMenipis();
                break;

            case 0:
                printf("\nTerima kasih telah menggunakan program!\n");
                printf("Program selesai.\n");
                break;

            default:
                printf("Menu tidak tersedia!\n");
        }

    } while (pilihan != 0);

    return 0;
}
