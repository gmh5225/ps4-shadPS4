#include "Disassembler.h"
#include <stdio.h>


Disassembler::Disassembler()
{
	ZydisDecoderInit(&m_decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
	ZydisFormatterInit(&m_formatter, ZYDIS_FORMATTER_STYLE_INTEL);
}

Disassembler::~Disassembler()
{
}

void Disassembler::printInstruction(void* code,u64 address)//print a single instruction
{
	ZydisDecodedInstruction instruction;
	ZydisDecodedOperand     operands[ZYDIS_MAX_OPERAND_COUNT_VISIBLE];
	ZyanStatus              status = ZydisDecoderDecodeFull(&m_decoder, code, sizeof(code), &instruction, operands);
	if (!ZYAN_SUCCESS(status))
	{
		printf("decode instruction failed at %p\n", code);
	}
	else
	{
		printInst(instruction, operands,address);
	}
}

void Disassembler::printInst(ZydisDecodedInstruction& inst, ZydisDecodedOperand* operands,u64 address)
{
	const int bufLen = 256;
	char      szBuffer[bufLen];
	ZydisFormatterFormatInstruction(&m_formatter, &inst, operands,inst.operand_count_visible, szBuffer, sizeof(szBuffer), address, ZYAN_NULL);
    printf("instruction: %s\n", szBuffer);
}