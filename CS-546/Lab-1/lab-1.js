// Value to return on error or invalid parameters
const ERROR_VAL = -1;

/**
 * retirementAmountIfSavingPerMonth()
 *
 * Calculate the amount of money that will be saved based on saving on a monthly basis
 *
 * @param number yearsUntilRetirement The number of years until retirement
 * @param number amountSavingPerMonth The amount of money being saved per month
 * @param number yearlyInterestRateOfInvestment The yearly interest rate of the investment
 */
function retirementAmountIfSavingPerMonth (yearsUntilRetirement, amountSavingPerMonth, yearlyInterestRateOfInvestment) {
    var total = 0;

    // Make sure everything is a number and >= 0
    if (typeof yearsUntilRetirement != "number" || typeof amountSavingPerMonth != "number" || typeof yearsUntilRetirement != "number" ||
        yearsUntilRetirement < 0 || amountSavingPerMonth < 0 || yearlyInterestRateOfInvestment < 0) {
        total = ERROR_VAL;
    }

    // Calculate running total
    for (var i = 0; i < yearsUntilRetirement && total != ERROR_VAL; i++) {
        total = (total + amountSavingPerMonth) * (1 + (yearlyInterestRateOfInvestment / 12));
    }

    // We only care about two decimal places
    return (total == ERROR_VAL) ? ERROR_VAL : total.toFixed(2);
}

/**
 * investedAmountAfterSomeYears()
 *
 * Calculate the end amount of money after investing for a certain number of years at a fixed interest rate
 *
 * @param number yearsInvesting The number of years to invest for
 * @param number initialAmount The starting amount of money
 * @param number yearlyInterestRateOfInvestment The amount of interest earned per year
 */
function investedAmountAfterSomeYears (yearsInvesting, initialAmount, yearlyInterestRateOfInvestment) {
    var total = initialAmount;

    // Make sure everyting is a number and >= 0
    if (typeof yearsInvesting != "number" || typeof initialAmount != "number" || typeof yearlyInterestRateOfInvestment != "number" ||
        yearsInvesting < 0 || initialAmount < 0 || yearlyInterestRateOfInvestment < 0) {
        total = ERROR_VAL;
    }

    // Calculate running total
    for (var i = 0; i < yearsInvesting && total != ERROR_VAL; i++) {
        total = total * (1 + yearlyInterestRateOfInvestment);
    }

    // We only care about two decimal places
    return (total == ERROR_VAL) ? ERROR_VAL : total.toFixed(2);
}

/**
 * monthsToPayOffLoan()
 *
 * Calculate how many months are required to pay off a loan
 *
 * @param number monthlyPaymentAmount The amount being paid off per month
 * @param number initialLoanAmount The amount of the initial loan
 * @param number yearlyInterestRateOfLoan The yearly interest rate of the loan
 */
function monthsToPayOffLoan (monthlyPaymentAmount, initialLoanAmount, yearlyInterestRateOfLoan) {
    var months = 0;

    // Make sure everything is a number and >= 0
    if (typeof monthlyPaymentAmount != "number" || typeof initialLoanAmount != "number" || typeof yearlyInterestRateOfLoan != "number" ||
        monthlyPaymentAmount < 0 || initialLoanAmount < 0 || yearlyInterestRateOfLoan < 0) {
        months = ERROR_VAL;
    }

    // Calculate months
    while (months != ERROR_VAL && initialLoanAmount > 0) {
        initialLoanAmount = (initialLoanAmount * (1 + (yearlyInterestRateOfLoan / 12))) - monthlyPaymentAmount;
        months++;
    }

    // Subtract one to account for the last iteration of the loop
    return (monthls == ERROR_VAL) ? months : --months;
}