int modulo(int k, int i)
{
  while (k > 0){
    k = k - i;
  }
  return k;
}

bool isLeapYear(int n)
{
  if ((modulo(n,4) == 0 && modulo(n,100) != 0) || (modulo(n,400) == 0)){
    return true;
  }
  return false;
}

void main()
{
  print("Please enter a year: ");
  print_nl();

  int n;
  n = read_int();

  print_int(n);
  if (isLeapYear(n)){
    print(" is a leap year.");
  }
  else
  {
    print(" is not a leap year.");
  }
  print_nl();
}
