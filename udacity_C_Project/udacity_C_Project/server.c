#include "server.h"

extern ST_accountsDB_t arrOfSt_DB[255];
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	

	for(int i=0;i<255;i++)
	{

		for (int j=0,c=0;j<20;j++) 
		{
			if (cardData->primaryAccountNumber[j] == arrOfSt_DB[i].primaryAccountNumber[j]) 
				c++;

			else
			{
				break;
			}
			if (c == 20)
				return OK_server;
		}

	}
	
	return ACCOUNT_NOT_FOUND;
	


}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_cardData_t* cardData)
{
	int i = 0; int c = 0;
	for (i = 0; i < 255; i++)
	{

		for (int j = 0; j < 20; j++)
		{
			if (cardData->primaryAccountNumber[j] == arrOfSt_DB[i].primaryAccountNumber[j])
				c++;

			else
			{
				break;
			}
			if (c == 20)
				break;
		}
		if (c != 20)
			c = 0;
		else
		{
			break;
		}

	}

	if (termData->transAmount <= arrOfSt_DB[i].balance)
		return OK_server;
	return LOW_BALANCE;
}


EN_serverError_t saveTransaction(ST_transaction_t* transData, ST_cardData_t cardData, ST_terminalData_t termData) 
{
	transData->cardHolderData = cardData;
	transData->terminalData = termData;
	transData->transactionSequenceNumber++;
	
}


EN_transState_t recieveTransactionData(ST_transaction_t* transData, ST_cardData_t cardData, ST_terminalData_t termData)

{	

	EN_transState_t state = APPROVED;

	if (isValidAccount(&cardData))
		state= DECLINED_STOLEN_CARD;

	if (isAmountAvailable(&termData, &cardData))
		state= DECLINED_INSUFFECIENT_FUND;

	saveTransaction(transData, cardData, termData);
	
	if (state == APPROVED)
	{
		int indx=search(&cardData);
		arrOfSt_DB[indx].balance -= termData.transAmount;

	}

		transData->transState = state;

	return state;

	

}

int search(ST_cardData_t *cardData)
{
	int i = 0; int c = 0;
	for (i = 0; i < 255; i++)
	{

		for (int j = 0; j < 19; j++)
		{
			if (cardData->primaryAccountNumber[j] == arrOfSt_DB[i].primaryAccountNumber[j])
				c++;

			else
			{
				break;
			}
			if (c == 19)
				break;
		}
		if (c != 19)
			c = 0;
		else
		{
			break;
		}

	}
	return i;
}