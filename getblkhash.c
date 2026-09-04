#include<stdio.h>

typedef struct node{
    //int k;
    int id;
    int dw;
    struct node* freestat;
    struct node* next;
} node;

int hashfn(int blkno){
    return blkno%3;
}

node *getblk(node* ht[4], int id){ //13 ht[]
    int found =0;
    int idx = hashfn(id);
    node* current = ht[idx];
        
    while(current != NULL){
        if(current->id == id){
            if(current->freestat != NULL && current->dw != 1){
                printf("NODE FOUND: c1 s1 : %d", current->id);
                found = 1;
                current->freestat = NULL;
                return current;
            }else{
                printf("NODE FOUND: BUSY s5");
                return NULL;
            }
        }
        current = current->next;
    }
    if(found==0){
        current = ht[3]->freestat;
        while(current!=NULL){ //do i need to search only in free list after?
            if(current->next == NULL){
                printf("FREE LIST EMPTY: s4");
                return NULL;
            }else if(current->dw == 1){
                printf("DELAYED WRITE: s3");
                current = current->freestat;
            }else{
                printf("NODE FOUND: c2 s2: %d", current->id);
                return current; //*current; returns dereferenced value node
            }
        }
    }
}

int main(){

    node n01,n02,n03,n04,n05,n11,n12,n13,n14,n15,n21,n22,n23,n24,n25;
    node freelst;//{-1, 0, &n02, NULL};

    n05 = (node){15, 0, NULL, NULL};
    n04 = (node){12, 1, &n11, &n05};
    n03 = (node){9, 0, NULL, &n04};
    n02 = (node){6, 0, &n04, &n03};
    n01 = (node){3, 0, NULL, &n02}; //h

    n15 = (node){16, 0, NULL, NULL};
    n14 = (node){13, 1, &n22, &n15};
    n13 = (node){10, 0, NULL, &n14};
    n12 = (node){7, 0, NULL, &n13};
    n11 = (node){4, 0, &n14, &n12}; //h

    n25 = (node){14, 0, NULL, NULL};
    n24 = (node){11, 1, &freelst, &n25}; //n&02 or NULL -> fl loops back to head ?
    n23 = (node){8, 0, NULL, &n24};
    n22 = (node){5, 1, &n24, &n23};
    n21 = (node){2, 0, NULL, &n22}; //h
    

    node* HashTab[4] = {&n01, &n11, &n21, &freelst};

    node* availbuff = getblk(HashTab, 51);
    //node* availbuff = getblk(HashTab, 10);
    //node* availbuff = getblk(HashTab, 5);

    

}