#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

/*
int get_months( int total) {
  return ( total % 12);
}

int get_years( int total) {
  return ((total - get_months(total) )/12);
}


void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance;
  double interest;
  int i;
  int total_age = startAge + working.months + retired.months;
  int work_age = total_age - retired.months;
  balance = initial;


  for(i = startAge; i <= total_age; i++) {
    printf("Age %3d month %2d you have %.2lf\n", get_years(i), get_months(i), balance);
    if( i <= work_age){
      interest = balance*working.rate_of_return;
      balance += interest;
      balance += working.contribution;
    }  else {
      interest = balance*retired.rate_of_return;
      balance += interest;
      balance += retired.contribution;
    }
  }
}

int main(){

  retire_info works;
  retire_info retirements;
  int s_a;
  double init;

  
  printf("\nWorking: ");
  printf("\n--------");
  printf("\nMonths: ");
  scanf("%d", &works.months);

  printf("\nPer Month savings: ");
  scanf("%lf", &works.contribution);

  printf("\nRate of return: ");
  scanf("%lf", &works.rate_of_return);

  printf("\nRetired: ");
  printf("\n--------");
  printf("\nMonths: ");
  scanf("%d", &retirements.months);

  printf("\nPer Month savings: ");
  scanf("%lf", &retirements.contribution);

  printf("\nRate of return:");
  scanf("%lf", &retirements.rate_of_return);

  printf("\nStarting conditions: ");
  printf("\n--------");
  printf("\nAges: ");
  scanf("%d", &s_a);
  printf("\nSavings:");
  scanf("%lf",&init);

  retirement(s_a, init, works, retirements);
  return 0;

}*/


void print_monthly_info(int months, double balance) {
  printf("Age %3d month %2d you have $%.2lf\n", months / 12, months % 12, balance);

  return;
}

double balance_calc(double balance, retire_info retire_stats) {
  balance += balance * retire_stats.rate_of_return;
  balance += retire_stats.contribution;

  return balance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  // Set balance at initial to start
  double balance = initial;
  int total_months = startAge - 1;

  for (int i = 0; i < working.months; i++) {
    total_months += 1;
    print_monthly_info(total_months, balance);
    balance = balance_calc(balance, working);
  }

  for (int j = 0; j < retired.months; j++) {
    total_months += 1;
    print_monthly_info(total_months, balance);
    balance = balance_calc(balance, retired);
  }

  return;
}






int main() {
    retire_info works;
    works.months = 489;
    works.contribution = 1000;
    works.rate_of_return = 0.045 / 12.0;

    retire_info retirements;
    retirements.months = 384;
    retirements.contribution = -4000;
    retirements.rate_of_return = 0.01 / 12.0;

    retirement(327, 21345, works, retirements);

    return 0;
  }



