#include <iostream>

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
	//int program[] = {2,5,4,501,4,513,3,7,5,514,8,10,10,4,512,0};
	//int program[] = {12,12,13,14,15,17,0,0};
	int program[] = {1,1,2,12,3,12,4,12,5,12,6,12,7,12,8,9,10,12,11,12,12,13,1,16,1,0,14,15,16,12,17,12,0,17,12};
	int programSize = (sizeof(program)/sizeof(program[0]));
	int displacement = OSmemory + programSize;
 
	loadProgramInMemory(memory,program,programSize);
	//printMemory(memory,0,16);

	int Xreg = 0, Yreg = 0, IPreg = 0;

	for(; IPreg < programSize;) {

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
				printMemory(memory,500,520);
				IPreg+=2;
			break;

			case 5:
				// MOV(m,y) instruction
				memory[memory[IPreg+1] + displacement] = Yreg;
				printMemory(memory,500,520);
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
			default:
				IPreg++;
		}
		cout<<"\nXreg: "<<Xreg<<"\n";
		cout<<"Yreg: "<<Yreg<<"\n";
	}
	

	return 0;

}