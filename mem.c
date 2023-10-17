#include "main.h"

/**
 * memCpy - a function to copy data from one void pointer to another
 * @ptrNew: pointer to the adress where the data is copied
 * @pntr: the data to be copied
 * @sizeNew: variable for new pointer size
 * Return: nothing
 */

void memCpy(void *ptrNew, const void *pntr, unsigned int sizeNew)
{
char *charPtr = (char *)pntr;
char *charPtrNew = (char *)ptrNew;
unsigned int cnt;
for (cnt = 0; cnt < sizeNew; cnt++)
charPtrNew[cnt] = charPtr[cnt];
}


/**
 * reAlloc - function that reallocates memory
 * @pntr: pointer to previous memory
 * @sizeOld: size of previous memory
 * @sizeNew: size of pointer to new memory
 * Return: new size on success or 0 wehn malloc fails
 */

void *reAlloc(void *pntr, unsigned int sizeOld, unsigned int sizeNew)
{
void *ptrNew;
if (pntr == NULL)
return (malloc(sizeNew));
if (sizeNew == 0)
{
free(pntr);
return (NULL);
}
if (sizeNew == sizeOld)
return (pntr);
ptrNew = malloc(sizeNew);
if (ptrNew == NULL)
return (NULL);
if (sizeNew < sizeOld)
memCpy(ptrNew, pntr, sizeNew);
else
memCpy(ptrNew, pntr, sizeOld);
free(pntr);
return (ptrNew);
}


/**
 * reAllocDp - function for memory allocation for the case of a double pointer
 * @pntr: pointer to previous memory block
 * @sizeOld: size of pointer to previous memory
 * @sizeNew: current size of pointer to memory
 * Return: new size on success else NULL if malloc fails
 */

char **reAllocDp(char **pntr, unsigned int sizeOld, unsigned int sizeNew)
{
char **ptrNew;
unsigned int cnt;
if (pntr == NULL)
return (malloc(sizeof(char *) * sizeNew));
if (sizeNew == sizeOld)
return (pntr);
ptrNew = malloc(sizeof(char *) * sizeNew);
if (ptrNew == NULL)
return (NULL);
for (cnt = 0; cnt < sizeOld; cnt++)
ptrNew[cnt] = pntr[cnt];
free(pntr);
return (ptrNew);
}
