#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("please enter current date as the following format DD/MM/YYYY: ");
	scanf("%s", &(termData->transactionDate));

	/*ensure that user enter 10 characters*/

	uint8_t* ptrToChar = &(termData->transactionDate);
	for (int i = 0; i < 11; i++)
	{
		if (ptrToChar[i] == '\0')
		{
			if (i == 10)
				break;
			else
			{
				return WRONG_DATE;
			}
		}
		if(i==10)
			return WRONG_DATE;
	}

	/*ensure that user enter right format*/

	if (ptrToChar[2] != '/' || ptrToChar[5] != '/')
		return WRONG_DATE;

	/*now we ensure that user enter 2 charachters / 2 charachters/ 4 characters*/

	/*we will ensure that user enter numerical characters*/
	for (int i = 0; i < 10; i++)
	{

		if (ptrToChar[i] < 48  || ptrToChar[i] > 57)
		{
			if (i == 2 || i==5)
				continue;
			return WRONG_DATE;
		}
	}

	/*finally 100% the user enters right format*/

	/*to convert characters into numbers*/
	uint8_t day = (ptrToChar[0] - 48) * 10 + ptrToChar[1] - 48;
	uint8_t  month = (ptrToChar[3] - 48) * 10 + ptrToChar[4] - 48;
	unsigned int year = (ptrToChar[6] - 48) * 1000 + (ptrToChar[7] - 48)*100+ (ptrToChar[8] - 48) * 10 + ptrToChar[9] - 48;
	/*if month variable exceeds 12 it's a logical error*/

	if (month > 12 || day>31 )
		return WRONG_DATE;

	

	return OK_terminal;

}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) 
{
	
	
	if (((cardData.cardExpirationDate[3] -48)*10 + cardData.cardExpirationDate[4] - 48 + 2000) < (((termData.transactionDate[6] - 48) * 1000) + (termData.transactionDate[7] - 48) * 100 + (termData.transactionDate[8] - 48) * 10 + termData.transactionDate[9] - 48))
		return EXPIRED_CARD;
	if (((cardData.cardExpirationDate[3] - 48) * 10 + cardData.cardExpirationDate[4] - 48 + 2000) > (((termData.transactionDate[6] - 48) * 1000) + (termData.transactionDate[7] - 48) * 100 + (termData.transactionDate[8] - 48) * 10 + termData.transactionDate[9] - 48))
		return OK_terminal;

	if (((cardData.cardExpirationDate[0] -48) *10 + cardData.cardExpirationDate[1] - 48) < ((termData.transactionDate[3] -48) *10 + termData.transactionDate[4] - 48))
		return EXPIRED_CARD;

	
	return OK_terminal;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("please enter the transaction amount : ");
	scanf("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;
	return OK_terminal;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("please enter max amount :");
	scanf("%f", &(termData->maxTransAmount));
	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;

	return OK_terminal;

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) 
{
	if (termData->maxTransAmount < termData->transAmount)
		return EXCEED_MAX_AMOUNT;
	return OK_terminal;

}


