#include "Graphics.h"

using namespace std;

Graphics::Graphics(int base, int lenght, float score){
  this->base = base;
  this->lenght = lenght;
  this->score = score;
}

void Graphics::description(){
  cout << "   ";
  cout << "PROGRAM";
  cout << "    ";
  cout << "WARNING";
  cout << "\n";
}

void subtitles(float c, float w, float e){
  cout << "\033[32m ♦ \033[0m";
  cout << "Código correto " << "(" << (round(c*10000)/100) << "%)";
  cout << "\n";
  cout << "\033[31m ♦ \033[0m";
  cout << "Código incorreto " << "(" << (round(e*10000)/100) << "%)";
  cout << "\n";
  cout << "\033[33m ♦ \033[0m";
  cout << "Warning " << "(" << (round(w*10000)/100) << "%)";
  cout << "\n";
}

void Graphics::boundaries(int b){
    for(int i = 0; i < b; i ++)
        cout << "-";
    cout << "\n";
}

void Graphics::graph(float c, float w, float e){
  cout << "\n";
  for(int i = this->lenght; i > 0; i --){
    cout << "     ";
    if(i <= round(this->lenght*c))
      for(int j = this->base; j > 0; j --)
        cout << "\033[32m█\033[0m";

    if(i >= round(this->lenght*c) + 1){
      for(int j = this->base; j > 0; j --)
        cout << "\033[31m█\033[0m";
      }
      cout << "        ";

    if(i <= round(this->lenght*w))
    for(int j = this->base; j > 0; j --)
      cout << "\033[33m█\033[0m";
      cout << "\n";
  }

  description();
  boundaries(30);
  subtitles(c, w, e);
  scorePrint();
  boundaries(30);
}

void Graphics::scorePrint(){
  cout << "\n\nSCORE: " << this->score << " (0-10)\n";
}
