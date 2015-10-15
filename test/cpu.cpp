#include "gtest/gtest.h"
#include "cpu.hpp"
#include "env.hpp"
#include <stdio.h>
using namespace MIPS;
using namespace Env;
using std::string;
TEST(cpu, addi)
{
    CPU cpu;
    // <input:0> addi $v0, $v0, 32
    cpu.instMem.loadMemory(0x00000000, 0x20420020);
    // End of program
    cpu.instMem.loadMemory(0x00000004, 0xFFFFFFFF);

    EXPECT_EQ(32, cpu.run());
}

TEST(cpu, add)
{
    CPU cpu;
    // <input:0> addi $v0, $v0, 32
    cpu.instMem.loadMemory(0x00000000, 0x20420020);
    // <input:1> add $v0, $v0, $v0
    cpu.instMem.loadMemory(0x00000004, 0x00421020);
    // End of program
    cpu.instMem.loadMemory(0x00000008, 0xFFFFFFFF);
    EXPECT_EQ(64, cpu.run());
}

TEST(cpu, sub)
{
    CPU cpu;
    // <input:0> addi $v0, $v0, 8
    cpu.instMem.loadMemory(0x00000000, 0x20420008);
    // <input:1> addi $v1, $v1, -8
    cpu.instMem.loadMemory(0x00000004, 0x2063fff8);
    // <input:2> sub $v0, $v0, $v1
    cpu.instMem.loadMemory(0x00000008, 0x00431022);
    // End of program
    cpu.instMem.loadMemory(0x0000000c, 0xFFFFFFFF);
    EXPECT_EQ(16, cpu.run());
}

TEST(cpu, lw)
{
    CPU cpu;
    cpu.dataMem.loadMemory(0x00000000, 4);
    cpu.dataMem.loadMemory(0x00000004, 5);
    // <input:0> lw $v1, 0($v0)
    cpu.instMem.loadMemory(0x00000000, 0x8c430000);
    // <input:1> lw $v2, 4($v0)
    cpu.instMem.loadMemory(0x00000004, 0x8c440004);
    // <input:2> sub $v0, $v1, $v2
    cpu.instMem.loadMemory(0x00000008, 0x00641022);
    // End of program
    cpu.instMem.loadMemory(0x0000000c, 0xFFFFFFFF);
    EXPECT_EQ(-1, cpu.run());
}

TEST(cpu, sw)
{
    CPU cpu;
    // <input:0> addi $v1, $v1, 90
    cpu.instMem.loadMemory(0x00000000, 0x2063005a);
    // <input:1> sw $v1, 0($v0)
    cpu.instMem.loadMemory(0x00000004, 0xac430000);
    // <input:2> lw $v0, 0($v0)
    cpu.instMem.loadMemory(0x00000008, 0x8c420000);
    // End of program
    cpu.instMem.loadMemory(0x0000000c, 0xFFFFFFFF);
    EXPECT_EQ(90, cpu.run());
}

TEST(cpu, branch_succ)
{
    CPU cpu;
    cpu.dataMem.loadMemory(0, 4);
    cpu.dataMem.loadMemory(4, 4);
    // <input:0> lw $v1, 0($v0)
    cpu.instMem.loadMemory(0x00000000, 0x8c430000);
    // <input:1> lw $v2, 4($v0)
    cpu.instMem.loadMemory(0x00000004, 0x8c440004);
    // <input:2> beq $v1, $v2, babel
    cpu.instMem.loadMemory(0x00000008, 0x10640001);
    // <input:3> addi $v0, $v0, 1
    cpu.instMem.loadMemory(0x0000000c, 0x20420001);
    // <input:5> addi $v0, $v0, 1
    cpu.instMem.loadMemory(0x00000010, 0x20420001);
    // End of program
    cpu.instMem.loadMemory(0x00000018, 0xFFFFFFFF);
    EXPECT_EQ(1, cpu.run());
}

