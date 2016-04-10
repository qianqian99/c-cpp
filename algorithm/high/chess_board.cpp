#include <iostream>
#include <cstring>
#include <iomanip>
template <typename Type, unsigned Size>
class Chess{
  private:
    int title;
    Type chess[Size][Size];
  public:
    Chess() : title(0){
      memset(chess, 0, sizeof(chess));
    }
    ~Chess(){}
    void chess_board(int, int, int=0, int=0, int=Size);
    void show(){
    for (int i=0; i<Size; ++i) {
     for (int j=0; j<Size; ++j) {
        std::cout <<  std::setw(3) << chess[i][j];
     }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};
template <typename Type, unsigned Size>
void Chess<Type, Size>::chess_board(int dr, int dc, 
                                    int fr, int fc, 
                                    int size){
  if (size > 1){
    int t = ++title;
    int s = size>>1;
    if (dr < fr+s && dc < fc+s){
      chess_board(dr, dc, fr, fc, s);
    }
    else{
      chess[fr+s-1][fc+s-1] = t;
      chess_board(fr+s-1, fc+s-1, fr, fc, s);
    }

    if (dr < fr+s && dc >= fc+s) {
      chess_board(dr, dc, fr, fc+s, s);
    }
    else {
      chess[fr+s-1][fc+s] = t;
      chess_board(fr+s-1, fc+s, fr, fc+s, s);
    }

    if (dr >= fr+s && dc < fc+s) {
      chess_board(dr, dc, fr+s, fc, s);
    }
    else {
      chess[fr+s][fc+s-1] = t;
      chess_board(fr+s, fc+s-1, fr+s, fc, s);
    }

    if (dr >= fr+s && dc >= fc+s) {
      chess_board(dr, dc, fr+s, fc+s, s);
    }
    else {
      chess[fr+s][fc+s] = t;
      chess_board(fr+s, fc+s, fr+s, fc+s, s);
    }
  }
}


int main(){
  Chess<int, 16> chess;
  chess.show();
  chess.chess_board(1,3);
  chess.show();
  return 0;
}







