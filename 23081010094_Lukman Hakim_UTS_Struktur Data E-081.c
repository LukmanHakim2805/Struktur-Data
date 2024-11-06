#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa {
    char nama[50];
    char jenis_kelamin;
    struct Mahasiswa* next;
};

// Fungsi untuk membuat mahasiswa baru
struct Mahasiswa* buatMahasiswa(char nama[], char jenis_kelamin) {
    struct Mahasiswa* pnew = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
    if (pnew == NULL) {
        printf("Memory allocation Gagal!\n");
        exit(1);
    }
    strcpy(pnew->nama, nama);
    pnew->jenis_kelamin = jenis_kelamin;
    pnew->next = NULL;
    return pnew;
}

// Fungsi untuk menambahkan mahasiswa ke lingkaran
void tambahMahasiswa(struct Mahasiswa** head, char nama[], char jenis_kelamin) {
    struct Mahasiswa* pnew = buatMahasiswa(nama, jenis_kelamin);

    if (*head == NULL) {
        *head = pnew;
        (*head)->next = *head; 
    } else {
        struct Mahasiswa* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = pnew;
        pnew->next = *head; 
    }
}

// Fungsi untuk menampilkan seluruh mahasiswa dalam lingkaran
void tampilkanLingkaran(struct Mahasiswa* head) {
    if (head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }
    struct Mahasiswa* temp = head;
    do {
    printf("Nama : %s , jenis kelamin : %c \n", temp->nama, temp->jenis_kelamin);
        temp = temp->next;
    } while (temp != head);
}

// Fungsi untuk memisahkan lingkaran menjadi mahasiswa laki-laki dan perempuan
void pisahkanLingkaran(struct Mahasiswa* head, struct Mahasiswa** lingkaranLaki, struct Mahasiswa** lingkaranPerempuan) {
    if (head == NULL) {
        printf("Lingkaran kosong, tidak ada yang bisa dipisahkan.\n");
        return;
    }

    struct Mahasiswa* temp = head; 
    struct Mahasiswa* tailLaki = NULL; 
    struct Mahasiswa* tailPerempuan = NULL; 

    do {
        struct Mahasiswa* pnew = buatMahasiswa(temp->nama, temp->jenis_kelamin);
        
        if (temp->jenis_kelamin == 'L') {
            if (*lingkaranLaki == NULL) {
                *lingkaranLaki = pnew;
                tailLaki = pnew;
                tailLaki->next = *lingkaranLaki; 
            } else {
                tailLaki->next = pnew;
                tailLaki = pnew;
            }
            tailLaki->next = *lingkaranLaki; 
        } else if (temp->jenis_kelamin == 'P') {
            if (*lingkaranPerempuan == NULL) {
                *lingkaranPerempuan = pnew;
                tailPerempuan = pnew;
                tailPerempuan->next = *lingkaranPerempuan; 
            } else {
                tailPerempuan->next = pnew;
                tailPerempuan = pnew;
            }
            tailPerempuan->next = *lingkaranPerempuan; 
        }

        temp = temp->next; 
    } while (temp != head);


    if (tailLaki) {
        tailLaki->next = *lingkaranLaki;
    }
    if (tailPerempuan) {
        tailPerempuan->next = *lingkaranPerempuan;
    }

    printf("Lingkaran telah dipisahkan menjadi mahasiswa laki-laki dan mahasiswi perempuan.\n");
}

// Fungsi untuk menghapus mahasiswa berdasarkan nama
void hapusMahasiswa(struct Mahasiswa** head, char nama[]) {
    if (*head == NULL) {
        printf("Lingkaran kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    struct Mahasiswa *current = *head, *prev = NULL;
    int found = 0;

    do {
        if (strcmp(current->nama, nama) == 0) {
            found = 1;
            if (prev == NULL) {
                
                struct Mahasiswa* temp = *head;
                while (temp->next != *head) {
                    temp = temp->next;
                }
                temp->next = current->next; 
                *head = current->next; 
            } else {
                
                prev->next = current->next;
            }
            free(current);
            printf("Mahasiswa %s telah dihapus.\n", nama);
            return;
        }
        prev = current;
        current = current->next;
    } while (current != *head);

    if (!found) {
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n", nama);
    }
}

// Menu baru setelah pemisahan lingkaran
void menuSetelahPemisahan(struct Mahasiswa* lingkaranLaki, struct Mahasiswa* lingkaranPerempuan) {
    int pilihan;
    do {
        printf("\nMenu Setelah Pemisahan Lingkaran:\n");
        printf("1. Tampilkan Lingkaran Mahasiswa Laki-Laki\n");
        printf("2. Tampilkan Lingkaran Mahasiswi Perempuan\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("\nLingkaran Mahasiswa Laki-Laki:\n");
                tampilkanLingkaran(lingkaranLaki);
                break;
            case 2:
                printf("\nLingkaran Mahasiswi Perempuan:\n");
                tampilkanLingkaran(lingkaranPerempuan);
                break;
            case 3:
                printf("Kembali ke menu utama...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        
        if (pilihan == 1 || pilihan == 2) {
            printf("Tekan Enter untuk melanjutkan...");
            getchar(); 
            getchar(); 
            system("cls"); 
        }
    } while (pilihan != 3);
}

// Fungsi utama
int main() {
    struct Mahasiswa* lingkaran = NULL;
    struct Mahasiswa* lingkaranLaki = NULL;
    struct Mahasiswa* lingkaranPerempuan = NULL;
    int pilihan;
    int count = 0; // Inisialisasi penghitung jumlah mahasiswa

    do {
        printf("1. Tambah Mahasiswa Laki-Laki\n");
        printf("2. Tambah Mahasiswi Perempuan\n");
        printf("3. Tampilkan Lingkaran\n");
        printf("4. Mahasiswa yang ingin keluar dari lingkaran\n");
        printf("5. Pisahkan Lingkaran\n");
        printf("6. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                if (count >= 20) {
                    printf("Jumlah maksimum mahasiswa telah tercapai (20 mahasiswa).\n");
                    break;
                }
                char nama[50];
                printf("Masukkan Nama Laki-Laki: ");
                scanf("%s", nama);
                tambahMahasiswa(&lingkaran, nama, 'L');
                count++; 
                system("cls"); 
                break;
            }
            case 2: {
                if (count >= 20) {
                    printf("Jumlah maksimum mahasiswa telah tercapai (20 mahasiswa).\n");
                    break;
                }
                char nama[50];
                printf("Masukkan Nama Perempuan: ");
                scanf("%s", nama);
                
                if(nama == cindy)
                tambahMahasiswa(&lingkaran, nama, 'P');
                count++; 
                system("cls"); 
                break;
            }
            case 3:
                printf("\nLingkaran Saat Ini:\n");
                tampilkanLingkaran(lingkaran);
                printf("Tekan Enter untuk melanjutkan...");
                getchar(); 
                getchar(); 
                system("cls"); 
                break;
            case 4: {
                char nama[50];
                printf("Masukkan Nama Mahasiswa yang Ingin Dihapus: ");
                scanf("%s", nama);
                hapusMahasiswa(&lingkaran, nama);
                count--; 
                system("cls"); 
                break;
            }
            case 5:
                pisahkanLingkaran(lingkaran, &lingkaranLaki, &lingkaranPerempuan);
                menuSetelahPemisahan(lingkaranLaki, lingkaranPerempuan);
                break;
            case 6:
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 6);

    return 0;
}

