#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <locale.h>
#include <ctype.h>

int main()
{
    setlocale(LC_ALL,"Turkish");
    int secim=0;
    int secim2=0;
    char txtName[100][150];
    int *z,*hh;
    char yetimEtiket[100][100];
    openFile(txtName,&z);

    while(secim!=4)
    {

        printf("\n\n\n\t\t          *-*-*-*-*-MENU-*-*-*-*-*\n\n");
        printf( "                   1. Arama Yapmak icin secin\n" );
        printf( "                   2. Guncelleme icin secin\n" );
        printf( "                   3. Dosyaya yazma\n" );
        printf( "                   4. Cikis\n\n" );
        printf( "                   Seciminiz: ");
        scanf("%d",&secim );

        switch(secim )
        {
        case 1:
            printf( "Arama Ekrani aciliyor\n\n\n" );
            char aranan[70];
            printf("aranan kelimeyi giriniz:");
            fflush(stdin);
            gets(aranan);
            printf("%s\n",aranan);
            ariyorum(txtName,z,aranan);
            openFile(txtName,&z);
            output_buluyorum(txtName,z,yetimEtiket,&hh,secim2);

            break;
        case 2:
            printf( "guncelleme Ekrani aciliyor\n\n\n" );
            char etiket[70];
            char yeni_etiket[70];
LOOP:
            printf("Yapmak Istediginiz Guncellemeyi Seciniz\n");
            printf(" 1 : Etiket Degistirme\n 2 : Yetim Etiket Degistirme\n");
            fflush(stdin);
            scanf("%d",&secim2);
            if(secim2==1 || secim2==2)
            {
                if(secim2==1)
                {
                    printf("Guncellemek istediginiz etiketi giriniz:");
                    fflush(stdin);
                    gets(etiket);
                    printf("Yeni etiketi giriniz:");
                    fflush(stdin);
                    gets(yeni_etiket);
                    update(txtName,z,etiket,yeni_etiket);
                    openFile(txtName,&z);
                    output_buluyorum(txtName,z,yetimEtiket,&hh,secim2);
                }
                if(secim2==2)
                {
                    output_buluyorum(txtName,z,yetimEtiket,&hh,secim2);
                    printf("Guncellemek istediginiz etiketi giriniz:");
                    update2(txtName,z,yetimEtiket,hh);
                    secim2=0;
                    output_buluyorum(txtName,z,yetimEtiket,&hh,secim2);
                    printf("Yetim etiket guncellendi.\n");
                }
            }
            else
            {
                printf("Luften gecerli rakam giriniz!\n");
                goto LOOP;
            }




            break;
        case 3:
            printf( "Dosyaya yaziliyor\n\n\n" );
            output_buluyorum(txtName,z,yetimEtiket,&hh,secim2);

            break;
        case 4:
            printf( "menuden cikildi\n\n\n" );
            exit(0);
        default:
            printf( "Giris kabul edilmedi. Duzgun rakam giriniz.\n\n\n" );
            break;
        }
        fflush(stdin);
    }
    return 0;
}
void openFile(char txtName[][150],int *z)
{
    DIR *dir;
    struct dirent *entity;
    DIR *dir_2;
    struct dirent *entity_2;
    char *dosyaYolu="C:\\\\Users\\uzumc\\\\OneDrive\\\\Masaüstü\\\\Üniversite\\\\";
    // char txtName[30][150];
    char d_ismi[50][50];
    char d_ismi_2[50][50];
    int i=0,j=0,a=0;
    int    k=0;

    if ((dir = opendir (dosyaYolu)) != NULL)
    {

        while ((entity = readdir (dir)) != NULL)
        {
            //printf ("--------%s-------\n", entity->d_name);
            char dosyaYolu_2[80]="C:\\\\Users\\\\uzumc\\\\OneDrive\\\\Masaüstü\\\\Üniversite\\\\";
            strcat(dosyaYolu_2,entity->d_name);

            if((dir_2=opendir(dosyaYolu_2)) != NULL)
            {
                // printf("Dosya icine giriliyor: %s \n",dosyaYolu_2);
                while((entity_2 = readdir(dir_2)) != NULL)
                {
                    char dosyaYolu_3[30][80];
                    strcpy(dosyaYolu_3[a],dosyaYolu_2);
                    strcat(dosyaYolu_3[a],"\\\\");
                    //printf(" dosya yolu 3: %s \n",dosyaYolu_3[a]);
                    //printf("Klasor adi: %s  Dosya adi:%s\n",entity->d_name,entity_2->d_name);
                    strcat(dosyaYolu_3[a],entity_2->d_name);
                    if(strstr(dosyaYolu_3[a],".txt")!=NULL)
                    {
                        if(strstr(dosyaYolu_3[a],"output.txt")==NULL)
                        {
                            // printf("Txt dosyasi bulundu.\n");
                            strcpy(txtName[k],dosyaYolu_3[a]);
                            // printf("index : %d    txtName :     %s\n",k,txtName[k]);
                            k++;
                        }

                    }
                    a++;
                }
            }

        }
    }
    else
    {
        perror ("");
        return EXIT_FAILURE;
    }
    *z=k;
    closedir(dir_2);
    closedir (dir);

}
void ariyorum(char dosyaYolu[][150],int k,char aranan[20])
{
    FILE *dosya;
    int i=0;
    printf("\n");
  /* for(i=0; i<k; i++)
    {
        printf("Dosya ismi : %s  \n",dosyaYolu[i]);

    }*/
    char buf[5000];
    char cumle[5000]="";
    int sonuc;
    int sonuc_2;
    int sayac=0;
    int sayac_2=0;
    char aranan_2[20]="[[";
    strcat(aranan_2,aranan);
    strcat(aranan_2,"]]");
    int etiket_mi=0;
    char kelime_3;
    char buf2[200];
    char konum[50][150];
    int konum_satiri[50];
    // printf("\n\n\n");
    for(i=0; i<k; i++)
    {
        if((dosya=fopen(dosyaYolu[i],"a+")) == NULL )
        {
            printf("dosya acilamadi!\n");
            exit(1);
        }
        else
        {
            // printf("dosya acma basarili: %s \n",dosyaYolu[i]);
            int satir_sayisi = 0;
            // satir satir okuma islemi
            while ( fgets( buf, 200, dosya) != NULL )
            {

                strcpy(buf2,buf);
                satir_sayisi++;

                if(strstr(buf,aranan_2)!= NULL)
                {
                    // printf("Etiket buldum knk :)\n");
                    etiket_mi++;
                    sayac_2++;
                }

                char *ptr=strstr(buf2,aranan);
                while(ptr!=NULL)
                {
                    int index=ptr-buf2;
                    // printf("\n\n%d\n",ptr);
                    int uzunluk = strlen(aranan);
                    if( buf2[index+uzunluk] == ' ' || buf2[index+uzunluk] == '.' || buf2[index+uzunluk] == ']' || buf2[index+uzunluk] == ','
                            || buf2[index+uzunluk] == ':' || buf2[index+uzunluk] == '[' || buf2[index+uzunluk] == '(' || buf2[index+uzunluk] == ')')
                    {
                        //printf("dosya yolu: %s \n %d . satirda geciyor.. \n",dosyaYolu[i],satir_sayisi);
                        strcpy(konum[sayac],dosyaYolu[i]);
                        konum_satiri[sayac]=satir_sayisi;
                        sayac++;
                    }
                    ptr = strstr(ptr+1, aranan);
                }
            }
            fclose(dosya);
        }

    }


    if(sayac!=0)
    {
        printf("----ARADIGINIZ KELIME BULUNDU----\n");

        if(etiket_mi!=0)
        {
            printf("aradiginiz kelime bir etikettir.\n");
            printf("%s kelimesi %d kere geciyor\n",aranan,sayac);
        }
        else
        {
            printf("aradiginiz kelime bir etiket degildir.\n");
            printf("%s kelimesi %d kere geciyor\n",aranan,sayac);
        }
        for(i=0; i<sayac; i++)
        {
            printf("Dosya Yolu: %s\n %d . satirda geciyor.\n",konum[i],konum_satiri[i]);
        }
    }
    else
    {
        printf("aradiginiz kelime bulunamadi..");
    }


}