TEST(cpu, branch_fail)
{
    CPU cpu;
    cpu.dataMem.loadMemory(0, 4);
    cpu.dataMem.loadMemory(4, 5);
    // <input:0> lw $v1, 0($v0)
    cpu.instMem.loadMemory(0x00000000, 0x8c430000);
    // <input:1> lw $v2, 4($v0)
    cpu.instMem.loadMemory(0x00000004, 0x8c440004);
    // <input:2> beq $v1, $v2, babel
    cpu.instMem.loadMemory(0x00000008, 0x10640001);
    // <input:3> addi $v0, $v0, 1
    cpu.instMem.loadMemory(0x0000000c, 0x20420001);
    // <input:5> addi $v0, $v0, 1
    cpu.instMem.loadMemory(0x00000010, 0x20420001);
    // End of program
    cpu.instMem.loadMemory(0x00000018, 0xFFFFFFFF);
    EXPECT_EQ(2, cpu.run());
}

TEST(cpu, feb)
{
    CPU cpu;
    cpu.dataMem.loadMemory(0, 10);
    // <input:0> addi $v1, $v0, 1
    cpu.instMem.loadMemory(0x00000000, 0x20430001);
    // <input:1> addi $v2, $v0, 1
    cpu.instMem.loadMemory(0x00000004, 0x20440001);
    // <input:2> addi $v4, $v0, 1
    cpu.instMem.loadMemory(0x00000008, 0x20460001);
    // <input:3> lw $v3, 0($v0)
    cpu.instMem.loadMemory(0x0000000c, 0x8c450000);
    // <input:5> beq $v4, $v3, next
    cpu.instMem.loadMemory(0x00000010, 0x10c50005);
    // <input:6> add $v5, $v1, $v2
    cpu.instMem.loadMemory(0x00000014, 0x00643820);
    // <input:7> addi $v1, $v2, 0
    cpu.instMem.loadMemory(0x00000018, 0x20830000);
    // <input:8> addi $v2, $v5, 0
    cpu.instMem.loadMemory(0x0000001c, 0x20e40000);
    // <input:9> addi $v4, $v4, 1
    cpu.instMem.loadMemory(0x00000020, 0x20c60001);
    // <input:10> beq $v0, $v0, label
    cpu.instMem.loadMemory(0x00000024, 0x1042fffa);
    // <input:12> addi $v0, $v1, 0
    cpu.instMem.loadMemory(0x00000028, 0x20620000);
    // End of program
    cpu.instMem.loadMemory(0x00000034, 0xFFFFFFFF);
    EXPECT_EQ(55, cpu.run());
}
TEST(cpu, jump)
{
	CPU cpu;
	//j 0x00000002
	cpu.instMem.loadMemory(0x00000000, 0x8000002);

	//addi $v0,$v0,4
	cpu.instMem.loadMemory(0x00000004, 0x20420004);
	//addi $v0,$v0,4
	cpu.instMem.loadMemory(0x00000008, 0x20420004);
	//end
	cpu.instMem.loadMemory(0x0000000C, 0xFFFFFFFF);
	EXPECT_EQ(4, cpu.run());
}
TEST(cpu, jr)
{
	CPU cpu;
	//addi $a0,$a0,16
	cpu.instMem.loadMemory(0x00000000, 0x20840010);
	//jr $a0
	cpu.instMem.loadMemory(0x00000004, 0x00800008);
	//addi $v0,$v0,4
	cpu.instMem.loadMemory(0x00000008, 0x20420004);
	//addi $v0,$v0,4
	cpu.instMem.loadMemory(0x0000000C, 0x20420004);
	//end
	cpu.instMem.loadMemory(0x00000010, 0xFFFFFFFF);
	EXPECT_EQ(0, cpu.run());
}
TEST(cpu, jal)
{
	CPU cpu;
	//add $v0,$v0,$ra
	cpu.instMem.loadMemory(0x00000000, 0x20420004);
	//jal 3
	cpu.instMem.loadMemory(0x00000004, 0x0C000003);
	//addi $v0,$v0,1
	cpu.instMem.loadMemory(0x00000008, 0x20420001);
	//addi $v0,$v0,1
	cpu.instMem.loadMemory(0x0000000C, 0x20420001);
	//add $v0,$v0,$ra
	cpu.instMem.loadMemory(0x00000010, 0x20420004);
	//end
	cpu.instMem.loadMemory(0x00000014, 0xFFFFFFFF);
	EXPECT_EQ(9, cpu.run());
}

