

#include <cstdlib>
#include <iostream>
#include <string.h>
using namespace std;
template <typename T>
struct Stack {
  T s;
  Stack <T> *next;
};
Stack <double> *HeadX = NULL;
Stack <char> *HeadY = NULL;
char OPZ[512]= "";

int prior(char s) {
  if (s == '=') return 1;
  else if (s == '(') return 2;
  else if ((s == '+') || (s == '-')) return 3;
  else return 4;
}
template <typename T>
void Add(Stack <T> *&Head, T tmp) {
  Stack <T> *New_El = new Stack <T>;
  New_El->next = Head;
  Head = New_El;
  Head->s = tmp;
}

template <typename T>
T Delete(Stack <T> *&Head) {
  Stack <T> *P = Head;
  T s_copy = Head->s;
  Head = Head->next;
  delete P;
  return s_copy;
}

int Operate(int k) {//ѕрименение соответствующей операции
  while (HeadY && (HeadY->s != '(')) {
    char t[] = "  ";
    t[1] = HeadY->s;
    strcat(OPZ, t);
    double tmp;
    if (HeadY->s == '+')
      tmp = Delete(HeadX) + Delete(HeadX);
    else if (HeadY->s == '-'){
      double x = - Delete(HeadX);
      double y = Delete(HeadX);
      tmp = x + y;

    }
    Add(HeadX, tmp);
    Delete(HeadY);
    if (k) return 1;
  }
  if (HeadY)
    Delete(HeadY);
  return 1;
}
void ProstoTak(char s, char tmp[], int &i, int &N) {
  tmp[N] = s;
  i++;
  N++;
}
void read(char string[]) {
  char tmp[80] = " ";
  int N = 1;
  int i = 0;
  while (1){
    if ((string[i] == '-') && (!i || string[i - 1] == '('))
      ProstoTak('-', tmp, i, N);
    else if ((string[i] >= '0') && (string[i] <= '9') || (string[i] == '.'))
      ProstoTak(string[i], tmp, i, N);
    else if (string[i] == 'e')
      for (int k = 0; k <= 3; k++)
        ProstoTak(string[i], tmp, i, N);
    else {
      if (tmp[1] != '\0') {
        tmp[N] = '\0';
        strcat(OPZ, tmp);
        Add(HeadX, atof(tmp));
        tmp[1] = '\0';
        N = 1;
      }
      if (!HeadY || (string[i] == '('))
        Add(HeadY, string[i]);
      else if (string[i] == ')') {
        if (!Operate(0)) return;
      }
      else if (prior(string[i]) > prior(HeadY->s))
        Add(HeadY, string[i]);
      else{
        if (string[i] == '=') {
          if (!Operate(0)) return;
          break;
        }
        if (!Operate(1)) return;
        Add(HeadY, string[i]);
      }
      i++;
    }
  }
  cout << "\nResult: " << HeadX->s;
  cout << "\nOPZ: " << OPZ;
}

int main()
{

  char str[512];
  cout << "vvedite primer: ";
  cin >> str;
  read(str);
}