output_buluyorum(char dosyaYolu[][150],int k,char tagListYetim[][100],int *hh,int secim)
{
    FILE *dosya;
    char etikets[500][50];
    char buf[5000];
    char *p,*q;
    int X,a=0,i,j,b,n;
    int    g=0;
    int h=0;
    int f=0;   ///f=tum etiketlerin tekrarsiz sayisi h=yetim icin g=yetim olmayan etiket sayisi
    int e_sayac=0;
    char s1[]="[[";
    char s2[]="]]";
    char tagList[100][50]= {};
    ///char  tagListYetim[100][50] ;        /// --->  yetim etiketler tekrarsiz bir sekilde buradadýr
    char etiketListe[100][50];         ///--->  tüm etikeler tekrarsýz bir sekilde burada tutulur
    int yetim[100];
    int duz[100];
    printf("\n");

    for(i=0; i<k; i++)
    {
        if((dosya=fopen(dosyaYolu[i],"a+")) == NULL )
        {
            printf("dosya acilamadi!\n");
            exit(1);
        }
        else
        {
            int satir_sayisi = 0;
            // satir satir okuma islemi
            while ( fgets( buf, 500, dosya) != NULL )
            {
                satir_sayisi++;

                const char *ayrac = ".,;\n:"; // bosluk, nokta ve virgul, noktali virgul...
                char *kelime = strtok(buf,ayrac);
                while (kelime != NULL)
                {
                    if(p=strstr(kelime,s1))
                    {
                        if(q=strstr(kelime,s2))
                        {
                            // printf("bu arkadas etikettir..%s  \n",kelime);
                            // printf("%u -- %u \n",p,q);
                            X=q-(p+2);
                            // printf("\n %d \n",X);
                            strncpy(etikets[a],p+2,X);
                            etikets[a][X]='\0';
                            // printf("---%s---\n",etikets[a]);
                            a++;

                        }
                    }
                    kelime = strtok(NULL, ayrac);
                }

            }

        }

        fclose(dosya);
    }

    int kacTane[a];
    int etiketSay[a];
    for(i=0; i<a; i++)
    {
        etiketSay[i]=1;
        kacTane[i]=0;
        //	printf("b:%d\n",kacTane[i]);
    }
    strcpy(etiketListe[0],"aa");
    int etiketVarMi=0;

    int say1=0;
    strcpy(etiketListe[0],etikets[0]);
    f=1;
    for(i=0; i<a; i++)
    {
        etiketVarMi=0;

        for(n=0; n<=i; n++)
        {

            if(strcmp(etikets[i],etiketListe[n])==NULL)
            {
                etiketVarMi++;
                //say1++;
                // etiketSay[f]=say1;
                // printf("%10s: %d\n",etikets[i],etiketSay[f]);

            }
        }

        if(etiketVarMi==0)
        {
            // say1=1;
            //printf("ayni etiket var mi kontrol..\n");
            //printf("1etiketler: %s \n",etikets[i]);
            strcpy(etiketListe[f],etikets[i]);
            //etiketSay[f]=say1;
            //printf("etiketler: %s \n",etikets[i]);
            //printf("index : %2d  etiket: %27s       sayisi: %d\n",f,etiketListe[f],say1);
            f++;
            //say1++;

        }
    }
    for(i=0; i<f; i++)
    {
        for(j=0; j<a; j++)
        {
            if(strcmp(etiketListe[i],etikets[j])==NULL)
            {
                say1++;
            }
        }
        etiketSay[i]=say1;
        say1=0;
    }
    for(i=0; i<f; i++)          //etiketleri sirasiyla gonderiyoruz
    {
        for(j=0; j<k; j++)   //dosyalaryn hepsini etiket ile karsilastiriyoruz
        {
            if(strstr(dosyaYolu[j],etiketListe[i])!=NULL)
            {
                e_sayac++;
            }
        }
        if(e_sayac==0)
        {
            strcpy(tagListYetim[h],etiketListe[i]);
            yetim[h]=etiketSay[i];
            //printf("Yetim etiket         : %27s              %d\n",etiketListe[i],etiketSay[i]);
            h++;
        }
        else
        {
            strcpy(tagList[g],etiketListe[i]);
            duz[g]=etiketSay[i];
            //printf("Dumduz etiket olanlar: %27s              %d\n",tagList[g],etiketSay[i]);
            g++;
        }
        e_sayac=0;
    }
    char outpuTxt[5][30];
    for(i=0; i<3; i++)
    {
        strcpy(outpuTxt[i],"");
    }
    FILE *dosyaptr_2;
    dosyaptr_2=fopen("C:\\\\Users\\uzumc\\\\OneDrive\\\\Masaüstü\\\\Üniversite\\\\output.txt","a+");
    fprintf(dosyaptr_2,"\n%30s\n","Guncel Liste");
    strcpy(outpuTxt[0],"                    Etiket Listesi            Miktar\n");
    fprintf(dosyaptr_2,"%30s\n",outpuTxt[0]);
    int saysay[f];
    printf("\n\n                Etiket Listesi             Miktar\n");
    for(i=0; i<f; i++)
    {
        //printf("  %27s                   %d\n",tagList[i],duz[i]);
        printf("  %27s                   %d\n",etiketListe[i],etiketSay[i]);
        fprintf(dosyaptr_2,"%30s:			%d\n",etiketListe[i],etiketSay[i]);
    }
    printf("\n\n        Yetim Etiket Listesi\n");
    strcpy(outpuTxt[1], "\n           Yetim Etiket Listesi\n");
    fprintf(dosyaptr_2,"%30s\n",outpuTxt[1]);
    for(j=0; j<h; j++)
    {
        printf("	%27s\n",tagListYetim[j]);
        fprintf(dosyaptr_2,"%.30s\n",tagListYetim[j]);
    }

    fclose(dosyaptr_2);

    int i_sayac=0,i2=0,j2=0;
    char tagListIstenen[50][100];
    ///istenen etiket bulma
    printf("\n                Istenen Etiketler:\n");
    for(i=0; i<k; i++)              ///dosyalar, sýrasýyla gönderiyoruz
    {
        for(j=0; j<f; j++)          ///etiketleri sirasiyla gönderiyoruz
        {
            if(strstr(dosyaYolu[i],etiketListe[j])!=NULL)
            {
                i_sayac++;
            }
        }
        if(i_sayac==0)
        {
            char txtDosyaIsmi[20][35];


            const char *ayrac = "\\";
            char *kelime = strtok(dosyaYolu[i], ayrac);
            while (kelime != NULL)
            {
                /// printf("%s\n", kelime);
                char *iptr=0;
                if((iptr=strstr(kelime,".txt"))!=NULL)
                {
                    int xx=iptr-kelime;
                    /// printf("%d--\n",j2);
                    /// printf("aaa----%s---\n",txtDosyaIsmi[j2]);
                    strncpy(txtDosyaIsmi[j2],kelime,xx);
                    txtDosyaIsmi[j2][xx+1]='\0';
                    printf("        %27s\n",txtDosyaIsmi[j2]);
                    j2++;
                }
                kelime = strtok(NULL, ayrac);
            }
           /// strcpy(tagListIstenen[i2],dosyaYolu[i]);
            //printf("Istenen etiket         : %27s\n",dosyaYolu[i]);
            i2++;
        }
        i_sayac=0;
    }
    *hh=h;

    if(secim!=2)
    {
        return main();
        exit(0);
    }

}