int func(int a0)
{
	if (a0 < 3) return a0;

	return func(a0-1)+func(a0-2)*2+func(a0-3)*3;
}
TEST(cpu, project1)
{
    CPU cpu;
	cpu.instMem.loadMemory(0x00000000, 0x20840006);	//addi $a0,$a0,6	
	cpu.instMem.loadMemory(0x00000004, 0x23BD1000);//addi $sp,$sp,4096	
	cpu.instMem.loadMemory(0x00000008, 0x0C000004);//jal FACT	
	cpu.instMem.loadMemory(0x0000000C, 0xFFFFFFFF);//output

	//FACT:	
	cpu.instMem.loadMemory(0x00000010, 0x23BDFFF8);//addi $sp,$sp,-8	
	cpu.instMem.loadMemory(0x00000014, 0xAFBF0004);//sw $ra,4($sp)	
	cpu.instMem.loadMemory(0x00000018, 0xAFA40000);//sw $a0,0($sp)	
	cpu.instMem.loadMemory(0x0000001C, 0x20180003);//addi $t8,$0,3	
	cpu.instMem.loadMemory(0x00000020, 0x0098402A);//slt $t0,$a0,$t8	
	cpu.instMem.loadMemory(0x00000024, 0x10080003);//beq $t0,$0,Line1	
	cpu.instMem.loadMemory(0x00000028, 0x00801020);//add $v0,$0,$a0	
	cpu.instMem.loadMemory(0x0000002C, 0x23BD0008);//addi $sp,$sp,8	 
	cpu.instMem.loadMemory(0x00000030, 0x03E00008);//jr $ra

	//Line1:
	cpu.instMem.loadMemory(0x00000034, 0x2084FFFF);//addi $a0,$a0,-1	
	cpu.instMem.loadMemory(0x00000038, 0x0C000004);//jal FACT	
	cpu.instMem.loadMemory(0x0000003C, 0x00408820);//add $s1,$v0,$0	
	cpu.instMem.loadMemory(0x00000040, 0x23BDFFFC);//addi $sp,$sp,-4	
	cpu.instMem.loadMemory(0x00000044, 0xAFB10000);//sw $s1,0($sp)	
	cpu.instMem.loadMemory(0x00000048, 0x2084FFFF);//addi $a0,$a0,-1	
	cpu.instMem.loadMemory(0x0000004C, 0x0C000004);//jal FACT	
	cpu.instMem.loadMemory(0x00000050, 0x00409020);//add $s2,$v0,$0	
	cpu.instMem.loadMemory(0x00000054, 0x23BDFFFC);//addi $sp,$sp,-4	
	cpu.instMem.loadMemory(0x00000058, 0xAFB20000);//sw $s2,0($sp)	
	cpu.instMem.loadMemory(0x0000005C, 0x2084FFFF);//addi $a0,$a0,-1	
	cpu.instMem.loadMemory(0x00000060, 0x0C000004);//jal FACT	
	cpu.instMem.loadMemory(0x00000064, 0x00409820);//add $s3,$v0,$0	
	cpu.instMem.loadMemory(0x00000068, 0x23BDFFFC);//addi $sp,$sp,-4	
	cpu.instMem.loadMemory(0x0000006C, 0xAFB30000);//sw $s3,0($sp)	
	cpu.instMem.loadMemory(0x00000070, 0x8FB10008);//lw $s1,8($sp)	
	cpu.instMem.loadMemory(0x00000074, 0x8FB20004);//lw $s2,4($sp)	
	cpu.instMem.loadMemory(0x00000078, 0x8FB30000);//lw $s3,0($sp)	
	cpu.instMem.loadMemory(0x0000007C, 0x23BD000C);//addi $sp,$sp,12			
	cpu.instMem.loadMemory(0x00000080, 0x00111020);//add $v0,$s1,$0	
	cpu.instMem.loadMemory(0x00000084, 0x02529020);//add $s2,$s2,$s2
	cpu.instMem.loadMemory(0x00000088, 0x00521020);//add $v0,$s2,$v0		
	cpu.instMem.loadMemory(0x0000008C, 0x20090000);//addi $t1,$0,0	
	cpu.instMem.loadMemory(0x00000090, 0x01334820);//add $t1,$t1,$s3	
	cpu.instMem.loadMemory(0x00000094, 0x02739820);//add $s3,$s3,$s3	
	cpu.instMem.loadMemory(0x00000098, 0x01339820);//add $s3,$s3,$t1	
	cpu.instMem.loadMemory(0x0000009C, 0x00531020);//add $v0,$s3,$v0	
	cpu.instMem.loadMemory(0x000000A0, 0x8FA40000);//lw $a0,0($sp)	
	cpu.instMem.loadMemory(0x000000A4, 0x8FBF0004);//lw $ra,4($sp)	
	cpu.instMem.loadMemory(0x000000A8, 0x23BD0008);//addi $sp,$sp,8	
	cpu.instMem.loadMemory(0x000000AC, 0x03E00008);//jr $ra	

    EXPECT_EQ(func(6), cpu.run());
}

