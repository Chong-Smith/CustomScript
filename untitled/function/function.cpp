#include "function.h"

function function::instance;
function& function::GetInstance()
{
    return instance;
}

function::function()
{ }




function& FuncUnit = function::GetInstance();
