#include <bits/stdc++.h>
using namespace std;
string x;
bool placed[30][30],check_vertical[30][30],check_horizontal[30][30];
int arr[30][30];
void init(){
  for (int i=0;i<=16;i++) for(int j=0;j<=20;j++) {
    arr[i][j]=0;
    check_vertical[i][j]=0;
    check_horizontal[i][j]=0;
    placed[i][j]=0;
  }
}
void print(){
  cout<<"  ";
  for (int i=1;i<=20;i++){
    cout<<char(96+i)<<" ";
  }
  cout<<"\n";
  for (int i=1;i<=16;i++){
    cout<<char(64+i)<<" ";
    for (int j=1;j<=20;j++){
      cout<<arr[i][j]<<" ";
    }
    cout<<"\n";
  }
}
void place(int u){
  if (u==1){
    int z=0,temp[7],cnt=0;
    for (int i=2;i<8;i++){
      z++;
      temp[z]=int(x[i])-48;
    }
    int val1=int(x[0])-64,val2=int(x[1])-96;
    if (x[8]=='h'){
      for (int i=val2;i<=val2+5;i++){
        cnt++;
        arr[val1][i]=temp[cnt];
      }
      cnt=0;
      for (int i=val2+5;i>=val2;i--){
        cnt++;
        arr[val1+1][i]=temp[cnt];
      }
    }
    else if (x[8]=='v'){
      for (int i=val1;i<=val1+5;i++){
        cnt++;
        arr[i][val2+1]=temp[cnt];
      }
      cnt=0;
      for (int i=val1+5;i>=val1;i--){
        cnt++;
        arr[i][val2]=temp[cnt];
      }
    }
  }
  else{
    int dummy;
    int o=0,temp[8],k=0;
    for (int i=0;i<=5;i++){
      o++;
      temp[o]=int(x[i])-48;
    }
    for (int i=1;i<=16;i++){
      for (int j=1;j<=20;j++){
        if (check_horizontal[i][j]){
          for (int z=j;z<=j+5;z++){
            k++;
            arr[i][z]=temp[k]; 
          }
          k=0;
          for (int z=j+5;z>=j;z--){
            k++;
            arr[i+1][z]=temp[k];
          }
          cout<<char(i+64)<<char(j+96)<<"h\n";
          cout.flush();
          goto end;
        }
        if (check_vertical[i][j]){
          for (int z=i;z<=i+5;z++){
            k++;
            arr[z][j+1]=temp[k];
          }
          k=0;
          for (int z=i+5;z>=i;z--){
            k++;
            arr[z][j]=temp[k];
          }
          cout<<char(i+64)<<char(j+96)<<"v\n";
          cout.flush();
          goto end;
        }
      }
    }
    end:
      dummy=0;
  }
}
void check_placeable(){
  memset(placed,0,sizeof(placed));
  memset(check_horizontal,0,sizeof(check_horizontal));
  memset(check_vertical,0,sizeof(check_vertical));
  for (int i=1;i<=16;i++){
    for (int j=1;j<=20;j++){
      if (arr[i][j]!=0) placed[i][j]=1;
    }
  }
  //Checking horizontal
  bool failsafe;
  int dem;
  for (int i=1;i<=16;i++){
    for (int j=1;j<=15;j++){
      failsafe=false;
      dem=0;
      for (int z=i;z<=i+1;z++){
        for (int y=j;y<=j+5;y++){
          if (placed[z][y+1] || placed[z+1][y] || placed[z-2][y]) failsafe=true;
          if (placed[z][y]) dem++;
        }
      }
      if (dem<=4 && failsafe) check_horizontal[i][j]=true;
    }
  }
  failsafe=false;
  dem=0;
  for (int i=1;i<=11;i++){
    for (int j=2;j<=19;j++){
      dem=0;
      failsafe=false;
      for (int y=j;y<=j+1;y++){
        for (int z=i;z<=i+5;z++){
          if (placed[z+1][y] || placed[z][y+1] || placed[z][y-2]) failsafe=true;
          if (arr[z][y]!=0) dem++;
        }
      }
      if (dem<=4 && failsafe) check_vertical[i][j]=true;
    }
  }
}
int main(){
  init();
  while(true){
    cin>>x;
    check_placeable();
    if (x=="Quit") break;
    else if (x=="Start") continue;
    else if (x.size()==1) continue;
    if (x.size()==6){ 
      place(2);
    }
    else{
      place(1);
    }
    //print();
  }
}