void update(char dosyaYolu[][150],int k,char etiket[70],char yeni_etiket[70])
{
    FILE *dosya;
    FILE *dosyaptr;
    int a=0;

    char buf[500]="";                               ///="Guz Zorunlu dersler: [[Matematik_I]] , [[Programlama_I]].";
    char buf2[500]="";
    char buf3[5000]="";
    char bos[5000]="";
    char kelime[40]="";
    char ara[70]="[[";
    strcat(ara,etiket);
    strcat(ara,"]]");
    char ara2[70]="[[";
    strcat(ara2,yeni_etiket);
    strcat(ara2,"]]");
    int sayac2=0;
    for(a=0; a<k; a++)
    {
        if((dosya=fopen(dosyaYolu[a],"a+")) == NULL )
        {
            printf("dosya acilamadi!\n");
            exit(1);
        }
        else
        {
            int sayac=0;
            /// printf("Dosya acildi. %s\n",dosyaYolu[a]);
            int satir_sayisi = 0;
            // satir satir okuma islemi
            while ( fgets(buf, 200, dosya) != NULL )
            {
                satir_sayisi++;
                memcpy(buf2,bos,500);
                int i,j,len;
                len=strlen(ara);
                i=0,j=0;
                int length=strlen(buf);
                while(i<=length)
                {
                    strncpy(kelime,&buf[i],len);
                    kelime[len]='\0';
                    if(strcmp(kelime,ara)==0)
                    {
                        strcat(buf2,ara2);
                        i=i+len-1;
                        j=j+strlen(ara2)-1;
                        sayac++;
                        sayac2++;
                    }
                    else
                        buf2[j]=buf[i];

                    i++;
                    j++;
                }
                strcat(buf3,buf2);
            }
            fclose(dosya);

            if(sayac!=0)
            {
                //printf("\nDosya Yolu:%s \n%s\n",dosyaYolu[a],buf3);
                dosyaptr=fopen(dosyaYolu[a],"w");
                fprintf(dosyaptr,"%s\n",buf3);
                sayac=0;
                fclose(dosyaptr);
            }
            memcpy(buf3,bos,5000);
        }
    }

    char etiket2[70]="\\";
    strcat(etiket2,etiket);
    strcat(etiket2,".txt");
    // printf("%s      :%d \n",etiket2,strlen(etiket2));
    char yetiket2[70]="";
    strcpy(yetiket2,yeni_etiket);
    strcat(yetiket2,".txt");
    //printf("%s      :%d \n",yetiket2,strlen(yetiket2));

    int ij=0;
    while(ij<k)
    {
        char *ptr=NULL;
        ptr=strstr(dosyaYolu[ij],etiket2);

        if(ptr!=NULL)
        {
            int duzunluk=ptr-dosyaYolu[ij];
            //printf("%d-----\n",duzunluk);

            char yeniDosya[150]="";
            memcpy(yeniDosya,dosyaYolu[ij],duzunluk+1);
            strcat(yeniDosya,yetiket2);
            // printf("%s++++++\n",yeniDosya);
            // printf("%s++++++\n",dosyaYolu[ij]);
            int result;
            result=rename(dosyaYolu[ij],yeniDosya);
            if(result==0)
            {
                printf("Islem basarili\n");
            }
            else
            {
                //printf("olmadi ..\n");
            }
        }

        ij++;
    }

    if(sayac2==0)
    {
        printf("Yanlis kelime girdiniz!!!\n");
    }
    else
        printf("GUNCELLEME BASARILI BIR SEKILDE GERCEKLESMISTIR...\n");


}

