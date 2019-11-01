#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Algorithm{                                                                                //Struct yap˝s˝nda nodelar˝ tutuyor
    int node;
} MST;

bool control(MST** mst, int m,int n,int size){                                                            //Bu fonksiyon m ve n elemanlar˝ ayn˝ k¸mede var m˝ kontrol
    for(int i=0;i<size;i++)                                                                                //yap˝yor.Eer varsa false yoksa true dˆnd¸r¸yor
        for(int j=0;mst[i][j].node!=999;j++)                                                            //i ve j indisleri b¸t¸n elemanlar˝ geziyor
            if(mst[i][j].node==m)                                                                        //eer m eleman˝ varsa ayn˝ k¸mede n eleman˝ aran˝yor
                for(int k=0;mst[i][k].node!=999;k++)
                    if(mst[i][k].node == n)
                        return false;
    return true;
}

bool control2(MST** mst,int m, int n){                                                                    //Bu fonksiyon m K¸mesinde n eleman˝ var m˝ kontrol ediyor
    int k=0;                                                                                            //Eer varsa false yoksa true dˆnd¸r¸yor
    while(mst[m][k].node!=999){                                                                            //M k¸mesinin b¸t¸n elemanlar˝n˝ geziyor
        if(mst[m][k].node == n)                                                                            //n deerine e˛it deer var m˝ bak˝yor
            return false;                                                                                //Eer varsa false dˆnd¸r¸yor
        k++;
    }
    return true;                                                                                        //Yoksa while dan k¸me bitince Á˝k˝yor ve true dˆnd¸r¸yor
}
int birlestir(MST** mst, int i, int j, int size,int q){                                                    //Bu fonksiyon verilen i ve j k¸melerini birle˛tiriyor
    int k=0,b=0;
    while(mst[i][k].node!=999)                                                                            //i k¸mesinin ilk bo˛ adresine kadar ilerliyor
        k++;
    
    while(mst[j][b].node!=999){                                                                            //j k¸mesinin her bir eleman˝n˝ kontrol ediyor
        if(control2(mst,i,mst[j][b].node)){                                                                    //Eer bir eleman i k¸mesinde de var ise eklemiyor
            mst[i][k].node=mst[j][b].node;                                                                    //Eer yoksa eleman˝ i k¸mesine ekliyor
            mst[mst[j][b].node][size-1].node=i;                                                                //Eleman˝n point ettii noktay˝ i yap˝yor
            mst[j][b].node=999;                                                                                //Eleman˝ j k¸mesinden siliyor
            k++;                                                                                            //i k¸mesinin indisini bir artt˝r˝yor
        }else
            mst[mst[j][b].node][size-1].node=i;
        b++;
    }
    
    return ++q;                                                                                            //Ekleme yapt˝˝ iÁin q deerini bir artt˝r˝p dˆnd¸r¸yor
}

