#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
#include "app.h"



int main() {

	
	
	 appStart();

	
	return 0;
}

void appStart(void)
{

	

	ST_cardData_t cardData;
	ST_terminalData_t termData;

	getCardHolderName(&cardData);
	getCardExpiryDate(&cardData);
	getCardPAN(&cardData);

	getTransactionDate(&termData);
	setMaxAmount(&termData);
	getTransactionAmount(&termData);



	int i = 0;
	for (i = 0; i < 20; i++)
	{
		if (StolenPAN[i] != cardData.primaryAccountNumber[i])
		{
			break;
		}
	}


	if (isCardExpired(cardData, termData)) 
	{
		printf("card is expired");
		
	}

	else if (isBelowMaxAmount(&termData))
	{
		printf("amount exceed maximum of the terminal");
		
	}

	else if(isValidAccount(&cardData))
	{
		printf("invalid account");
		
	}
	else if (isAmountAvailable(&termData, &cardData))
	{
		printf("not enough money in your account");
		
	}

	else if(i==20)
	{
		printf("it is a stolen card");
	}
	else 
	{
			saveTransaction(&arrOfst_tran[0], &cardData, &termData);
			printf("/n the transaction is done successfully");
		
	}



}