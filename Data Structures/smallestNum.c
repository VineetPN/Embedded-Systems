#include<stdio.h>
int smallestNumber(int n) {
    int k = n;
    for(int i = n; i <= 1000; i++){
        k = i;
        
        while(k > 0){
            if((k & 0x01) == 0x01)
            {
                k>>=1;
            }
            else break;
        }
        if (k == 0) break;
    }
    return k;
}
int main(){
    smallestNumber(5);
}