int main(){
    
    MST **mst;                                                                                            //Minimum Spanning Tree iÁin nodelar˝ tutan structure
    int **matris,i,j,k,n;                                                                                //Matris dosyadan okunan matrisi haf˝zada tutuyor
    char *line, *ptr;                                                                                    //Dosyadan okuma yaparken kullan˝lan pointerlar
    FILE *fp;                                                                                            //Okunacak dosya iÁin file pointer aÁ˝l˝yor
    printf("Matrisin boyutunu giriniz=");                                                                //Okunacak dosyadaki matrisin boyutu al˝n˝yor
    scanf("%d",&n);
    fp=fopen("dataLab.txt","r");                                                                            //fp pointer˝na text at˝l˝yor
    mst=(MST**)calloc(n,sizeof(MST*));
    for(i=0;i<n;i++)                                                                                //MST struct iÁin calloc ile yer aÁ˝l˝yor(Áift pointer)
        mst[i]=(MST*)calloc(n,sizeof(MST));
    
    for(i=0;i<n;i++){                                                                                //K¸melerin ilk eleman˝na indisini at˝yor
        mst[i][0].node=i;                                                                            //Dier elemanlar˝ min bulabilmek iÁin 999 yap˝yor
        for(j=1;j<n;j++)
            mst[i][j].node=999;
    }
    matris = (int**)malloc(n*sizeof(int*));                                                                //File dan okunan deerleri yazmak iÁin matrise
    for(int i=0; i<n;i++)                                                                            //30-30 luk matris yeri aÁ˝yor (dinamic memory)
        matris[i]= (int*)malloc(n*sizeof(int));
    
    line=(char*)malloc(60*sizeof(char));                                                                //Okunan sat˝rlar iÁin yer aÁ˝yor
    
    for(i=0;i<n;i++){
        line=fgets(line,70,fp);                                                                            //Dosyadaki her sat˝r˝ s˝ras˝ ile line a at˝yor
        ptr=strtok(line,", ");                                                                            //Sat˝rdaki metini ilk ", " gˆrene kadar ptr iÁine at˝yor
        matris[i][0]=atoi(ptr);                                                                            //atoi fonksiyonu ile metini int deere dˆn¸˛t¸p matrise at˝yor
        if(matris[i][0]==0)
            matris[i][0]=999;                                                                            //Eer deer 0 ise min bulabilmek iÁin 999 yap˝yor
        
        for(j=1;j<n;j++){                                                                                //Geriye kalan metin iÁinde her " ," gˆrene kadar ptr at˝yor
            ptr=strtok(NULL," ,");                                                                        //ptr dei˛keninin iÁindeki metini atoi ile int t¸r¸ne dˆn¸˛t¸r¸p
            matris[i][j]=atoi(ptr);                                                                        //matrisin iÁine at˝yor
            if(matris[i][j]==0)
                matris[i][j]=999;                                                                        //Eer deer 0 ise min bulabilmek iÁin 999 yap˝yor
        }
    }
    fclose(fp);
    for(i=0;i<n;i++){                                                                                    //Dosyadan okuduu matrisi formatl˝ ˛ekilde ekrana yazd˝r˝yor
        for(j=0;j<n-1;j++){
            if(matris[i][j]==999)
                printf(" 0 ");
            else
                printf("%2d ",matris[i][j]);
        }
        if(matris[i][n-1]==999)
            printf(" 0 \n");
        else
            printf("%2d \n",matris[i][n-1]);
    }
    
    int count,q=0,min,min_i,min_j;
    printf("Kume sayisini gir=");                                                                        //Toplam kaÁ k¸me istenildii soruluyor
    scanf("%d",&count);
    
    while(q < (n-count)){                                                                                //(Matris boyutu)-(istenilen k¸me say˝s˝) kadar kruskal uygulan˝yor
        
        for(i=0, min=999;i<n;i++)                                                                            //Matrisin ilk indisi iÁin for dˆng¸s¸
            for(j=i+1;j<n;j++)                                                                                //Matrisin ikinci indisi iÁin for dˆng¸s¸
                if(min > matris[i][j]){                                                                        //if ile matrisin elemanlar˝n˝n en k¸Á¸k deeri bulunuyor
                    min_i=i;                                                                            //En k¸Á¸k eleman˝ min dei˛kenine at˝yor
                    min_j=j;                                                                            //En k¸Á¸k eleman˝n indislerini de min_i ve min_j at˝yor
                    min=matris[i][j];
                }
        matris[min_i][min_j]=999;                                                                            //Min deeri bulunduu iÁin matrisin o deerini 999 yap˝yor
        printf("Bulunan minimum: %2d min_i:%2d min_j:%2d\n",min,min_i+1,min_j+1);                            //Bulunan deeri ve indisleri ekrana yazd˝r˝yor
        k=0;
        if(control(mst,min_i,min_j,n)){                                                                        //2 nokta da ayn˝ k¸medeyse dˆng¸ olaca˝ iÁin ekleme yapm˝yor
            if(mst[min_i][0].node==999 && mst[min_j][0].node==999)                                                //2 nokta da bir k¸meye dahil mi bak˝yor
                q=birlestir(mst,mst[min_i][n-1].node,mst[min_j][n-1].node,n,q);                                    //Dahilse dahil olduklar˝ k¸meleri birle˛tiriyor
            else if(mst[min_i][0].node==999)                                                                    //Sadece min_i dahil mi kontrol ediyor
                q=birlestir(mst,mst[min_i][n-1].node,min_j,n,q);                                                //Dahilse min_i nin point ettii k¸meye min_j ekliyor
            else if(mst[min_j][0].node==999)                                                                    //Sadece min_j yi dahil mi kontrol ediyor
                q=birlestir(mst,mst[min_j][n-1].node,min_i,n,q);                                                //Dahilse min_j nin point ettii k¸meye min_i ekliyor
            else if(mst[min_i][0].node==min_i)                  ///////////////////////////////////////////////////////////////////////////////
                q=birlestir(mst,mst[min_i][0].node,min_j,n,q);
            else if(mst[min_j][0].node==min_j)                  //HOCAM BURAYI EKLEDİM SADECE, KÜMENİN İLK ELEMANI MİN i yada MİN J ise HATA VERİYORDU ONU DÜZELTİP BİRLEŞTİRDİM
                q=birlestir(mst,mst[min_j][0].node,min_i,n,q);          ///////////////////////////////////////////////////////////////////////////////////////////
            else{                                                                                               //Eer 2 noktada hiÁbir k¸meye ait deilse
                
                while(mst[min_i][k].node!=999)                                                                        //Eklenecek k¸menin ilk bo˛ yerine gidiliyor
                    k++;
                mst[min_i][k].node=min_j;                                                                            //K¸menin ilk bo˛ yerine min_j deerini at˝yor
                mst[min_j][0].node=999;                                                                                //Dier k¸meyi s˝f˝rl˝yor
                mst[min_j][n-1].node=min_i;                                                                            //Dier k¸menin son eleman˝na eleman˝n nerede olduunu yaz˝yor
                q++;                                                                                                //Ekleme yapt˝˝ iÁin q deerini artt˝r˝yor
            }
        }
    }
    int tmp;
    for(i=0;i<n;i++){
        if(mst[i][0].node!=999){                                                                        //K¸melerin son halini selection sort algoritmas˝ ile
            for(j=0;mst[i][j].node!=999;j++){                                                            //S˝ral˝yor
                min=mst[i][j].node;
                min_i=i;                                                                                    //Her dˆng¸de en k¸Á¸k eleman˝ buluyor ve
                min_j=j;                                                                                    //s˝rayla ba˛a al˝yor
                for(k=j+1;mst[i][k].node!=999;k++){
                    if(min > mst[i][k].node){
                        min=mst[i][k].node;
                        min_i=i;
                        min_j=k;
                    }
                }
                tmp=mst[i][j].node;
                mst[i][j].node=min;
                mst[min_i][min_j].node=tmp;
            }
        }
    }
    
    tmp=0;
    for(i=0;i<n;i++){                                                                                //K¸melerin son halini formatl˝ bir ˛ekilde ekrana yazd˝r˝yor
        if(mst[i][0].node != 999){
            printf("%2d. kume = {",tmp+1);                                                                //÷nce k¸me say˝s˝n˝ yazd˝r˝yor
            for(j=0;mst[i][j].node!=999;j++)
                printf("%2d ",mst[i][j].node+1);                                                            //Ard˝ndan k¸menin iÁeriini yazd˝r˝yor
            tmp++;
            printf("}\n");                                                                                //Ve k¸meyi kapat˝yor
        }
    }
    /*    printf("\nNereyi point ettikleri\n");                                                            //Hangi noktan˝n hangi k¸meye i˛aret ettiini yazd˝r˝yor
     for(i=0;i<n;i++)
     printf("%d. -> %d\n",i+1,mst[i][n-1].node+1);*/
    printf("\n");
    return 0;
}

