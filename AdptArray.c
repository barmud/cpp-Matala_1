#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"
typedef struct AdptArray_
{
    int ArrSize;
    PElement *pElement;
    DEL_FUNC delfunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc)
{
    PAdptArray pArr = NULL;
    pArr = (PAdptArray)malloc(sizeof(AdptArray));

    if (pArr == NULL)
        return NULL;
    pArr->ArrSize = 1;
    pArr->pElement = (PElement *)calloc(sizeof(PElement), 1);
    if (pArr->pElement == NULL)
    {
        return NULL;
    }
    *(pArr->pElement) = NULL;
    pArr->delfunc = delFunc;
    pArr->copyFunc = copyFunc;
    pArr->printFunc = printFunc;
    return pArr;
}

void DeleteAdptArray(PAdptArray pArr)
{
    if (pArr == NULL)
    {
        return;
    }
    PElement currElem = *(pArr->pElement);
    while (currElem != NULL)
    {
        pArr->delfunc(currElem);
        currElem++;
    }
    free(pArr->pElement);
    free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pElem)
{
    if (pArr == NULL)
    {
        return FAIL;
    }
    if (index > pArr->ArrSize - 1)
    {  
        PElement* newArray = (PElement*)calloc(sizeof(PElement),index+1);
        if (newArray == NULL)
        {
            free(pArr->pElement);
            return FAIL;
        }
        memcpy(newArray, pArr->pElement, (pArr->ArrSize) *sizeof(PElement));
        free(pArr->pElement);
        pArr->pElement = newArray;
        pArr->ArrSize = index + 1;
    }
    
    PElement changeElem = (pArr->pElement)[index];
    if (changeElem == NULL)
    {
        (pArr->pElement)[index] = pArr->copyFunc(pElem);
    }
    else
    {
        pArr->delfunc(changeElem);
        (pArr->pElement)[index] = pArr->copyFunc(pElem);
    }
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int index)
{
    if (pArr == NULL)
    {
        return NULL;
    }
    PElement currElem = pArr->pElement[index];
    if (currElem == NULL)
    {
        return NULL;
    }
    return pArr->copyFunc(currElem);
}

int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr->pElement == NULL)
    {
        return -1;
    }
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL || pArr->pElement == NULL)
    {
        return;
    }
    for (size_t i = 0; i < pArr->ArrSize; i++)
    {
        PElement curr = pArr->pElement[i];
        if (curr!=NULL)
        {
           pArr->printFunc(curr);
        }
    }
}