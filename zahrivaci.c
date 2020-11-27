#include <stdio.h>

int main(void) {
  char* citat[5]={(char*)"Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.", "Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.", "Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.","Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.","Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej."};
  printf("%s", "ml' nob:\n");
  int choice;
  if(scanf("%d", &choice)!=1 || choice < 1 || choice >5){
    printf("%s", "luj\n");
  }else{
    printf("%s\n", citat[choice-1]);
  }
    
  return 0;
}