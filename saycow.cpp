#include <iostream>
#include <string>
using namespace std;

int print_message(string);
void draw_cow(int);

int main()
{
    string entrada;

    cout << "Say what the cow should say: ";
    getline(cin, entrada);

    draw_cow(print_message(entrada));


    return 0;
}

int print_message(string msg)
{
    int size = msg.length();
    int mid = size / 2;
    for(int line=0; line<3; line++)
    {
        if(line == 1)
        {
            cout << "< " << msg << " >" << endl;

            continue;
        }
        cout << " ";
        for(int i=0; i<size+2; i++)
        {
            cout << "-";
        }
        cout << " " << endl;

    }
    return mid;
}

void draw_cow(int mid)
{
    for(int linha=1; linha<=5; linha++)
    {
        for(int i=0; i<mid; i++)
        {
            cout << " ";
        }
        
        if(linha == 1)
        {
            cout << "\\   ^__^";
        }
        else if(linha == 2)
        {
            cout << " \\  (oo)\\_______";
        }
        else if(linha == 3)
        {
            cout << "    (__)\\       )\\/\\";
        }
        else if(linha == 4)
        {
            cout << "        ||----w |";
        }
        else
        {
            cout << "        ||     ||";
        }
        
        cout << endl;
    }


}