/*
TEST(cpu, project1)
{
    CPU cpu;
	cpu.instMem.loadMemory(0x00000000, 0x20840006);//addi $a0, $a0, 6
	//cpu.instMem.loadMemory(0x00000004, 0x20820000);//addi $v0, $a0, 0
	cpu.instMem.loadMemory(0x00000008, 0x23BD8000);//addi $sp, $sp, 32768
	//fun
	cpu.instMem.loadMemory(0x0000000c, 0x23BDFFE0);//addi $sp, $sp, -32		# create its stack frame
	cpu.instMem.loadMemory(0x00000010, 0xAFBF001C);//sw $ra, 28($sp)		# save the return address
	cpu.instMem.loadMemory(0x00000014, 0xAFBE0018);//sw $fp, 24($sp)		# save $fp of caller
	cpu.instMem.loadMemory(0x00000018, 0xAFB00014);//sw $s0, 20($sp) 		# callee saved registers
	cpu.instMem.loadMemory(0x0000001c, 0xAFB10010);//sw $s1, 16($sp) 		# callee saved registers
	cpu.instMem.loadMemory(0x00000020, 0xAFB2000c);//sw $s2, 12($sp) 		# callee saved registers
	cpu.instMem.loadMemory(0x00000024, 0xAFB30008);//sw $s3, 8($sp) 		# callee saved registers
	cpu.instMem.loadMemory(0x00000028, 0x23BE0020);//addi $fp, $sp, 32

	cpu.instMem.loadMemory(0x0000002c, 0x20900000);//addi $s0, $a0, 0
	cpu.instMem.loadMemory(0x00000030, 0x20080003);//addi $t0, $0, 3;
	cpu.instMem.loadMemory(0x00000034, 0x0110402A);//slt $t0, $t0, $s0
	cpu.instMem.loadMemory(0x00000038, 0x1100001D);//beq $t0, $0, fun_base 		# if n < 3, do the base case

	cpu.instMem.loadMemory(0x0000003c, 0x2204FFFF);//addi $a0, $s0, -1      # compute fun(n-1)
	cpu.instMem.loadMemory(0x00000040, 0x0C000002);//jal fun
	cpu.instMem.loadMemory(0x00000044, 0x20510000);//addi $s1, $v0, 0		# t1 = fun(n-1)

	cpu.instMem.loadMemory(0x00000048, 0x2204FFFE);//addi $a0, $s0, -2 	 	# compute fun(n-2)
	cpu.instMem.loadMemory(0x0000004c, 0x0C000002);//jal fun
	cpu.instMem.loadMemory(0x00000050, 0x20520000);//move $s2, $v0			# t2 = fun(n-2)

	cpu.instMem.loadMemory(0x00000054, 0x2204FFFD);//addi $a0, $s0, -3 	 	# compute fun(n-3)
	cpu.instMem.loadMemory(0x00000058, 0x0C000002);//jal fun
	cpu.instMem.loadMemory(0x0000005c, 0x20530000);//move $s3, $v0 		 	# t3 = fun(n-3)

	cpu.instMem.loadMemory(0x00000060, 0x02731020);//add $v0, $s3, $s3
	cpu.instMem.loadMemory(0x00000064, 0x00531020);//add $v0, $v0, $s3
	cpu.instMem.loadMemory(0x00000068, 0x00521020);//add $v0, $v0, $s2
	cpu.instMem.loadMemory(0x0000006c, 0x00521020);//add $v0, $v0, $s2
	cpu.instMem.loadMemory(0x00000070, 0x00501020);//add $v0, $v0, $s1		# v0 = f(n-1) + 2*f(n-2) + 3*f(n-3)
	cpu.instMem.loadMemory(0x00000074, 0x08000026);//j fun_ret

	//fun_base:
	cpu.instMem.loadMemory(0x00000078, 0x20880001);//addi $t0, 0, 1
	cpu.instMem.loadMemory(0x0000007c, 0x20890002);//addi $t1, 0, 2
	cpu.instMem.loadMemory(0x00000080, 0x10880003);//beq $a0, $t0, Else1
	cpu.instMem.loadMemory(0x00000084, 0x10890004);//beq $a0, $t1, Else2
	cpu.instMem.loadMemory(0x00000088, 0x20400000);//li $v0, 0
	cpu.instMem.loadMemory(0x0000008c, 0x0800004C);//j fun_ret
	//Else1:
	cpu.instMem.loadMemory(0x00000090, 0x20400001);//li $v0, 1
	cpu.instMem.loadMemory(0x00000094, 0x0800004C);//j fun_ret
	//Else2:
	cpu.instMem.loadMemory(0x00000098, 0x20400002);//li $v0, 2

	//fun_ret:
	cpu.instMem.loadMemory(0x0000009c, 0x8FBF001C);//lw $ra, 28($sp)		# restore the return address
	cpu.instMem.loadMemory(0x000000a0, 0x8FBE0018);//lw $fp, 24($sp)		# restore $fp to caller¡¯s frame pointer
	cpu.instMem.loadMemory(0x000000a4, 0x8FB00014);//lw $s0, 20($sp) 		# restore $s0
	cpu.instMem.loadMemory(0x000000a8, 0x8FB10010);//lw $s1, 16($sp) 		# restore $s1
	cpu.instMem.loadMemory(0x000000ac, 0x8FB10010);//lw $s2, 12($sp) 		# restore $s2
	cpu.instMem.loadMemory(0x000000b0, 0x8FB10010);//lw $s3, 8($sp) 		# restore $s2
	cpu.instMem.loadMemory(0x000000b4, 0x23BD0020);//addi $sp, $sp, 32   	# restore the stack pointer
	cpu.instMem.loadMemory(0x000000b8, 0x03E00008);//jr $ra

    cpu.instMem.loadMemory(0x000000bc, 0xFFFFFFFF);//output

    EXPECT_EQ(func(6), cpu.run());
}*/