#include <stdio.h>
#include <stdlib.h>

struct macierz{
  unsigned int il_wierszy;
  unsigned int il_kolumn;
  double **wspolczynniki;
};

struct macierz* stworz_macierz(unsigned int n, unsigned int m){
  struct macierz *a;
  int i;
  a=(struct macierz*)malloc(sizeof(struct macierz));
  a->il_wierszy=n;
  a->il_kolumn=m;
  a->wspolczynniki=(double**)malloc(sizeof(double)*n);
  for(i=0;i<n;i++)
  {
    a->wspolczynniki[i]=(double*)malloc(sizeof(double)*m);
  }
  return a;
}

void zwolnij_macierz(struct macierz *a){
  int i;
  for(i=0;i<a->il_wierszy;i++)
    free(a->wspolczynniki[i]);
  free(a->wspolczynniki);
  free(a);
}

struct macierz* przemnoz_macierz(struct macierz *a,struct macierz *b)
{
  int i,j,k;
  struct macierz *c;
  if(a==NULL || b==NULL || a->il_kolumn!=b->il_wierszy)
    return NULL;
  c=stworz_macierz(a->il_wierszy,b->il_kolumn);
  for(i=0;i<a->il_wierszy;i++)
  {
    for(j=0;j<b->il_kolumn;j++)
    {
      c->wspolczynniki[i][j]=0;
      for(k=0;k<b->il_wierszy;k++)
      {
        c->wspolczynniki[i][j]+=a->wspolczynniki[i][k]*b->wspolczynniki[k][j];
      }
    }
  }
  return c;
}

void wypisz_macierz(struct macierz *a)
{
  int i,j;
  for(i=0;i<a->il_wierszy;i++)
  {
    for(j=0;j<a->il_kolumn;j++)
    {
      printf("%lf ",a->wspolczynniki[i][j]);
    }
    printf("\n");
  }
}

struct macierz* wczytaj_macierz_ze_strumienia(FILE *strumien)
{
  unsigned int n, m;
  int i,j;
  struct macierz *a;
  fscanf(strumien,"%u %u",&n ,&m);
  a=stworz_macierz(n,m);
  for(i=0;i<n;i++)
  {
    for(j=0;j<m;j++)
    {
      fscanf(strumien,"%lf",&a->wspolczynniki[i][j]);
    }
  }
  return a;
}

struct macierz* wczytaj_macierz_z_pliku(char *nazwa_pliku)
{
    struct macierz *a;
    FILE *strumien;
    strumien=fopen(nazwa_pliku,"r");
    if(strumien==NULL)
      return NULL;
    a=wczytaj_macierz_ze_strumienia(strumien);
    fclose(strumien);
    return a;
}

void zapisz_macierz_do_strumienia(struct macierz* m, FILE* strumien){
     int i, j;
     fprintf(strumien, "%d %d\n", m->il_wierszy, m->il_kolumn);
     for(i=0; i<m -> il_wierszy; i++)
    {
        for(j=0; j< m -> il_kolumn; j++)
        {
            fprintf(strumien,"%lf ",m->wspolczynniki[i][j]);
        }
        fprintf(strumien,"\n");
    }
}

void zapisz_macierz_do_pliku(struct macierz* m,const char *nazwa_pliku )
{
    FILE *strumien;
    strumien=fopen(nazwa_pliku, "wt");
    if(strumien==NULL)
    {
        exit(1);
    }
    zapisz_macierz_do_strumienia(m,strumien);
    fclose(strumien);
}

int main(int argc, char* argv[])
{
  struct macierz *a,*b,*c;
    if(argc==1)
    {
        a=wczytaj_macierz_ze_strumienia(stdin);
    }
    else
    {
        a=wczytaj_macierz_z_pliku(argv[1]);
    }
    if(argc<=2)
    {
        b=wczytaj_macierz_ze_strumienia(stdin);
    }
    else
    {
        b=wczytaj_macierz_z_pliku(argv[2]);
    }
    c=przemnoz_macierz(a,b);
    if(argc<=3)
    {
        zapisz_macierz_do_strumienia(c,stdout);
    }
    else
    {
       zapisz_macierz_do_pliku(c,argv[3]);
    }
  zwolnij_macierz(a);
  zwolnij_macierz(b);
  zwolnij_macierz(c);
  return 0;
}
