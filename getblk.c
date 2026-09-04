#include<stdio.h>

typedef struct block{
    int blk_id;
    int status; //0:free 1:occupied 2:dw
    struct block *next;
} block;

block getblk(int bid, block bf[]){
    int found = 0, blkid, i=0;

    for(i=0; i<10; i++){
        blkid = bf[i].blk_id;
        if(blkid==bid){
            if(bf[i].status==1){
                printf("BLOCK FOUND : state=allocated\n");
                continue;
            }else{
                bf[i].status = 1;
                printf("FOUND : CASE 1");
                return bf[i];
            }
        }else{
            if(bf[i].status == 2){
                printf("BLOCK NOT FOUND : state=delayed write\n");
                continue;
            }else if(bf[i].status ==0){
                printf("FOUND : CASE 2\n");
                bf[i].blk_id = bid;
                bf[i].status = 1;
                break;
            }else{
                printf("NO ANY BLOCK AVAILABLE : state=sleep\n");
                continue;
            }
        }
    }
}
int main(){
    
    block b9 = {9,1,NULL};
    block b8 = {8,0,NULL};
    block b7 = {7,2,NULL};
    block b6 = {6,1,NULL};
    block b5 = {5,1,NULL};
    block b4 = {4,0,&b5};
    block b3 = {3,2,&b4};
    block b2 = {2,1,&b3};
    block b1 = {1,1,&b2};
    
    block blk_buffer[9] = {b1,b2,b3,b4,b5,b6,b7,b8,b9};

    block allocated = getblk(3, blk_buffer);
}

/*
node *getblk(node* ht[4], int id){ //13 ht[]
    int found ==0;
    idx = hashfn(id);
    node* current = ht[idx];
    
    for(int i=0; i<sizeof(ht); i++){
        current=ht[i];
        while(current != NULL){
            if(current->id == id){
                if(current->freestat != NULL){
                    printf("NODE FOUND: c1 s1");
                    return current;
                }else{
                    printf("NODE FOUND: BUSY s5");
                    current = current->next;
                }
            }
        } //do i need to search only in free list after?
    }    
    
    if(current->freestat == NULL){
        printf("FREE LIST EMPTY: s4");
        current = current->next;
    }else if(current->dw == 1){
        printf("DELAYED WRITE: s3");
        current = current->next;
    }else{
        printf("NODE FOUND: c2 s2");
        return current; //*current; returns dereferenced value node
    }
}
*/