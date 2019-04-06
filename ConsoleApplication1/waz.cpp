#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>
#include <cstdlib>

using namespace std;


struct cialo{
int x;
int y;
};

char ekran[30][50]; //tutaj rysuje bydlaka i jabuszko;



int przycisk(){
    static int pamietacz=2;

    if(GetKeyState(VK_UP) < 0&&pamietacz!=3)
    {
        //cout<<GetKeyState(VK_UP)<<" ";
        pamietacz =1;
        return 1;
    }
    if(GetKeyState(VK_RIGHT) < 0&&pamietacz!=4)
    {
        //cout<<GetKeyState(VK_RIGHT)<<" ";
        pamietacz =2;
        return 2;
    }
    if(GetKeyState(VK_DOWN) < 0&&pamietacz!=1)
    {
        //cout<<GetKeyState(VK_DOWN)<<" ";
        pamietacz =3;
        return 3;
    }
    if(GetKeyState(VK_LEFT) < 0&&pamietacz!=2)
    {
        //cout<<GetKeyState(VK_LEFT)<<" ";
        pamietacz =4;
        return 4;
    }

    return pamietacz;

}

int main(){

 for(int i=0;i<30;i++)
        for(int j=0;j<50;j++)
            ekran[i][j]=' ';

//czêœæ wejœciowa
//ramka
for(int i=0;i<50;i++)
    ekran[0][i]='#';
for(int i=0;i<50;i++)
    ekran[29][i]='#';
for(int i=0;i<30;i++)
    ekran[i][0]='#';
for(int i=0;i<30;i++)
    ekran[i][49]='#';

srand(time(NULL));
vector <cialo> waz;
int pozycja_glowy=0;
cialo bufor;
cialo jedzonko;
jedzonko.x=rand()%48+1;
jedzonko.y=rand()%28+1;
bufor.x=25;
bufor.y=15;
waz.push_back(bufor);
bufor.x=bufor.x-3;
waz.push_back(bufor);
bufor.x++;
waz.push_back(bufor);
bufor.x++;
waz.push_back(bufor);


while(true){//g³ówna pêtla gry wychodzenie breake;

    for(int i=1;i<29;i++)
        for(int j=1;j<49;j++)//czyszcze ekran
            ekran[i][j]=' ';


    switch(przycisk()){
    case 2:
        if(pozycja_glowy!=waz.size()-1)
        {
            waz[pozycja_glowy+1].x=waz[pozycja_glowy].x+1;
            waz[pozycja_glowy+1].y=waz[pozycja_glowy].y;
            pozycja_glowy++;
        }else
        {
            waz[0].x=waz[pozycja_glowy].x+1;
            waz[0].y=waz[pozycja_glowy].y;
            pozycja_glowy=0;
        }
    break;
    case 4:
        if(pozycja_glowy!=waz.size()-1)
        {
            waz[pozycja_glowy+1].x=waz[pozycja_glowy].x-1;
            waz[pozycja_glowy+1].y=waz[pozycja_glowy].y;
            pozycja_glowy++;
        }else
        {
            waz[0].x=waz[pozycja_glowy].x-1;
            waz[0].y=waz[pozycja_glowy].y;
            pozycja_glowy=0;
        }
    break;
    case 3:
        if(pozycja_glowy!=waz.size()-1)
        {
            waz[pozycja_glowy+1].y=waz[pozycja_glowy].y+1;
            waz[pozycja_glowy+1].x=waz[pozycja_glowy].x;
            pozycja_glowy++;
        }else
        {
            waz[0].y=waz[pozycja_glowy].y+1;
            waz[0].x=waz[pozycja_glowy].x;
            pozycja_glowy=0;
        }
    break;
    case 1:
        if(pozycja_glowy!=waz.size()-1)
        {
            waz[pozycja_glowy+1].y=waz[pozycja_glowy].y-1;
            waz[pozycja_glowy+1].x=waz[pozycja_glowy].x;
            pozycja_glowy++;
        }else
        {
            waz[0].y=waz[pozycja_glowy].y-1;
            waz[0].x=waz[pozycja_glowy].x;
            pozycja_glowy=0;
        }
    break;

    };
    bool kolizja=0;
    for(int i=0;i<waz.size();i++)
        if(waz[pozycja_glowy].x==waz[i].x&&waz[pozycja_glowy].y==waz[i].y&&pozycja_glowy!=i)
            kolizja=1;
    if(waz[pozycja_glowy].x==0||waz[pozycja_glowy].y==0||waz[pozycja_glowy].x==49||waz[pozycja_glowy].y==29)
        kolizja=1;
    if(waz[pozycja_glowy].y==jedzonko.y&&waz[pozycja_glowy].x==jedzonko.x)
    {
        jedzonko.x=rand()%48+1;
        jedzonko.y=rand()%28+1;
        if(pozycja_glowy==0)
        {
            bufor.y=waz[waz.size()-1].y;
            bufor.x=waz[waz.size()-1].x;
        }else if(pozycja_glowy==1)
        {
            bufor.y=waz[0].y;
            bufor.x=waz[0].x;
        }
        else
        {
            bufor.y=waz[pozycja_glowy-1].y;
            bufor.x=waz[pozycja_glowy-1].x;
        }
        waz.insert(waz.begin()+pozycja_glowy++,bufor);
    }




    for(int i=0;i<waz.size();i++)
        ekran[waz[i].y][waz[i].x]='X';//rysowanie byfdlaka
    ekran[jedzonko.y][jedzonko.x]='@';
    ekran[waz[pozycja_glowy].y][waz[pozycja_glowy].x]='0';
    string buforektranu;
    buforektranu.clear();
    //przekazywanie "pixeli" do jednego "obrazka"
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<50;j++)
            buforektranu+=ekran[i][j];
        buforektranu+="\n";
    }
    //robie takie cuda z tym buforem bo wyświetlanie znak po znaku strasznie źle działało
    system("cls");
    //wyswietlanie weza

    cout<<buforektranu;
//    cout<<endl<<waz[0].x<<waz[0].y;
//    cout<<endl<<waz[1].x<<waz[1].y;
//    cout<<endl<<waz[2].x<<waz[2].y;
//    cout<<endl<<pozycja_glowy;
    Sleep(400);
    if(kolizja==1)
        break;

}
system("cls");
cout<<"============Przegrałes============="<<endl<<"twoj wynik to :"<<waz.size();
Sleep(10000);
return 0;
}
