#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void initializeStack(Stack *s) {
    s->top = -1;
    printf("Stack diinisialisasi\n");
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

int isStackFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(Stack *s, int value) {
    if (isStackFull(s)) {
        printf("Stack penuh, tidak dapat menambah elemen\n");
    } else {
        s->data[++s->top] = value;
        printf("%d berhasil ditambahkan ke stack\n", value);
    }
}

int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack kosong, tidak ada elemen yang dihapus\n");
        return -1;
    } else {
        int poppedValue = s->data[s->top--];
        printf("%d dihapus dari stack\n", poppedValue);
        return poppedValue;
    }
}

int peek(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack kosong, tidak ada elemen teratas\n");
        return -1;
    } else {
        return s->data[s->top];
    }
}

int getStackSize(Stack *s) {
    return s->top + 1;
}

void clearStack(Stack *s) {
    s->top = -1;
    printf("Stack dikosongkan\n");
}

int main() {
    Stack s;
    initializeStack(&s);
    int choice, value;

    do {
        printf("\nMenu Stack\n");
        printf("1. Tambah Data (Push)\n");
        printf("2. Hapus Data (Pop)\n");
        printf("3. Lihat Elemen Teratas (Peek)\n");
        printf("4. Lihat Jumlah Elemen (Size)\n");
        printf("5. Kosongkan Stack (Clear)\n");
        printf("6. Keluar\n");
        printf("Pilih operasi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan elemen: ");
                scanf("%d", &value);
                push(&s, value);
                break;
            case 2:
                pop(&s);
                break;
            case 3:
                value = peek(&s);
                if (value != -1) {
                    printf("Elemen teratas: %d\n", value);
                }
                break;
            case 4:
                printf("Jumlah elemen dalam stack: %d\n", getStackSize(&s));
                break;
            case 5:
                clearStack(&s);
                break;
            case 6:
                printf("Keluar dari program\n");
                break;
            default:
                printf("Pilihan tidak valid, silakan coba lagi\n");
        }
    } while (choice != 6);

    return 0;
}

