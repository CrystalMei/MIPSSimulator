#include "reg.hpp"
#include "env.hpp"
#include <iostream>
using namespace Env;
using std::vector;

namespace MIPS {
Reg::Reg() : BaseComponent("Register Stack")
{
	memory.resize(max_reg_num);
}
void Reg::onChange()
{
	// Add your code here
	setOutput(readData1,memory[in[readReg1]]);
	setOutput(readData2,memory[in[readReg2]]);

	//std::cout << in[readReg1]<<output(readData1)<<' ';

}

void Reg::onClock()
{
	if(in[regWrite] == 1) memory[in[writeReg]] = in[writeData];
	else if(in[regWrite] == 2) memory[31] = in[newPC]+4;
	onChange();
}

void Reg::logStatus()
{
	printf("=========================\n");
	printf("Reg value: \n");
	for (int i = 0 ; i != memory.size(); ++i)
	{
		printf("r%d\t:%d\n", i, memory[i]);
	}
	printf("=========================\n");
}
}
