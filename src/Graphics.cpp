#include "Graphics.h"

using namespace std;

Graphics::Graphics(int base, int lenght){
  this->base = base;
  this->lenght = lenght;
}

void Graphics::description(){
  cout << "###";
  cout << " \033[32mcorrect\033[0m ";
  cout << " \033[33mwarning\033[0m ";
  cout << " \033[31merror\033[0m ";
  cout << "\n";
}

void Graphics::percentage(int i){
  cout << i*10;
  cout << "%";

  if(i < 10)
    cout << "   ";
  else
    cout << "  ";
}

void Graphics::boundaries(int b){
  for(int i = 0; i < b; i ++)
    cout << "#";
}

void Graphics::graph(int c, int w, int e){
  for(int i = this->lenght; i > 0; i --){
  percentage(i);

  if(i <= c)
    for(int j = this->base; j > 0; j --)
      cout << "\033[32m*\033[0m";
    cout << "      ";

  if(i <= w)
    for(int j = this->base; j > 0; j --)
      cout << "\033[33m*\033[0m";
    cout << "     ";

  if(i <= e)
    for(int j = this->base; j > 0; j --)
      cout << "\033[31m*\033[0m";
    cout << "\n";
  }

  description();
}
