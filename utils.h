#include "boolean.h"

boolean is_numeric(char);

boolean is_numeric(char ch)
{
  return (ch >= '0' && ch <= '9');
}
