#include "ComplexStateMachine.h"
#include <hsm/hsm.h>

#include <iostream>


int main()
{
    flatten_transition_table(ComplexStateMachine{});

    return 0;
}