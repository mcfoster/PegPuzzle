//
// Created by chris on 4/18/18.
//
#include <stdlib.h>
#include <memory.h>
#include "CJumpChoices.h"

/***************************************************************************
 * Create a duplicate
 * @param choices
 */
CJumpChoices::CJumpChoices(CJumpChoices *choices)
{
    header = NULL;
    RecCount = 0;
    for(int i=0;i<choices->RecCount; i++)
    {
        add(choices->get(i));
    }
} // CJumpChoices

/****************************************************************************
 * Add a record to the list
 * @param rec record to be added
 */
void CJumpChoices::add(JumpChoice rec)
{
    JumpChoice *prec = new JumpChoice();
    prec->from = rec.from;
    prec->to = rec.to;
    prec->jumped = rec.jumped;
    Node *ptr = header;
    if(ptr == NULL)
    {
        header = new Node();
        header->prec = prec;
        header->next = NULL;
        RecCount++;
    }
    else
    {
        while(ptr->next != NULL)
            ptr = ptr->next;
        if(ptr->next == NULL) // Found
        {
            ptr->next = new Node();
            ptr->next->prec = prec;
            ptr->next->next = NULL;
            RecCount++;
        }
    }
} // CJumpChoices::add

/****************************************************************************
 * Get the index for the
 * @param idx
 * @return
 */
JumpChoice CJumpChoices::get(int idx)
{
    JumpChoice rec;
    Node *ptr = header;

    rec.from = rec.to = rec.jumped = 0;
    // Bail on invalid request
    if((header!= NULL) && (idx <= RecCount))
    {
        int i=0;
        while ((i < idx) && (ptr->next != NULL))
        {
            ptr = ptr->next;
            i++;
        }
        if(i== idx) // Found
        {
            rec.from = ptr->prec->from;
            rec.to = ptr->prec->to;
            rec.jumped = ptr->prec->jumped;
        }
    }
    return rec;
} // CJumpChoices::get


/****************************************************************************
 * Delete the record at the selected index
 * @param idx
 */
void CJumpChoices::remove(int idx)
{
    Node *ptr = header;
    Node *prevPtr = NULL;
    // Bail on invalid request
    if((header!= NULL) && (idx <= RecCount))
    {
        int i=0;
        while ((i < idx) && (ptr->next != NULL))
        {
            prevPtr = ptr;
            ptr = ptr->next;
            i++;
        }
        if(i== idx) // Found
        {
            if(idx==0) {
                prevPtr = header;
                header = ptr->next;
                delete prevPtr->prec;
                delete prevPtr;
            }
            else {
                prevPtr->next = ptr->next;
                delete ptr->prec;
                delete ptr;
            }
            RecCount--;
        }
    }
} // CJumpChoices::remove

/****************************************************************************
 * Delete all records in the list
 */
void CJumpChoices::clear()
{
    Node *p = header;
    Node *next = NULL;

    while (p != NULL)
    {
        next = p->next;
        delete p->prec;
        delete p;

        p = next;
    }
    RecCount = 0;
    header = NULL;
} // CJumpChoices::clear
