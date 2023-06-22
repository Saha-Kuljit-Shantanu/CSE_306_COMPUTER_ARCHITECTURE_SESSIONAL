#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<stdlib.h>
#include<map>
#include<algorithm>

///CLONPHADFMKBGJIE

using namespace std;

map <string,char> hashmap;

map <string,string> labelmap;

map <string,char> jumpmap;

void Init_Map(){

    hashmap["sub"] = '0'; ///R
    hashmap["lw"] = '1'; ///I
    hashmap["bneq"] = '2'; ///I
    hashmap["beq"] = '3'; ///I
    hashmap["j"] = '4'; ///J
    hashmap["jal"] = '4'; ///J
    //hashmap["jr"] = '4'; ///J
    hashmap["ori"] = '5'; ///I
    hashmap["add"] = '6'; ///R
    hashmap["subi"] = '7'; ///I


    hashmap["andi"] = '8'; ///I
    hashmap["sw"] = '9'; ///I
    hashmap["nor"] = 'a'; ///R
    hashmap["addi"] = 'b'; ///I
    hashmap["or"] = 'c'; ///R
    hashmap["srl"] = 'd';/// S
    hashmap["sll"] = 'e';/// S
    hashmap["and"] = 'f'; ///R
    hashmap["jr"] = 'f';

    hashmap["$zero"] = '0';
    hashmap["$t0"] = '1';
    hashmap["$t1"] = '2';
    hashmap["$t2"] = '3';
    hashmap["$t3"] = '4';
    hashmap["$t4"] = '5';
    hashmap["$sp"] = '6';
    hashmap["$ra"] = '7';
    hashmap["$a0"] = '8';
    hashmap["$a1"] = '9';
    hashmap["$v0"] = 'a';
    hashmap["$v1"] = 'b';
    hashmap["$s0"] = 'c';
    hashmap["$s1"] = 'd';

    jumpmap["j"] = '0';
    //jumpmap["jal"] = '1';
    //jumpmap["jr"] = '2';

}

char type(char k){

    if( k == '0' || k == '6' || k == 'a' || k == 'c' ||  k == 'f'){

        return 'R';
    }

    if( k == 'd' || k == 'e' ){

        return 'S';
    }

    else if( k == '4'){

        return 'J';
    }

    else if( k == '1' || k == '9'){

        return 'i';
    }

    else if( k == '2' || k == '3'){

        return 'B';
    }


    else return 'I';

}

string removeSpaces(string input)
{
    input.erase(std::remove(input.begin(),input.end(),' '),input.end());
    input.erase(std::remove(input.begin(),input.end(),'\t'),input.end());
    return input;
}

