#pragma once
#ifndef _ExcelTable_H
#define _ExcelTable_H

#include "Table.h"

template <typename T>
class ExcelTable
{
public:
    vector<Block *> tables;
};

#endif