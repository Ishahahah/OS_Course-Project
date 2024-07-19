/*Phase1*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class VM
{
private:
    char buffer[40];
    char Memory[100][4];
    char IR[4];  // Instruction Register
    char R[4];   // General purpose Register 
    bool C;     //  Toggle Register
    int IC;     // Instruction counter
    int SI;     // System Interrupt
    fstream infile;
    ofstream outfile;

    void resetAll(){
        fill(buffer, buffer + sizeof(buffer), '\0');
        fill(&Memory[0][0], &Memory[0][0] + sizeof(Memory), '\0');
        fill(IR, IR + sizeof(IR), '\0');
        fill(R, R + sizeof(R), '\0');
        IC = 0;
        C = true;
        SI = 0;
    }

    void resetBuffer(){
        fill(buffer, buffer + sizeof(buffer), '\0');
    }

    void masterMode()
    { // Master Mode
        switch (SI)
        {
        case 1:
            READ();
            break;

        case 2:
            WRITE();
            break;

        case 3:
            TERMINATE();
            break;
        }
        SI = 0;
    }

    void READ()
    {
        cout << "Read function called\n";

        string data;
        getline(infile, data);
        int len = data.size();
        for (int i = 0; i < len; i++)
        {
            buffer[i] = data[i];
        }
        int buff = 0, mem_ptr = (IR[2] - '0') * 10;
        while (buff < 40 && buffer[buff] != '\0')
        {
            for (int i = 0; i < 4; i++)
            {
                Memory[mem_ptr][i] = buffer[buff];
                buff++;
            }
            mem_ptr++;
        }
        resetBuffer();
    }

    void WRITE()
    {
        cout << "Write function called\n";
        outfile.open("output.txt", ios::app);

        for (int i = (IR[2] - '0') * 10; i < (IR[2] - '0' + 1) * 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (Memory[i][j] != '\0')
                {
                    outfile << Memory[i][j];
                }
            }
        }
        outfile << "\n";
        outfile.close();
    }

    void TERMINATE()
    {
        outfile.open("output.txt", ios::app);
        cout << "Terminate called\n\n";
        outfile << "\n\n";
        outfile.close();
    }

    void LOAD(){

        if (infile.is_open())
        {
            string s;
            while (getline(infile, s))
            { 
                if (s[0] == '$' && s[1] == 'A' && s[2] == 'M' && s[3] == 'J'){
                    resetAll();
                    cout<<"New Job started\n";
                }
                else if (s[0] == '$' && s[1] == 'D' && s[2] == 'T' && s[3] == 'A'){
                    cout << "Data card loding\n";
                    resetBuffer();
                    MOSstartexe();
                }

                else if (s[0] == '$' && s[1] == 'E' && s[2] == 'N' && s[3] == 'D'){
                    cout << "END of Job\n";
                    
                    }

                else{

                    cout << "Program Card loding\n";
                    int length = s.size();
                    resetBuffer();

                    // Buffer <-- Program Card
                    for (int i = 0; i < length; i++){
                        buffer[i] = s[i];
                    }
                    int buff = 0;
                    int ref = 0;
                    
                    // Memory <-- Buffer
                    while (buff < 40 && buffer[buff] != '\0'){
                        for (int j = 0; j < 4; j++){
                            if (buffer[buff] == 'H'){
                                Memory[IC][j] = 'H';
                                buff++;
                                break;
                            }
                            Memory[IC][j] = buffer[buff];
                            buff++;
                        }
                        IC++;
                    }
                }
            }
            infile.close(); // Input File closed
        }
    }

    void MOSstartexe(){
        IC = 0;
        executeUserProgram();
    }

    void executeUserProgram(){  // Slave Mode
        while (IC < 99 && Memory[IC][0] != '\0'){

            for (int i = 0; i < 4; i++){
                IR[i] = Memory[IC][i];
            }

            IC++;
            /* System Interupts
                1 - GD 
                2 - PD 
                3 - H 
            */
           // GD - GET DATA
            if (IR[0] == 'G' && IR[1] == 'D'){
                SI = 1;
                masterMode();
            }

            // PD - PRINT DATA
            else if (IR[0] == 'P' && IR[1] == 'D'){
                SI = 2;
                masterMode();
            }

            // H - HALT
            else if (IR[0] == 'H'){
                SI = 3;
                masterMode();
                return;
            }

            // LR - LOAD DATA (R <-- memory[IR[2,3]])
            else if (IR[0] == 'L' && IR[1] == 'R'){
                for (int i = 0; i < 4; i++){
                    R[i] = Memory[(IR[2] - '0') * 10 + (IR[3] - '0')][i];
                }
            }

            // SR - STORE (memory[IR[2,3]] <-- R)
            else if (IR[0] == 'S' && IR[1] == 'R'){
                for (int i = 0; i < 4; i++){
                    Memory[(IR[2] - '0') * 10 + (IR[3] - '0')][i] = R[i];
                }
            }

            // CR - COMPARE(R, memory[IR[2,3]])
            else if (IR[0] == 'C' && IR[1] == 'R'){
                int cnt = 0;
                for (int i = 0; i < 4; i++  ){
                    if (Memory[(IR[2] - '0') * 10 + (IR[3] - '0')][i] == R[i]){
                        cnt++;
                    }
                }
                if (cnt == 4){
                    C = true;
                }
                else{
                    C = false;
                }
            }

            // BT (JUMP if toogle is T)
            else if (IR[0] == 'B' && IR[1] == 'T'){
                if (C){
                    IC = (IR[2] - '0') * 10 + (IR[3] - '0');
                }
            }
        }
    }

public:
    VM()
    {
        infile.open("input.txt", ios::in);
        resetAll();
        LOAD();
    }
};

int main()
{
    VM v;
    return 0;
}