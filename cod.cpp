#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    for(int i=1; i<=5; i++)
    {
    char palavra[100];
    FILE* arq;
    int resultado;
    string nomedoarquivo= "./documentos/d" +to_string(i);
    nomedoarquivo=nomedoarquivo+".txt";
    cout<<nomedoarquivo<<endl;
    arq=fopen(nomedoarquivo.c_str(), "rt");
    if(arq==NULL)
    {
        cout<<"Não foi possivel localizar arquivo"<<endl;
        return 0;
    }
    
   while (resultado= fscanf(arq,"%s",palavra) != EOF)
    {
        
        cout<<palavra<<endl;
    }
    }
    return 0;
}
