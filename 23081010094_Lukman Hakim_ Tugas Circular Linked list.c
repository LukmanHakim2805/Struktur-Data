#include <stdio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahAkhir(node **head);
void tambahData(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void pencarianData(node *head);
void jumlahData(node *head);
void penjumlahanData(node *head);
void tranverse(node *head);

//========================================================

int main() {
    node *head = NULL;
    char pilih;

    do {
        system("cls");
        printf("Masukkan pilihan\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir\n");
        printf("4. Cetak isi list\n");
        printf("5. Hapus data di awal\n");
        printf("6. Hapus data di tengah\n");
        printf("7. Hapus data di akhir\n");
        printf("8. Pencarian data\n");
        printf("9. Jumlah data\n");
        printf("10. Penjumlahan semua data\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);
        
        if (pilih == '1') {
            tambahAwal(&head);
        } else if (pilih == '2') {
            tambahData(&head);
        } else if (pilih == '3') {
            tambahAkhir(&head);
        } else if (pilih == '4') {
            tranverse(head);
            getch();
        } else if (pilih == '5') {
            hapusAwal(&head);
        } else if (pilih == '6') {
            hapusTengah(&head);
        } else if (pilih == '7') {
            hapusAkhir(&head);
        } else if (pilih == '8') {
            pencarianData(head);
        } else if (pilih == '9') {
            jumlahData(head);
        } else if (pilih == '10') {
            penjumlahanData(head);
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);
    
    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) {
            pNew->next = pNew;
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pNew->next = *head;
            pCur->next = pNew;
        }
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);
    
    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) {
            *head = pNew;
            pNew->next = pNew;
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *head;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai: ");
    scanf("%d", &pos);
    printf("bilangan: ");
    scanf("%d", &bil);

    pCur = *head;
    if (pCur == NULL) {
        printf("List kosong, tidak ada data untuk disisipkan.\n");
        getch();
        return;
    }

    do {
        if (pCur->data == pos) {
            pNew = (node *)malloc(sizeof(node));
            if (pNew == NULL) {
                printf("Alokasi memori gagal");
                getch();
                return;
            }
            pNew->data = bil;
            pNew->next = pCur->next;
            pCur->next = pNew;
            return;
        }
        pCur = pCur->next;
    } while (pCur != *head);

    printf("Node dengan nilai %d tidak ditemukan.\n", pos);
    getch();
}

//========================================================

void hapusAwal(node **head) {
    node *pCur, *pTemp;

    if (*head == NULL) {
        printf("List kosong, tidak ada data untuk dihapus.\n");
        getch();
        return;
    }

    if ((*head)->next == *head) {  // Jika hanya ada satu node
        free(*head);
        *head = NULL;
    } else {
        pCur = *head;
        while (pCur->next != *head) {
            pCur = pCur->next;
        }
        pTemp = *head;
        pCur->next = (*head)->next;
        *head = (*head)->next;
        free(pTemp);
    }
    printf("Data di awal berhasil dihapus.\n");
    getch();
}

//========================================================

void hapusTengah(node **head) {
    int pos;
    node *pCur, *pPrev;

    system("cls");
    tranverse(*head);
    printf("\nposisi data yang akan dihapus: ");
    scanf("%d", &pos);

    if (*head == NULL) {
        printf("List kosong, tidak ada data untuk dihapus.\n");
        getch();
        return;
    }

    pCur = *head;
    pPrev = NULL;

    do {
        if (pCur->data == pos) {
            if (pPrev == NULL) { // Jika yang dihapus adalah node pertama
                hapusAwal(head);
            } else {
                pPrev->next = pCur->next;
                free(pCur);
                printf("Data di tengah berhasil dihapus.\n");
            }
            getch();
            return;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    printf("Node dengan nilai %d tidak ditemukan.\n", pos);
    getch();
}

//========================================================

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada data untuk dihapus.\n");
        getch();
        return;
    }

    node *pCur = *head;
    node *pPrev = NULL;

    if ((*head)->next == *head) {  // Jika hanya ada satu node
        free(*head);
        *head = NULL;
    } else {
        while (pCur->next != *head) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *head;
        free(pCur);
    }
    printf("Data di akhir berhasil dihapus.\n");
    getch();
}

//========================================================

void pencarianData(node *head) {
    int bilangan;
    node *pCur = head;

    system("cls");
    printf("Masukkan bilangan yang dicari: ");
    scanf("%d", &bilangan);
    
    if (head == NULL) {
        printf("List kosong.\n");
        getch();
        return;
    }

    do {
        if (pCur->data == bilangan) {
            printf("Data %d ditemukan.\n", bilangan);
            getch();
            return;
        }
        pCur = pCur->next;
    } while (pCur != head);

    printf("Data %d tidak ditemukan.\n", bilangan);
    getch();
}

//========================================================

void jumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    if (head == NULL) {
        printf("List kosong.\n");
        getch();
        return;
    }

    do {
        count++;
        pCur = pCur->next;
    } while (pCur != head);

    printf("Jumlah data di linked list: %d\n", count);
    getch();
}

//========================================================

void penjumlahanData(node *head) {
    int sum = 0;
    node *pCur = head;

    if (head == NULL) {
        printf("List kosong.\n");
        getch();
        return;
    }

    do {
        sum += pCur->data;
        pCur = pCur->next;
    } while (pCur != head);

    printf("Jumlah total dari semua data: %d\n", sum);
    getch();
}

//========================================================

void tranverse(node *head) {
    node *pCur = head;

    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }

    do {
        printf("%d -> ", pCur->data);
        pCur = pCur->next;
    } while (pCur != head);
    printf("(kembali ke awal)\n");
}
