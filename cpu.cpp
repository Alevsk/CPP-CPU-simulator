#include <iostream>
#include <unistd.h>

using namespace std;

void printMemory(int memory[], int from, int to) {
	cout<<"\n";
	for(int i = from; i < to; i++) {
		cout<<memory[i]<<" ";
	}
	cout<<"\n";
}

void initMemory(int (&memory)[1024]) {
	int i = 0;
	for(; i < ( sizeof(memory)/sizeof(memory[0]) ); i++) {
		memory[i] = 0;
	}
}

void loadProgramInMemory(int (&memory)[1024], int program[], int size) {
	int i = 0;
	for(; i < size; i++ ) {
		memory[i] = program[i];
		cout<<"memory: "<<memory[i]<<" program: "<<program[i]<<"\n";
	}
}

int main(int argc, char ** argv) {

	int memory[1024];
	initMemory(memory);
	int OSmemory = 512;
	int program[] = {2,200,4,195,2,209,4,196,2,4,197,2,4,198,2,23,4,200,2,12,4,201,2,80,4,202,2,50,4,203,2,70,4,204,2,99,4,205,2,205,4,206,2,17,4,207,2,1,4,208,2,148,4,209,6,195,18,5,199,6,195,7,196,14,16,69,15,1,63,15,17,106,1,74,6,195,12,4,195,18,5,198,6,199,4,197,14,15,16,94,17,100,1,86,6,197,4,199,1,59,7,198,5,199,1,59,0};
	int programSize = (sizeof(program)/sizeof(program[0]));
	int displacement = OSmemory + programSize;
 
	loadProgramInMemory(memory,program,programSize);
	//printMemory(memory,0,16);

	int Xreg = 0, Yreg = 0, IPreg = 0;

	for(; IPreg < programSize;) {
		//sleep(1);

		cout<<"\nInstruccion: "<<memory[IPreg]<<" ip: "<<IPreg<<"\n";
		switch(memory[IPreg]){

			case 0:
				cout<<"Fin del programa\n"<<memory[IPreg];
				return 0;
			break;

			case 1:
				// JMP(#) instruction
				IPreg = memory[IPreg+1];
			break;

			case 2:
				// MOV(x,#) instruction
				Xreg = memory[IPreg+1];
				IPreg+=2;
			break;

			case 3:
				// MOV(y,#) instruction
				Yreg = memory[IPreg+1];
				IPreg+=2;
			break;

			case 4:
				// MOV(m,x) instruction
				memory[memory[IPreg+1] + displacement] = Xreg;
				printMemory(memory,0,1023);
				IPreg+=2;
			break;

			case 5:
				// MOV(m,y) instruction
				memory[memory[IPreg+1] + displacement] = Yreg;
				printMemory(memory,0,1023);
				IPreg+=2;
			break;

			case 6:
				// MOV(x,m) instruction
				Xreg = memory[memory[IPreg+1] + displacement];
				IPreg+=2;
			break;

			case 7:
				// MOV(y,m) instruction
				Yreg = memory[memory[IPreg+1] + displacement];
				IPreg+=2;
			break;

			case 8:
				// ADD(x,y) instruction
				Xreg += Yreg;
				IPreg++;
			break;

			case 9:
				// ADD(y,x) instruction
				Yreg += Xreg;
				IPreg++;
			break;

			case 10:
				// ADD(x,#) instruction
				Xreg += memory[IPreg+1];
				IPreg+=2;
			break;

			case 11:
				// ADD(y,#) instruction
				Yreg += memory[IPreg+1];
				IPreg+=2;
			break;

			case 12:
				// INC(x) instruction
				Xreg++;
				IPreg++;
			break;

			case 13:
				// INC(y) instruction
				Yreg++;
				IPreg++;
			break;

			case 14:
				// DEC(x) instruction
				Xreg--;
				IPreg++;
			break;

			case 15:
				// DEC(y) instruction
				Yreg--;
				IPreg++;
			break;

			case 16:
				// Jz(x,#) instruction
				
				if(Xreg == 0) {
					IPreg = memory[IPreg+1]; 
				} else {
					IPreg+=2;
				}

			break;

			case 17:
				// Jz(y,#) instruction
				
				if(Yreg == 0) {
					IPreg = memory[IPreg+1]; 
				} else {
					IPreg+=2;
				}

			break;

			case 18:
				// mov(y,&x) instruction
				Yreg = memory[Xreg + displacement];
				IPreg++;
			break;

			case 19:
				// mov(&x,y) instruction
				memory[Xreg + displacement] = Yreg;
				IPreg++;
			break;

			default:
				IPreg++;
		}
		cout<<"\nXreg: "<<Xreg<<"\n";
		cout<<"Yreg: "<<Yreg<<"\n";
	}
	

	return 0;

}