void update2(char dosyaYolu[][150],int k,char yetimEtiket[][100],int hh)
{
    char etiket[70];
    fflush(stdin);
    gets(etiket);
    char etiket1[70]="";
    strcpy(etiket1,etiket);

    ///printf("\n%s-------\n\n\n",etiket2);
    ///printf("%d-------\n",sizeof(etiket2));
    char etikwt[70]="[[";
    strcat(etikwt,etiket);
    strcat(etikwt,"]]");
    ///printf("\n%s-------\n\n\n",etikwt);

   /// printf("\n%s-------\n\n\n",etikwt);
    int i=0,j=0;
    int kontrol=0;
    int kontrol2=0;
    int yy;


    int kod=200;
    while(j<hh)
    {
        ///printf("---%s--\n",tagListYetim[j]);
        char *yptr;
        yptr=strstr(yetimEtiket[j],etiket);
        /// printf("\n%s*-*-*-*%s-*-*\n",yetimEtiket[j],etiket);


        if(yptr!=NULL)
        {
            ///printf("-%s----\n",yetimEtiket[j]);
            ///printf("Yetim etikettir..\n");
            kontrol=1;
            break;
        }
        j++;
    }
      char etiket2[]="\\";
    strcat(etiket2,etiket1);
    strcat(etiket2,".txt");

    if(kontrol==1)
    {
        while(i<k)
        {
            char *eptr;
            eptr=strstr(dosyaYolu[i],etiket2);

            if(eptr!=NULL)
            {
                printf("Girdiginiz kelime ile zaten bir txt dosyasi mevcuttur...\n");
                break;
            }
            else
            {
                /// printf("txt dosyasi da yok..\n");
                kontrol2=1;
                break;
            }
        }
    }
    else
    {
        printf("Girdiginiz kelime yetim etiket degildir..\n");
    }


    char dosyaYolu_2[100]="C:\\\\Users\\uzumc\\\\OneDrive\\\\Masaüstü\\\\Üniversite\\\\Dersler\\";
    strcat(dosyaYolu_2,etiket2);
    printf("%s----\n",dosyaYolu_2);
    char bos[70]="";
    memcpy(etiket2,bos,70);
    strcat(etikwt,"[[");
    strcat(etikwt,etiket);
    strcat(etikwt,"]]");
   /// printf("%s\n",etikwt);
   /// printf("%s\n",etiket2);
    if(kontrol2==1)
    {
        FILE *dosyaa;
        printf("Dosya  olusturuldu..\n");
        dosyaa=fopen(dosyaYolu_2,"w");

          fprintf(dosyaa,"Dersin Kodu : BLM%d\n",kod);
          fprintf(dosyaa,"Dersin Adi : %s\n",etikwt);
          fprintf(dosyaa,"Dersin Icerigi : ");
          fclose(dosyaa);
        kod++;
    }

    return main();
    exit(0);
}




