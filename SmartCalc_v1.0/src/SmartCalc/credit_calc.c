//annuity, differentiated,
//total_amount, percent, period, period_value, calculation, credit_result
//#include "pol/pol.h"
//double annuity(double percent, double total_amount, double period) {
//  percent = percent / 100.0 / 12.0;
//  return total_amount * (percent * pow((1 + percent), period) / (pow(1 + percent, period) - 1));
//}

//double annuity_total_amount(double period_value, double period) { return period_value * period; }

//void differentiated(double proc, double sum, double month, double *max_mp,
//            double *min_mp, double *calc_sum, double *calc_proc) {
//  proc = proc / 100 / 12;
//  double sum_t = sum;
//  double pre_mp = sum / month;
//  *max_mp = pre_mp + (sum_t * proc);
//  *calc_proc = 0;
//  while (sum_t > 0) {
//    *calc_proc += (sum_t * proc);
//    sum_t -= pre_mp;
//    if (sum_t == pre_mp || sum_t < pre_mp) *min_mp = pre_mp + (sum_t * proc);
//  }
//  *calc_sum = *calc_proc + sum;
//}
