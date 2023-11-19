#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include "card.h"



EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("please enter card holder name : ");
	gets(&(cardData->cardHolderName));

	uint8_t* ptrToChar = &(cardData->cardHolderName);

	for (int i = 0; i < 25; i++)
	{
		if (ptrToChar[i] == '\0')
		{
			if (i < 20)
				return WRONG_NAME;

			break;
		}
		if (i == 24)
		{

			return WRONG_NAME;

		}

	}


	return OK;
}




EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{

	printf("please enter the expiration date as the following format 'MM/YY' : ");
	scanf("%s",&(cardData->cardExpirationDate));
	/*ensure that user enter five characters*/

	uint8_t* ptrToChar = &(cardData->cardExpirationDate);
	for (int i = 0; i < 6; i++)
	{
		if (ptrToChar[i] == '\0')
		{
			if (i == 5)
				break;
			else
			{
				return WRONG_EXP_DATE;
			}
		}
		if (i == 10)
			return WRONG_EXP_DATE;
	}
	/*ensure that user enter right format*/

	if (ptrToChar[2] != '/')
		return WRONG_EXP_DATE;
	/*now we ensure that user enter 2 charachters / 2 charachters*/

	/*we will ensure that user enter numerical characters*/
	for (int i = 0; i < 5; i++)
	{

		if (ptrToChar[i] < 48 || ptrToChar[i] > 57)
		{
			if (i == 2)
				continue;
			return WRONG_EXP_DATE;
		}
	}

	/*finally 100% the user enters right format*/

	/*to convert characters into numbers*/
	uint8_t month = (ptrToChar[0] - 48) * 10 + ptrToChar[1] - 48;
	uint8_t year = (ptrToChar[3] - 48) * 10 + ptrToChar[4] - 48;
	/*if month variable exceeds 12 it's a logical error*/

	if (month > 12)
		return WRONG_EXP_DATE;


	return OK;


}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("please enter PAN : ");
	scanf("%s", & (cardData->primaryAccountNumber));

	uint8_t* ptrToChar = &(cardData->primaryAccountNumber);

	for (int i = 0; i < 20; i++)
	{
		
		if (ptrToChar[i] > 57 || (ptrToChar[i] < 48 && ptrToChar[i] !='\0'))
			return WRONG_PAN;
		
		if (ptrToChar[i] == '\0')
		{
			if (i < 16)
				return WRONG_PAN;

			break;
		}
		if (i == 19)
		{

			return WRONG_PAN;

		}

	}
	return OK;
}