int main(){

    bool jr = false;

    ifstream file ("input.txt");
    ofstream fout("output.txt");

    fout << "v2.0 raw" << endl;

    int cnt =-1,num,jal;
    char hexa = 'H',tp,jtp = '0';

    string t;

    Init_Map();

    string line,word;
    char words[3];

    while(getline(file,line)){

        if(strlen(line.c_str()) == 0){

            continue;
        }

        else {

            //line = line.erase(remove(line.begin(),line.end(),' '),line.end());

            stringstream v;

            int a = line.find(":");
            if( a >= 0){

                    line = line.substr(0,a+1);
                    cout << "Found label : " << line << endl;
                    v << hex << cnt+1;
                    if(cnt<16) labelmap[line] = '0' + v.str();
                    else labelmap[line] = v.str();
                    if(a != strlen(line.c_str() )-1)cnt++;
                    continue;

            }

        }

        cout << cnt << " " << line << endl;

        cnt++;


    }


    file.close();
    ifstream fin ("input.txt");

    cnt= -1;

    while(getline(fin,line)){



        stringstream x(line),y,z(line),w(line),v,u,k,l;

        num = 0;

        if(strlen(line.c_str()) == 0){

            continue;
        }

        while(1){

            if(line[num] == '\t'){

                //break;
                num++;
                getline(x,word,'\t');
            }
            else if(line[num] == ' '){

                num++;
                getline(x,word,' ');
            }




            else break;
        }

        cnt ++;

        if(getline(x,word,' ')){

            hexa = word[strlen(word.c_str()) -1];
            if(hexa == ':'){

               v << hex << cnt;
               //if(cnt<16) labelmap[word] = '0' + v.str();
               //else labelmap[word] = v.str();
               continue;

            }

            hexa = hashmap[word];
            if(word == "jr") jr = true;
            if(type(hexa) == 'J' && word == "jal") {

                u << hex << cnt+1;

                jumpmap[word] = u.str()[0];
                jtp = jumpmap[word];

            }
            cout << hexa;
            fout << hexa;
            getline(z,word,' ');
            //hashmap["jr"] = '4'; ///J
            //v << hex << cnt;
            //labelmap[word] = v.str();
            //continue;
            //

        }

        else cout << "Error Generated" << endl;


        if(hexa != 'H') tp = type(hexa);

        if(tp == 'J' && getline(x,word,' ')){

            //word = word.erase(remove_if(word.begin(),word.end(),isspace),word.end());
            //word = word.erase(remove(word.begin(),word.end(),'\t'),word.end());
            word = removeSpaces(word);

            //cout << word << endl;


            words[0] = labelmap[word+":"][0];

            words[1] = labelmap[word+":"][1];

            words[2] = jtp;

            jtp = '0';
            cout << words[0] << words[1]<< words[2] << endl;
            fout << words[0] << words[1]<< words[2] << " ";
            continue;
        }

        else if(getline(x,word,',')){

            word = removeSpaces(word);

            if(hashmap[word] == '7' && jr == true){
                fout << "ff7" << " ";
                jr = false;
                continue;
            }

            if(tp == 'R') words[2] = hashmap[word];
            if(tp == 'I') words[1] = hashmap[word];
            if(tp == 'i') words[1] = hashmap[word];
            if(tp == 'S') words[1] = hashmap[word];
            if(tp == 'B') words[1] = hashmap[word];
            //cout << hexa;
            getline(z,word,',');

        }

        else cout << "Error Generated1" << endl;

        //stringstream z(x.str());


        if(getline(x,word,'(') && tp == 'i'){

            word = removeSpaces(word);


            num = stoi(word);
            if(num >= 0) y << hex << num;
            else y << hex << 16+num;
            words[2] = y.str()[0] ;
            //cout << words[2];


        }

        else if(getline(z,word,',')){

            word = removeSpaces(word);


            if(tp == 'R' ) words[0] = hashmap[word];
            if(tp == 'I' ) words[0] = hashmap[word];
            if(tp == 'S' ) words[0] = hashmap[word];
            if(tp == 'B') words[0] = hashmap[word];
            //cout << hexa;

        }

        else cout << "Error Generated2" << endl;

        //cout << x.str() << z.str();

        //stringstream w(x.str());

        if(getline(x,word,')') && tp == 'i'){//cout <<x.str();

            word = removeSpaces(word);

            words[0] = hashmap[word];

        }

        else if(getline(z,word,',')){

            word = removeSpaces(word);


            if(tp == 'R' ) words[1] = hashmap[word];
            if(tp == 'I' || tp == 'S') {

                num = stoi(word);
                if(num >= 0) y << hex << num;
                else y << hex << 16+num;
                words[2] = y.str()[0];
            }

            if(tp == 'B'){

                 y << hex << stoi(labelmap[word+":"],0,16) - cnt;
                 words[2] = y.str()[0];
            }

            //cout << hexa;

        }

        else cout << "Error Generated3" << endl;

        cout << words[0] << words[1]<< words[2] << endl;
        fout << words[0] << words[1]<< words[2] << " ";








    }

    fout.close();
}
