#pragma once

#include "Block.h"

class Peg : public Block{
public:
    explicit Peg(InterfaceGame *game, float x, float y, char PegType);
};